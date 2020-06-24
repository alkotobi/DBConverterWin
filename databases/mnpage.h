#ifndef MNPAGE_H
#define MNPAGE_H
#include <QString>
#include <QMap>
#include "mnrecord.h"
#include "log.h"
#include "mnquery.h"
#include "./imports/mnpathes.h"
#include "./databases/mntable.h"


class MNPage
{
    QString m_tableName;
    QString m_dbPath;
    QSqlRecord m_record;
public:
    typedef struct {
       int ID,pageNo,tomeNo,startFrom,wordsCount;
    }PageInfo;
    MNPage(const int &bkId);
    QString tableName() const;
    void setTableName(const QString &tableName);
    QString dbPath() const;
    void setDbPath(const QString &dbPath);
    QSqlRecord record() const;
    void setRecord(const QSqlRecord &record);
    void createRecord();
    QString pageNoName() const;
    QString startFromWordName() const;
    QString wordsCountName() const;
    QString tomeName() const;
    bool createTable();
    bool insert(const int &pageNo, const int &tome, const int &startFrom, const int &wordsCount);
    void getPage(const int &pageNo, const int &tome,PageInfo *pgInfo);

};

#endif // MNPAGE_H
