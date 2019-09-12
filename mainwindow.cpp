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
//    m_viewer = new GLWidget;
    Viewer *viewer = new Viewer();
    QLayout *layout = new QHBoxLayout;
    layout->addWidget(viewer);
    ui->frame->setLayout(layout);
}


MainWindow::~MainWindow()
{
    delete ui;
}
