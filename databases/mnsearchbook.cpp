#include "mnsearchbook.h"

int MNSearchBook::bkId() const
{
    return m_bkId;
}

void MNSearchBook::setBkId(int bkId)
{
    m_bkId = bkId;
}


QString MNSearchBook::dbPath() const
{
    return m_dbPath;
}

void MNSearchBook::setDbPath(const QString &dbPath)
{
    m_dbPath = dbPath;
}

QString MNSearchBook::tableName() const
{
    return m_tableName;
}

void MNSearchBook::setTableName(const QString &tableName)
{
    m_tableName = tableName;
}

bool MNSearchBook::createTable()
{
    return searchBook.createTable();
}

int MNSearchBook::linkBookToWord(const int &idBook, const int &idWord)
{
    return searchBook.linkLeftToRight(idBook,idWord);
}

MNSearchBook::MNSearchBook(const int &bkId)
    :searchBook(MNPathes::getdbSearchPath(),"T"+QString::number(bkId),MNWords::TABLE_NAME)
{
    setBkId(bkId);
    setDbPath(MNPathes::getdbSearchPath());
    setTableName("T"+QString::number(bkId));
}
