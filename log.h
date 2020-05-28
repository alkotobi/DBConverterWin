#ifndef LOG_H
#define LOG_H

#include <QString>
#include <QDebug>
#include <QDateTime>
#include <QVariant>
#define STD_OUT QTextStream(stdout)
static QVariant timeStamp=0;
class Log
{

    static QString formatMessage(QString msg);
public:

    static void showError(QString msg);
    static void showWarning(QString msg);
    static void showInfo(QString msg);
    static void showSuccess(QString msg);
    static void setTimeStampToCurrent();
    static QVariant gettimeInterval();
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
