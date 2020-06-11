#include "mninit.h"

MNInit::MNInit()
{

}


bool MNInit::createLocalDbs()
{
    // create db
     QString bkListDbDestPath=MNPathes::getdbBooksListPath();
     if (not MNDb::openSqliteDb(bkListDbDestPath)){
         MN_ERROR("cant open sqlite database");
         return false;
     }

     //create books table
     QSqlRecord rcd= MNBookList::createRecord();
     QString sql=MNSql::sqlCreateTable(rcd,BOOKS_LIST);
     QSqlQuery query=QSqlQuery(QSqlDatabase::database(bkListDbDestPath));
     query.exec(sql);
      rcd= MNAuthor::createRecord();
      sql=MNSql::sqlCreateTable(rcd,AUTHOR);
     query.exec(sql);
     MNDb::closeDb(bkListDbDestPath);
     return true;

}
void MNInit::init()
{
     MNPathes::createAppDataDirStructre();
     createLocalDbs();
}

