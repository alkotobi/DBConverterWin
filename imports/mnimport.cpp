#include "mnimport.h"

MNImport::MNImport()
{

}

bool MNImport::convertMultiAccessToSqlite(QStringList dbSourcePathes,QString destDir)
{
    bool success=true;
    foreach(QString dbSourcePath,dbSourcePathes){
       success= success and MNImport::convertAccessToSqlite( dbSourcePath,destDir);
    }
    return success;
}

bool MNImport::convertAccessToSqlite(QString &dbSourcePath,QString destDir)
{
    // check if access db file is valid
    bool success =true;
    QString logFilePath=dbSourcePath+".txt";
    if (not MNDb::openMsAccessDb( dbSourcePath)){
        Log::logErrToFileConsole(MNERR_CantOpenFile+dbSourcePath,logFilePath);
        return false;
    }

    // create sqlte db or open if exists
        QString destPath =MNPathes::combinePathes(destDir,QFileInfo(dbSourcePath).baseName()+".sqlite");
        if(not MNDb::openSqliteDb(destPath)){
            Log::logErrToFileConsole(MNERR_CantOpenFile+destPath,logFilePath);
            return false;
        }

        MNDb::makeSQliteDbFaster(destPath);

        // get access table names list
        QStringList list=MNDb::getDbTableNames(dbSourcePath);
        MNDb::dbStartTransaction(destPath);
        foreach(QString name,list){
            success=success and MNDb::dbExportTable(name,dbSourcePath,destPath);
        }
        if(success){
            if(MNDb::dbCommitTransaction(destPath)){
                Log::logErrToFileConsole(MNERR_CantCommitTransaction+destPath,logFilePath);
                return false;
            }
        }else MNDb::dbRollBackTransaction(destPath);

        MNDb::dbClose(destPath);
        MNDb::dbClose(dbSourcePath);
        return success;

}

