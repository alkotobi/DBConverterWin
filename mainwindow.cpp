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
 QString p= ui->txt_export_location->text();
 if(p=="") return;//TOEDO:show error message box
 if(p[p.length()-1]!='\\'){
         p=p+"\\";
}
 QString bkListDbDestPath=p+QString::number(book_id_source)+".sqlite";
 QString bkDbSourcePath ;
 QString bkListDbSourcePath=ui->txtShamelaPath->text();

 if (! MNDb::openSqliteDb(bkListDbDestPath)){
     MN_ERROR("cant open sqlite database");
 }
 if(! MNDb::openMsAccessDb(bkListDbSourcePath)){
     MN_ERROR("cant open main.mdb");
 }


 MNQuery::createTable(bkListDbDestPath,MNBookList::createRecord(),MNBookList::TABLE_NAME);
 MNQuery::createTable(bkListDbDestPath,MNAuthor::createRecord(),MNAuthor::TABLE_NAME);
 MNQuery::createTable(bkListDbDestPath,MNCat::createRecord(),MNCat::TABLE_NAME);
 MNMidleTableLink(bkListDbDestPath,MNBookList::TABLE_NAME,MNAuthor::TABLE_NAME).createTable();
 MNMidleTableLink(bkListDbDestPath,MNCat::TABLE_NAME,MNCat::TABLE_NAME).createTable();
 MNMidleTableLink(bkListDbDestPath,MNBookList::TABLE_NAME,MNCat::TABLE_NAME).createTable();


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
  MNBookList::updateAuthorID( book_id,  authid,bkListDbDestPath);
  MNMidleTableLink(bkListDbDestPath,MNBookList::TABLE_NAME,MNAuthor::TABLE_NAME).linkLeftToRight(book_id,authid);
  int catSourceId=MNCat::getSourceCatId(book_id,bkListDbSourcePath);
  int catId=MNCat::importCat(bkListDbSourcePath,bkListDbDestPath,catSourceId);
  MNMidleTableLink(bkListDbDestPath,MNBookList::TABLE_NAME,MNCat::TABLE_NAME).linkLeftToRight(book_id,catId);

  MNDb::makeSQliteDbFaster(bkListDbDestPath);
  MNDb::startTransaction(bkListDbDestPath);
  MNBook book(book_id,bkListDbDestPath);
  book.createTable();
  MNPage pages(book_id,bkListDbDestPath);
  pages.createTable();
  MNIndex index(book_id,bkListDbDestPath);
  index.createTable();
  index.importAllInd(bkDbSourcePath,book_id_source);

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
          int idbook = book.insert(kalima.original,kalima.norm,kalima.tachkil);
          bkIds<<idbook;
      }
      int pageNo=bksource.record().field("page").value().toInt();
      int tome=bksource.record().field("part").value().toInt();
      pages.insert(pageNo,tome,bkIds.at(0),bkIds.count());
      delete kalimat;
  }
  MNDb::commitTransaction(bkListDbDestPath);
  Log::showInfo("book imported");

 //close dbs
 MNDb::closeDb(bkListDbDestPath);
 MNDb::closeDb(bkListDbSourcePath);
 MNDb::closeDb(bkDbSourcePath);

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
