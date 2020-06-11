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
};

#endif // MNQUERY_H