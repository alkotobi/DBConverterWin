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



int MNCat::importCat(QString bkListDbSourcePath, QString bkListDbDestPath, int bkId)
{
    QSqlQuery qrbkListDbSource(QSqlDatabase::database(bkListDbSourcePath));
    QString authDbPath=MNPathes::getAuthDbSourcePath(bkListDbSourcePath);
    qrbkListDbSource.exec("select authno from [0bok] where bkid="+QString::number(bkId));
    if(qrbkListDbSource.first()){
        int authId=qrbkListDbSource.record().field(0).value().toInt();
        MN_SUCCESS(qrbkListDbSource.record().field(0).value().toString());
        QSqlQuery qrAuthDbSource(QSqlDatabase::database(authDbPath));
        //check if the author exists
        int id=MNQuery::getFirstId(bkListDbDestPath,TABLE_NAME,"authId ="+QString::number(authId));
        if(id!=0) return id;
        qrAuthDbSource.exec("select * from [Auth] where authid="+QString::number(authId));
        if(qrAuthDbSource.first()){
            QMap<QString,QString> map = createFieldsMap();
            QSqlRecord rcd =qrAuthDbSource.record();
            QSqlQuery qrBkListDest =QSqlQuery(QSqlDatabase::database(bkListDbDestPath));
            return MNQuery::insertRecord(rcd,qrBkListDest,TABLE_NAME,
                               bkListDbDestPath+".txt",map);
        }
    }
    return 0;
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

//TODO order staff
