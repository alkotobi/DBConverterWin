#ifndef MNWORDS_H
#define MNWORDS_H
#include <QString>
#include <QMap>
#include "mnrecord.h"
#include "log.h"
#include "./imports/mnpathes.h"
#include "mnquery.h"
#include "databases/mntable.h"

class MNWords
{
public:
    MNWords();
    inline static const QString FIELD_NAME="word";
    inline static const QString TABLE_NAME="words";
    static QSqlRecord createRecord();
    static bool createTable();
    static QString dbPath();
    static int insert(const QString &word);
};

#endif // MNWORDS_H
