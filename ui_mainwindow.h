/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *testConvert;
    QPushButton *bkImport;
    QPushButton *importCats;
    QPushButton *testNass;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(461, 258);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        testConvert = new QPushButton(centralwidget);
        testConvert->setObjectName(QString::fromUtf8("testConvert"));
        testConvert->setGeometry(QRect(160, 80, 121, 51));
        bkImport = new QPushButton(centralwidget);
        bkImport->setObjectName(QString::fromUtf8("bkImport"));
        bkImport->setGeometry(QRect(170, 150, 111, 41));
        importCats = new QPushButton(centralwidget);
        importCats->setObjectName(QString::fromUtf8("importCats"));
        importCats->setGeometry(QRect(310, 150, 101, 41));
        testNass = new QPushButton(centralwidget);
        testNass->setObjectName(QString::fromUtf8("testNass"));
        testNass->setGeometry(QRect(40, 60, 91, 41));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 461, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        testConvert->setText(QCoreApplication::translate("MainWindow", "convert db", nullptr));
        bkImport->setText(QCoreApplication::translate("MainWindow", "import book", nullptr));
        importCats->setText(QCoreApplication::translate("MainWindow", "import cats", nullptr));
        testNass->setText(QCoreApplication::translate("MainWindow", "testNass", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
