#ifndef MNMIDTABLESLINK_H
#define MNMIDTABLESLINK_H

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
#include "./databases/mntable.h"

class MNMidleTableLink
{
         QString m_tableName;
         QString m_leftId;
         QString m_rightId;
         QString m_dbPath;
         QSqlRecord m_record;
         bool m_isNeedSwitch =false;
         const QString ORDER_NAME="order";
public:
    MNMidleTableLink(const QString &dbPath, const QString &leftTableName, const QString &rightTableName);

     void createRecord();
     bool linkLeftToRight(int leftVal, int rightVal);
     QString tableName() const;
     void setTableName(const QString &tableName);
     QString leftIdName() const;
     void setLeftIdName(const QString &leftIdName);
     QString rightIdName() const;
     void setRightIdName(const QString &rightIdName);
     QSqlRecord record() const;
     void setRecord(const QSqlRecord &record);
     QString dbPath() const;
     void setDbPath(const QString &dbPath);
     bool createTable();
     /*!
      * \brief isNeedSwitch be carefall when the fields are created in the db in opposit order
      * \return
      */
     bool isNeedSwitch() const;
     void setIsNeedSwitch(bool isNeedSwitch);
     QString orderFldName() const;
};

#endif // MNMIDTABLESLINK_H
