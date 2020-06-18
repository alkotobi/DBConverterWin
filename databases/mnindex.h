#ifndef MNINDEX_H
#define MNINDEX_H
#include <QString>
#include <QMap>
#include "mnrecord.h"
#include "log.h"
#include "mnquery.h"
#include "./imports/mnpathes.h"
#include "./databases/mntable.h"

class MNIndex
{
    QString m_tableName;
    QString m_dbPath;
    QSqlRecord m_record;
public:
    MNIndex(const int &bkId);
    QString tableName() const;
    void setTableName(const QString &tableName);
    QString dbPath() const;
    void setDbPath(const QString &dbPath);
    QSqlRecord record() const;
    void setRecord(const QSqlRecord &record);
    void createRecord();
    QString pageNoName() const;
    QString idParentName() const;
    QString titleName() const;
    bool createTable();
    bool insert(const int &pageNo, const int &idParent, const QString &title);

};

#endif // MNINDEX_H
