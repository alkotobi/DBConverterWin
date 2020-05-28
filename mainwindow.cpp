#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QDebug"
#include "QSqlTableModel"
#include "QSqlQueryModel"
#include "mnsql.h"
#include <QSqlError>
#include "log.h"

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
  QString fileName =QFileDialog::getOpenFileName(this,
       tr("Open Source DB"), "", tr("ACCESS DB (*.mdb)"));
   QSqlDatabase db = QSqlDatabase::addDatabase("QODBC",fileName);
   db.setDatabaseName("DRIVER={Microsoft Access Driver (*.mdb, *.accdb)};FIL={MS Access};DBQ="+fileName);
   if (db.open()) {
       MN_SUCCESS("ok source opened");
        //destPath = fileName.replace(fileName.indexOf(".mdb"),4,".sqlite");
        QString destPath = QFileDialog::getSaveFileName(this,
            tr("Select Destination DB"), "", tr("SQLITE DB (*.sqlite)"));
       QSqlDatabase dbDest = QSqlDatabase::addDatabase("QSQLITE",destPath);

       dbDest.setDatabaseName(destPath);
       if(dbDest.open()){
            MN_SUCCESS( "ok source opened:" + dbDest.databaseName());
       }else{
           MN_ERROR("cant Open Source DB") ;
           return;
       }
       QSqlQuery query(db);
       QSqlQuery queryDest(dbDest);
       queryDest.exec("PRAGMA synchronous = OFF;"
                           "PRAGMA journal_mode = OFF;"
                           "locking_mode = SHARED;"
                           "temp_store = DEFAULT;"
                           "foreign_keys = ON;");
       QStringList list=db.tables(QSql::Tables);



       foreach(QString name,list){

           if (query.exec("select * from "+name)){
               MN_SUCCESS("table opened: select * from "+name);
           }else{
               QString str = "cant Open table "+query.lastError().text();
              MN_ERROR(str);
              db.close();
              return;
           }

           //create table destination
           QString sql =createTableSql(query.record(),name);
           qDebug() << sql;
           if(queryDest.exec(sql)){
              qDebug() << "ok table creatared";
           }else{
               MN_ERROR("cant create table :"+ queryDest.lastError().text());
               db.close();
               dbDest.close();
               return;
           }


           //move data
           dbDest.transaction();
            while(query.next()){
                //QString sql =insetSql(query.record(),name);
                PreparedQueryResult ret = insertSqlPrepared(query.record(),name);
                //qDebug()<<ret.preparedSql;
                if(not queryDest.prepare(ret.preparedSql)){
                  MN_ERROR(query.lastError().text());
                };
                int count=ret.values.count();
                for (int i=0;i<count;i++) {
                    queryDest.bindValue(":i"+QString::number(i),ret.values[":i"+QString::number(i)]);
                }
                //qDebug() << sql;
                if(queryDest.exec()){
                 //  MN_SUCCESS( "data inserted");

                }else{
                    MN_ERROR("cant insert data: "+queryDest.lastError().text());
                    dbDest.rollback();
                    db.close();
                    dbDest.close();
                    return;
                }
            }
            if (not dbDest.commit()){
                 MN_ERROR("cant commit tarnsaction :" +dbDest.lastError().text());
                 dbDest.rollback();
                 db.close();
                 dbDest.close();
                 return;
            }


           MN_SUCCESS(name);
       }


   dbDest.close();
}

   db.close();

}
