/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

/* Modified by Eric Paquette, eric.paquette@etsmtl.ca, 2019-01-08 */

#include "glwidget.h"

#include <QMouseEvent>
#include <QOpenGLShaderProgram>
#include <QCoreApplication>
#include <math.h>
#include <qopengl.h>
#include <iostream>

using namespace std;

#define GAP  25				/* gap between subwindows */
#define BUFFER_OFFSET(i) (static_cast<char *>(nullptr) + (i))

enum VAO_IDs { VAO_Sphere, NumVAOs };
enum Buffer_IDs { VBO_Sphere, EBO_Sphere, NumBuffers };

namespace
{
    GLuint VAOs[NumVAOs];
    GLuint Buffers[NumBuffers];
    int numRowSphere = 20;
    int numColSphere = numRowSphere+2;
    int numVerticesSphere = numColSphere * numRowSphere + 2;
    int numTriSphere = numColSphere*(numRowSphere-1)*2 + 2*numColSphere;
}

const GLuint NumVertices = 3;

GLWidget::GLWidget(QWidget *parent)
    : QOpenGLWidget(parent),
      m_program(nullptr)
{
}

GLWidget::~GLWidget()
{
    cleanup();
}

void GLWidget::cleanup()
{
    makeCurrent();
    delete m_program;
    m_program = nullptr;
    doneCurrent();
}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBindVertexArray(VAOs[VAO_Sphere]);
    m_program->bind();

    // Paint sphere
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    m_program->setUniformValue(m_uniformAmbientLightingLoc, getAmbientLightingR(), getAmbientLightingG(), getAmbientLightingB());
    m_program->setUniformValue(m_uniformDiffuseLightingLoc, getDiffuseLightingR(), getDiffuseLightingG(), getDiffuseLightingB());
    m_program->setUniformValue(m_uniformSpecularLightingLoc, getSpecularLightingR(), getSpecularLightingG(), getSpecularLightingB());
    m_program->setUniformValue(m_uniformSpecularExponentLoc, getSpecularLightingN());
    glDrawElements(GL_TRIANGLES, numTriSphere*3, GL_UNSIGNED_INT, 0);

    glFlush();
}

void GLWidget::resizeGL(int, int)
{
}

void GLWidget::initializeGL()
{
    connect(context(), &QOpenGLContext::aboutToBeDestroyed, this, &GLWidget::cleanup);

    initializeOpenGLFunctions();

    // Init shaders
    initRenderShaders();

    // Create our VertexArrays Objects and VertexBuffer Objects
    glGenVertexArrays(NumVAOs, VAOs);
    glGenBuffers(NumBuffers, Buffers);

    // Init sphere
    initGeometrySphere();

    glUseProgram(m_program->programId());

    glEnable(GL_DEPTH_TEST);

    // Init GL properties
    glPointSize(10.0f);
}

void GLWidget::initRenderShaders()
{
    m_program = new QOpenGLShaderProgram;

    // Load vertex and fragment shaders
    if (!m_program->addShaderFromSourceFile(QOpenGLShader::Vertex, "basicShader.vert")) {
        cerr << "Unable to load shader" << endl
             << "Log file:" << endl;
        qDebug() << m_program->log();
    }
    if (!m_program->addShaderFromSourceFile(QOpenGLShader::Fragment, "basicShader.frag")) {
        cerr << "Unable to load shader" << endl
             << "Log file:" << endl;
        qDebug() << m_program->log();
    }

    m_program->link();
    m_program->bind();

    // Specify shader input paramters
    // The strings "vPosition", "vNormal", etc. have to match an attribute name in the vertex shader.
    QString shaderParameter;
    shaderParameter = "vPosition";
    if ((m_vPositionLocation = m_program->attributeLocation(shaderParameter)) < 0)
       qDebug() << "Unable to find shader location for " << shaderParameter;

    shaderParameter = "vNormal";
    if ((m_vNormalLocation = m_program->attributeLocation(shaderParameter)) < 0)
       qDebug() << "Unable to find shader location for " << shaderParameter;

    shaderParameter = "uAmbientLighting";
    if ((m_uniformAmbientLightingLoc = m_program->uniformLocation(shaderParameter)) < 0)
        qDebug() << "Unable to find shader location for " << shaderParameter;

    shaderParameter = "uDiffuseLighting";
    if ((m_uniformDiffuseLightingLoc = m_program->uniformLocation(shaderParameter)) < 0)
        qDebug() << "Unable to find shader location for " << shaderParameter;

    shaderParameter = "uSpecularLighting";
    if ((m_uniformSpecularLightingLoc = m_program->uniformLocation(shaderParameter)) < 0)
        qDebug() << "Unable to find shader location for " << shaderParameter;

    shaderParameter = "uSpecularExponent";
    if ((m_uniformSpecularExponentLoc = m_program->uniformLocation(shaderParameter)) < 0)
        qDebug() << "Unable to find shader location for " << shaderParameter;
}

void GLWidget::initGeometrySphere()
{
  // Note: To ease the sphere creation, we use an index (aka elements) buffer. This allows us to create
  //			 each vertex once. Afterward, faces are created by specifying the index of the three vertices
  //			 inside the index buffer. For example, a 2D quad could be drawn using the following vertex and
  //       index buffers:
  //
  //			 vertices[4][2] = {{-1,-1},{1,-1},{1,1},{-1,1}};
  //       indices[2*3] = {0, 1, 3, 1, 2, 3};
  //
  //       In this example, the vertices buffer contains 4 vertices, and the indices buffer contains two
  //       triangles formed by the vertices (vertices[0], vertices[1], vertices[3]) and (vertices[1],
  //       vertices[2], vertices[3]) respectively.
  //
  //       Also note that indices are stored in a different type of buffer called Element Array Buffer.

  makeCurrent();

  // Create sphere vertices and faces
  GLfloat vertices[numVerticesSphere][3];
  GLfloat normals[numVerticesSphere][3];
  GLuint indices[numTriSphere*3][3];

  // Generate surrounding vertices
  unsigned int v = 0;
  float thetaInc = 2.0f*3.14159265f / static_cast<float>(numColSphere);
  float phiInc = 3.14159265f / static_cast<float>(numRowSphere+1);
  float ray = 0.9f ;
  for (int row=0; row<numRowSphere; ++row)
  {
    float phi = 3.14159265f - (static_cast<float>(row+1) * phiInc);
    for (int col=0; col<numColSphere; ++col, ++v)
    {
      float theta = col*thetaInc;
      vertices[v][0] = ray*sin(theta)*sin(phi); // x
      vertices[v][1] = ray*cos(phi);            // z
      vertices[v][2] = ray*cos(theta)*sin(phi); // y

      normals[v][0] = vertices[v][0]/ray;
      normals[v][1] = vertices[v][1]/ray;
      normals[v][2] = vertices[v][2]/ray;
    }
  }

  // Generate cap vertices
  vertices[numColSphere*numRowSphere+0][0] = 0.0f;
  vertices[numColSphere*numRowSphere+0][1] = -ray;
  vertices[numColSphere*numRowSphere+0][2] = 0.0f;

  vertices[numColSphere*numRowSphere+1][0] = 0.0f;
  vertices[numColSphere*numRowSphere+1][1] = ray;
  vertices[numColSphere*numRowSphere+1][2] = 0.0f;

  normals[numColSphere*numRowSphere+0][0] = 0.0f;
  normals[numColSphere*numRowSphere+0][1] = -1.0f;
  normals[numColSphere*numRowSphere+0][2] = 0.0f;

  normals[numColSphere*numRowSphere+1][0] = 0.0f;
  normals[numColSphere*numRowSphere+1][1] = 1.0f;
  normals[numColSphere*numRowSphere+1][2] = 0.0f;

  // Generate surrounding indices (faces)
  unsigned int tri = 0;
  for (unsigned int row=0; row<numRowSphere-1; ++row)
  {
    unsigned int rowStart = row*numColSphere;
    unsigned int topRowStart = rowStart + numColSphere;

    for (unsigned int col=0; col<numColSphere; ++col, tri += 2)
    {
      // Compute quad vertices
      unsigned int v = rowStart + col;
      unsigned int vi = (col<numColSphere-1) ? v+1 : rowStart;
      unsigned int vj = topRowStart + col;
      unsigned int vji = (col<numColSphere-1) ? vj+1 : topRowStart;

      // Add to indices
      indices[tri+0][0] = v;
      indices[tri+0][1] = vi;
      indices[tri+0][2] = vj;
      indices[tri+1][0] = vi;
      indices[tri+1][1] = vji;
      indices[tri+1][2] = vj;
    }
  }

  // Generate cap indices (faces)
  for (unsigned int col=0; col<numColSphere; ++col, tri += 2)
  {
    indices[tri+0][0] = numColSphere*numRowSphere;
    indices[tri+0][1] = (col<numColSphere-1) ? col+1 : 0;
    indices[tri+0][2] = col;

    unsigned int rowStart = (numRowSphere-1)*numColSphere;
    indices[tri+1][0] = numColSphere*numRowSphere+1;
    indices[tri+1][1] = rowStart + col;
    indices[tri+1][2] = (col<numColSphere-1) ? (rowStart + col + 1) : rowStart;
  }

  // Fill vertex VBO
  GLsizeiptr offsetVertices = 0;
  GLsizeiptr offsetNormals = sizeof(vertices);
  GLsizeiptr dataSize = offsetNormals + sizeof(normals);

  glBindBuffer(GL_ARRAY_BUFFER, Buffers[VBO_Sphere]);
  glBufferData(GL_ARRAY_BUFFER, dataSize, NULL, GL_STATIC_DRAW);
  glBufferSubData(GL_ARRAY_BUFFER, offsetVertices, sizeof(vertices), vertices);
  glBufferSubData(GL_ARRAY_BUFFER, offsetNormals, sizeof(normals), normals);

  // Set VAO
  glBindVertexArray(VAOs[VAO_Sphere]);

  glVertexAttribPointer(m_vPositionLocation, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(offsetVertices));
  glEnableVertexAttribArray(m_vPositionLocation);

  glVertexAttribPointer(m_vNormalLocation, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(offsetNormals));
  glEnableVertexAttribArray(m_vNormalLocation);

  // Fill in indices EBO
  // Note: The current VAO will remember the call to glBindBuffer for a GL_ELEMENT_ARRAY_BUFFER.
  //			 However, we will need to call glDrawElements() instead of glDrawArrays().
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Buffers[EBO_Sphere]);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  glClearColor(0.5f, 0.5f, 0.5f, 1.0);// add background
}

void GLWidget::setSphereLatitude(double l){
    numRowSphere = l;
    numVerticesSphere = numColSphere * numRowSphere + 2;
    numTriSphere = numColSphere*(numRowSphere-1)*2 + 2*numColSphere;
    initGeometrySphere();
    update();
}

void GLWidget::setSphereLongitude(double l){
    numColSphere = l;
    numVerticesSphere = numColSphere * numRowSphere + 2;
    numTriSphere = numColSphere*(numRowSphere-1)*2 + 2*numColSphere;
    initGeometrySphere();
    update();
}
