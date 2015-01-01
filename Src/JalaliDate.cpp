#include "JalaliDate.h"

JalaliDate::JalaliDate()
{
    m_Today = QDateTime::currentDateTime();
    QLocale locale(QLocale::Persian, QLocale::Iran);
    m_JToday = toJalali(locale.toInt(m_Today.toString("yyyy")),
                        locale.toInt(m_Today.toString("MM")),
                        locale.toInt(m_Today.toString("dd")));
}
int JalaliDate::div(int a,int b)
{
    return (a/b);
}

void JalaliDate::initMonths()
{
    m_Month[1]=QString::fromUtf8        ("فروردین");
    m_Month[2]=QString::fromUtf8        ("اردیبهشت");
    m_Month[3]=QString::fromUtf8        ("خرداد");
    m_Month[4]=QString::fromUtf8        ("تیر");
    m_Month[5]=QString::fromUtf8        ("مرداد");
    m_Month[6]=QString::fromUtf8        ("شهریور");
    m_Month[7]=QString::fromUtf8        ("مهر");
    m_Month[8]=QString::fromUtf8        ("آبان");
    m_Month[9]=QString::fromUtf8        ("آذر");
    m_Month[10]=QString::fromUtf8       ("دی");
    m_Month[11]=QString::fromUtf8       ("بهمن");
    m_Month[12]=QString::fromUtf8       ("اسفند");
}
void JalaliDate::initDays()
{
    m_Day["Saturday"]=QString::fromUtf8   ("شنبه");
    m_Day["Sunday"]=QString::fromUtf8     ("یکشنبه");
    m_Day["Monday"]=QString::fromUtf8     ("دوشنبه");
    m_Day["Tuesday"]=QString::fromUtf8    ("سه شنبه");
    m_Day["Wednesday"]=QString::fromUtf8  ("چهارشنبه");
    m_Day["Thursday"]=QString::fromUtf8   ("پنجشنبه");
    m_Day["Friday"]=QString::fromUtf8     ("آدینه");
}
bool JalaliDate::isLeapYear(int year)
{
    if (year == 0) year = m_JYear;
    int mod = year % 33;
    if (year<= 1472 && year >= 1343)
    {
        if (mod == 1 || mod == 5 || mod ==9 || mod == 13 || mod == 17 || mod==22 || mod==26 || mod==23)
            return true;
        else
            return false;
    }
    if (year <= 1342 && year >= 1244)
    {
        if (mod == 1 || mod == 5 || mod ==9 || mod == 13 || mod == 17 || mod==22 || mod==26 || mod==23)
            return true;
        else
            return false;
    }
    return false;
}
QString JalaliDate::toJalali(quint16 year, quint8 month, quint8 day)
{
    int pos = 0;
    m_Validator.setRange(1970, 2030);
    QString str = QString::number(year);
    if(m_Validator.validate(str, pos) == QValidator::Invalid)
    {
        return "NULL";
    }
    m_Validator.setRange(1, 12);
    str = QString::number(month);
    if(m_Validator.validate(str, pos) == QValidator::Invalid)
    {
        return "NULL";
    }
    m_Validator.setRange(1, 31);
    str = QString::number(day);
    if(m_Validator.validate(str, pos) == QValidator::Invalid)
    {
        return "NULL";
    }
    int g_y = year;
    int g_m = month;
    int g_d = day;
    QList<int> g_days_in_month, j_days_in_month;
    g_days_in_month << 31 << 28 << 31 << 30 << 31 << 30 << 31 << 31 << 30 << 31 << 30 << 31;
    j_days_in_month << 31 << 31 << 31 << 31 << 31 << 31 << 30 << 30 << 30 << 30 << 30 << 29;
    int  gy = g_y - 1600;
    int  gm = g_m - 1;
    int  gd = g_d - 1;
    int  g_day_no = 365 * gy + div(gy + 3, 4) - div(gy + 99, 100) + div(gy + 399, 400);
    for (int i = 0; i < gm; ++i) g_day_no += g_days_in_month[i];
    if (gm > 1 && ((gy % 4 == 0 && gy % 100 != 0) || (gy % 400 == 0))) g_day_no++;
    g_day_no += gd;
    int j_day_no = g_day_no - 79;
    int  j_np = div(j_day_no, 12053); // 12053 = 365*33 + 32/4
    j_day_no = j_day_no % 12053;
    int jy = 979 + 33 * j_np + 4 * div(j_day_no, 1461);// 1461 = 365*4 + 4/4
    j_day_no %= 1461;
    if (j_day_no >= 366)
    {
        jy += div(j_day_no - 1, 365);
        j_day_no = (j_day_no - 1) % 365;
    }
    int ii;
    for (int i = 0; i < 11 && j_day_no >= j_days_in_month[i]; ++i)
    {
        j_day_no -= j_days_in_month[i];
        ii = i;
    }
    int  jm = ii + 2;
    int  jd = j_day_no + 1;
    g_days_in_month.clear();
    j_days_in_month.clear();
    initMonths();
    m_JYear = jy;
    m_JMonth = jm;
    m_JDay = jd;
    m_JMonthText = m_Month[jm];
    QLocale locale(QLocale::Persian, QLocale::Iran);
    m_JDayText = locale.toString(m_Today, "dddd");
    return QString("%1/%2/%3")
            .arg(QString::number(jy))
            .arg(QString::number(jm), 2, QChar('0'))
            .arg(QString::number(jd), 2, QChar('0'));
}
QString JalaliDate::toGregorian(quint16 year, quint8 month, quint8 day)
{
    int pos = 0;
    m_Validator.setRange(1370, 1430);
    QString str = QString::number(year);
    if(m_Validator.validate(str, pos) == QValidator::Invalid)
    {
        return "NULL";
    }
    m_Validator.setRange(1, 12);
    str = QString::number(month);
    if(m_Validator.validate(str, pos) == QValidator::Invalid)
    {
        return "NULL";
    }
    m_Validator.setRange(1, 31);
    str = QString::number(day);
    if(m_Validator.validate(str, pos) == QValidator::Invalid)
    {
        return "NULL";
    }
    int Year = year;
    int Month = month;
    int Day = day;
    QList<int> miladiDate;
    QList<int> farvardin1st;
    miladiDate << 1 << 1 << 1;
    farvardin1st << 1 << 1 << 1;
    int miladiYear;
    int marchDayDiff;
    int dayCount;
    QList<int> miladiMonth;
    miladiMonth << 30 << 31 << 30 << 31 << 31 << 30 << 31 << 30 << 31 << 31 << 28 << 31;
    miladiYear = Year + 621;
    if (QDate::isLeapYear(miladiYear))
    {
        farvardin1st[1] =3;
        farvardin1st[2]= 20;
        marchDayDiff = 12;
    }
    else
    {
        farvardin1st[1] = 3;
        farvardin1st[2] =21;
        marchDayDiff = 11;
    }
    if (QDate::isLeapYear(miladiYear+1))
        miladiMonth[10] = miladiMonth[10] + 1;
    if (Month >=1 && Month<=6)
        dayCount = ((Month-1) * 31) + Day;
    else
        dayCount =(6 * 31) + ((Month - 7) * 30) + Day;
    int remainDay;
    if (dayCount <= marchDayDiff)
    {
        miladiDate[2] = dayCount + (31 - marchDayDiff);
        miladiDate[1] = 3;
        miladiDate[0] = miladiYear;
    }
    else remainDay = dayCount - marchDayDiff;
    int i=0;
    while (remainDay>miladiMonth[i])
    {
        remainDay = remainDay - miladiMonth[i];
        i = i+1;
    }
    miladiDate[2] = remainDay;
    if (i>8)
    {
        miladiDate[1] = i - 8;
        miladiDate[0] =  miladiYear + 1;
    }
    else
    {
        miladiDate[1] = i + 4;
        miladiDate[0] =  miladiYear;
    }
    farvardin1st.clear();
    m_GYear = miladiDate[0];
    m_GMonth = miladiDate[1];
    m_GDay = miladiDate[2];
    QLocale locale(QLocale::Persian, QLocale::Iran);
    m_GMonthText = locale.toString(QDate(m_GYear, m_GMonth, m_GDay), "MMMM");
    m_GDayText = locale.toString(QDate(m_GYear, m_GMonth, m_GDay), "dddd");
    QString result = QString("%1/%2/%3")
            .arg(QString::number(miladiDate[0]))
            .arg(QString::number(miladiDate[1]))
            .arg(QString::number(miladiDate[2]));
    miladiDate.clear();
    return result;
}
QString JalaliDate::Today()
{
    return m_JToday;
}
QString JalaliDate::TodayText()
{
    initDays();
    if(QTime::currentTime().hour() == 0)
    {
        m_Today = QDateTime::currentDateTime();
    }
    QLocale locale(QLocale::Persian, QLocale::Iran);
    toJalali(locale.toInt(m_Today.toString("yyyy")),
             locale.toInt(m_Today.toString("MM")),
             locale.toInt(m_Today.toString("dd")));
    return QString("%1 %2 %3 %4")
            .arg(m_JDayText)
            .arg(QString::number(m_JDay))
            .arg(m_JMonthText)
            .arg(m_JYear);
}
int JalaliDate::GetJTodayYear()
{
    return m_JYear;
}
int JalaliDate::GetJTodayMonth()
{
    return m_JMonth;
}
int JalaliDate::GetJTodayDay()
{
    return m_JDay;
}
int JalaliDate::GetGTodayYear()
{
    return m_GYear;
}
int JalaliDate::GetGTodayMonth()
{
    return m_GMonth;
}
int JalaliDate::GetGTodayDay()
{
    return m_GDay;
}
