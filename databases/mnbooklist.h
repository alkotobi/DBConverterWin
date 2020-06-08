#ifndef MNBOOKLIST_H
#define MNBOOKLIST_H
#include <QString>
#include <QSqlQuery>
#include <QDir>
#include <QSqlRecord>
#include <QSqlField>
#include "mninit.h"
#include <QMap>

class MNBookList
{
public:
    MNBookList();
    static QString getBkDbSourcePath(const QString &bkListDbSourcePath,int bkId);
    static QSqlRecord createRecord();
    static QMap<QString,QString> createFieldsMap();
};

#endif // MNBOOKLIST_H
