#include "mnbook.h"

QString MNBook::tableName() const
{
    return m_tableName;
}

void MNBook::setTableName(const QString &tableName)
{
    m_tableName = tableName;
}

QString MNBook::dbPath() const
{
    return m_dbPath;
}

void MNBook::setDbPath(const QString &dbPath)
{
    m_dbPath = dbPath;
}

QSqlRecord MNBook::record() const
{
    return m_record;
}

void MNBook::setRecord(const QSqlRecord &record)
{
    m_record = record;
}

QString MNBook::sqlPreperedInsert() const
{
    return m_sqlPreperedInsert;
}

void MNBook::setSqlPreperedInsert(const QString &sqlPreperedInsert)
{
    m_sqlPreperedInsert = sqlPreperedInsert;
}

void MNBook::createRecord()
{
    QSqlRecord rcd;
    rcd.append(QSqlField("ID",QVariant::Int));
    rcd.append(QSqlField(wordName(),QVariant::String));
    rcd.append(QSqlField(wordIdName(),QVariant::Int));
   setRecord(rcd);
}

QString MNBook::wordName() const
{
    return "word";
}

QString MNBook::wordIdName() const
{
    return "wordId";
}


bool MNBook::createTable()
{
    return MNQuery::createTable(dbPath(),record(),tableName());
}

int MNBook::insert(const QString &word, const int &wordID)
{
    QString sql=sqlPreperedInsert();
    QList<QVariant> list;
    list<<word<<wordID;
    MN_WARNING(sql);
    return  MNQuery::execPreparedInsertSql(dbPath(),sql,list);
}

MNBook::MNBook(const int &bkId)
{
    setTableName("B"+QString::number(bkId));
    createRecord();
    setDbPath(MNPathes::getDbBookPath(bkId));
    setSqlPreperedInsert("INSERT INTO "+tableName()+"("+wordName()+","+wordIdName()+") "+
                         "VALUES(:"+wordName()+",:"+
                         wordIdName()+");"
                );
}



