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
      QDir dir(bkListDbSourcePath);
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
    MNInit::initRecord(rcd);
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
