#ifndef MNIMPORT_H
#define MNIMPORT_H


#include "log.h"
#include "mnpathes.h"
#include "mndb.h"

class MNImport
{
public:
    MNImport();
    static bool convertMultiAccessToSqlite(QStringList fileNames, QString destDir);
    static bool convertAccessToSqlite(QString &fileName, QString destDir);
    static bool dbExportTable(QString tableName, QString sourceDbName,QString destDbName);
    static bool dbExportTableData(QSqlQuery &querySource, QSqlQuery &queryDest, QString sourceTableName, QString logFilePath);
};

#endif // MNIMPORT_H
