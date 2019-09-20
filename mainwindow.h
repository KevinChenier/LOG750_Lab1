/* Modified by Eric Paquette, eric.paquette@etsmtl.ca, 2019-01-08 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "glwidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setupMediator();

private slots:

private:
    Ui::MainWindow *ui;

    GLWidget* m_viewer;
};

#endif // MAINWINDOW_H
