/* Modified by Eric Paquette, eric.paquette@etsmtl.ca, 2019-01-08 */
#include "simpleViewer.h"
#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSurfaceFormat fmt;
    fmt.setVersion(4, 0);
    fmt.setProfile(QSurfaceFormat::CoreProfile);
    QSurfaceFormat::setDefaultFormat(fmt);

    MainWindow w;
    w.setupMediator();
    w.show();

    return a.exec();
}
