#ifndef MNAUTHOR_H
#define MNAUTHOR_H
#include <QString>
#include <QMap>
#include "mnrecord.h"
#include "log.h"
#include "mnquery.h"
#include "./imports/mnpathes.h"
#include "./databases/mntable.h"


class MNAuthor
{
public:
    MNAuthor();
    inline static QString TABLE_NAME="author";
    static QSqlRecord createRecord();
    static QMap<QString,QString> createFieldsMap();
    static int importAuthor(QString bkListDbSourcePath,QString bkListDbDestPath,int bkId);
    static bool createTable();
};

#endif // MNAUTHOR_H
