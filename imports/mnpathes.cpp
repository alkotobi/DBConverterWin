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



bool MNPathes::createAppDataDir()
{
    QStringList strs=  QStandardPaths::standardLocations(QStandardPaths::AppDataLocation);
    QDir dir;
    if( strs.count()!=0)
    if (!dir.exists(strs[0])){
        return  dir.mkpath(strs[0]);
    }

    return false;
}

QString MNPathes::getKotobDir()
{
    return QDir::cleanPath(getAppDataDir() + QDir::separator() + "kotob");

}
QString MNPathes::getdbBooksListPath()
{
    return QDir::cleanPath(getKotobDir() + QDir::separator() + "kotob.sqlite");

}

QString MNPathes::getAppDataDir()
{
    return  QStandardPaths::standardLocations(QStandardPaths::AppDataLocation)[0];

}

bool MNPathes::createKotobDir()
{
        QDir dir;
        return  dir.mkpath(getAppDataDir()+"/kotob/");
}

bool MNPathes::createAppDataDirStructre()
{
    createAppDataDir();
    return createKotobDir();

}

QStringList MNPathes::getFilesPathes()
{
    QFileDialog dialog;
    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setViewMode(QFileDialog::Detail);
    QStringList fileNames;
    if (dialog.exec())
        fileNames = dialog.selectedFiles();

    return  fileNames;
}

QString MNPathes::getFileName(QString path)
{
    QFileInfo fi(path);
    return  fi.fileName();
}

QString MNPathes::getKotobDbPath(QString KotobDbName)
{
    return getKotobDir()+KotobDbName;
}

QString MNPathes::getAuthDbSourcePath(const QString &bkListDbSourcePath)
{

    QDir dir(QFileInfo(bkListDbSourcePath).absolutePath());
    QString path= QDir::cleanPath(dir.path() +QDir::separator()+
                                   "special.mdb");
    return path;
}
