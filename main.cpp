#include "mainwindow.h"

#include <QApplication>
#include "mninit.h"

int main(int argc, char *argv[])
{
    //this solve the problem of small application windows
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication a(argc, argv);
    MainWindow w;
    MNInit::init();
    w.show();
    return a.exec();
}
