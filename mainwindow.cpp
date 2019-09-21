/* Modified by Eric Paquette, eric.paquette@etsmtl.ca, 2019-01-10 */

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "glwidget.h"
#include <QBoxLayout>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_viewer(nullptr)
{
    ui->setupUi(this);
}

void MainWindow::setupMediator() {
    m_viewer = new GLWidget;
    QLayout *layout = new QHBoxLayout;
    layout->addWidget(m_viewer);
    ui->frame->setLayout(layout);

    //ambient lighting ui objects
    QObject::connect(ui->ambientR, SIGNAL(valueChanged(double)),m_viewer, SLOT(setAmbiantLightingR(double)));
    QObject::connect(ui->ambientG, SIGNAL(valueChanged(double)),m_viewer, SLOT(setAmbiantLightingG(double)));
    QObject::connect(ui->ambientB, SIGNAL(valueChanged(double)),m_viewer, SLOT(setAmbiantLightingB(double)));

    //diffuse lighting ui objects
    QObject::connect(ui->diffuseR, SIGNAL(valueChanged(double)),m_viewer, SLOT(setDiffuseLightingR(double)));
    QObject::connect(ui->diffuseG, SIGNAL(valueChanged(double)),m_viewer, SLOT(setDiffuseLightingG(double)));
    QObject::connect(ui->diffuseB, SIGNAL(valueChanged(double)),m_viewer, SLOT(setDiffuseLightingB(double)));

    //specular lighting ui objects
    QObject::connect(ui->specularR, SIGNAL(valueChanged(double)),m_viewer, SLOT(setSpecularLightingR(double)));
    QObject::connect(ui->specularG, SIGNAL(valueChanged(double)),m_viewer, SLOT(setSpecularLightingG(double)));
    QObject::connect(ui->specularB, SIGNAL(valueChanged(double)),m_viewer, SLOT(setSpecularLightingB(double)));
    QObject::connect(ui->specularN, SIGNAL(valueChanged(double)),m_viewer, SLOT(setSpecularLightingN(double))); // specular exponent

    //sphere parameters
    QObject::connect(ui->sphereNbLatitude, SIGNAL(valueChanged(double)),m_viewer, SLOT(setSphereLatitude(double)));
    QObject::connect(ui->sphereNbLongitude, SIGNAL(valueChanged(double)),m_viewer, SLOT(setSphereLongitude(double)));
}


MainWindow::~MainWindow()
{
    delete ui;
}
