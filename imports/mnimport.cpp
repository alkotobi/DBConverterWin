#include "mnimport.h"

MNImport::MNImport()
{

}

bool MNImport::convertMultiAccessToSqlite(QStringList fileNames,QString destDir)
{
    bool success=true;
    foreach(QString fileName,fileNames){
       success= success and MNImport::convertAccessToSqlite( fileName,destDir);
    }
    return success;
}

bool MNImport::convertAccessToSqlite(QString &fileName,QString destDir)
{
    bool success =true;
    QString logFilePath=fileName+".txt";
    if (not MNDb::openMsAccessDb( fileName)){
        Log::logErrToFileConsole(MNERR_CantOpenFile+fileName,logFilePath);
        return false;
    }

        QString destPath =MNPathes::combinePathes(destDir,QFileInfo(fileName).baseName()+".sqlite");
        if(not MNDb::openSqliteDb(destPath)){
            Log::logErrToFileConsole(MNERR_CantOpenFile+destPath,logFilePath);
            return false;
        }

        QSqlQuery(QSqlDatabase::database(destPath)).exec("PRAGMA synchronous = OFF;"
                                                         "PRAGMA journal_mode = OFF;"
                                                         "locking_mode = EXCLUSIVE;"
                                                         "temp_store = MEMORY;"
                                                         "foreign_keys = OFF;");

        QStringList list=QSqlDatabase::database(fileName).tables(QSql::Tables);

        foreach(QString name,list){
            success=success and MNImport::convertTable(name,fileName,destPath);
        }
        QSqlDatabase::database(destPath).close();

        QSqlDatabase::database(fileName).close();
    return success;

}

bool MNImport::convertTable(QString tableName,QString sourceDbName,QString destDbName)
{
    {
        QString logFilePath=sourceDbName+".txt";
        QSqlDatabase db = QSqlDatabase::database(sourceDbName,true);
        QSqlQuery query(db);
        QSqlDatabase dbDest = QSqlDatabase::database(destDbName,true);
        QSqlQuery queryDest(dbDest);
        if (query.exec("select * from "+tableName)){
            MN_SUCCESS("table opened: select * from "+tableName);
        }else{
            db.close();
            Log::logErrToFileConsole("cant Open table "+query.lastError().text(),logFilePath);
            return false;
        }

        //create table destination
        QString sql =createTableSql(query.record(),tableName);
        if(queryDest.exec(sql)){
            MN_SUCCESS("ok table creatared");
        }else{
            Log::logErrToFileConsole(MNERR_CantCreateTable+ queryDest.lastError().text(),logFilePath);
            return false;
        }

        //move data
        dbDest.transaction();
        while(query.next()){
            PreparedQueryResult ret = insertSqlPrepared(query.record(),tableName);
            if(not queryDest.prepare(ret.preparedSql)){
                MN_ERROR(query.lastError().text());
                Log::logToFile(query.lastError().text(),logFilePath);
                return false;
            };
            int count=ret.values.count();
            for (int i=0;i<count;i++) {
                queryDest.bindValue(":i"+QString::number(i),ret.values[":i"+QString::number(i)]);
            }
            if(queryDest.exec()){

            }else{
                dbDest.rollback();
                Log::logErrToFileConsole(MNERR_CantWriteData+queryDest.lastError().text(),logFilePath);
                return false;
            }
        }
        if (not dbDest.commit()){
            dbDest.rollback();
            Log::logErrToFileConsole(MNERR_CantCommitTransaction +dbDest.lastError().text(),logFilePath);
            return false;
        }
        MN_SUCCESS(tableName);
        return true;
    }

}



/*
        QSqlDatabase db = QSqlDatabase::addDatabase("QODBC",fileName);
        db.setDatabaseName("DRIVER={Microsoft Access Driver (*.mdb, *.accdb)};FIL={MS Access};DBQ="+fileName);
        //open source db
        if (db.open()) {
            MN_SUCCESS("ok source opened");
            //destPath = fileName.replace(fileName.indexOf(".mdb"),4,".sqlite");
            QString destPath = QFileDialog::getSaveFileName(nullptr,
                                                            "Select Destination DB",
                                                            fileName.replace(fileName.indexOf(".mdb"),4,".sqlite")
                                                            ,"SQLITE DB (*.sqlite)");
            if(destPath==""){
                db.close();
                Log::logErrToFileConsole("db destination :"+MNERR_NoFileSelected,logFilePath);
                return false;
            }
            QSqlDatabase dbDest = QSqlDatabase::addDatabase("QSQLITE",destPath);

            dbDest.setDatabaseName(destPath);
            //open dfestination db
            if(dbDest.open()){
                MN_SUCCESS( "ok source opened:" + dbDest.databaseName());
            }else{
                Log::logErrToFileConsole(MNERR_CantOpenFile+destPath,logFilePath);
                return false;
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
                    db.close();
                    Log::logErrToFileConsole("cant Open table "+query.lastError().text(),logFilePath);
                    return false;
                }

                //create table destination
                QString sql =createTableSql(query.record(),name);
                qDebug() << sql;
                if(queryDest.exec(sql)){
                    MN_SUCCESS("ok table creatared");
                }else{
                    db.close();
                    dbDest.close();
                    Log::logErrToFileConsole(MNERR_CantCreateTable+ queryDest.lastError().text(),logFilePath);
                    return false;
                }

                //move data
                dbDest.transaction();
                while(query.next()){
                    PreparedQueryResult ret = insertSqlPrepared(query.record(),name);
                    if(not queryDest.prepare(ret.preparedSql)){
                        MN_ERROR(query.lastError().text());
                        Log::logToFile(query.lastError().text(),logFilePath);
                        return false;
                    };
                    int count=ret.values.count();
                    for (int i=0;i<count;i++) {
                        queryDest.bindValue(":i"+QString::number(i),ret.values[":i"+QString::number(i)]);
                    }
                    if(queryDest.exec()){

                    }else{
                        dbDest.rollback();
                        db.close();
                        dbDest.close();
                        Log::logErrToFileConsole(MNERR_CantWriteData+queryDest.lastError().text(),logFilePath);
                        return false;
                    }
                }
                if (not dbDest.commit()){
                    dbDest.rollback();
                    db.close();
                    dbDest.close();
                    Log::logErrToFileConsole(MNERR_CantCommitTransaction +dbDest.lastError().text(),logFilePath);
                    return false;
                }
                MN_SUCCESS(name);
            }
            dbDest.close();
        }
        db.close();

 */
