/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout;
    QLabel *lblToday;
    QScrollArea *taskListScrollArea;
    QWidget *taskListWidget;
    QVBoxLayout *taskListLayout;
    QSpacerItem *verticalSpacer;
    QGroupBox *gbComment;
    QVBoxLayout *verticalLayout;
    QTextEdit *teComment;
    QPushButton *mainOperationButton;
    QGroupBox *gb_Report;
    QGridLayout *gridLayout_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *leFromDate;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *leToDate;
    QPushButton *pbReport;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(229, 655);
        QFont font;
        font.setFamily(QStringLiteral("B Nazanin"));
        font.setPointSize(12);
        font.setBold(true);
        font.setWeight(75);
        MainWindow->setFont(font);
        MainWindow->setLayoutDirection(Qt::RightToLeft);
        MainWindow->setStyleSheet(QLatin1String("QMainWindow\n"
"{\n"
"	background-image: url(:/icons/Background.png);\n"
"}\n"
"QWidget\n"
"{\n"
"	font-family: \"B Nazanin\";\n"
"	font-style: bold;\n"
"	color: white;\n"
"}\n"
"\n"
"QTextEdit\n"
"{\n"
"    background-color: transparent;/*#242424;*/\n"
"}\n"
"QPushButton\n"
"{\n"
"    color: #b1b1b1;\n"
"    background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #565656, stop: 0.1 #525252, stop: 0.5 #4e4e4e, stop: 0.9 #4a4a4a, stop: 1 #464646);\n"
"    border-width: 1px;\n"
"    border-color: #1e1e1e;\n"
"    border-style: solid;\n"
"    border-radius: 6;\n"
"    padding: 3px;\n"
"    padding-left: 5px;\n"
"    padding-right: 5px;\n"
"}\n"
"QPushButton:pressed\n"
"{\n"
"    background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #2d2d2d, stop: 0.1 #2b2b2b, stop: 0.5 #292929, stop: 0.9 #282828, stop: 1 #252525);\n"
"}\n"
"QComboBox:hover,QPushButton:hover,QLineEdit:hover, QTextEdit:hover\n"
"{\n"
"    border: 2px solid QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #ffa02f,"
                        " stop: 1 #d7801a);\n"
"}\n"
"/*QScrollArea\n"
"{\n"
"	background-color: transparent;\n"
"    color: #b1b1b1;\n"
"    background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #565656, stop: 0.1 #525252, stop: 0.5 #4e4e4e, stop: 0.9 #4a4a4a, stop: 1 #464646);\n"
"    border-width: 1px;\n"
"    border-color: #1e1e1e;\n"
"    border-style: solid;\n"
"    border-radius: 6;\n"
"    padding: 3px;\n"
"    padding-left: 5px;\n"
"    padding-right: 5px;\n"
"}*/\n"
"QLineEdit \n"
"{\n"
"	background-color: transparent;\n"
"	border: 2px solid gray;/*QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #ffa02f, stop: 1 #d7801a);*/\n"
"	border-radius: 6px;\n"
"	padding: 2px;\n"
"	selection-background-color: darkgray;\n"
"}\n"
"\n"
" QGroupBox::title \n"
"{\n"
"     subcontrol-origin: margin;\n"
"     subcontrol-position: top center;\n"
" }\n"
"QScrollBar:horizontal {\n"
"     border: 1px solid #222222;\n"
"     background: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0.0 #121212, stop: 0.2 #282828, stop: "
                        "1 #484848);\n"
"     height: 7px;\n"
"     margin: 0px 16px 0 16px;\n"
"}\n"
"\n"
"QScrollBar::handle:horizontal\n"
"{\n"
"      background: QLinearGradient( x1: 0, y1: 0, x2: 1, y2: 0, stop: 0 #ffa02f, stop: 0.5 #d7801a, stop: 1 #ffa02f);\n"
"      min-height: 20px;\n"
"      border-radius: 2px;\n"
"}\n"
"\n"
"QScrollBar::add-line:horizontal {\n"
"      border: 1px solid #1b1b19;\n"
"      border-radius: 2px;\n"
"      background: QLinearGradient( x1: 0, y1: 0, x2: 1, y2: 0, stop: 0 #ffa02f, stop: 1 #d7801a);\n"
"      width: 14px;\n"
"      subcontrol-position: right;\n"
"      subcontrol-origin: margin;\n"
"}\n"
"\n"
"QScrollBar::sub-line:horizontal {\n"
"      border: 1px solid #1b1b19;\n"
"      border-radius: 2px;\n"
"      background: QLinearGradient( x1: 0, y1: 0, x2: 1, y2: 0, stop: 0 #ffa02f, stop: 1 #d7801a);\n"
"      width: 14px;\n"
"     subcontrol-position: left;\n"
"     subcontrol-origin: margin;\n"
"}\n"
"\n"
"QScrollBar::right-arrow:horizontal, QScrollBar::left-arrow:horizontal\n"
"{\n"
"   "
                        "   border: 1px solid black;\n"
"      width: 1px;\n"
"      height: 1px;\n"
"      background: white;\n"
"}\n"
"\n"
"QScrollBar::add-page:horizontal, QScrollBar::sub-page:horizontal\n"
"{\n"
"      background: none;\n"
"}\n"
"\n"
"QScrollBar:vertical\n"
"{\n"
"      background: QLinearGradient( x1: 0, y1: 0, x2: 1, y2: 0, stop: 0.0 #121212, stop: 0.2 #282828, stop: 1 #484848);\n"
"      width: 7px;\n"
"      margin: 16px 0 16px 0;\n"
"      border: 1px solid #222222;\n"
"}\n"
"\n"
"QScrollBar::handle:vertical\n"
"{\n"
"      background: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #ffa02f, stop: 0.5 #d7801a, stop: 1 #ffa02f);\n"
"      min-height: 20px;\n"
"      border-radius: 2px;\n"
"}\n"
"\n"
"QScrollBar::add-line:vertical\n"
"{\n"
"      border: 1px solid #1b1b19;\n"
"      border-radius: 2px;\n"
"      background: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #ffa02f, stop: 1 #d7801a);\n"
"      height: 14px;\n"
"      subcontrol-position: bottom;\n"
"      subcontrol-origin: margin;\n"
"}"
                        "\n"
"\n"
"QScrollBar::sub-line:vertical\n"
"{\n"
"      border: 1px solid #1b1b19;\n"
"      border-radius: 2px;\n"
"      background: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #d7801a, stop: 1 #ffa02f);\n"
"      height: 14px;\n"
"      subcontrol-position: top;\n"
"      subcontrol-origin: margin;\n"
"}\n"
"\n"
"QScrollBar::up-arrow:vertical, QScrollBar::down-arrow:vertical\n"
"{\n"
"      border: 1px solid black;\n"
"      width: 1px;\n"
"      height: 1px;\n"
"      background: white;\n"
"}\n"
"\n"
"\n"
"QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical\n"
"{\n"
"      background: none;\n"
"}"));
        MainWindow->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout_2 = new QVBoxLayout(centralWidget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setStyleSheet(QLatin1String("QGroupBox\n"
" {\n"
"	background-color: transparent;\n"
"	border: 2px solid gray;\n"
"	border-radius: 6px;\n"
"	padding: 2px;\n"
"	selection-background-color: darkgray;\n"
"	margin-top: 0ex;\n"
"	}\n"
" QGroupBox::title {\n"
"     subcontrol-origin: margin;\n"
"     subcontrol-position: top center;\n"
" }\n"
"QGroupBox:hover\n"
"{\n"
"    border: 2px solid QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #ffa02f, stop: 1 #d7801a);\n"
"}\n"
""));
        gridLayout = new QGridLayout(groupBox_2);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        lblToday = new QLabel(groupBox_2);
        lblToday->setObjectName(QStringLiteral("lblToday"));
        lblToday->setFont(font);
        lblToday->setFrameShape(QFrame::NoFrame);
        lblToday->setFrameShadow(QFrame::Plain);
        lblToday->setLineWidth(1);
        lblToday->setMidLineWidth(0);

        gridLayout->addWidget(lblToday, 0, 0, 1, 1);


        verticalLayout_2->addWidget(groupBox_2);

        taskListScrollArea = new QScrollArea(centralWidget);
        taskListScrollArea->setObjectName(QStringLiteral("taskListScrollArea"));
        taskListScrollArea->setFont(font);
        taskListScrollArea->setFocusPolicy(Qt::ClickFocus);
        taskListScrollArea->setStyleSheet(QLatin1String("QScrollArea \n"
"{\n"
"	background-color:transparent;border: 2px solid gray;border-radius: 6px;\n"
"}\n"
"QScrollArea QWidget\n"
"{   \n"
"    background-color:transparent;\n"
"}\n"
"QScrollArea:hover\n"
"{\n"
"    border: 2px solid QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #ffa02f, stop: 1 #d7801a);\n"
"}"));
        taskListScrollArea->setFrameShape(QFrame::Box);
        taskListScrollArea->setFrameShadow(QFrame::Raised);
        taskListScrollArea->setWidgetResizable(true);
        taskListWidget = new QWidget();
        taskListWidget->setObjectName(QStringLiteral("taskListWidget"));
        taskListWidget->setGeometry(QRect(0, 0, 207, 209));
        taskListLayout = new QVBoxLayout(taskListWidget);
        taskListLayout->setSpacing(6);
        taskListLayout->setContentsMargins(11, 11, 11, 11);
        taskListLayout->setObjectName(QStringLiteral("taskListLayout"));
        verticalSpacer = new QSpacerItem(20, 269, QSizePolicy::Minimum, QSizePolicy::Expanding);

        taskListLayout->addItem(verticalSpacer);

        taskListScrollArea->setWidget(taskListWidget);

        verticalLayout_2->addWidget(taskListScrollArea);

        gbComment = new QGroupBox(centralWidget);
        gbComment->setObjectName(QStringLiteral("gbComment"));
        gbComment->setFont(font);
        gbComment->setAlignment(Qt::AlignCenter);
        verticalLayout = new QVBoxLayout(gbComment);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        teComment = new QTextEdit(gbComment);
        teComment->setObjectName(QStringLiteral("teComment"));
        QFont font1;
        font1.setFamily(QStringLiteral("B Nazanin"));
        font1.setPointSize(12);
        font1.setBold(false);
        font1.setWeight(50);
        teComment->setFont(font1);
        teComment->setStyleSheet(QStringLiteral("color:white;"));

        verticalLayout->addWidget(teComment);


        verticalLayout_2->addWidget(gbComment);

        mainOperationButton = new QPushButton(centralWidget);
        mainOperationButton->setObjectName(QStringLiteral("mainOperationButton"));
        mainOperationButton->setMinimumSize(QSize(78, 50));
        mainOperationButton->setFont(font);
        mainOperationButton->setCursor(QCursor(Qt::PointingHandCursor));

        verticalLayout_2->addWidget(mainOperationButton);

        gb_Report = new QGroupBox(centralWidget);
        gb_Report->setObjectName(QStringLiteral("gb_Report"));
        gb_Report->setFont(font);
        gridLayout_2 = new QGridLayout(gb_Report);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(gb_Report);
        label->setObjectName(QStringLiteral("label"));
        label->setFont(font);

        horizontalLayout->addWidget(label);

        leFromDate = new QLineEdit(gb_Report);
        leFromDate->setObjectName(QStringLiteral("leFromDate"));
        leFromDate->setFont(font);

        horizontalLayout->addWidget(leFromDate);


        gridLayout_2->addLayout(horizontalLayout, 0, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_2 = new QLabel(gb_Report);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setFont(font);

        horizontalLayout_2->addWidget(label_2);

        leToDate = new QLineEdit(gb_Report);
        leToDate->setObjectName(QStringLiteral("leToDate"));
        leToDate->setFont(font);

        horizontalLayout_2->addWidget(leToDate);


        gridLayout_2->addLayout(horizontalLayout_2, 1, 0, 1, 1);


        verticalLayout_2->addWidget(gb_Report);

        pbReport = new QPushButton(centralWidget);
        pbReport->setObjectName(QStringLiteral("pbReport"));
        pbReport->setMinimumSize(QSize(78, 50));
        pbReport->setFont(font);
        pbReport->setCursor(QCursor(Qt::PointingHandCursor));

        verticalLayout_2->addWidget(pbReport);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Task-Tracker", 0));
        groupBox_2->setTitle(QString());
        lblToday->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        gbComment->setTitle(QApplication::translate("MainWindow", " \330\252\331\210\330\266\333\214\330\255\330\247\330\252 ", 0));
        mainOperationButton->setText(QApplication::translate("MainWindow", "\330\247\331\201\330\262\331\210\330\257\331\206 \332\251\330\247\330\261 \330\254\330\257\333\214\330\257", 0));
        gb_Report->setTitle(QApplication::translate("MainWindow", "\332\257\330\262\330\247\330\261\330\264", 0));
        label->setText(QApplication::translate("MainWindow", "\330\247\330\262:", 0));
        leFromDate->setInputMask(QApplication::translate("MainWindow", "0000/00/00", 0));
        label_2->setText(QApplication::translate("MainWindow", "\330\252\330\247:", 0));
        leToDate->setInputMask(QApplication::translate("MainWindow", "0000/00/00", 0));
        pbReport->setText(QApplication::translate("MainWindow", "\332\257\330\262\330\247\330\261\330\264", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
