#include "mnindex.h"

QString MNIndex::tableName() const
{
    return m_tableName;
}

void MNIndex::setTableName(const QString &tableName)
{
    m_tableName = tableName;
}


QSqlRecord MNIndex::record() const
{
    return m_record;
}

void MNIndex::setRecord(const QSqlRecord &record)
{
    m_record = record;
}

void MNIndex::createRecord()
{
    QSqlRecord rcd;
    rcd.append(QSqlField("ID",QVariant::Int));
    rcd.append(QSqlField(idParentName(),QVariant::Int));
    rcd.append(QSqlField(pageNoName(),QVariant::Int));
    rcd.append(QSqlField(titleName(),QVariant::String));
    setRecord(rcd);
}

QString MNIndex::pageNoName() const
{
    return "pageNo";
}

QString MNIndex::idParentName() const
{
    return "idParent";
}

QString MNIndex::titleName() const
{
    return "title";
}

bool MNIndex::createTable()
{
    return MNQuery::createTable(dbPath,record(),tableName());
}

int MNIndex::insert(const int &pageNo, const int &idParent, const QString &title)
{
    QString sql="INSERT INTO "+tableName()+"("+pageNoName()+","+idParentName()+","+titleName()+") "+
            "VALUES("+QString::number(pageNo)+","+
            QString::number(idParent)+",:"+
            titleName()+");";
    MN_WARNING(sql);
    QSqlQuery query(QSqlDatabase::database(dbPath));
    query.prepare(sql);
    query.addBindValue(title);
      if(query.exec()) return query.lastInsertId().toInt();else return 0;
}

bool MNIndex::importAllInd(QString bkDbSourcePath)
{
    QSqlQuery qrbkSource(QSqlDatabase::database(bkDbSourcePath));
    QString title;
    QString sql;
    if(QSqlDatabase::database(bkDbSourcePath).tables().contains("title")){
      sql="select * from title ORDER BY id,sub;";
    }else{
      sql="select * from t"+QString::number(bkId)+" ORDER BY id,sub;";
    }
    qrbkSource.exec(sql);
    QMap<int,int> lvls;
    while(qrbkSource.next()){
    title =qrbkSource.record().field("tit").value().toString();
    int id = 0;
    int lvl = qrbkSource.record().field("lvl").value().toInt();
    if(lvl>1){
        int prevLvl=0;
        foreach(int lvl1,lvls.keys()){
           if(lvl1>=lvl){
               break;
           }else prevLvl = lvl1;
        }
        id=insert(qrbkSource.record().field("id").value().toInt(),lvls[prevLvl],title);
        lvls.insert(lvl,id);
    }else{
        id=insert(qrbkSource.record().field("id").value().toInt(),0,title);
        lvls.clear();
        lvls.insert(lvl,id);
    }

    }

    return  true;
}

MNIndex::MNIndex(const int &bkId)
{
    setTableName("I"+QString::number(bkId));
    createRecord();
    dbPath=MNPathes::getDbBookPath(bkId);
    this->bkId=bkId;
}
