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

 bool MNDb::dbStartTransaction(QString dbPath)
 {
     return QSqlDatabase::database(dbPath).transaction();

 }

 bool MNDb::dbCommitTransaction(QString dbPath)
 {
     return QSqlDatabase::database(dbPath).commit();

 }

 void MNDb::dbClose(QString dbPath)
 {
     QSqlDatabase::database(dbPath).close();
 }

 bool MNDb::dbRollBackTransaction(QString dbPath)
 {
     return QSqlDatabase::database(dbPath).rollback();
 }

 bool MNDb::dbExec(QString dbPath, QString sql)
 {
     return  QSqlQuery(QSqlDatabase::database(dbPath)).exec(sql);
 }

 bool MNDb::makeSQliteDbFaster(QString dbPath)
 {
     return dbExec(dbPath,"PRAGMA synchronous = OFF;"
                   "PRAGMA journal_mode = OFF;"
                   "locking_mode = EXCLUSIVE;"
                   "temp_store = MEMORY;"
                   "foreign_keys = OFF;");
 }


 bool MNDb::dbExportTable(QString sourceTableName,QString sourceAccessDbName
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
         QString sql =sqlCreateTable(querySource.record(),sourceTableName);
         if(queryDest.exec(sql)){
             MN_SUCCESS("ok table created");
         }else{
             Log::logErrToFileConsole(MNERR_CantCreateTable+ queryDest.lastError().text(),logFilePath);
             return false;
         }

         //move data
         if(dbExportTableData(querySource,queryDest,sourceTableName,logFilePath,map)){
             MN_SUCCESS(sourceTableName);

         }else return false;



     }
      return true;

 }


 bool MNDb::dbExportTableData(QSqlQuery &querySource, QSqlQuery &queryDest,
                             QString sourceTableName,QString logFilePath,QMap<QString,QString> *map)
 {
     while(querySource.next()){
         PreparedQueryResult ret = MNDb::sqlInsertPrepared(querySource.record(),sourceTableName,map);
         if(not queryDest.prepare(ret.preparedSql)){
             MN_ERROR(querySource.lastError().text());
             Log::logToFile(querySource.lastError().text(),logFilePath);
             return false;
         };
         int count=ret.values.count();
         for (int i=0;i<count;i++) {
             queryDest.bindValue(":i"+QString::number(i),ret.values[":i"+QString::number(i)]);
         }
         if(not queryDest.exec()){
             Log::logErrToFileConsole(MNERR_CantWriteData+queryDest.lastError().text(),logFilePath);
             return false;
         }
     }
     return true;

 }

 PreparedQueryResult MNDb::sqlInsertPrepared(const QSqlRecord &rcd,QString tableName,QMap<QString,QString> *map){
     /*
   INSERT INTO table_name (column1, column2, column3, ...)
   VALUES (value1, value2, value3, ...);
        */
     PreparedQueryResult ret;
       QString str1=0,str2 ="",str3="";
    if(map==nullptr){// if field from dest and source are same definition
       for(int i=0;i<rcd.count();i++){
            QSqlField fld= rcd.field(i);
            QString type=fld.value().typeToName(fld.value().type());
            QString strType = type;
            if(str1!="") str1=str1+",";//coma only if have items before
            str1 =str1+"["+fld.name()+"]";
            if(str2!="") str2=str2+",";//coma only if have items before
                ret.values[":i"+QString::number(i)]=fld.value();
                 str2=str2+":i"+QString::number(i);

       }


    }
    else{//with fields mapping
        int i=0;
        foreach(QString key,map->keys()){
            QSqlField fld= rcd.field(map->value(key));
            QString type=fld.value().typeToName(fld.value().type());
            QString strType = type;
            if(str1!="") str1=str1+",";//coma only if have items before
            str1 =str1+"["+key+"]";
            if(str2!="") str2=str2+",";//coma only if have items before
                ret.values[":i"+QString::number(i)]=fld.value();
                 str2=str2+":i"+QString::number(i);
                 i=i+1;

        }
    }
    str1 ="INSERT INTO ["+tableName+"] ("+str1+") ";
    str2 =" VALUES ("+str2+");";
    ret.preparedSql=str1 + str2;
    return ret;


 }

 QString MNDb::sqlCreateTable(const QSqlRecord &rcd,QString tableName)
 {
     QString str="CREATE TABLE IF NOT EXISTS '"+tableName+"' (";



        for(int i=0;i<rcd.count();i++){
            if (rcd.field(i).isGenerated()){
                QSqlField fld=rcd.field(i);
                QString type=fld.value().typeToName(fld.value().type());
                QString strType =(type=="QString")? "TEXT":type;
                QString str1="'"+fld.name()+"' "+
                        strType;
                if(!(i==rcd.count()-1)){
                    str1=str1+",";
                 }
                str =str+str1;
            }
        }

        str=str+");";


        return str;
 }

