#ifndef LOGGER_H
#define LOGGER_H

#include <QObject>
#include <QString>
#include <QFile>
#include <QMessageBox>

#include "Const.h"

#ifdef ENABLE_LOGGER
#define LOGGER_START() Logger::Start();
#define LOGGER_STOP() Logger::Stop();
#define LOGGER_LEVEL(MIN_PRIORITY, MAX_PRIORITY) Logger::SetLogLevels(MIN_PRIORITY, MAX_PRIORITY);
#define LOGGER_WRITE(PRIORITY, MESSAGE) Logger::Write(PRIORITY, MESSAGE);
#endif

class Logger
{
public:
    enum Priority
    {
        INFO,
        CONFIG,
        WARNING,
        ERROR,
        DEBUG
    };
    static void Start();
    static void Stop();
    static void Write(Priority priority, const QString &message);
    static void SetLogLevels(Priority minpriority, Priority maxpriority);
private:
    Logger();
    bool                        active;
    QFile                       m_file;
    Priority                    minPriority;
    Priority                    maxPriority;
    static const QString        PRIORITY_NAMES[];
    static Logger               instance;
};

#endif // LOGGER_H
