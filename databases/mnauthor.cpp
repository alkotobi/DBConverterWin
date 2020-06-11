#include "mnauthor.h"

MNAuthor::MNAuthor()
{

}

QSqlRecord MNAuthor::createRecord()
{
    QSqlRecord rcd;
    QSqlField fld;
    MNRecord::initRecord(rcd);
    rcd.append(QSqlField("shortName",QVariant::String));
    rcd.append(QSqlField("longName",QVariant::String));
    rcd.append(QSqlField("info",QVariant::String));
    rcd.append(QSqlField("hijri",QVariant::Int));
    rcd.append(QSqlField("authId",QVariant::Int));
    fld = QSqlField("selected",QVariant::Int);
    fld.setValue(0);
    rcd.append(fld);
    fld=QSqlField("version",QVariant::Int);
    fld.setValue(0);
    rcd.append(fld);

    return rcd;
}

QMap<QString, QString> MNAuthor::createFieldsMap()
{
    QMap<QString,QString> map;
    map["shortName"]="auth";
    map["longName"]="Lng";
    map["info"]="inf";
    map["hijri"]="AD";
    map["authId"]="authid";
    return map;
}



int MNAuthor::importAuthor(QString bkListDbSourcePath, QString bkListDbDestPath, int bkId)
{
    QSqlQuery qrbkListDbSource(QSqlDatabase::database(bkListDbSourcePath));
    QString authDbPath=MNPathes::getAuthDbSourcePath(bkListDbSourcePath);
    qrbkListDbSource.exec("select authno from [0bok] where bkid="+QString::number(bkId));
    if(qrbkListDbSource.first()){
        int authId=qrbkListDbSource.record().field(0).value().toInt();
        MN_SUCCESS(qrbkListDbSource.record().field(0).value().toString());
        QSqlQuery qrAuthDbSource(QSqlDatabase::database(authDbPath));
        //check if the author exists
        int id=MNQuery::getFirstId(bkListDbDestPath,AUTHOR,"authId ="+QString::number(authId));
        if(id!=0) return id;
        qrAuthDbSource.exec("select * from [Auth] where authid="+QString::number(authId));
        if(qrAuthDbSource.first()){
            QMap<QString,QString> map = createFieldsMap();
            QSqlRecord rcd =qrAuthDbSource.record();
            QSqlQuery qrBkListDest =QSqlQuery(QSqlDatabase::database(bkListDbDestPath));
            return MNQuery::insertRecord(rcd,qrBkListDest,AUTHOR,
                               bkListDbDestPath+".txt",map);
        }
    }
    return 0;
}
