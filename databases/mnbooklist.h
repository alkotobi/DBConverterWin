#ifndef MNBOOKLIST_H
#define MNBOOKLIST_H
#include <QString>
#include <QMap>
#include "mnrecord.h"
#include "log.h"
#include "./imports/mnpathes.h"
#include "mnquery.h"
#include "databases/mntable.h"



class MNBookList
{
public:
    MNBookList();
    inline static const QString TABLE_NAME="booksList";
    static QString getBkDbSourcePath(const QString &bkListDbSourcePath,int bkId);
    static QSqlRecord createRecord() ;
    static QString getTableName() ;
    static QMap<QString,QString> createFieldsMap();
    static int importBook(QString bkListDbSourcePath,QString bkListDbDestPath,int bkId);
    static bool updateAuthorID(int bkID,int authID);
    static bool createTable();

};

#endif // MNBOOKLIST_H
