#include "mnwords.h"

MNWords::MNWords()
{

}

QSqlRecord MNWords::createRecord()
{
    QSqlRecord rcd;
    QSqlField fld;
    MNRecord::initRecord(rcd);
    rcd.append(QSqlField(FIELD_NAME,QVariant::String));
    return rcd;
}

bool MNWords::createTable()
{
 return MNQuery::createTable(MNPathes::getdbSearchPath(),createRecord(),TABLE_NAME);
}

QString MNWords::dbPath(){
    return MNPathes::getdbSearchPath();
}

int MNWords::insert(const QString &word){
 return MNQuery::execInsertSqlIfNotExists(dbPath(),TABLE_NAME,FIELD_NAME,word);
}


