#ifndef MNBOOKLIST_H
#define MNBOOKLIST_H
#include <QString>
#include <QSqlQuery>
#include <QDir>
#include <QSqlRecord>
#include <QSqlField>
#include "mninit.h"
#include <QMap>


    static const QString BOOKS_LIST="booksList";
class MNBookList
{
public:
    MNBookList();

    static QString getBkDbSourcePath(const QString &bkListDbSourcePath,int bkId);
    static QSqlRecord createRecord();
    static QMap<QString,QString> createFieldsMap();
    static bool importBook(QString bkListDbSourcePath,QString bkListDbDestPath,int bkId);
};

#endif // MNBOOKLIST_H
