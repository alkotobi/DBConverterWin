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
    QSqlRecord m_record;
    int bkId;
public:
    QString dbPath;
    MNIndex(const int &bkId);
    QString tableName() const;
    void setTableName(const QString &tableName);
    QSqlRecord record() const;
    void setRecord(const QSqlRecord &record);
    void createRecord();
    QString pageNoName() const;
    QString idParentName() const;
    QString titleName() const;
    bool createTable();
    int insert(const int &pageNo, const int &idParent, const QString &title);

    bool importAllInd(QString bkDbSourcePath);
};

#endif // MNINDEX_H
