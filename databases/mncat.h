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
#include "./databases/mntable.h"

class MNCat
{
public:
    MNCat();
    inline static QString TABLE_NAME="cat";
    static QSqlRecord createRecord();
    static QMap<QString, QString> createFieldsMap();
    static bool importAllCat(QString bkListDbSourcePath);
    static int getSourceCatId(const int &bkId);
    static bool createTable();
};

#endif // MNCAT_H
