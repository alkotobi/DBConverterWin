#ifndef MNDB_H
#define MNDB_H

#include <QString>
#include <QSqlDatabase>

class MNDb
{
public:
    MNDb();
    static bool openMsAccessDb(QString dbPath);
    static bool openSqliteDb(QString dbPath);
};

#endif // MNDB_H
