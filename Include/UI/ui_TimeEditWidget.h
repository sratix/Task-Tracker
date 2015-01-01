/********************************************************************************
** Form generated from reading UI file 'TimeEditWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TIMEEDITWIDGET_H
#define UI_TIMEEDITWIDGET_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TimeEditWidget
{
public:
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QLabel *label_4;
    QSpinBox *secondsSpinBox;
    QLabel *label;
    QSpinBox *minutesSpinBox;
    QLabel *label_2;
    QSpinBox *hoursSpinBox;
    QLabel *label_3;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QWidget *TimeEditWidget)
    {
        if (TimeEditWidget->objectName().isEmpty())
            TimeEditWidget->setObjectName(QStringLiteral("TimeEditWidget"));
        TimeEditWidget->resize(360, 280);
        QFont font;
        font.setFamily(QStringLiteral("B Nazanin"));
        TimeEditWidget->setFont(font);
        TimeEditWidget->setStyleSheet(QLatin1String("color:black;\n"
"font-style:bold;\n"
"font-size:17px;\n"
"font-family:\"B Nazanin\";"));
        horizontalLayout = new QHBoxLayout(TimeEditWidget);
        horizontalLayout->setSpacing(1);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        label_4 = new QLabel(TimeEditWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setFont(font);
        label_4->setLayoutDirection(Qt::RightToLeft);
        label_4->setStyleSheet(QLatin1String("color:white;\n"
"font-style:bold;\n"
"font-size:17px;\n"
"font-family:\"B Nazanin\";"));
        label_4->setLocale(QLocale(QLocale::Persian, QLocale::Iran));

        horizontalLayout->addWidget(label_4);

        secondsSpinBox = new QSpinBox(TimeEditWidget);
        secondsSpinBox->setObjectName(QStringLiteral("secondsSpinBox"));
        secondsSpinBox->setFont(font);
        secondsSpinBox->setMaximum(59);

        horizontalLayout->addWidget(secondsSpinBox);

        label = new QLabel(TimeEditWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setStyleSheet(QLatin1String("color:white;\n"
"font-style:bold;\n"
"font-size:17px;\n"
"font-family:\"B Nazanin\";"));

        horizontalLayout->addWidget(label);

        minutesSpinBox = new QSpinBox(TimeEditWidget);
        minutesSpinBox->setObjectName(QStringLiteral("minutesSpinBox"));
        minutesSpinBox->setMaximum(59);

        horizontalLayout->addWidget(minutesSpinBox);

        label_2 = new QLabel(TimeEditWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setStyleSheet(QLatin1String("color:white;\n"
"font-style:bold;\n"
"font-size:17px;\n"
"font-family:\"B Nazanin\";"));

        horizontalLayout->addWidget(label_2);

        hoursSpinBox = new QSpinBox(TimeEditWidget);
        hoursSpinBox->setObjectName(QStringLiteral("hoursSpinBox"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(hoursSpinBox->sizePolicy().hasHeightForWidth());
        hoursSpinBox->setSizePolicy(sizePolicy);
        hoursSpinBox->setMinimum(0);
        hoursSpinBox->setMaximum(999);

        horizontalLayout->addWidget(hoursSpinBox);

        label_3 = new QLabel(TimeEditWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setStyleSheet(QLatin1String("color:white;\n"
"font-style:bold;\n"
"font-size:17px;\n"
"font-family:\"B Nazanin\";"));

        horizontalLayout->addWidget(label_3);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        retranslateUi(TimeEditWidget);

        QMetaObject::connectSlotsByName(TimeEditWidget);
    } // setupUi

    void retranslateUi(QWidget *TimeEditWidget)
    {
        TimeEditWidget->setWindowTitle(QApplication::translate("TimeEditWidget", "Form", 0));
        label_4->setText(QApplication::translate("TimeEditWidget", ")", 0));
        label->setText(QApplication::translate("TimeEditWidget", ":", 0));
        label_2->setText(QApplication::translate("TimeEditWidget", ":", 0));
        label_3->setText(QApplication::translate("TimeEditWidget", "(", 0));
    } // retranslateUi

};

namespace Ui {
    class TimeEditWidget: public Ui_TimeEditWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TIMEEDITWIDGET_H
