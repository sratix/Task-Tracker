QT       += gui xml script sql

greaterThan(QT_MAJOR_VERSION, 4){
    QT += widgets printsupport
    DEFINES += HAVE_QT5
}
include(CommonFiles/CommonFiles_QtRpt.pri)

INCLUDEPATH += $$PWD

SOURCES += $$PWD/qtrpt.cpp \
           $$PWD/RptSql.cpp
HEADERS += $$PWD/qtrpt.h \
           $$PWD/qtrptnamespace.h \
           $$PWD/RptSql.h
