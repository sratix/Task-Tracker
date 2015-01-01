#include "Report.h"

Report::Report(QObject *parent)
    : QObject(parent)
{
}
void Report::makeReport(QString from, QString to)
{
    m_FromJDate = from;
    m_ToJDate   = to;
    dateElement de = dateExtract(from);
    m_FromDate = m_jDate.toGregorian(de.dateYear, de.dateMonth, de.dateDay);
    de = dateExtract(to);
    m_ToDate   = m_jDate.toGregorian(de.dateYear, de.dateMonth, de.dateDay);

    DBManager::Instance()->readAllDateTask(m_FromDate, m_ToDate, m_Tasks);
    if (m_Tasks.size() == 0)
    {
        QMessageBox::critical(0/*(QWidget*)this*/, "خطا", "هنوز کاری اضافه نشده است");
        return;
    }
    totalTimeConsumed = 0;
    totalCreatedTask  = m_Tasks.size();
    totalStartedTask  = 0;
    totalRunningTask  = 0;
    totalWaitedTask   = 0;
    totalDoneTask     = 0;
    foreach (TaskData task , m_Tasks)
    {
        totalTimeConsumed += task.taskConsumeTime;
        if (!task.taskStartDate.compare("0000/00/00") == 0) totalStartedTask++;
        if (!task.taskDoneDate.compare("0000/00/00") == 0) totalDoneTask++;
        switch(task.taskState)
        {
        case RUNNING:
            totalRunningTask++;
            break;
        case WAITED:
            totalWaitedTask++;
            break;
        }
    }
    print();
}
void Report::setValue(int &recNo, QString &paramName, QVariant &paramValue, int reportPage)
{
    Q_UNUSED(reportPage);
    if (paramName == "FD")
        paramValue = m_FromJDate;
    if (paramName == "TD")
        paramValue = m_ToJDate;
    if (paramName == "LN")
        paramValue = recNo+1;
    if (paramName == "TSN")
    {
        paramValue = m_Tasks[recNo].taskShortName.trimmed();
    }
    if (paramName == "TCD")
    {
        dateElement de = dateExtract(m_Tasks[recNo].taskCreatedDate);
        paramValue = m_jDate.toJalali(de.dateYear, de.dateMonth, de.dateDay);
    }
    if (paramName == "TCT")
    {
        paramValue = m_Tasks[recNo].taskCreatedTime;
    }
    if (paramName == "TSD")
    {
        QString TSD = m_Tasks[recNo].taskStartDate;
        dateElement de = dateExtract(TSD);
        paramValue = (TSD.compare("0000/00/00") == 0)?"--":m_jDate.toJalali(de.dateYear, de.dateMonth, de.dateDay);
    }
    if (paramName == "TST")
    {
        QString TST = m_Tasks[recNo].taskStartTime;
        paramValue = (TST.compare("00:00:00") == 0)?"--":TST;
    }
    if (paramName == "TDD")
    {
        QString TDD = m_Tasks[recNo].taskDoneDate;
        dateElement de = dateExtract(TDD);
        paramValue = (TDD.compare("0000/00/00") == 0)?"--":m_jDate.toJalali(de.dateYear, de.dateMonth, de.dateDay);
    }
    if (paramName == "TDT")
    {
        QString TDT = m_Tasks[recNo].taskDoneTime;
        paramValue = (TDT.compare("00:00:00") == 0)?"--":TDT;
    }
    if (paramName == "TC")
    {
        paramValue = IntTime(m_Tasks[recNo].taskConsumeTime);
    }
    if (paramName == "TS")
    {
        QString TS = "";
        switch (m_Tasks[recNo].taskState)
        {
        case CREATED:
            TS = QString::fromUtf8("ایجاد شده");
            break;
        case STARTED:
            TS = QString::fromUtf8("شروع شده");
            break;
        case RUNNING:
            TS = QString::fromUtf8("در حال اجرا");
            break;
        case WAITED:
            TS = QString::fromUtf8("مکث شده");
            break;
        case DONE:
            TS = QString::fromUtf8("خاتمه یافته");
            break;
        }
        paramValue = TS;
    }
    if (paramName == "TCS")
    {
        paramValue = m_Tasks[recNo].taskComment.trimmed();
    }
    if(paramName == "STARTED")
    {
        paramValue = QString::number(totalStartedTask);
    }
    if(paramName == "RUNNING")
    {
        paramValue = QString::number(totalRunningTask);
    }
    if(paramName == "WAITED")
    {
        paramValue = QString::number(totalWaitedTask);
    }
    if(paramName == "DONE")
    {
        paramValue = QString::number(totalDoneTask);
    }
    if(paramName == "TOTALTASK")
    {
        paramValue = QString::number(totalCreatedTask);
    }
    if(paramName == "TOTALTIME")
    {
        paramValue = IntTime(totalTimeConsumed);
    }
}
void Report::setValueDiagram(Chart &chart)
{
    if (chart.objectName() == "diagram1")
    {
        GraphParam param;
        param.color = colorFromString("rgba(170,0,127,255)");
        param.valueReal = totalCreatedTask/(float)m_Tasks.size()*100.0;
        chart.setData(param);

        param.color = colorFromString("rgba(255,255,0,255)");
        param.valueReal = totalStartedTask/(float)m_Tasks.size()*100.0;
        chart.setData(param);

        param.color = colorFromString("rgba(0,0,255,255)");
        param.valueReal = totalRunningTask/(float)m_Tasks.size()*100.0;
        chart.setData(param);

        param.color = colorFromString("rgba(255,0,0,255)");
        param.valueReal = totalWaitedTask/(float)m_Tasks.size()*100.0;
        chart.setData(param);

        param.color = colorFromString("rgba(0,128,128,255)");
        param.valueReal = totalDoneTask/(float)m_Tasks.size()*100.0;
        chart.setData(param);
    }
}
//void Report::setValueImage(int &recNo, QString &paramName, QImage &paramValue, int reportPage)
//{
//    Q_UNUSED(recNo);
//    Q_UNUSED(reportPage);
//    if (paramName == "image") {
//        QImage *image = new QImage(QCoreApplication::applicationDirPath()+"/qt.png");
//        paramValue = *image;
//    }
//}
void Report::print()
{
    QString fileName = ":/data/TTReport.xml";
    m_Report = new QtRPT((QWidget*)this->parent());
    //m_Report->setBackgroundImage(QPixmap("./qt_background_portrait.png"));
    m_Report->recordCount << m_Tasks.size();
    if (m_Report->loadReport(fileName) == false)
    {
        qDebug()<<"Report's file not found";
    }
    QObject::connect(m_Report, SIGNAL(setValue(int&, QString&, QVariant&, int)),
                     this, SLOT(setValue(int&, QString&, QVariant&, int)));
    QObject::connect(m_Report, SIGNAL(setValueDiagram(Chart&)),this,SLOT(setValueDiagram(Chart&)));
    //    QObject::connect(report, SIGNAL(setValueImage(int&, QString&, QImage&, int)),
    //                     this, SLOT(setValueImage(int&, QString&, QImage&, int)));
    //report->setCallbackFunc(getReportValue);
    //m_Report->printExec(true);
    m_Report->printPDF(qApp->applicationDirPath().remove("/release").remove("/debug")+"/Rep/Report.pdf", true);
}

