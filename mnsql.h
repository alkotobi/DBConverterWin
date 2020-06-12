#ifndef MNSQL_H
#define MNSQL_H
#include "QString"
#include "QSqlRecord"
#include "QSqlField"
#include <QMap>
#include <QSqlDatabase>
#include <QSqlQuery>


struct PreparedQueryResult{
public:
    QString preparedSql;
    QMap<QString,QVariant> values;

};
QString insetSql(const QSqlRecord &rcd,QString tableName);

class MNSql{

public:
    static QString sqlCreateTable(const QSqlRecord &rcd, QString tableName);
    static PreparedQueryResult sqlInsertPrepared(const QSqlRecord &rcd, QString tableName, QMap<QString, QString> *map);
    static QString sqlUpdatePrepared(const QString &tableName, const QString &whereSQl, const QMap<QString,QVariant> &namesAndValues);
};


#endif // MNSQL_H
