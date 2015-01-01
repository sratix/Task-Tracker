#include "Task.h"

Task::Task(QObject *parent)
    : QObject(parent)
    , name("")
    , time(0)
    , active(false)
{
}
void Task::makeID()
{
    uid = QUuid::createUuid().toByteArray();
}
void Task::toggle()
{
    setActive(!isActive());
    emit toggled();
}
void Task::setActive(bool active)
{
    bool toggled = (this->active != active);
    this->active = active;
    if(toggled)
    {
        emit this->toggled();
    }
}
void Task::setID(const QByteArray id)
{
    uid = id;
}
void Task::setTime(const int time)
{
    this->time = time;
}
void Task::setTaskState(TaskState state)
{
    m_TaskState = state;
}
void Task::setName(const QString name)
{
    this->name = name;
}
QByteArray Task::getID() const
{
    return uid;
}
void Task::tick()
{
    if(active)
    {
        time++;
    }
}
int Task::getTime() const
{
    return time;
}
TaskState Task::getTaskState() const
{
    return m_TaskState;
}
QString Task::getName() const
{
    return name;
}
QString Task::toText() const
{
    return QString("(%1) %2")
            .arg(IntTime(getTime()))
            .arg(getName());
}
bool Task::isActive() const
{
    return active;
}
