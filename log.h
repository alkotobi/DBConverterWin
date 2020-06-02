#ifndef LOG_H
#define LOG_H

#include <QString>
#include <QDebug>
#include <QDateTime>
#include <QVariant>
#include <QFile>
#include <QTextStream>

#define STD_OUT QTextStream(stdout)
static QVariant timeStamp=0;
static QString LOG_FILE_PATH="C:\\dev\\logs\\";
static QString MNERR_NoFileSelected="Did not select any file ";
static QString MNERR_CantOpenFile="cant Open Source DB ";
static QString MNERR_CantCreateTable="cant create table: ";
static QString MNERR_CantWriteData="cant insert data: ";
static QString MNERR_CantCommitTransaction="cant commit tarnsaction: ";
class Log
{

    static QString formatMessage(QString msg);
private:

public:

    static void showError(QString msg);
    static void showWarning(QString msg);
    static void showInfo(QString msg);
    static void showSuccess(QString msg);
    static void setTimeStampToCurrent();
    static QVariant gettimeInterval();
    static void logToFile(QString text,QString fileName);//write logs to text file in LOG_FILE_PATH location
    static void logErrToFileConsole(QString text,QString fileName);
    static QString getTxtFileNameFromDate();
};

#ifdef  QT_DEBUG
#define MN_ERROR(...) Log::showError( __VA_ARGS__ )
#define MN_WARNING(...) Log::showWarning( __VA_ARGS__ )
#define MN_INFO(...) Log::showInfo( __VA_ARGS__ )
#define MN_SUCCESS(...) Log::showSuccess( __VA_ARGS__ )
#else
#define MN_ERROR(...)
#define MN_WARNING(...)
#define MN_INFO(...)
#define MN_SUCCESS(...)
#endif
#endif // LOG_H
