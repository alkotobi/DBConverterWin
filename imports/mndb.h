#ifndef MNDB_H
#define MNDB_H

#include <QString>
#include <QSqlDatabase>
#include <QStringList>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QSqlField>
#include <QMap>

#include "log.h"
#include "./imports/mnpathes.h"
#include "mnsql.h"
#include "mnrecord.h"
#include "mnquery.h"



class MNDb
{
    static bool exportAllTableData(QSqlQuery &querySource, QSqlQuery &queryDest,
                                  QString sourceTableName, QString logFilePath,QMap<QString,QString> *map=nullptr);

public:
    MNDb();
    static bool openMsAccessDb(QString dbPath);
    static bool openSqliteDb(QString dbPath);
    static QStringList getDbTableNames(QString dbPath);
    static bool startTransaction(QString dbPath);
    static bool commitTransaction(QString dbPath);
    static void closeDb(QString dbPath);
    static bool rollBackTransaction(QString dbPath);
    static bool execSQl(QString dbPath,QString sql);
    static bool makeSQliteDbFaster(QString dbPath);
//    static bool dbExportTable(QString sourceTableName, QString sourceAccessDbName, QString destSqliteDbName);
    static bool exportTable(QString sourceTableName, QString sourceAccessDbName, QString destSqliteDbName,QMap<QString,QString> *map=nullptr);

};

#endif // MNDB_H
