#include "mncat.h"

MNCat::MNCat()
{

}

QSqlRecord MNCat::createRecord()
{
    QSqlRecord rcd;
    QSqlField fld;
    MNRecord::initRecord(rcd);
    rcd.append(QSqlField("name",QVariant::String));
    rcd.append(QSqlField("info",QVariant::String));
    rcd.append(QSqlField("catId",QVariant::Int));
    fld = QSqlField("selected",QVariant::Int);
    fld.setValue(0);
    rcd.append(fld);
    fld=QSqlField("version",QVariant::Int);
    fld.setValue(0);
    rcd.append(fld);
    return rcd;
}

QMap<QString, QString> MNCat::createFieldsMap()
{
    QMap<QString,QString> map;
    map["name"]="name";
    map["catId"]="id";
    return map;
}





bool MNCat::importAllCat(QString bkListDbSourcePath)
{
    QSqlQuery qrbkListDbSource(QSqlDatabase::database(bkListDbSourcePath));
    QSqlQuery qrbkListDbDest(QSqlDatabase::database(MNPathes::getdbBooksListPath()));
    qrbkListDbSource.exec("select * from [0cat] ORDER BY catord");
    int prevID = 0;
    QString sql ="insert into "+TABLE_NAME+" (name,catID) VALUES (:name,:catID)";
    while(qrbkListDbSource.next()){
    qrbkListDbDest.prepare(sql);
    qrbkListDbDest.bindValue(":name",qrbkListDbSource.record().field("name").value());
    qrbkListDbDest.bindValue(":catID",qrbkListDbSource.record().field("id").value());
    qrbkListDbDest.exec();
    int idCat = qrbkListDbDest.lastInsertId().toInt();
    if(qrbkListDbSource.record().field("Lvl").value().toInt()!=0){
        MNMidleTableLink(MNPathes::getdbBooksListPath(),MNCat::TABLE_NAME,MNCat::TABLE_NAME).
                linkLeftToRight(idCat,prevID);
    }else{
        MNMidleTableLink(MNPathes::getdbBooksListPath(),MNCat::TABLE_NAME,MNCat::TABLE_NAME).
                linkLeftToRight(idCat,0);
                prevID=idCat;
    }

    }

    return  true;
}

int MNCat::getSourceCatId(const int &bkId)
{
     QSqlQuery qrbkListDbDest(QSqlDatabase::database(MNPathes::getdbBooksListPath()));
     qrbkListDbDest.exec("select catId from booksList where id="+QString::number(bkId));
     if(qrbkListDbDest.first()){
             QString id= qrbkListDbDest.record().field(0).value().toString();
             qrbkListDbDest.exec("select ID from cat where catid="+id);
             if (qrbkListDbDest.first()){
                 return qrbkListDbDest.record().field(0).value().toInt();
             }

     }
     return 0;
}

bool MNCat::createTable()
{
 return CREATE_TABLE;
}

//TODO order staff
