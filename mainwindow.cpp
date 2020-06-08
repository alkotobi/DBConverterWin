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

void MainWindow::on_bkImport_clicked()
{
 MNPathes::createAppDataDirStructre();
 int bkId=34460;
 QString bkDbDestPath;
 QString bkListDbDestPath=MNPathes::getdbBooksListPath();
 QString bkDbSourcePath ;
 QString bkListDbSourcePath=QFileDialog::getOpenFileName(this,
                          "Open Source DB", "", "ACCESS DB (*.mdb)");//main.mdb





 if (not MNDb::openSqliteDb(bkListDbDestPath)){
     MN_ERROR("cant open sqlite database");
 }
 if(not MNDb::openMsAccessDb(bkListDbSourcePath)){
     MN_ERROR("cant open main.mdb");
 }

 //get the book database link
 bkDbSourcePath=MNBookList::getBkDbSourcePath(bkListDbSourcePath,bkId);
 if(bkDbSourcePath == ""){
     QMessageBox messageBox;
     messageBox.critical(0,"Error","cant find the book "+QString::number(bkId));
     //TODO: must close DBS
     return ;
 }

 if(not MNDb::openMsAccessDb(bkDbSourcePath)){
     MN_ERROR("cant open the book: "+QString::number(bkId)+".mdb");
 }
 QSqlQuery qrBkSource(QSqlDatabase::database(bkDbSourcePath));
 QSqlQuery qrbkIndex(QSqlDatabase::database(bkDbSourcePath));

 //TODO: import book info data
 {
     QSqlQuery qrbkListDbSource(QSqlDatabase::database(bkListDbSourcePath));
     qrbkListDbSource.exec("select * from [0bok] where bkid="+QString::number(bkId));
     if(qrbkListDbSource.first()){
         MN_SUCCESS(qrbkListDbSource.record().field(1).value().toString());
     }
 }

 //*********************

 //TODO: inport author data

 //close dbs
 MNDb::dbClose(bkListDbDestPath);
 MNDb::dbClose(bkListDbSourcePath);
 MNDb::dbClose(bkDbSourcePath);

}
