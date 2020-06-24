#include "mnpage.h"

QString MNPage::tableName() const
{
    return m_tableName;
}

void MNPage::setTableName(const QString &tableName)
{
    m_tableName = tableName;
}

QString MNPage::dbPath() const
{
    return m_dbPath;
}

void MNPage::setDbPath(const QString &dbPath)
{
    m_dbPath = dbPath;
}

QSqlRecord MNPage::record() const
{
    return m_record;
}

void MNPage::setRecord(const QSqlRecord &record)
{
    m_record = record;
}

void MNPage::createRecord()
{
   QSqlRecord rcd;
   rcd.append(QSqlField("ID",QVariant::Int));
   rcd.append(QSqlField(pageNoName(),QVariant::Int));
   rcd.append(QSqlField(tomeName(),QVariant::Int));
   rcd.append(QSqlField(startFromWordName(),QVariant::Int));
   rcd.append(QSqlField(wordsCountName(),QVariant::Int));
   setRecord(rcd);
}

QString MNPage::pageNoName() const
{
    return "pageNo";
}

QString MNPage::startFromWordName() const
{
    return "startFromWord";
}

QString MNPage::wordsCountName() const
{
    return "wordsCount";
}

QString MNPage::tomeName() const
{
    return "tome";
}

bool MNPage::createTable()
{
    return MNQuery::createTable(dbPath(),record(),tableName());
}

bool MNPage::insert(const int &pageNo,const int &tome, const int &startFrom, const int &wordsCount)
{
    QString sql="INSERT INTO "+tableName()+"("+pageNoName()+","+tomeName()+","+startFromWordName()+","+wordsCountName()+") "+
            "VALUES("+QString::number(pageNo)+","+
            QString::number(tome)+","+
            QString::number(startFrom)+","+
            QString::number(wordsCount)+");";
    MN_WARNING(sql);
    return  MNQuery::execSQl(dbPath(),sql);
}

void MNPage::getPage(const int &pageNo, const int &tome,PageInfo *pgInfo)
{

    QString sql = "SELECT * from "+tableName()+" where "+pageNoName()+"="+
            QString::number(pageNo)+" and "+tomeName()+"="+QString::number(tome);
    QSqlRecord rcd = MNQuery::getFirstRecord(dbPath(),sql);
    if(rcd.count()>0){
        pgInfo->ID = rcd.field(0).value().toInt();
        pgInfo->pageNo=rcd.field(pageNoName()).value().toInt();
        pgInfo->tomeNo=rcd.field(tomeName()).value().toInt();
        pgInfo->startFrom=rcd.field(startFromWordName()).value().toInt();
        pgInfo->wordsCount=rcd.field(wordsCountName()).value().toInt();

    }

}

MNPage::MNPage(const int &bkId)
{
    setTableName("P"+QString::number(bkId));
    createRecord();
    setDbPath(MNPathes::getDbBookPath(bkId));
}


