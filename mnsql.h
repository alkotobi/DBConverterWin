#ifndef MNSQL_H
#define MNSQL_H
#include "QString"
#include "QSqlRecord"
#include "QSqlField"
#include <QMap>
#include <QSqlDatabase>
#include <QSqlQuery>


QString createTableSql(const QSqlRecord &rcd,QString tableName);
QString insetSql(const QSqlRecord &rcd,QString tableName);



#endif // MNSQL_H
