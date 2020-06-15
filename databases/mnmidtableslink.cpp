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
   bool success= MNQuery::execSQl(dbPath(),MNSql::sqlCreateTable(record(),tableName()));
   QList<QString> fieldsNames;
   fieldsNames.append(leftIdName());
   fieldsNames.append(rightIdName());
   QString indName=tableName()+"_"+ fieldsNames.join("_");
   success=success and MNQuery::createIndex(dbPath(),tableName(),indName,true,fieldsNames);
   return success;
}

bool MNMidleTableLink::isNeedSwitch() const
{
    return m_isNeedSwitch;
}

void MNMidleTableLink::setIsNeedSwitch(bool isNeedSwitch)
{
    m_isNeedSwitch = isNeedSwitch;
}

QString MNMidleTableLink::orderFldName() const
{
    return  ORDER_NAME;
}

MNMidleTableLink::MNMidleTableLink(const QString &dbPath,const QString &leftTableName,const QString &rightTableName )
{
    setDbPath(dbPath);
    //first check if table already exists  to correspond the correct right and left side
    if(!MNQuery::tableExists(dbPath,rightTableName+"_"+leftTableName)){
    setLeftIdName(leftTableName+"1ID");// i use 1ID and 2ID to solve the situation where leftTableName=rightTableName
    setRightIdName(rightTableName+"2ID");
    setTableName(leftTableName+"_"+rightTableName);
    setIsNeedSwitch(false);
    }else{
    setLeftIdName(rightTableName+"2ID");
    setRightIdName(leftTableName+"1ID");
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
    rcd.append(QSqlField(orderFldName(),QVariant::Int));
    setRecord(rcd);
}

 /**
 * @brief MNMidleTableLink::linkLeftToRight dont forget the situation where the fields created in opposit order
 * @param leftVal
 * @param rightVal
 * @return
 */
int MNMidleTableLink::linkLeftToRight(int leftVal, int rightVal)
{
    //TODO: make faster

    // check if link already exists and map fields
    QMap<QString,QVariant> map;
    QString where;
    if (isNeedSwitch()){
        where = leftIdName()+"="+QString::number(rightVal)+
                " and "+rightIdName()+"="+QString::number(leftVal);
        map[leftIdName()]=rightVal;
        map[rightIdName()]=leftVal;
    }else{
        where = leftIdName()+"="+QString::number(leftVal)+
                " and "+rightIdName()+"="+QString::number(rightVal);
        map[leftIdName()]=leftVal;
        map[rightIdName()]=rightVal;
    }
    int id=MNQuery::getFirstId(dbPath(),tableName(),where);
    if(id!=0) return id;
    // emd check link already exists and map fields

    QString sql =MNSql::sqlInsertPrepared(tableName(),map);
   // sql ="INSERT INTO "+tableName()+" ("+leftIdName()+","+rightIdName()+")"
   //         "VALUES( "+QString::number(leftVal)+",	"+QString::number(rightVal)+");";
    return MNQuery::execPreparedInsertSql(dbPath(),sql,map);
}


