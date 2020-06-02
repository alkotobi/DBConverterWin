#ifndef MNIMPORT_H
#define MNIMPORT_H
#include "mnsql.h"
#include <QSqlError>
#include <QFileDialog>
#include <QObject>
#include "log.h"
#include "mnpathes.h"
#include "mndb.h"

class MNImport
{
public:
    MNImport();
    static bool convertMultiAccessToSqlite(QStringList fileNames, QString destDir);
    static bool convertAccessToSqlite(QString &fileName, QString destDir);
    static bool convertTable(QString tableName, QString sourceDbName,QString destDbName);
};

#endif // MNIMPORT_H
