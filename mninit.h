#ifndef MNINIT_H
#define MNINIT_H
#include <QSqlRecord>
#include <QSqlField>
#include "MNConst.h"
#include "./imports/mnpathes.h"
#include "./imports/mndb.h"


class MNInit
{
public:
    MNInit();
    static void initRecord(QSqlRecord &rcd);
    static void init();
};

#endif // MNINIT_H
