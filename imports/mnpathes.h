#ifndef MNPATHES_H
#define MNPATHES_H
#include <QString>
#include <QDir>
#include <QFileInfo>

class MNPathes
{
public:
    MNPathes();
    static QString combinePathes(const QString& path1, const QString& path2);
    static QString getFileNameWithExt(QString path);
};

#endif // MNPATHES_H
