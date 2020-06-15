#include "mntachkil.h"

MNTachkil::MNTachkil()
{

}


QSqlRecord MNTachkil::createRecord()
{
    QSqlRecord rcd;
    QSqlField fld;
    MNRecord::initRecord(rcd);
    rcd.append(QSqlField(FIELD_NAME,QVariant::String));
    return rcd;
}

bool MNTachkil::createTable()
{
 return MNQuery::createTable(dbPath(),createRecord(),TABLE_NAME);
}

QString MNTachkil::dbPath(){
    return MNPathes::getdbSearchPath();
}

int MNTachkil::insert(const QString &tachkil){
 return MNQuery::execInsertSqlIfNotExists(dbPath(),TABLE_NAME,FIELD_NAME,tachkil);
}
