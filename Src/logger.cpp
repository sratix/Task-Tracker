#include "logger.h"

Logger Logger::instance;
const QString Logger::PRIORITY_NAMES[] =
{
    "INFO",
    "CONFIG",
    "WARNING",
    "ERROR",
    "DEBUG"
};
Logger::Logger() : active(false) {}

void Logger::Start()
{
    instance.active = true;
    instance.minPriority = Logger::INFO;
    instance.maxPriority = Logger::DEBUG;
    instance.m_file.setFileName(LogPath+"JVN."+QDate::currentDate().toString("yyyyMMdd")+".log");
    if (!instance.m_file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
    {
        QMessageBox::critical(0,
                              QObject::tr("خطا"),
                              QObject::tr("برنامه قادر به ساخت فایل بررسی نمی باشد."));
        exit(EXIT_FAILURE);
        return;
    }
}

void Logger::Stop()
{
    instance.active = false;
    if (instance.m_file.isOpen())
    {
        instance.m_file.close();
    }
}

void Logger::Write(Priority priority, const QString& message)
{
    QTime ctime = QTime::currentTime();
    if(ctime.hour() == 0
            && ctime.minute() == 0
            && ctime.second() == 0)
    {
        Logger::Stop();
        Logger::Start();
    }
    if (instance.active && priority >= instance.minPriority && priority <= instance.maxPriority)
    {
        if(instance.m_file.isOpen())
        {
            instance.m_file.write(QString(QTime::currentTime().toString("hh:mm:ss ")+PRIORITY_NAMES[priority]+ ": "+message+"\n").toStdString().c_str());
            instance.m_file.flush();
        }
    }
}

void Logger::SetLogLevels(Priority minpriority, Priority maxpriority)
{
    instance.minPriority = minpriority;
    instance.maxPriority = maxpriority;
}
