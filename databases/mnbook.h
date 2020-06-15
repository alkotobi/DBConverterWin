#ifndef MNBOOK_H
#define MNBOOK_H
#include <QString>
#include <QMap>
#include "mnrecord.h"
#include "log.h"
#include "mnquery.h"
#include "./imports/mnpathes.h"
#include "./databases/mntable.h"


class MNBook
{
    QString m_tableName;
    QString m_dbPath;
    QSqlRecord m_record;
    QString m_sqlPreperedInsert;
public:
    QString tableName() const;
    void setTableName(const QString &tableName);
    QString dbPath() const;
    void setDbPath(const QString &dbPath);
    QSqlRecord record() const;
    void setRecord(const QSqlRecord &record);
    void createRecord();
    QString wordName() const;
    QString wordIdName() const;
    bool createTable();
    QString sqlPreperedInsert() const;
    void setSqlPreperedInsert(const QString &sqlPreperedInsert);
    MNBook(const int &bkId);
    int insert(const QString &word, const int &wordID);
};

#endif // MNBOOK_H
