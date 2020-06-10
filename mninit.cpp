#include "mninit.h"

MNInit::MNInit()
{

}

void MNInit::initRecord(QSqlRecord &rcd)
{
    QSqlField fld=QSqlField(FLD_ID,QVariant::Int);
    fld.setValue(-1);
    rcd.append(fld);
    fld = QSqlField(FLD_ID_PARENT,QVariant::Int);
    fld.setValue(-1);
    rcd.append(fld);
}

void MNInit::init()
{
     MNPathes::createAppDataDirStructre();
     MNDb::createLocalDbs();
}

