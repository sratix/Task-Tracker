#ifndef COMMONCLASSES_H
#define COMMONCLASSES_H

#include <QMap>
#include <QMetaEnum>
#include <QEvent>
#include <QtMath>
#include <QObject>
#include <QWidget>

QString double2MoneyUKR(double n, int currency = 1);
QString double2MoneyRUS(double n, int currency = 2);
QString double2MoneyENG(double number);
QString double2Money(double n, QString lang);
QString colorToString(QColor color);
QColor colorFromString(QString value);
QString eventType(QEvent *ev);

#endif // COMMONCLASSES_H
