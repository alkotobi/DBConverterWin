#ifndef MNAUTHOR_H
#define MNAUTHOR_H
#include <QString>
#include <QSqlQuery>
#include <QDir>
#include <QSqlRecord>
#include <QSqlField>
#include <QMap>
#include "mnrecord.h"
#include "log.h"
#include "mnquery.h"
#include "./imports/mnpathes.h"

static QString AUTHOR="author";
class MNAuthor
{
public:
    MNAuthor();
    static QSqlRecord createRecord();
    static QMap<QString,QString> createFieldsMap();
    static int importAuthor(QString bkListDbSourcePath,QString bkListDbDestPath,int bkId);
};

#endif // MNAUTHOR_H