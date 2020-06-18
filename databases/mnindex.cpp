#include "mnindex.h"

QString MNIndex::tableName() const
{
    return m_tableName;
}

void MNIndex::setTableName(const QString &tableName)
{
    m_tableName = tableName;
}

QString MNIndex::dbPath() const
{
    return m_dbPath;
}

void MNIndex::setDbPath(const QString &dbPath)
{
    m_dbPath = dbPath;
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
    return MNQuery::createTable(dbPath(),record(),tableName());
}

bool MNIndex::insert(const int &pageNo, const int &idParent, const QString &title)
{
    QString sql="INSERT INTO "+tableName()+"("+pageNoName()+","+idParentName()+","+titleName()+") "+
            "VALUES("+QString::number(pageNo)+","+
            QString::number(idParent)+",:"+
            title+");";
    MN_WARNING(sql);
    QSqlQuery query(dbPath());
    query.prepare(sql);
    query.addBindValue(title);
    return  query.exec();
}

MNIndex::MNIndex(const int &bkId)
{
    setTableName("I"+QString::number(bkId));
    createRecord();
    setDbPath(MNPathes::getDbBookPath(bkId));
}
