#ifndef MNNASS_H
#define MNNASS_H
#include <QString>
#include "log.h"

class MNNass
{
public:
    MNNass();
    struct Kalimat{
    public:
        QString tachkil;
        QString original;
        QString norm;
    };
    static QList<Kalimat> *getKalimat(const QString &nass) ;
};

#endif // MNNASS_H
