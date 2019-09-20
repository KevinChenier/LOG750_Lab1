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
    QObject::connect(ui->ambientR, SIGNAL(valueChanged(double)),m_viewer, SLOT(SetAmbiantLightingR(double)));
    QObject::connect(ui->ambientG, SIGNAL(valueChanged(double)),m_viewer, SLOT(SetAmbiantLightingG(double)));
    QObject::connect(ui->ambientB, SIGNAL(valueChanged(double)),m_viewer, SLOT(SetAmbiantLightingB(double)));

    //diffuse lighting ui objects
    QObject::connect(ui->diffuseR, SIGNAL(valueChanged(double)),m_viewer, SLOT(SetDiffuseLightingR(double)));
    QObject::connect(ui->diffuseG, SIGNAL(valueChanged(double)),m_viewer, SLOT(SetDiffuseLightingG(double)));
    QObject::connect(ui->diffuseB, SIGNAL(valueChanged(double)),m_viewer, SLOT(SetDiffuseLightingB(double)));

    //specular lighting ui objects
    QObject::connect(ui->specularR, SIGNAL(valueChanged(double)),m_viewer, SLOT(SetSpecularLightingR(double)));
    QObject::connect(ui->specularG, SIGNAL(valueChanged(double)),m_viewer, SLOT(SetSpecularLightingG(double)));
    QObject::connect(ui->specularB, SIGNAL(valueChanged(double)),m_viewer, SLOT(SetSpecularLightingB(double)));
    QObject::connect(ui->specularN, SIGNAL(valueChanged(double)),m_viewer, SLOT(SetSpecularLightingN(double))); // specular exponent

    //sphere parameters
    QObject::connect(ui->sphereNbLatitude, SIGNAL(valueChanged(double)),m_viewer, SLOT(SetSphereLatitude(double)));
    QObject::connect(ui->sphereNbLongitude, SIGNAL(valueChanged(double)),m_viewer, SLOT(SetSphereLongitude(double)));
}


MainWindow::~MainWindow()
{
    delete ui;
}
