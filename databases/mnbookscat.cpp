#include "mnbookscat.h"

MNBooksCat::MNBooksCat()
{

}

QSqlRecord MNBooksCat::createRecord()
{
    QSqlRecord rcd;
    QSqlField fld;
    MNRecord::initRecord(rcd);
    rcd.append(QSqlField("catName",QVariant::String));
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

QMap<QString, QString> MNBooksCat::createFieldsMap()
{
    QMap<QString,QString> map;
    map["catName"]="name";
    map["catId"]="id";
    return map;
}
