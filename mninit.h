#ifndef MNINIT_H
#define MNINIT_H

#include "./imports/mnpathes.h"
#include "./imports/mndb.h"
#include "mnsql.h"
#include "./databases/mnbooklist.h"
#include "./databases/mnauthor.h"
#include "./databases/mnmidtableslink.h"
#include "./databases/mncat.h"


class MNInit
{
public:
    MNInit();
    static void initRecord(QSqlRecord &rcd);
    static void init();
    static bool createLocalDbs();
};

#endif // MNINIT_H
