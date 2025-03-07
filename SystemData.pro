QT       += core gui sql network serialport serialbus

INCLUDEPATH += /home/src

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

#LIBS += -lmysqlclient
# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
#DEFINES += QT_DEPRECATED_WARNINGS

#LIBS += -L/usr/include/modbus/lib -lmodbus

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Alarm/alarm.cpp \
    DPLCExt/dplcackbase.cpp \
    DPLCExt/dplcact.cpp \
    DPLCExt/dplcai.cpp \
    DPLCExt/dplcand.cpp \
    DPLCExt/dplcao.cpp \
    DPLCExt/dplcbase.cpp \
    DPLCExt/dplcbranch.cpp \
    DPLCExt/dplccc.cpp \
    DPLCExt/dplccw.cpp \
    DPLCExt/dplcdc.cpp \
    DPLCExt/dplcdi.cpp \
    DPLCExt/dplcdo.cpp \
    DPLCExt/dplcds.cpp \
    DPLCExt/dplcextbase.cpp \
    DPLCExt/dplcf.cpp \
    DPLCExt/dplcm.cpp \
    DPLCExt/dplcn.cpp \
    DPLCExt/dplcnot.cpp \
    DPLCExt/dplcor.cpp \
    DPLCExt/dplcpc.cpp \
    DPLCExt/dplcpw.cpp \
    DPLCExt/dplcreset.cpp \
    DPLCExt/dplcsc.cpp \
    DPLCExt/dplcserver.cpp \
    DPLCExt/dplcss.cpp \
    DPLCExt/dplcstationbase.cpp \
    DPLCExt/dplctrigger.cpp \
    DPLCExt/dplcvcc.cpp \
    Datasystem/datafreshthread.cpp \
    Datasystem/mytcpsocket.cpp \
    Datasystem/serialport.cpp \
    Datasystem/serialportserver.cpp \
    Datasystem/tcpserver.cpp \
    Filesystem/fileserver.cpp \
    Filesystem/filesocket.cpp \
    Filesystem/jsonfile.cpp \
    Globals/debugdialog.cpp \
    Globals/globals.cpp \
    Globals/main.cpp \
    Globals/mainwindow.cpp \
    Globals/threadtimer.cpp \
    Mysql/handlesysdata.cpp \
    Mysql/systemsql.cpp

HEADERS += \
    Alarm/alarm.h \
    DPLCExt/dplcackbase.h \
    DPLCExt/dplcact.h \
    DPLCExt/dplcai.h \
    DPLCExt/dplcand.h \
    DPLCExt/dplcao.h \
    DPLCExt/dplcbase.h \
    DPLCExt/dplcbranch.h \
    DPLCExt/dplccc.h \
    DPLCExt/dplccw.h \
    DPLCExt/dplcdc.h \
    DPLCExt/dplcdi.h \
    DPLCExt/dplcdo.h \
    DPLCExt/dplcds.h \
    DPLCExt/dplcextbase.h \
    DPLCExt/dplcf.h \
    DPLCExt/dplcm.h \
    DPLCExt/dplcn.h \
    DPLCExt/dplcnot.h \
    DPLCExt/dplcor.h \
    DPLCExt/dplcpc.h \
    DPLCExt/dplcpw.h \
    DPLCExt/dplcreset.h \
    DPLCExt/dplcsc.h \
    DPLCExt/dplcserver.h \
    DPLCExt/dplcss.h \
    DPLCExt/dplcstationbase.h \
    DPLCExt/dplctrigger.h \
    DPLCExt/dplcvcc.h \
    Datasystem/datafreshthread.h \
    Datasystem/mytcpsocket.h \
    Datasystem/serialport.h \
    Datasystem/serialportserver.h \
    Datasystem/tcpserver.h \
    Filesystem/fileserver.h \
    Filesystem/filesocket.h \
    Filesystem/jsonfile.h \
    Globals/debugdialog.h \
    Globals/globals.h \
    Globals/mainwindow.h \
    Globals/structdef.h \
    Globals/threadtimer.h \
    Mysql/handlesysdata.h \
    Mysql/systemsql.h

FORMS += \
    Globals/debugdialog.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
