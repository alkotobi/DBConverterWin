#include "databases/mnmidtableslink.h"

QString MNMidleTableLink::tableName() const
{
    return m_tableName;
}

void MNMidleTableLink::setTableName(const QString &tableName)
{
    m_tableName = tableName;
}

QString MNMidleTableLink::leftIdName() const
{
    return m_leftId;
}

void MNMidleTableLink::setLeftIdName(const QString &LeftId)
{
    m_leftId = LeftId;
}

QString MNMidleTableLink::rightIdName() const
{
    return m_rightId;
}

void MNMidleTableLink::setRightIdName(const QString &RightId)
{
    m_rightId = RightId;
}

QSqlRecord MNMidleTableLink::record() const
{
    return m_record;
}

void MNMidleTableLink::setRecord(const QSqlRecord &record)
{
    m_record = record;
}

QString MNMidleTableLink::dbPath() const
{
    return m_dbPath;
}

void MNMidleTableLink::setDbPath(const QString &dbPath)
{
    m_dbPath = dbPath;
}

bool MNMidleTableLink::createTable()
{
   return MNQuery::execSQl(dbPath(),MNSql::sqlCreateTable(record(),tableName()));
}

bool MNMidleTableLink::isNeedSwitch() const
{
    return m_isNeedSwitch;
}

void MNMidleTableLink::setIsNeedSwitch(bool isNeedSwitch)
{
    m_isNeedSwitch = isNeedSwitch;
}

MNMidleTableLink::MNMidleTableLink(const QString &dbPath,const QString &leftTableName,const QString &rightTableName )
{
    setDbPath(dbPath);
    //first check if table already exists  to correspond the correct right and left side
    if(!MNQuery::tableExists(dbPath,rightTableName+"_"+leftTableName)){
    setLeftIdName(leftTableName+"ID");
    setRightIdName(rightTableName+"ID");
    setTableName(leftTableName+"_"+rightTableName);
    setIsNeedSwitch(false);
    }else{
    setLeftIdName(rightTableName+"ID");
    setRightIdName(leftTableName+"ID");
    setTableName(rightTableName+"_"+leftTableName);
    setIsNeedSwitch(true);
    }
    createRecord();
}

 void MNMidleTableLink::createRecord()
{
    QSqlRecord rcd;
    rcd.append(QSqlField(leftIdName(),QVariant::Int));
    rcd.append(QSqlField(rightIdName(),QVariant::Int));
    setRecord(rcd);
}

 /**
 * @brief MNMidleTableLink::linkLeftToRight dont forget the situation where the fields created in opposit order
 * @param leftVal
 * @param rightVal
 * @return
 */
bool MNMidleTableLink::linkLeftToRight(int leftVal, int rightVal)
{
    //TODO: make faster
    QSqlQuery query(QSqlDatabase::database(dbPath()));
    QMap<QString,QVariant> map;
    if(!isNeedSwitch()){
    map[leftIdName()]=leftVal;
    map[rightIdName()]=rightVal;
    }else{
    map[leftIdName()]=rightVal;
    map[rightIdName()]=leftVal;
    }
    QString sql =MNSql::sqlInsertPrepared(tableName(),map);
   // sql ="INSERT INTO "+tableName()+" ("+leftIdName()+","+rightIdName()+")"
   //         "VALUES( "+QString::number(leftVal)+",	"+QString::number(rightVal)+");";
    return MNQuery::execPreparedSql(dbPath(),sql,map);


}
