#include "log.h"




QString Log::formatMessage(QString msg)
{
    if(timeStamp==0) setTimeStampToCurrent();
    return QDateTime::currentDateTime().toString("dd/MM/yyyy hh:mm:ss.zzz")+
            ": "+msg+"\n timePassed: "+gettimeInterval().toString()+" ms";
    setTimeStampToCurrent();
}

QString Log::getTxtFileNameFromDate()
{
   return QDateTime::currentDateTime().toString("dd.MM.yyyy hh_mm_ss")+".txt";
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

void Log::logToFile(QString text,QString fileName)
{
     QFile *file;
     file = new QFile;
     file->setFileName(fileName);
     file->open(QIODevice::Append | QIODevice::Text);
     text = QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss ") + text;
     QTextStream out(file);
     out.setCodec("UTF-8");
     if (file != 0) {
      out << text <<"\n";
     }

     if (file != 0)
     file->close();

     delete file;




}

void Log::logErrToFileConsole(QString text, QString fileName)
{
 MN_ERROR(text);
 logToFile(text,fileName);
}
