#ifndef MNCAT_H
#define MNCAT_H

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
#include "./databases/mnmidtableslink.h"

class MNCat
{
public:
    MNCat();
    inline static QString TABLE_NAME="cat";
    static QSqlRecord createRecord();
    static QMap<QString, QString> createFieldsMap();
    static int importCat(QString bkListDbSourcePath, QString bkListDbDestPath, int bkId);
    static bool importAllCat(QString bkListDbSourcePath);
};

#endif // MNCAT_H
