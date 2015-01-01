#ifndef CONST_H
#define CONST_H

#include <QtCore>
#include <QCryptographicHash>

enum TaskState{
    CREATED = 100,
    STARTED,
    RUNNING,
    WAITED,
    DONE
};

typedef struct
{
    QByteArray  taskuID;
    QString     taskShortName;
    TaskState   taskState;
    QString     taskCreatedTime;
    QString     taskCreatedDate;
    QString     taskStartTime;
    QString     taskStartDate;
    QString     taskDoneTime;
    QString     taskDoneDate;
    int         taskConsumeTime;
    QString     taskComment;
} TaskData;

typedef struct
{
    quint16 dateYear;
    quint8  dateMonth;
    quint8  dateDay;
} dateElement;

const QString DBName        = "./DB/TaskDB";
const QString LogPath       = "/Logs/";
const QString TaskTable     = "Task";
const QString LinuxAppStartupFileName = "task-tracker.desktop";
const QString LinuxAppStartupPath = QDir::homePath()+"/.config/autostart/";



inline QString IntTime(quint64 time)
{
    quint8 seconds = time % 60;
    quint8 minutes = (time / 60) % 60;
    quint8 hours = time / 3600;
    return QString("%1:%2:%3")
           .arg(QString::number(hours)  , 2, QChar('0'))
           .arg(QString::number(minutes), 2, QChar('0'))
           .arg(QString::number(seconds), 2, QChar('0'));
}

inline dateElement dateExtract(QString date)
{
    dateElement de;
    QLocale locale(QLocale::Persian, QLocale::Iran);
    QStringList list = date.split('/', QString::SkipEmptyParts);
    de.dateYear = locale.toInt(list[0]);
    de.dateMonth = locale.toInt(list[1]);
    de.dateDay = locale.toInt(list[2]);
    list.clear();
    return de;
}

#endif // JDCONST_H
