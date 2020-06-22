#include "mnquery.h"

MNQuery::MNQuery()
{

}


int MNQuery::insertRecord(QSqlRecord &recordSource, QSqlQuery &queryDest,QString tableName,
                        QString logFilePath ,QMap<QString, QString> &fieldsMap)
{
    PreparedQueryResult ret = MNSql::sqlInsertPrepared(recordSource,tableName,&fieldsMap);
    if(! queryDest.prepare(ret.preparedSql)){
        MN_ERROR(queryDest.lastError().text());
        Log::logToFile(queryDest.lastError().text(),logFilePath);
        return 0;
    };
    int count=ret.values.count();
    for (int i=0;i<count;i++) {
        queryDest.bindValue(":i"+QString::number(i),ret.values[":i"+QString::number(i)]);
    }
    if(! queryDest.exec()){
        Log::logErrToFileConsole(MNERR_CantWriteData+queryDest.lastError().text(),logFilePath);
        return 0;
    }
    return queryDest.lastInsertId().toInt();

}

bool  MNQuery::updateRecord(const QString &dbPAth,const QString &tableName,const QString &whereSQl,const QMap<QString,QVariant> &namesAndValues){
    QString sql ;
    sql=MNSql::sqlUpdatePrepared(tableName,whereSQl,namesAndValues);
    return MNQuery::execSql(dbPAth,sql,namesAndValues);
}

/**
  * execute a prepared sql statments fileds names and values are stored in the namesAndValues map
  * return true if success
  * @param &dbPAth link me
 */
bool MNQuery::execSql(const QString &dbPAth,const QString &sql,const QMap<QString,QVariant> &namesAndValues){
    QSqlQuery query(QSqlDatabase::database(dbPAth));
    query.prepare(sql);
    foreach(QString fieldName,namesAndValues.keys()){
        query.bindValue(":"+fieldName,namesAndValues.value(fieldName));
    }
    bool bl= query.exec();
    MN_SUCCESS( query.lastQuery());
    return bl;
}

int MNQuery::execPreparedInsertSql(const QString &dbPAth,const QString &sql,const QMap<QString,QVariant> &namesAndValues){
    QSqlQuery query(QSqlDatabase::database(dbPAth));
    query.prepare(sql);
    foreach(QString fieldName,namesAndValues.keys()){
        query.bindValue(":"+fieldName,namesAndValues.value(fieldName));
    }
    if (query.exec()) return query.lastInsertId().toInt();else return 0;
}

int MNQuery::execPreparedInsertSql(const QString &dbPAth, const QString &sql, const QList<QVariant> &Values)
{
    QSqlQuery query(QSqlDatabase::database(dbPAth));
    query.prepare(sql);
    foreach(QVariant val,Values){
        query.addBindValue(val);
    }
    if (query.exec()) return query.lastInsertId().toInt();else return 0;
}

int MNQuery::execInsertSql(const QString &dbPAth, const QString &tableName,const QString &field, const QVariant &value)
{
    QString sql;
    sql= "INSERT INTO "+tableName+"("+field+") VALUES(:"+field+");";
    QSqlQuery query(QSqlDatabase::database(dbPAth));
    query.prepare(sql);
    query.bindValue(":"+field,value);
    if (query.exec()) return query.lastInsertId().toInt();else return 0;
}

int MNQuery::execInsertSqlIfNotExists(const QString &dbPAth, const QString &tableName, const QString &field, const QVariant &value)
{
    int id = getFirstId(dbPAth,tableName,field,value);
    if(id!=0) return id;
    return execInsertSql(dbPAth,tableName,field,value);
}

int MNQuery::getFirstId(const QString &dbPAth, const QString &tableName, const QString &field, const QVariant &value)
{
    QString sql = "SELECT ID from "+tableName+" WHERE "+field+"=:"+field+" LIMIT 1";
    QSqlQuery query(QSqlDatabase::database(dbPAth));
    query.prepare(sql);
    query.bindValue(":"+field,value);
    query.exec();
    if(query.first()){
        return query.record().field(0).value().toInt();
    }else return 0;
}


bool MNQuery::tableExists(const QString &dbPath, const QString &tableName)
{
    return QSqlDatabase::database(dbPath).tables().contains(tableName);
}

bool MNQuery::execSQl(const QString &dbPath, const QString &sql)
{
    return QSqlQuery(QSqlDatabase::database(dbPath)).exec(sql);
}

bool MNQuery::createTable(const QString &dbPath, const QSqlRecord &record, const QString &tableName)
{
    return MNQuery::execSQl(dbPath,MNSql::sqlCreateTable(record,tableName));

}

bool MNQuery::createIndex(const QString &dbPath, const QString &tableName, const QString &indName, const bool &isUnic, const QList<QString> &fieldsList)
{
    /*
    CREATE UNIQUE INDEX "nono" ON "author" (
    "shortName"	ASC,
    "info"	ASC
     );
     */
    QString unic;
    if(isUnic)unic ="UNIQUE"; else unic="";
    QString sql = "CREATE "+unic+" INDEX '"+indName+"' ON '"+tableName+"' (";
    QString fls;
    foreach(QString fld,fieldsList){
        if(fls!="") fls=fls+",";
        fls=fls+"'"+fld+"'";
    }
    sql=sql+fls+");";
    QSqlQuery query = QSqlQuery(QSqlDatabase::database(dbPath));
    MN_WARNING(sql);
    return query.exec(sql);

}

bool MNQuery::isTableEmpty(const QString &dbPath, const QString &tableName)
{
        QSqlQuery query = QSqlQuery(QSqlDatabase::database(dbPath));
        query.exec("select * from "+tableName);
        return query.size()==0;
}

int MNQuery::recordsCount(const QString &dbPath, const QString &tableName, QString whereSql)
{
    QSqlQuery query = QSqlQuery(QSqlDatabase::database(dbPath));
    QString where;
    if(whereSql!="") where=" WHERE "+whereSql;
    QString sql = "SELECT COUNT(*) from "+tableName+where;
    query.exec(sql);
    if(query.first()){
        return query.record().field(0).value().toInt();
    }
    return 0;
}

int MNQuery::getFirstId(QString dbPath, QString tableName,QString whereSql)
{
    QSqlQuery query = QSqlQuery(QSqlDatabase::database(dbPath));
    QString where;
    if(whereSql!="") where=" WHERE "+whereSql;
    QString sql = "select ID from "+tableName+where +" limit 1;";
    query.exec(sql);
    if(query.first()){
        return query.record().field(0).value().toInt();
    }
    return 0;
}
