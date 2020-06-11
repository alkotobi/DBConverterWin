#ifndef MNRECORD_H
#define MNRECORD_H
#include <QSqlRecord>
#include <QSqlField>
#include <QSqlQuery>
#include <QSqlError>
#include "log.h"
#include "mnsql.h"

const QString FLD_ID="ID";
const QString FLD_ID_PARENT="IDParent";
class MNRecord
{
public:
    MNRecord();
    static void initRecord(QSqlRecord &rcd);
};

#endif // MNRECORD_H
