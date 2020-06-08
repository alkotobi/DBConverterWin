#ifndef MNINIT_H
#define MNINIT_H
#include <QSqlRecord>
#include <QSqlField>
#include "MNConst.h"


class MNInit
{
public:
    MNInit();
    static void initRecord(QSqlRecord &rcd);
};

#endif // MNINIT_H
