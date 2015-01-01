#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QObject>
#include <QtSql>
#include <QDebug>
#include <QDesktopServices>

#include "Const.h"
#include "logger.h"

class DBManager : public QObject
{
    Q_OBJECT
public:
    static DBManager* Instance()
    {
        if(!instance)
            instance = new DBManager();
        return instance;
    }

    void loadDB(QString path);
    bool isConnectDB();
    QString lastError();
    void closeDB();

    void readAllTask(QVector<TaskData> & tasks);
    bool addTask(QVector<QVariant> params);
    bool editTask(QByteArray ID, QVector<QVariant> params);
    bool readTask(QByteArray ID, TaskData &task);
    bool deleteTask(QByteArray ID);
    void readAllExistTask(QVector<TaskData> & tasks);
    void readAllDateTask(QString from, QString to, QVector<TaskData> & tasks);
    bool readComment(QByteArray ID, QString &comment);
    bool updateTask(QByteArray ID, TaskState state, QString date, QString time);
    bool updateTaskConsumedTime(QByteArray ID, int time);
    bool updateNameConsumeComment(QByteArray ID, TaskState state, QString name, int consume, QString comment);
    bool clearDB();

    QString toMD5(QString text);

private:
    DBManager();
    bool createDB(void);
    QSqlQuery Query(QString queryString);
    bool insertTable(QString tableName, QVector<QVariant> fieldValue);
    bool updateTable(QByteArray uID, QString tableName, QVector<QVariant> fieldValue);
    bool deleteTable(QByteArray uID, QString tableName);
private:
    static DBManager *instance;
    QString m_DBPath;
    QSqlDatabase m_DB;
    QSqlQueryModel m_QueryModel;
    QString m_LastError;
    QByteArray uid;
signals:    
public slots:
};

#endif // DBMANAGER_H
