#ifndef TASK_H
#define TASK_H

#include <QObject>
#include <QString>
#include <QUuid>
#include "DBManager.h"
#include "Const.h"

class Task : public QObject
{
    Q_OBJECT
public:
    Task(QObject *parent = 0);

    void makeID();
    void toggle();
    void setActive(bool active);
    void setID(const QByteArray id);
    void setName(const QString name);
    void setTime(int time);
    void setTaskState(TaskState state);

    QByteArray getID() const;
    bool isActive() const;
    QString getName() const;
    int getTime() const;
    TaskState getTaskState() const;
    QString toText() const;

    void tick();

signals:
    void toggled();

private:
    QString name;
    int time;
    bool active;
    QByteArray uid;
    TaskState m_TaskState;
};

#endif // TASK_H
