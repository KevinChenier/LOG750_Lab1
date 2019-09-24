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

#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QOpenGLWidget>

#include <QOpenGLFunctions_4_0_Core>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QMatrix4x4>

QT_FORWARD_DECLARE_CLASS(QOpenGLShaderProgram)

class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions_4_0_Core
{
    Q_OBJECT

public:
    GLWidget(QWidget *parent = nullptr);
    ~GLWidget() override;

    void cleanup();

    // Getters
    GLfloat getAmbientLightingR() const { return ambientR > 1.0f ? 1.0f : ambientR < 0.0f ? 0.0f : ambientR; }
    GLfloat getAmbientLightingG() const { return ambientG > 1.0f ? 1.0f : ambientG < 0.0f ? 0.0f : ambientG; }
    GLfloat getAmbientLightingB() const { return ambientB > 1.0f ? 1.0f : ambientB < 0.0f ? 0.0f : ambientB; }
    GLfloat getDiffuseLightingR() const { return diffuseR > 1.0f ? 1.0f : diffuseR < 0.0f ? 0.0f : diffuseR; }
    GLfloat getDiffuseLightingG() const { return diffuseG > 1.0f ? 1.0f : diffuseG < 0.0f ? 0.0f : diffuseG; }
    GLfloat getDiffuseLightingB() const { return diffuseB > 1.0f ? 1.0f : diffuseB < 0.0f ? 0.0f : diffuseB; }
    GLfloat getSpecularLightingR() const { return specularR > 1.0f ? 1.0f : specularR < 0.0f ? 0.0f : specularR; }
    GLfloat getSpecularLightingG() const { return specularG > 1.0f ? 1.0f : specularG < 0.0f ? 0.0f : specularG; }
    GLfloat getSpecularLightingB() const { return specularB > 1.0f ? 1.0f : specularB < 0.0f ? 0.0f : specularB; }
    GLfloat getSpecularLightingN() const { return specularN < 1.0f ? 1.0f : specularN; }
    GLfloat getSphereLongitude() const { return sphereLongitude < 0.0f ? 0.0f : sphereLongitude; }
    GLfloat getSphereLatitude() const { return sphereLatitude < 0.0f ? 0.0f : sphereLatitude; }
    GLfloat getLightingPositionX() const { return lightingPositionX; }
    GLfloat getLightingPositionY() const { return lightingPositionY; }
    GLfloat getLightingPositionZ() const { return lightingPositionZ; }

public slots:
    //Setters
    void setAmbientLightingR(double r) { ambientR = GLfloat(r); update(); }
    void setAmbientLightingG(double g) { ambientG = GLfloat(g); update(); }
    void setAmbientLightingB(double b) { ambientB = GLfloat(b); update(); }
    void setDiffuseLightingR(double r) { diffuseR= GLfloat(r); update(); }
    void setDiffuseLightingG(double g) { diffuseG = GLfloat(g); update(); }
    void setDiffuseLightingB(double b) { diffuseB = GLfloat(b); update(); }
    void setSpecularLightingR(double r) { specularR = GLfloat(r); update(); }
    void setSpecularLightingG(double g) { specularG = GLfloat(g); update(); }
    void setSpecularLightingB(double b) { specularB = GLfloat(b); update(); }
    void setSpecularLightingN(double n) { specularN = GLfloat(n); update(); }
    void setSphereLongitude(double l) { sphereLongitude = GLfloat(l); update(); }
    void setSphereLatitude(double l) { sphereLatitude = GLfloat(l); update(); }
    void setLightingPositionX(double x) { lightingPositionX = GLfloat(x); update(); }
    void setLightingPositionY(double y) { lightingPositionY = GLfloat(y); update(); }
    void setLightingPositionZ(double z) { lightingPositionZ = GLfloat(z); update(); }


protected:
    void initializeGL() Q_DECL_OVERRIDE;
    void paintGL() Q_DECL_OVERRIDE;
    void resizeGL(int width, int height) Q_DECL_OVERRIDE;
    void initGeometrySphere();
    void initRenderShaders();

private:
    // Shader Parameters
    int m_vPositionLocation;
    int m_vNormalLocation;
    int m_uniformAmbientLightingLoc;
    int m_uniformDiffuseLightingLoc;
    int m_uniformSpecularLightingLoc;
    int m_uniformSpecularExponentLoc;
    int m_uniformLightingPosition;

    // Lighting and sphere parameters
    GLfloat ambientR = 0.0f;
    GLfloat ambientG = 0.0f;
    GLfloat ambientB = 0.0f;
    GLfloat diffuseR = 0.0f;
    GLfloat diffuseG = 0.0f;
    GLfloat diffuseB = 0.0f;
    GLfloat specularR = 0.0f;
    GLfloat specularG = 0.0f;
    GLfloat specularB = 0.0f;
    GLfloat specularN = 1.0f;
    GLfloat sphereLongitude = 0.0f;
    GLfloat sphereLatitude = 0.0f;
    GLfloat lightingPositionX = 1.0f;
    GLfloat lightingPositionY = 1.0f;
    GLfloat lightingPositionZ = 1.0f;

    QOpenGLShaderProgram *m_program;
};

#endif
