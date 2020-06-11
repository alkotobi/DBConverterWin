#include "mnquery.h"

MNQuery::MNQuery()
{

}


int MNQuery::insertRecord(QSqlRecord &recordSource, QSqlQuery &queryDest,QString tableName,
                        QString logFilePath ,QMap<QString, QString> &fieldsMap)
{
    PreparedQueryResult ret = MNSql::sqlInsertPrepared(recordSource,tableName,&fieldsMap);
    if(not queryDest.prepare(ret.preparedSql)){
        MN_ERROR(queryDest.lastError().text());
        Log::logToFile(queryDest.lastError().text(),logFilePath);
        return 0;
    };
    int count=ret.values.count();
    for (int i=0;i<count;i++) {
        queryDest.bindValue(":i"+QString::number(i),ret.values[":i"+QString::number(i)]);
    }
    if(not queryDest.exec()){
        Log::logErrToFileConsole(MNERR_CantWriteData+queryDest.lastError().text(),logFilePath);
        return 0;
    }
    return queryDest.lastInsertId().toInt();

}

int MNQuery::getFirstId(QString dbPath, QString tableName,QString whereSql)
{
    QSqlQuery query = QSqlQuery(QSqlDatabase::database(dbPath));
    QString sql = "select ID from "+tableName+" where "+whereSql +" limit 1;";
    query.exec(sql);
    if(query.first()){
        return query.record().field(0).value().toInt();
    }
    return 0;
}
