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

enum VAO_IDs { Triangles, NumVAOs };
enum Buffer_IDs { ArrayBuffer, NumBuffers };

namespace
{
    GLuint VAOs[NumVAOs];
    GLuint Buffers[NumBuffers];
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

void GLWidget::initializeGL()
{
    connect(context(), &QOpenGLContext::aboutToBeDestroyed, this, &GLWidget::cleanup);

    initializeOpenGLFunctions();

    GLfloat vertices[NumVertices][2] = {
        { -0.90f, -0.90f }, // Triangle 1
        { 0.85f, -0.90f },
        { -0.90f, 0.85f }
    };
    glGenVertexArrays(NumVAOs, VAOs);
    glBindVertexArray(VAOs[Triangles]);
    glGenBuffers(NumBuffers, Buffers);
    glBindBuffer(GL_ARRAY_BUFFER, Buffers[ArrayBuffer]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices),
                 vertices, GL_STATIC_DRAW);

    m_program = new QOpenGLShaderProgram;
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

    // The strings "vPosition", "mvMatrix", etc. have to match an attribute name in the vertex shader.
    QString shaderParameter;
    shaderParameter = "vPosition";
    if ((m_vPositionLocation = m_program->attributeLocation(shaderParameter)) < 0)
        qDebug() << "Unable to find shader location for " << shaderParameter;

    glUseProgram(m_program->programId());
    glVertexAttribPointer(GLuint(m_vPositionLocation), 2, GL_FLOAT,
                          GL_FALSE, 0, BUFFER_OFFSET(0));
    glEnableVertexAttribArray(GLuint(m_vPositionLocation));

    glEnable(GL_DEPTH_TEST);
}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBindVertexArray(VAOs[Triangles]);
    m_program->bind();

    glDrawArrays(GL_TRIANGLES, 0, 3);

    glFlush();
}

void GLWidget::resizeGL(int, int)
{
}
