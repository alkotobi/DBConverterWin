#include "mnpathes.h"

MNPathes::MNPathes()
{

}

QString MNPathes::combinePathes(const QString& path1, const QString& path2)
{
    return QDir::cleanPath(path1 + QDir::separator() + path2);
}

QString MNPathes::getFileNameWithExt(QString path)
{
   return QFileInfo(QFile(path).fileName()).fileName();
}
