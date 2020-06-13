#ifndef MNBOOKSCAT_H
#define MNBOOKSCAT_H

#include <QString>
#include <QSqlQuery>
#include <QDir>
#include <QSqlRecord>
#include <QSqlField>
#include <QMap>
#include "mnrecord.h"
#include "log.h"
#include "mnquery.h"
#include "./imports/mnpathes.h"


class MNBooksCat
{
public:
    MNBooksCat();
    static QSqlRecord createRecord();
    static QMap<QString, QString> createFieldsMap();
};

#endif // MNBOOKSCAT_H
