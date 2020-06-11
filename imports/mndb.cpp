#include "mndb.h"

MNDb::MNDb()
{

}

bool MNDb::openMsAccessDb(QString dbPath)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC",dbPath);
    db.setDatabaseName("DRIVER={Microsoft Access Driver (*.mdb, *.accdb)};FIL={MS Access};DBQ="+dbPath);
    //open source db
    if (db.open()) {
        return true;
    }else{

        return false;
    }
}

bool MNDb::openSqliteDb(QString dbPath)
{
    QSqlDatabase dbDest = QSqlDatabase::addDatabase("QSQLITE",dbPath);

    dbDest.setDatabaseName(dbPath);
    //open dfestination db
    if(dbDest.open()){
        return true;
    }else{

        return false;
    }
}

 QStringList MNDb::getDbTableNames(QString dbPath)
{
    return  QSqlDatabase::database(dbPath).tables(QSql::Tables);

 }

 bool MNDb::startTransaction(QString dbPath)
 {
     return QSqlDatabase::database(dbPath).transaction();

 }

 bool MNDb::commitTransaction(QString dbPath)
 {
     return QSqlDatabase::database(dbPath).commit();

 }

 void MNDb::closeDb(QString dbPath)
 {
     QSqlDatabase::database(dbPath).close();
 }

 bool MNDb::rollBackTransaction(QString dbPath)
 {
     return QSqlDatabase::database(dbPath).rollback();
 }

 bool MNDb::execSQl(QString dbPath, QString sql)
 {
     return  QSqlQuery(QSqlDatabase::database(dbPath)).exec(sql);
 }

 bool MNDb::makeSQliteDbFaster(QString dbPath)
 {
     return execSQl(dbPath,"PRAGMA synchronous = OFF;"
                   "PRAGMA journal_mode = OFF;"
                   "locking_mode = EXCLUSIVE;"
                   "temp_store = MEMORY;"
                   "foreign_keys = OFF;");
 }


 bool MNDb::exportTable(QString sourceTableName,QString sourceAccessDbName
                                  ,QString destSqliteDbName,QMap<QString,QString> *map)
 {
     {
         // will use this path to save a log file contains any convert errors
         QString logFilePath=destSqliteDbName+".txt";
         QSqlQuery querySource(QSqlDatabase::database(sourceAccessDbName,true));
         QSqlQuery queryDest(QSqlDatabase::database(destSqliteDbName,true));
         if (querySource.exec("select * from "+sourceTableName)){
             MN_SUCCESS("table opened: select * from "+sourceTableName);
         }else{
             Log::logErrToFileConsole("cant Open table "+querySource.lastError().text(),logFilePath);
             return false;
         }

         //create table destination
         QString sql =MNSql::sqlCreateTable(querySource.record(),sourceTableName);
         if(queryDest.exec(sql)){
             MN_SUCCESS("ok table created");
         }else{
             Log::logErrToFileConsole(MNERR_CantCreateTable+ queryDest.lastError().text(),logFilePath);
             return false;
         }

         //move data
         if(exportAllTableData(querySource,queryDest,sourceTableName,logFilePath,map)){
             MN_SUCCESS(sourceTableName);

         }else return false;



     }
      return true;

 }






 bool MNDb::exportAllTableData(QSqlQuery &querySource, QSqlQuery &queryDest,
                             QString sourceTableName,QString logFilePath,QMap<QString,QString> *map)
 {
     while(querySource.next()){
         QSqlRecord rcd =querySource.record();
        MNQuery::insertRecord(rcd,queryDest,sourceTableName,logFilePath,*map);
     }
     return true;

 }




