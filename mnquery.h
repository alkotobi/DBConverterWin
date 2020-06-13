#ifndef MNQUERY_H
#define MNQUERY_H

#include <QSqlQuery>
#include "mnsql.h"
#include <QSqlError>
#include "log.h"


class MNQuery
{
public:
    MNQuery();
    static int insertRecord(QSqlRecord &recordSource, QSqlQuery &queryDest, QString tableName, QString logFilePath, QMap<QString, QString> &fieldsMap);
    static int getFirstId(QString dbPath, QString tableName, QString whereSql);
    static bool updateRecord(const QString &dbPAth, const QString &tableName, const QString &whereSQl, const QMap<QString, QVariant> &namesAndValues);
    static bool execPreparedSql(const QString &dbPAth, const QString &sql, const QMap<QString, QVariant> &namesAndValues);
    static bool tableExists(const QString &dbPath,const QString &tableName);
    static bool execSQl(const QString &dbPath,const QString &sql);
    static bool createTable(const QString &dbPath,const QSqlRecord &record,const QString &tableName);
};

#endif // MNQUERY_H
