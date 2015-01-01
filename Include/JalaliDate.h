#ifndef JALALIDATE_H
#define JALALIDATE_H

#include <QDebug>
#include <QDate>
#include <QMap>
#include <QIntValidator>

class JalaliDate
{
public:
    JalaliDate();

    bool isLeapYear(int year = 0);
    QString toJalali(quint16 year, quint8 month, quint8 day);   //MMDDYYYY
    QString toGregorian(quint16 year, quint8 month, quint8 day); //YYYYMMDD
    QString Today();
    QString TodayText();
    int GetJTodayYear();
    int GetJTodayMonth();
    int GetJTodayDay();
    int GetGTodayYear();
    int GetGTodayMonth();
    int GetGTodayDay();

private:
    int div(int, int);
    void initMonths();
    void initDays();
    QIntValidator m_Validator;
    QMap<int,QString> m_Month;
    QMap<QString,QString> m_Day;
    QDateTime m_Today;
    QString m_JToday;

    int m_JYear, m_JMonth, m_JDay;
    QString m_JDayText, m_JMonthText;

    int m_GYear, m_GMonth, m_GDay;
    QString m_GDayText, m_GMonthText;
};

#endif // JALALIDATE_H
