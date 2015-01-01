#ifndef REPORT_H
#define REPORT_H

#include <QObject>
#include <QDate>
#include <QtSql>
#include <QMessageBox>
#include "JalaliDate.h"
#include "Const.h"
#include "DBManager.h"
#include "qtrpt.h"

class Report : public QObject
{
    Q_OBJECT
public:
    Report(QObject *parent = 0);
    void makeReport(QString from, QString to);
private:
    JalaliDate m_jDate;
    QString m_FromJDate, m_ToJDate;
    QString m_FromDate, m_ToDate;
    QString Query;
    QVector<TaskData> m_Tasks;
    QtRPT *m_Report;
    int totalTimeConsumed;
    int totalCreatedTask;
    int totalStartedTask;
    int totalRunningTask;
    int totalWaitedTask;
    int totalDoneTask;

private slots:
    void print();
    void setValue(int &recNo, QString &paramName, QVariant &paramValue, int reportPage);
    void setValueDiagram(Chart &chart);
//    void setValueImage(int &recNo, QString &paramName, QImage &paramValue, int reportPage);
};

#endif // REPORT_H
