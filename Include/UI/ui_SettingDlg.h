/********************************************************************************
** Form generated from reading UI file 'SettingDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGDLG_H
#define UI_SETTINGDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SettingDlg
{
public:
    QGroupBox *gb_About;
    QGridLayout *gridLayout_2;
    QTabWidget *tabWidget;
    QWidget *tab;
    QGridLayout *gridLayout_3;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer_2;
    QLabel *label_7;
    QSpacerItem *verticalSpacer;
    QLabel *label_8;
    QLabel *label_9;
    QWidget *tab_2;
    QGridLayout *gridLayout_4;
    QTextEdit *textEdit;
    QWidget *tab_3;
    QGridLayout *gridLayout_5;
    QTextEdit *textEdit_2;
    QGroupBox *gb_Settings;
    QPushButton *pbClearDB;
    QLabel *label_12;
    QCheckBox *cbStartup;
    QGroupBox *gb_Shortcuts;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLabel *label_4;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLabel *label_5;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QLabel *label_6;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_10;
    QLabel *label_11;

    void setupUi(QDialog *SettingDlg)
    {
        if (SettingDlg->objectName().isEmpty())
            SettingDlg->setObjectName(QStringLiteral("SettingDlg"));
        SettingDlg->resize(391, 421);
        QFont font;
        font.setFamily(QStringLiteral("B Nazanin"));
        SettingDlg->setFont(font);
        SettingDlg->setLayoutDirection(Qt::RightToLeft);
        SettingDlg->setStyleSheet(QLatin1String("QDialog\n"
"{\n"
"	background-image: url(:/icons/Background.png);\n"
"}\n"
"QWidget\n"
"{\n"
"	font-family: \"B Nazanin\";\n"
"	font-style: bold;\n"
"	color:white;\n"
"	font-size:15px;\n"
"	background-color:transparent;\n"
"}\n"
"QTabBar::tab {\n"
"    color: #b1b1b1;\n"
"    border: 1px solid #444;\n"
"    border-bottom-style: none;\n"
"    background-color: #323232;\n"
"    padding-left: 10px;\n"
"    padding-right: 10px;\n"
"    padding-top: 3px;\n"
"    padding-bottom: 2px;\n"
"    margin-right: -1px;\n"
"}\n"
"\n"
"QTabWidget::pane {\n"
"    border: 1px solid #444;\n"
"    top: 1px;\n"
"}\n"
"\n"
"QTabBar::tab:last\n"
"{\n"
"    margin-right: 0; /* the last selected tab has nothing to overlap with on the right */\n"
"    border-top-right-radius: 3px;\n"
"}\n"
"\n"
"QTabBar::tab:first:!selected\n"
"{\n"
" margin-left: 0px; /* the last selected tab has nothing to overlap with on the right */\n"
"\n"
"\n"
"    border-top-left-radius: 3px;\n"
"}\n"
"\n"
"QTabBar::tab:!selected\n"
"{\n"
"    color: #b1b1b1;\n"
""
                        "    border-bottom-style: solid;\n"
"    margin-top: 3px;\n"
"    background-color: QLinearGradient(x1:0, y1:0, x2:0, y2:1, stop:1 #212121, stop:.4 #343434);\n"
"}\n"
"\n"
"QTabBar::tab:selected\n"
"{\n"
"    border-top-left-radius: 3px;\n"
"    border-top-right-radius: 3px;\n"
"    margin-bottom: 0px;\n"
"}\n"
"\n"
"QTabBar::tab:!selected:hover\n"
"{\n"
"    /*border-top: 2px solid #ffaa00;\n"
"    padding-bottom: 3px;*/\n"
"    border-top-left-radius: 3px;\n"
"    border-top-right-radius: 3px;\n"
"    background-color: QLinearGradient(x1:0, y1:0, x2:0, y2:1, stop:1 #212121, stop:0.4 #343434, stop:0.2 #343434, stop:0.1 #ffaa00);\n"
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
""
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
"    border: 2px solid QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #ffa02f, stop: 1 #d7801a);\n"
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
"	border: 2px solid gray;/*"
                        "QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #ffa02f, stop: 1 #d7801a);*/\n"
"	border-radius: 6px;\n"
"	padding: 2px;\n"
"	selection-background-color: darkgray;\n"
"}\n"
" QGroupBox::title \n"
"{\n"
"     subcontrol-origin: margin;\n"
"     subcontrol-position: top center;\n"
" }\n"
"QScrollBar:horizontal {\n"
"     border: 1px solid #222222;\n"
"     background: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0.0 #121212, stop: 0.2 #282828, stop: 1 #484848);\n"
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
"      subcontrol-po"
                        "sition: right;\n"
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
"      border: 1px solid black;\n"
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
"      background: QLinearGradient( x1"
                        ": 0, y1: 0, x2: 0, y2: 1, stop: 0 #ffa02f, stop: 0.5 #d7801a, stop: 1 #ffa02f);\n"
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
"}\n"
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
"QScrollBar::add-page:vertical, QScrol"
                        "lBar::sub-page:vertical\n"
"{\n"
"      background: none;\n"
"}"));
        gb_About = new QGroupBox(SettingDlg);
        gb_About->setObjectName(QStringLiteral("gb_About"));
        gb_About->setGeometry(QRect(10, 180, 371, 231));
        gb_About->setFont(font);
        gridLayout_2 = new QGridLayout(gb_About);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        tabWidget = new QTabWidget(gb_About);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        gridLayout_3 = new QGridLayout(tab);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        label_7 = new QLabel(tab);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setPixmap(QPixmap(QString::fromUtf8(":/icons/tasktracker.png")));
        label_7->setScaledContents(false);
        label_7->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_7);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        label_8 = new QLabel(tab);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_8);

        label_9 = new QLabel(tab);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_9);


        gridLayout_3->addLayout(verticalLayout, 0, 0, 1, 1);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        gridLayout_4 = new QGridLayout(tab_2);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        textEdit = new QTextEdit(tab_2);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setLineWrapMode(QTextEdit::NoWrap);

        gridLayout_4->addWidget(textEdit, 0, 0, 1, 1);

        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QStringLiteral("tab_3"));
        gridLayout_5 = new QGridLayout(tab_3);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        textEdit_2 = new QTextEdit(tab_3);
        textEdit_2->setObjectName(QStringLiteral("textEdit_2"));

        gridLayout_5->addWidget(textEdit_2, 0, 0, 1, 1);

        tabWidget->addTab(tab_3, QString());

        gridLayout_2->addWidget(tabWidget, 0, 0, 1, 1);

        gb_Settings = new QGroupBox(SettingDlg);
        gb_Settings->setObjectName(QStringLiteral("gb_Settings"));
        gb_Settings->setGeometry(QRect(200, 10, 181, 171));
        gb_Settings->setFont(font);
        pbClearDB = new QPushButton(gb_Settings);
        pbClearDB->setObjectName(QStringLiteral("pbClearDB"));
        pbClearDB->setGeometry(QRect(15, 120, 151, 41));
        pbClearDB->setFont(font);
        pbClearDB->setCursor(QCursor(Qt::PointingHandCursor));
        label_12 = new QLabel(gb_Settings);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setGeometry(QRect(90, 90, 31, 21));
        label_12->setFont(font);
        cbStartup = new QCheckBox(gb_Settings);
        cbStartup->setObjectName(QStringLiteral("cbStartup"));
        cbStartup->setGeometry(QRect(9, 50, 161, 41));
        gb_Shortcuts = new QGroupBox(SettingDlg);
        gb_Shortcuts->setObjectName(QStringLiteral("gb_Shortcuts"));
        gb_Shortcuts->setGeometry(QRect(10, 10, 181, 170));
        gb_Shortcuts->setFont(font);
        gridLayout = new QGridLayout(gb_Shortcuts);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(gb_Shortcuts);
        label->setObjectName(QStringLiteral("label"));
        label->setFont(font);

        horizontalLayout->addWidget(label);

        label_4 = new QLabel(gb_Shortcuts);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setScaledContents(false);

        horizontalLayout->addWidget(label_4);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_2 = new QLabel(gb_Shortcuts);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setFont(font);

        horizontalLayout_2->addWidget(label_2);

        label_5 = new QLabel(gb_Shortcuts);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout_2->addWidget(label_5);


        gridLayout->addLayout(horizontalLayout_2, 1, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_3 = new QLabel(gb_Shortcuts);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setFont(font);

        horizontalLayout_3->addWidget(label_3);

        label_6 = new QLabel(gb_Shortcuts);
        label_6->setObjectName(QStringLiteral("label_6"));

        horizontalLayout_3->addWidget(label_6);


        gridLayout->addLayout(horizontalLayout_3, 2, 0, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_10 = new QLabel(gb_Shortcuts);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setFont(font);

        horizontalLayout_4->addWidget(label_10);

        label_11 = new QLabel(gb_Shortcuts);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setScaledContents(false);

        horizontalLayout_4->addWidget(label_11);


        gridLayout->addLayout(horizontalLayout_4, 3, 0, 1, 1);


        retranslateUi(SettingDlg);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(SettingDlg);
    } // setupUi

    void retranslateUi(QDialog *SettingDlg)
    {
        SettingDlg->setWindowTitle(QApplication::translate("SettingDlg", "\330\252\331\206\330\270\333\214\331\205\330\247\330\252", 0));
        gb_About->setTitle(QApplication::translate("SettingDlg", " \330\257\330\261\330\250\330\247\330\261\331\207 ", 0));
        label_7->setText(QString());
        label_8->setText(QApplication::translate("SettingDlg", "Task-Tracker 0.1", 0));
        label_9->setText(QApplication::translate("SettingDlg", "Based on Qt 5.2.0", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("SettingDlg", "Time-Tracker", 0));
        textEdit->setHtml(QApplication::translate("SettingDlg", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'B Nazanin'; font-size:15px; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; background-color:#ffffff;\"><span style=\" font-family:'monospace'; font-size:8pt; color:#000000; background-color:#ffffff;\">Task-Tracker try to manage your tasks in better way</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; background-color:#ffffff;\"><span style=\" font-family:'monospace'; font-size:8pt; color:#000000; background-color:#ffffff;\">    Copyright (C) &lt;2014&gt;  &lt;S. Rasul Ataee&gt;</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-b"
                        "ottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'monospace'; font-size:8pt; color:#000000; background-color:#ffffff;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; background-color:#ffffff;\"><span style=\" font-family:'monospace'; font-size:8pt; color:#000000; background-color:#ffffff;\">    This program is free software: you can redistribute it and/or modify</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; background-color:#ffffff;\"><span style=\" font-family:'monospace'; font-size:8pt; color:#000000; background-color:#ffffff;\">    it under the terms of the GNU General Public License as published by</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; background-color:#ffffff;\"><span style=\" font-family:'mon"
                        "ospace'; font-size:8pt; color:#000000; background-color:#ffffff;\">    the Free Software Foundation, either version 3 of the License, or</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; background-color:#ffffff;\"><span style=\" font-family:'monospace'; font-size:8pt; color:#000000; background-color:#ffffff;\">    (at your option) any later version.</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'monospace'; font-size:8pt; color:#000000; background-color:#ffffff;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; background-color:#ffffff;\"><span style=\" font-family:'monospace'; font-size:8pt; color:#000000; background-color:#ffffff;\">    This program is distributed in the hope that it will be useful,</span></p>\n"
"<p "
                        "style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; background-color:#ffffff;\"><span style=\" font-family:'monospace'; font-size:8pt; color:#000000; background-color:#ffffff;\">    but WITHOUT ANY WARRANTY; without even the implied warranty of</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; background-color:#ffffff;\"><span style=\" font-family:'monospace'; font-size:8pt; color:#000000; background-color:#ffffff;\">    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; background-color:#ffffff;\"><span style=\" font-family:'monospace'; font-size:8pt; color:#000000; background-color:#ffffff;\">    GNU General Public License for more details.</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom"
                        ":0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'monospace'; font-size:8pt; color:#000000; background-color:#ffffff;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; background-color:#ffffff;\"><span style=\" font-family:'monospace'; font-size:8pt; color:#000000; background-color:#ffffff;\">    You should have received a copy of the GNU General Public License</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:14px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; background-color:#ffffff;\"><span style=\" font-family:'monospace'; font-size:8pt; color:#000000; background-color:#ffffff;\">    along with this program.  If not, see &lt;http://www.gnu.org/licenses/&gt;.</span></p></body></html>", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("SettingDlg", "License", 0));
        textEdit_2->setHtml(QApplication::translate("SettingDlg", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'B Nazanin'; font-size:15px; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:11pt;\">Task-Tracker 0.1 </span></p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:11pt;\">Based on lighttask developed by priomsrb qt-apps.org </span></p>\n"
"<p align=\"center\" style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:11pt;\"><br /></p>\n"
"<p align=\"center\" style=\" margin-top:0px; margi"
                        "n-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:11pt;\"> Main Developer:</span></p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:11pt;\"> S. Rasul Ataee</span></p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><a href=\"mailto:Rasul.Ataee@gmail.com\"><span style=\" font-size:11pt; text-decoration: underline; color:#0000ff;\">Rasul.Ataee@gmail.com</span></a></p>\n"
"<p align=\"center\" style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:11pt;\"><br /></p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:11pt;\">Library:<"
                        "/span></p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:11pt;\">Qt-digia Qt 5.2.0</span></p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:11pt;\">QtRPT</span></p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:15px;\">QXT</span></p></body></html>", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("SettingDlg", "Developers", 0));
        gb_Settings->setTitle(QApplication::translate("SettingDlg", " \330\252\331\206\330\270\333\214\331\205\330\247\330\252 ", 0));
        pbClearDB->setText(QApplication::translate("SettingDlg", "\331\276\330\247\332\251\330\263\330\247\330\262\333\214 \331\276\330\247\333\214\332\257\330\247\331\207 \330\257\330\247\330\257\331\207", 0));
        label_12->setText(QApplication::translate("SettingDlg", "?", 0));
        cbStartup->setText(QApplication::translate("SettingDlg", "\330\247\330\254\330\261\330\247 \331\276\330\263 \330\247\330\262 \330\250\330\247\330\261\332\257\330\260\330\247\330\261\333\214 \330\263\333\214\330\263\330\252\331\205", 0));
        gb_Shortcuts->setTitle(QApplication::translate("SettingDlg", " \330\261\330\247\331\207\331\206\331\205\330\247\333\214 \331\205\333\214\330\247\331\206\330\250\330\261 \331\207\330\247 ", 0));
        label->setText(QApplication::translate("SettingDlg", "\332\251\330\247\330\261 \330\254\330\257\333\214\330\257", 0));
        label_4->setText(QApplication::translate("SettingDlg", "Ctrl+T", 0));
        label_2->setText(QApplication::translate("SettingDlg", "\331\201\330\271\330\247\331\204/\330\272\333\214\330\261\331\201\330\271\330\247\331\204 \331\276\331\206\330\254\330\261\331\207", 0));
        label_5->setText(QApplication::translate("SettingDlg", "Ctrl+1..9", 0));
        label_3->setText(QApplication::translate("SettingDlg", "\331\206\331\205\330\247\333\214\330\264 \331\276\331\206\330\254\330\261\331\207", 0));
        label_6->setText(QApplication::translate("SettingDlg", "Ctrl+Shift+A", 0));
        label_10->setText(QApplication::translate("SettingDlg", "\330\256\330\261\331\210\330\254", 0));
        label_11->setText(QApplication::translate("SettingDlg", "Ctrl+Q", 0));
    } // retranslateUi

};

namespace Ui {
    class SettingDlg: public Ui_SettingDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGDLG_H
