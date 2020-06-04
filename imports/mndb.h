#ifndef MNDB_H
#define MNDB_H

#include <QString>
#include <QSqlDatabase>
#include <QStringList>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QSqlField>

#include "log.h"


struct PreparedQueryResult{
public:
    QString preparedSql;
    QMap<QString,QVariant> values;

};

class MNDb
{
    static bool dbExportTableData(QSqlQuery &querySource, QSqlQuery &queryDest, QString sourceTableName, QString logFilePath);
    static PreparedQueryResult sqlInsertPrepared(const QSqlRecord &rcd, QString tableName);
    static QString sqlCreateTable(const QSqlRecord &rcd, QString tableName);
public:
    MNDb();
    static bool openMsAccessDb(QString dbPath);
    static bool openSqliteDb(QString dbPath);
    static QStringList getDbTableNames(QString dbPath);
    static bool dbStartTransaction(QString dbPath);
    static bool dbCommitTransaction(QString dbPath);
    static void dbClose(QString dbPath);
    static bool dbRollBackTransaction(QString dbPath);
    static bool dbExec(QString dbPath,QString sql);
    static bool makeSQliteDbFaster(QString dbPath);
    static bool dbExportTable(QString sourceTableName, QString sourceAccessDbName, QString destSqliteDbName);

};

#endif // MNDB_H
