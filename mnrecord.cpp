#include "mnrecord.h"


void MNRecord::initRecord(QSqlRecord &rcd)
{
    QSqlField fld=QSqlField(FLD_ID,QVariant::Int);
    fld.setValue(0);
    rcd.append(fld);
//    fld = QSqlField(FLD_ID_PARENT,QVariant::Int);
//    fld.setValue(0);
//    rcd.append(fld);
}


