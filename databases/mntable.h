#ifndef MNTABLE_H
#define MNTABLE_H
#include <QString>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlField>
#include <QMap>
#include "mnrecord.h"
#include "log.h"
#include "mnquery.h"
#include "./imports/mnpathes.h"


#define CREATE_TABLE  MNQuery::createTable(MNPathes::getdbBooksListPath(),createRecord(),TABLE_NAME)

class MNTable
{

public:

};

#endif // MNTABLE_H
