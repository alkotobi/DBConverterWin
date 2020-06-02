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
