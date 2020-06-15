#include "mnbooklist.h"


MNBookList::MNBookList()
{

}

QString MNBookList::getBkDbSourcePath(const QString &bkListDbSourcePath, int bkId)
{
    QSqlQuery qrBooksList(QSqlDatabase::database(bkListDbSourcePath));
    QString sql="select * from [0bok] where bkid ="+QString::number(bkId);
    qrBooksList.exec(sql);
    if(!qrBooksList.first()){
        return "";
    }
    int archNo=qrBooksList.record().field("Archive").value().toInt();
    if(archNo!=0){//book in archive
      QDir dir(QFileInfo(bkListDbSourcePath).absolutePath());
      if(!dir.cdUp()){

          return "";
      }
      QString path= QDir::cleanPath(dir.path() + QDir::separator() + "books"+
                                     QDir::separator()+"Archive"+QDir::separator()+
                                     QString::number(archNo)+".mdb");
      return path;
    }else{
     QString bkDir = QString::number(bkId % 10);
     QDir dir(QFileInfo(bkListDbSourcePath).absolutePath());
     if(!dir.cdUp()){
         return "";
     }
     QString path= QDir::cleanPath(dir.path() + QDir::separator() + "books"+
                                    QDir::separator()+bkDir+QDir::separator()+
                                    QString::number(bkId)+".mdb");
     return path;
    }

}

QSqlRecord MNBookList::createRecord()
{
    QSqlRecord rcd;
    MNRecord::initRecord(rcd);
    rcd.append(QSqlField("title",QVariant::String));
    rcd.append(QSqlField("catId",QVariant::Int));
    rcd.append(QSqlField("bkId",QVariant::Int));
    rcd.append(QSqlField("info",QVariant::String));
    rcd.append(QSqlField("authId",QVariant::Int));
    rcd.append(QSqlField("selected",QVariant::Int));
    rcd.append(QSqlField("exists",QVariant::Int));
    rcd.append(QSqlField("version",QVariant::Int));

    return rcd;


}

QString MNBookList::getTableName()
{
    return TABLE_NAME;
}

QMap<QString, QString> MNBookList::createFieldsMap()
{
 QMap<QString,QString> map;
 map["title"]="bk";
 map["catId"]="cat";
 map["bkId"]="bkid";
 map["info"]="betaka";
 map["authId"]="authno";

 return map;
}
/**
 * @brief MNBookList::importBook return the new inserted id
 * @param bkListDbSourcePath
 * @param bkListDbDestPath
 * @param bkId the mdb source book id
 * @return normal
 */
int MNBookList::importBook(QString bkListDbSourcePath,QString bkListDbDestPath,int bkId )
{
    QSqlQuery qrbkListDbSource(QSqlDatabase::database(bkListDbSourcePath));
    qrbkListDbSource.exec("select * from [0bok] where bkid="+QString::number(bkId));
    if(qrbkListDbSource.first()){
        MN_SUCCESS(qrbkListDbSource.record().field(1).value().toString());
        QMap<QString,QString> map = MNBookList::createFieldsMap();
        QSqlRecord rcd =qrbkListDbSource.record();
        QSqlQuery qrBkListDest =QSqlQuery(QSqlDatabase::database(bkListDbDestPath));
        //check if the book exists
        int id=MNQuery::getFirstId(bkListDbDestPath,TABLE_NAME,"bkid ="+QString::number(bkId));
        if(id!=0) return id;
        return MNQuery::insertRecord(rcd,qrBkListDest,TABLE_NAME,
                           bkListDbDestPath+".txt",map);
        //TODO: update id
        //TODO: test getFirstId

    }else return 0;

}

bool MNBookList::updateAuthorID(int bkID, int authID)
{
    QMap<QString,QVariant> map;
    map["authid"]=authID;
    return MNQuery::updateRecord(MNPathes::getdbBooksListPath(),TABLE_NAME,"ID="+QString::number(bkID),map);

}

bool MNBookList::createTable()
{
 return MNQuery::createTable(MNPathes::getdbBooksListPath(),createRecord(),TABLE_NAME);
}


