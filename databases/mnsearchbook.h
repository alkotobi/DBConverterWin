#ifndef MNSEARCHBOOK_H
#define MNSEARCHBOOK_H
#include <QString>
#include <QMap>
#include "mnrecord.h"
#include "log.h"
#include "./imports/mnpathes.h"
#include "mnquery.h"
#include "databases/mntable.h"
#include "./databases/mnmidtableslink.h"
#include "./databases/mnwords.h"

class MNSearchBook
{
    int m_bkId;
    QString m_dbPath;
    QString m_tableName;
    MNMidleTableLink searchBook;
public:
    MNSearchBook(const int &bkId);
    int bkId() const;
    void setBkId(int bkId);
    QString dbPath() const;
    void setDbPath(const QString &dbPath);
    QString tableName() const;
    void setTableName(const QString &tableName);
    bool createTable();
    int linkBookToWord(const int &idBook,const int &idWord);
};

#endif // MNSEARCHBOOK_H
