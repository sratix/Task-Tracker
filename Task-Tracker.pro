#-------------------------------------------------
#
# Project created by QtCreator 2014-11-27T16:11:20
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4)
{
    QT += widgets printsupport
    DEFINES += HAVE_QT5
}

TARGET = TaskTracker
TEMPLATE = app

MOC_DIR        = ./buildTMP/MOC
OBJECTS_DIR    = ./buildTMP/OBJ
RCC_DIR        = ./buildTMP/RC
UI_DIR         = Include/UI

DEFINES += ENABLE_LOGGER
USE_QXT = 1

INCLUDEPATH += ThirdParty\
    Include

SOURCES += \
    main.cpp \
    Src/TaskButton.cpp \
    Src/MainWindow.cpp \
    Src/SettingDlg.cpp \
    Src/Report.cpp \
    Src/DBManager.cpp \
    Src/Task.cpp \
    Src/JalaliDate.cpp \
    Src/TimeEditWidget.cpp \
    Src/logger.cpp \
    Src/qticonloader.cc

HEADERS  += \
    Include/JalaliDate.h \
    Include/TimeEditWidget.h \
    Include/TaskButton.h \
    Include/Task.h \
    Include/qticonloader.h \
    Include/DBManager.h \
    Include/MainWindow.h \
    Include/Const.h \
    Include/logger.h \
    Include/Report.h \
    Include/SettingDlg.h \
    ui_MainWindow.h \
    ui_SettingDlg.h \
    ui_TimeEditWidget.h

FORMS    += \
    Ui/TimeEditWidget.ui \
    Ui/MainWindow.ui \
    Ui/SettingDlg.ui

OTHER_FILES += \
    Other/tasktracker.rc

RC_FILE = Other/tasktracker.rc

RESOURCES += \
    Res/data/data.qrc \
    Res/icons/icons.qrc

include(ThirdParty/QtRPT/QtRPT.pri)
equals(USE_QXT,1)
{
    win32{
        SOURCES += ThirdParty/qxt/qxtglobalshortcut_win.cpp
    }
    unix{
        SOURCES += ThirdParty/qxt/qxtglobalshortcut_x11.cpp
        LIBS    += -lX11 -lXfixes
    }
    DEFINES += BUILD_QXT_GUI

    HEADERS += ThirdParty/qxt/qxtglobal.h
    SOURCES += ThirdParty/qxt/qxtglobal.cpp

    HEADERS += ThirdParty/qxt/qxtglobalshortcut.h
    HEADERS += ThirdParty/qxt/qxtglobalshortcut_p.h
    SOURCES += ThirdParty/qxt/qxtglobalshortcut.cpp
}
