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

QString MNBook::wordNormName(){
    return "word_norm";
}

QString MNBook::wordTachkilName(){
    return "tachkil";
}

void MNBook::createRecord()
{
    QSqlRecord rcd;
    rcd.append(QSqlField("ID",QVariant::Int));
    rcd.append(QSqlField(wordName(),QVariant::String));
    rcd.append(QSqlField(wordNormName(),QVariant::String));
    rcd.append(QSqlField(wordTachkilName(),QVariant::String));
    //rcd.append(QSqlField(wordIdName(),QVariant::Int));
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

int MNBook::insert(const QString &word,const QString &wordNorm,const QString &tachkil)
{
    QString sql=sqlPreperedInsert();
    QList<QVariant> list;
    list<<word<<wordNorm<<tachkil;
    MN_WARNING(sql);
    return  MNQuery::execPreparedInsertSql(dbPath(),sql,list);
}
/**
 * @brief MNBook::getWordsList dont forget to delete the pointer after call this
 * @param idFirst
 * @param WordsCount
 * @return
 */
void MNBook::getWordsList(const int &idFirst, const int &WordsCount,QStringList *valuesListAsStrings)
{
    QString sql ="SELECT "+wordName()+" from "+tableName()+" where ID>="+QString::number(idFirst)+
            " limit "+QString::number(WordsCount);
    MNQuery::getFirstFieldValuesListAsStrings(dbPath(),sql,valuesListAsStrings);
}

MNBook::MNBook(const int &bkId,QString path)
{
    setTableName("B"+QString::number(bkId));
    createRecord();
    setDbPath(path);
    setSqlPreperedInsert("INSERT INTO "+tableName()+"("+wordName()+","+wordNormName()+","+wordTachkilName()+") "+
                         "VALUES(:"+wordName()+",:"+
                         wordNormName()+",:"+
                         wordTachkilName()+");"
                );
}



