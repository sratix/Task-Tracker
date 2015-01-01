INCLUDEPATH += $$PWD

SOURCES += $$PWD/CommonClasses.cpp \
           $$PWD/chart.cpp
HEADERS += $$PWD/CommonClasses.h \
           $$PWD/chart.h

include($$PWD/Barcode/Barcode.pri)
