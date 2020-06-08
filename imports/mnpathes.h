#ifndef MNPATHES_H
#define MNPATHES_H
#include <QString>
#include <QDir>
#include <QFileInfo>
#include <QStandardPaths>
#include <QFileDialog>

class MNPathes
{
public:
    MNPathes();
    static QString combinePathes(const QString& path1, const QString& path2);
    static QString getFileNameWithExt(QString path);
    static bool createDirStructur();
    static bool createAppDataDir();
    static QString getKotobDir();
    static QString getAppDataDir();
    static bool createKotobDir();
    static QString getKotobDbPath(QString KotobDbName);
    static QString getFileName(QString path);
    static QStringList getFilesPathes();
    static bool createAppDataDirStructre();
    static QString getdbBooksListPath();
};

#endif // MNPATHES_H
