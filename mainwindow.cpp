#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include "./imports/mnimport.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_testConvert_clicked()
{
    QStringList fileNames =QFileDialog::getOpenFileNames(this,
                           "Open Source DB", "", "ACCESS DB (*.mdb)");
    if(fileNames.count()==0){
        QMessageBox messageBox;
        messageBox.critical(0,"Error","You did not select any file");
        return ;
    }
    QString destDir = QFileDialog::getExistingDirectory(this,"Select Destination DB directory","",QFileDialog::ShowDirsOnly);

    if(destDir==""){
        QMessageBox messageBox;
        messageBox.critical(0,"Error","You did not select any file");
        return ;
    }

    if (not MNImport::convertMultiAccessToSqlite(fileNames,destDir)){
             QMessageBox messageBox;
             messageBox.critical(0,"Error","could not convert some database check logFile ");
    }

}
