#ifndef MNBOOKLIST_H
#define MNBOOKLIST_H
#include <QString>
#include <QSqlQuery>
#include <QDir>
#include <QSqlRecord>
#include <QSqlField>
#include <QMap>
#include "mnrecord.h"
#include "log.h"
#include "./imports/mnpathes.h"
#include "mnquery.h"


    static const QString BOOKS_LIST="booksList";
class MNBookList
{
public:
    MNBookList();

    static QString getBkDbSourcePath(const QString &bkListDbSourcePath,int bkId);
    static QSqlRecord createRecord();
    static QMap<QString,QString> createFieldsMap();
    static int importBook(QString bkListDbSourcePath,QString bkListDbDestPath,int bkId);
};

#endif // MNBOOKLIST_H
