#include "log.h"




QString Log::formatMessage(QString msg)
{
    if(timeStamp==0) setTimeStampToCurrent();
    return QDateTime::currentDateTime().toString("dd/MM/yyyy hh:mm:ss.zzz")+
            ": "+msg+"\n timePassed: "+gettimeInterval().toString()+" ms";
    setTimeStampToCurrent();
}

void Log::showError(QString msg)
{
    STD_OUT << QString("  \033[47m|\033[0m\033[1;97;41m ERROR \033[0m \033[1;31m%1\033[0m").arg(formatMessage(msg)) << endl;

}

void Log::showWarning(QString msg)
{
    STD_OUT << QString("  \033[47m|\033[0m\033[1;97;43m WARNING \033[0m \033[1;33m%1\033[0m").arg(formatMessage(msg)) << endl;

}

void Log::showInfo(QString msg)
{
    STD_OUT << QString("  \033[47m|\033[0m\033[1;97;46m INFO    \033[0m \033[1;36m%1\033[0m").arg(formatMessage(msg)) << endl;


}

void Log::showSuccess(QString msg)
{
    STD_OUT << QString("  \033[47m|\033[0m\033[1;97;42m SUCCESS     \033[0m \033[1;32m%1\033[0m").arg(formatMessage(msg)) << endl;

}

void Log::setTimeStampToCurrent()
{
    timeStamp = QDateTime::currentDateTime().toMSecsSinceEpoch();
}

QVariant Log::gettimeInterval()
{
    return -timeStamp.toLongLong()+QDateTime::currentDateTime().toMSecsSinceEpoch();
}
