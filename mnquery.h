#ifndef MNQUERY_H
#define MNQUERY_H

#include <QSqlQuery>
#include "mnsql.h"
#include <QSqlError>
#include "log.h"
#include <QList>


class MNQuery
{
public:
    MNQuery();
    static int insertRecord(QSqlRecord &recordSource, QSqlQuery &queryDest, QString tableName, QString logFilePath, QMap<QString, QString> &fieldsMap);
    static int getFirstId(QString dbPath, QString tableName, QString whereSql);
    static bool updateRecord(const QString &dbPAth, const QString &tableName, const QString &whereSQl, const QMap<QString, QVariant> &namesAndValues);
    static bool execSql(const QString &dbPAth, const QString &sql, const QMap<QString, QVariant> &namesAndValues);
    static bool tableExists(const QString &dbPath,const QString &tableName);
    static bool execSQl(const QString &dbPath,const QString &sql);
    static bool createTable(const QString &dbPath,const QSqlRecord &record,const QString &tableName);
    static bool createIndex(const QString &dbPath, const QString &tableName,
                            const QString &indName, const bool &isUnic, const QList<QString> &fieldsList);
    static bool isTableEmpty(const QString &dbPath, const QString &tableName);
    static int  recordsCount(const QString &dbPath, const QString &tableName,QString whereSql);

    static int execPreparedInsertSql(const QString &dbPAth, const QString &sql, const QMap<QString, QVariant> &namesAndValues);
    static int execPreparedInsertSql(const QString &dbPAth, const QString &sql, const QList<QVariant> &Values);
    static int execInsertSql(const QString &dbPAth, const QString &tableName, const QString &field, const QVariant &value);
    static int execInsertSqlIfNotExists(const QString &dbPAth, const QString &tableName, const QString &field, const QVariant &value);
    static int getFirstId(const QString &dbPAth, const QString &tableName, const QString &field, const QVariant &value);
    static QSqlRecord getFirstRecord(const QString &dbPAth,const QString &sql);
    static void getFirstFieldValuesListAsStrings(const QString &dbPAth, const QString &sql, QStringList *firstFieldValuesList);
};

#endif // MNQUERY_H
