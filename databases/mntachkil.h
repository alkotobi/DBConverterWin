#ifndef MNTACHKIL_H
#define MNTACHKIL_H
#include <QString>
#include <QMap>
#include "mnrecord.h"
#include "log.h"
#include "./imports/mnpathes.h"
#include "mnquery.h"
#include "databases/mntable.h"

class MNTachkil
{
public:
    MNTachkil();
    inline static const QString TABLE_NAME="tachkil";
    inline static const QString FIELD_NAME="tachkil";
    static QSqlRecord createRecord();
    static bool createTable();
    static int insert(const QString &tachkil);
    static QString dbPath();
};

#endif // MNTACHKIL_H
