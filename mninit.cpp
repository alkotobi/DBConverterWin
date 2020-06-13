#include "mninit.h"

MNInit::MNInit()
{

}


bool MNInit::createLocalDbs()
{
    // create db
    //TODO: handle possible errors of tables creation
    //TODO: refactor to classes
     QString bkListDbDestPath=MNPathes::getdbBooksListPath();
     if (not MNDb::openSqliteDb(bkListDbDestPath)){
         MN_ERROR("cant open sqlite database");
         return false;
     }

     //create books table

     MNQuery::createTable(bkListDbDestPath,MNBookList::createRecord(),MNBookList::TABLE_NAME);
     MNQuery::createTable(bkListDbDestPath,MNAuthor::createRecord(),MNAuthor::TABLE_NAME);
     MNQuery::createTable(bkListDbDestPath,MNCat::createRecord(),MNCat::TABLE_NAME);
     MNMidleTableLink(bkListDbDestPath,MNBookList::TABLE_NAME,MNAuthor::TABLE_NAME).createTable();
     MNMidleTableLink(bkListDbDestPath,MNCat::TABLE_NAME,MNCat::TABLE_NAME).createTable();
     MNDb::closeDb(bkListDbDestPath);
     return true;

}
void MNInit::init()
{
     MNPathes::createAppDataDirStructre();
     createLocalDbs();
}

