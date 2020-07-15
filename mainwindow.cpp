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
#ifndef Q_OS_WIN
    return;
#endif
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

    if (! MNImport::convertMultiAccessToSqlite(fileNames,destDir)){
             QMessageBox messageBox;
             messageBox.critical(0,"Error","could not convert some database check logFile ");
    }

}

void MainWindow::on_bkImport_clicked()
{
#ifndef Q_OS_WIN
    return;
#endif
 int book_id_source=21710;
 QString bkDbDestPath;
 QString bkListDbDestPath=MNPathes::getdbBooksListPath();
 QString bkDbSourcePath ;
 QString bkListDbSourcePath=ui->txtShamelaPath->text();




 if (! MNDb::openSqliteDb(bkListDbDestPath)){
     MN_ERROR("cant open sqlite database");
 }
 if(! MNDb::openMsAccessDb(bkListDbSourcePath)){
     MN_ERROR("cant open main.mdb");
 }

 //get the book database link
 bkDbSourcePath=MNBookList::getBkDbSourcePath(bkListDbSourcePath,book_id_source);
 if(bkDbSourcePath == ""){
     QMessageBox messageBox;
     messageBox.critical(0,"Error","cant find the book "+QString::number(book_id_source));
     //TODO: must close DBS
     return ;
 }

 if(! MNDb::openMsAccessDb(bkDbSourcePath)){
     MN_ERROR("cant open the book: "+QString::number(bkId)+".mdb");
 }
 QSqlQuery qrBkSource(QSqlDatabase::database(bkDbSourcePath));
 QSqlQuery qrbkIndex(QSqlDatabase::database(bkDbSourcePath));
 QString authDbPath=MNPathes::getAuthDbSourcePath(bkListDbSourcePath);
 if(! MNDb::openMsAccessDb(authDbPath)){
  MN_ERROR("cant open the authors access db ");
  return;
 }
  int authid=MNAuthor::importAuthor(bkListDbSourcePath,bkListDbDestPath,book_id_source);
  int book_id=MNBookList::importBook( bkListDbSourcePath, bkListDbDestPath, book_id_source );
  MNBookList::updateAuthorID( book_id,  authid);
  MNMidleTableLink(bkListDbDestPath,MNBookList::TABLE_NAME,MNAuthor::TABLE_NAME).linkLeftToRight(book_id,authid);
  //MNCat::importAllCat(bkListDbSourcePath);
  int catId=MNCat::getSourceCatId(book_id);
  MNMidleTableLink(bkListDbDestPath,MNBookList::TABLE_NAME,MNCat::TABLE_NAME).linkLeftToRight(book_id,catId);

  //import text
  QString dbSearchPath=MNPathes::getdbSearchPath();
  MNDb::openSqliteDb(dbSearchPath);
  MNDb::openSqliteDb(MNPathes::getDbBookPath(book_id));
  MNDb::makeSQliteDbFaster(dbSearchPath);
  MNDb::makeSQliteDbFaster(MNPathes::getDbBookPath(book_id));
  MNDb::startTransaction(dbSearchPath);
  MNDb::startTransaction(MNPathes::getDbBookPath(book_id));
  MNBook book(book_id);
  book.createTable();
  MNPage pages(book_id);
  pages.createTable();
  MNSearchBook bksearch(book_id);
  bksearch.createTable();
  MNIndex index(book_id);
  index.createTable();
  index.importAllInd(bkDbSourcePath);

  //check if table is from archive or not
  QSqlQuery bksource(QSqlDatabase::database(bkDbSourcePath));
  if(QSqlDatabase::database(bkDbSourcePath).tables().
          contains("b" + QString::number(book_id_source))){
     bksource.exec("select nass,page,part from b"+
                   QString::number(book_id_source)) ;
  }else{
     bksource.exec("select nass,page,part from book") ;
  }
  Log::setTimeStampToCurrent();
  while(bksource.next()){
      QString nass=bksource.record().field("nass").value().toString();
      QList<MNNass::Kalimat>* kalimat = MNNass::getKalimat(nass);
      QList<int> bkIds;
      foreach(MNNass::Kalimat kalima,*kalimat){
          int idKalima=MNWords::insert(kalima.norm);
          int idTachkil=MNTachkil::insert(kalima.tachkil);
          MNMidleTableLink(MNPathes::getdbSearchPath(),
                           MNWords::TABLE_NAME,MNTachkil::TABLE_NAME).
                  linkLeftToRight(idKalima,idTachkil);
          int idbook = book.insert(kalima.original,idKalima);
          bkIds<<idbook;
          bksearch.linkBookToWord(idbook,idKalima);
      }
      int pageNo=bksource.record().field("page").value().toInt();
      int tome=bksource.record().field("part").value().toInt();
      pages.insert(pageNo,tome,bkIds.at(0),bkIds.count());
      delete kalimat;
  }
  MNDb::commitTransaction(dbSearchPath);
  MNDb::commitTransaction(MNPathes::getDbBookPath(book_id));
  Log::showInfo("book imported");






 //close dbs
 MNDb::closeDb(bkListDbDestPath);
 MNDb::closeDb(bkListDbSourcePath);
 MNDb::closeDb(bkDbSourcePath);
 MNDb::closeDb(dbSearchPath);
 MNDb::closeDb(MNPathes::getDbBookPath(book_id));


}

void MainWindow::on_importCats_clicked()
{
#ifndef Q_OS_WIN
    return;
#endif
    QString bkListDbSourcePath=ui->txtShamelaPath->text();//main.mdb
    MNDb::openMsAccessDb(bkListDbSourcePath);
    MNDb::openSqliteDb(MNPathes::getdbBooksListPath());
    MNCat::importAllCat(bkListDbSourcePath);
    MNDb::closeDb(bkListDbSourcePath);
    MNDb::closeDb(MNPathes::getdbBooksListPath());
}

void MainWindow::on_testNass_clicked()
{
 }

void MainWindow::on_bookView_clicked()
{
    MNBookShowForm *frm = new MNBookShowForm(this);
    frm->show();
}



void MainWindow::on_btnShamelahPath_clicked()
{
    QString bkListDbSourcePath=QFileDialog::getOpenFileName(this,
                             "Open Source DB", "", "ACCESS DB (*.mdb)");
    ui->txtShamelaPath->setText(bkListDbSourcePath);
}
