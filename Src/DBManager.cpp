#include "DBManager.h"

DBManager *DBManager::instance = 0;

DBManager::DBManager()
{
}
//---------------------------------------- Public Commands  ----------------------------------------//
void DBManager::readAllTask(QVector<TaskData> &tasks)
{
    QSqlQuery query =  Query("SELECT * FROM "+TaskTable);
    while (query.next())
    {
        TaskData task;
        task.taskuID            = query.value(0).toByteArray();
        task.taskShortName      = query.value(1).toString();
        task.taskState           = TaskState(query.value(2).toInt());
        task.taskCreatedTime    = query.value(3).toString();
        task.taskCreatedDate    = query.value(4).toString();
        task.taskStartTime      = query.value(5).toString();
        task.taskStartDate      = query.value(6).toString();
        task.taskDoneTime       = query.value(7).toString();
        task.taskDoneDate       = query.value(8).toString();
        task.taskConsumeTime    = query.value(9).toInt();
        task.taskComment        = query.value(10).toString();
        tasks.push_back(task);
    }
}

bool DBManager::addTask(QVector<QVariant> params)
{
    return (insertTable(TaskTable, params));
}

bool DBManager::editTask(QByteArray ID, QVector<QVariant> params)
{
    return (updateTable(ID, TaskTable, params));
}

bool DBManager::readTask(QByteArray ID, TaskData &task)
{
    QSqlQuery query =  Query("SELECT * FROM "+TaskTable+" WHERE uID like '"+ID+"'");
    if (query.next())
    {
        task.taskuID            = query.value(0).toByteArray();
        task.taskShortName      = query.value(1).toString();
        task.taskState           = TaskState(query.value(2).toInt());
        task.taskCreatedTime    = query.value(3).toString();
        task.taskCreatedDate    = query.value(4).toString();
        task.taskStartTime      = query.value(5).toString();
        task.taskStartDate      = query.value(6).toString();
        task.taskDoneTime       = query.value(7).toString();
        task.taskDoneDate       = query.value(8).toString();
        task.taskConsumeTime    = query.value(9).toInt();
        task.taskComment        = query.value(10).toString();
        return(true);
    }
    return(false);
}

bool DBManager::deleteTask(QByteArray ID)
{
    return (deleteTable(ID, TaskTable));
}

void DBManager::readAllExistTask(QVector<TaskData> &tasks)
{
    QSqlQuery query =  Query(QString("SELECT * FROM %1 WHERE TaskState <> %2")
                             .arg(TaskTable)
                             .arg(QString::number(DONE))
                             );
    while (query.next())
    {
        TaskData task;
        task.taskuID            = query.value(0).toByteArray();
        task.taskShortName      = query.value(1).toString();
        task.taskState           = TaskState(query.value(2).toInt());
        task.taskCreatedTime    = query.value(3).toString();
        task.taskCreatedDate    = query.value(4).toString();
        task.taskStartTime      = query.value(5).toString();
        task.taskStartDate      = query.value(6).toString();
        task.taskDoneTime       = query.value(7).toString();
        task.taskDoneDate       = query.value(8).toString();
        task.taskConsumeTime    = query.value(9).toInt();
        task.taskComment        = query.value(10).toString();
        tasks.push_back(task);
    }
}

void DBManager::readAllDateTask(QString from, QString to, QVector<TaskData> &tasks)
{
    QSqlQuery query = Query(QString("SELECT * FROM Task WHERE (TaskCreatedDate >= '%1' AND TaskCreatedDate <= '%2')")
                            .arg(from)
                            .arg(to));
    while (query.next())
    {
        TaskData task;
        task.taskuID            = query.value(0).toByteArray();
        task.taskShortName      = query.value(1).toString();
        task.taskState           = TaskState(query.value(2).toInt());
        task.taskCreatedTime    = query.value(3).toString();
        task.taskCreatedDate    = query.value(4).toString();
        task.taskStartTime      = query.value(5).toString();
        task.taskStartDate      = query.value(6).toString();
        task.taskDoneTime       = query.value(7).toString();
        task.taskDoneDate       = query.value(8).toString();
        task.taskConsumeTime    = query.value(9).toInt();
        task.taskComment        = query.value(10).toString();
        tasks.push_back(task);
    }
}

bool DBManager::readComment(QByteArray ID, QString &comment)
{
    QSqlQuery query =  Query("SELECT TaskComment FROM "+TaskTable+" WHERE uID like '"+ID+"'");
    if (query.next())
    {
        comment = query.value(0).toString();
        return(true);
    }
    return(false);
}

bool DBManager::updateTaskConsumedTime(QByteArray ID, int time)
{
    QSqlQuery query =  Query("UPDATE "+TaskTable+" SET TaskConsumedTime = "+time+" WHERE uID like '"+ID+"'");
    return true;
}

bool DBManager::updateTask(QByteArray ID, TaskState state, QString date, QString time)
{
    QString tQuery = "";
    switch (state)
    {
    case STARTED:
        tQuery = QString(", TaskStartTime = '%1', TaskStartDate = '%2'").arg(time).arg(date);
        break;
    case RUNNING:
        tQuery = "";
        break;
    case WAITED:
        tQuery = "";
        break;
    case DONE:
        tQuery = QString(", TaskDoneTime = '%1', TaskDoneDate = '%2'").arg(time).arg(date);
        break;
    }
    QSqlQuery query = Query(QString("UPDATE %1 SET TaskState = %2 %3 WHERE uID like '%4'")
                            .arg(TaskTable)
                            .arg(QString::number(state))
                            .arg(tQuery)
                            .arg(QString(ID))
                            );
    return true;
}

bool DBManager::updateNameConsumeComment(QByteArray ID, TaskState state, QString name, int consume, QString comment)
{
    QSqlQuery query =  Query(QString("UPDATE %1 SET TaskShortName = '%2' , TaskConsumeTime = %3 , TaskComment = '%4', TaskState = %5 WHERE uID like '%6'")
                             .arg(TaskTable)
                             .arg(name)
                             .arg(QString::number(consume))
                             .arg(comment)
                             .arg(state)
                             .arg(QString(ID)));
    return true;
}
bool DBManager::clearDB()
{
    QSqlQuery query =  Query(QString("Delete From Task"));
    return true;
}
void DBManager::loadDB(QString path)
{
    m_DBPath = path;
    if (!isConnectDB())
    {
        m_LastError = "Error to Open ["+path+"] file.";
        LOGGER_WRITE(Logger::ERROR, m_LastError);
        QMessageBox::critical(0, "Error", m_LastError);
        exit(EXIT_FAILURE);
    }
}

void DBManager::closeDB()
{
    if(m_DB.isOpen()) m_DB.close();
}
//---------------------------------------- Private Commands ----------------------------------------//
QString DBManager::lastError()
{
    return (m_LastError);
}

bool DBManager::isConnectDB()
{
    if (!QSqlDatabase::contains())
    {
        m_DB = QSqlDatabase::addDatabase("QSQLITE");
//        QString path(QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation));
//        path.append(QDir::separator()).append(m_DBPath);
//        path = QDir::toNativeSeparators(path);
        m_DB.setDatabaseName(m_DBPath);//path);
        QFile dbFile(m_DB.databaseName());
        if (!dbFile.exists())
        {
            qDebug() << "database does not exist. then close!";
            if (!createDB()) return false;
        }
        if (!m_DB.open())
        {
            qDebug() << m_DB.lastError().text();
            return false;
        }
    }
    else m_DB = QSqlDatabase::database();
    return true;
}
bool DBManager::createDB()
{
    if (!m_DB.open())
    {
        qDebug() << m_DB.lastError().text();
        return false;
    }
    QFile sqlFile(":/icons/Task.sql");
    if (sqlFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QString sql = "";
        QTextStream in(&sqlFile);
        QSqlQuery qry;
        while (!in.atEnd())
        {
            QString line = in.readLine();
            sql += line;
            if (line.contains(';'))
            {
                if (!qry.exec(sql))
                {
                    qDebug() << qry.lastError().text();
                    m_DB.close();
                    return false;
                }
                sql = "";
            }
        }
        sqlFile.close();
        m_DB.close();
        return true;
    }
    else
    {
        return false;
    }
}
QSqlQuery DBManager::Query(QString queryString)
{
    QSqlDatabase::database().transaction();
    QSqlQuery query;
    query.prepare(queryString);
    query.exec();
    m_LastError = query.lastError().text();
    QSqlDatabase::database().commit();
    return query;
}

bool DBManager::insertTable(QString tableName,  QVector<QVariant> fieldValue)
{
    QSqlQuery query =  Query("SELECT * FROM "+tableName);
    QStringList fieldName;
    for (int i = 0; i < query.record().count(); i++)
        fieldName << query.record().fieldName(i);
    QString queryString = "INSERT INTO "+ tableName +" (";
    for (int i = 0; i < fieldValue.size(); i++)
        queryString += fieldName[i]+", ";
    queryString.remove(queryString.length()-2, 2);
    queryString += ") VALUES (";
    queryString += (QString("?,").repeated(fieldName.length()));
    queryString.remove(queryString.length()-1, 1);
    queryString += ")";
    QSqlDatabase::database().transaction();
    query.prepare(queryString);
    for (int i = 0; i < fieldValue.size(); i++) query.addBindValue(fieldValue[i]);
    bool result = query.exec();
    m_LastError = query.lastError().text();
    QSqlDatabase::database().commit();
    return(result);
}

bool DBManager::updateTable(QByteArray uID, QString tableName, QVector<QVariant> fieldValue)
{
    QStringList fieldName;
    QSqlQuery query =  Query("SELECT * FROM "+tableName);
    for (int i = 0; i < query.record().count(); i++) //Just need to update not new insert
        fieldName << query.record().fieldName(i);
    QString queryString = "UPDATE "+ tableName +" SET ";
    for (int i = 0; i < fieldValue.size(); i++)
        queryString += (fieldName[i]+" = :"+fieldName[i]+", ");
    queryString.remove(queryString.length()-2, 1);
    queryString += ("WHERE uID = :uID");
    query.prepare(queryString);
    for (int i = 0; i < fieldValue.size(); i++)
        query.bindValue(":"+fieldName[i], fieldValue[i]);
    query.bindValue(":uID", uID);
    QSqlDatabase::database().transaction();
    bool result = query.exec();
    m_LastError = query.lastError().text();
    QSqlDatabase::database().commit();
    return(result);
}

bool DBManager::deleteTable(QByteArray uID, QString tableName)
{
    QSqlQuery query;
    query.prepare("DELETE FROM "+tableName+" WHERE uID = :uID");
    query.bindValue(":uID", uID);
    bool result = query.exec();
    m_LastError = query.lastError().text();
    return(result);
}

QString DBManager::toMD5(QString text)
{
    QCryptographicHash hash(QCryptographicHash::Md5);
    hash.addData(text.toStdString().c_str(), text.length());
    return (QString(hash.result().toHex()));
}
