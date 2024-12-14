QT       += core gui sql network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    fileserver2.cpp \
    filesocket.cpp \
    globals.cpp \
    jsonfile.cpp \
    main.cpp \
    mainwindow.cpp \
    mytcpsocket.cpp \
    systembase.cpp \
    systembaseallog.cpp \
    systembasedatahis.cpp \
    systembasedatarec.cpp \
    systembasedatart.cpp \
    systembasedepartment.cpp \
    systembasedevice.cpp \
    systembasegroup.cpp \
    systembasemanagers.cpp \
    systembaseoperations.cpp \
    systembaseoplog.cpp \
    systembaseroles.cpp \
    systembasesheet.cpp \
    systembasesheetdata.cpp \
    systembasesheetfield.cpp \
    systembasesyslog.cpp \
    systembaseuser.cpp \
    systemsql.cpp \
    tcpserver.cpp

HEADERS += \
    fileserver2.h \
    filesocket.h \
    globals.h \
    jsonfile.h \
    mainwindow.h \
    mytcpsocket.h \
    systembase.h \
    systembaseallog.h \
    systembasedatahis.h \
    systembasedatarec.h \
    systembasedatart.h \
    systembasedepartment.h \
    systembasedevice.h \
    systembasegroup.h \
    systembasemanagers.h \
    systembaseoperations.h \
    systembaseoplog.h \
    systembaseroles.h \
    systembasesheet.h \
    systembasesheetdata.h \
    systembasesheetfield.h \
    systembasesyslog.h \
    systembaseuser.h \
    systemsql.h \
    tcpserver.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
