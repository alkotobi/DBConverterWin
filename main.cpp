#include "mainwindow.h"

#include <QApplication>
#include "mninit.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    MNInit::init();
    w.show();
    return a.exec();
}
