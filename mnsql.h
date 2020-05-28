#ifndef MNSQL_H
#define MNSQL_H
#include "QString"
#include "QSqlRecord"
#include "QSqlField"
#include <QMap>

struct PreparedQueryResult{
public:
    QString preparedSql;
    QMap<QString,QVariant> values;

};
QString createTableSql(const QSqlRecord &rcd,QString tableName);
QString insetSql(const QSqlRecord &rcd,QString tableName);
PreparedQueryResult insertSqlPrepared(const QSqlRecord &rcd,QString tableName);


#endif // MNSQL_H
