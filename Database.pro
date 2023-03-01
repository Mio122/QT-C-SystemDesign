#-------------------------------------------------
#
# Project created by QtCreator 2019-04-15T12:20:18
#
#-------------------------------------------------

QT       += core gui sql webkitwidgets printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Database
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    databaselogin.cpp \
    formuser.cpp \
    formtable.cpp \
    forminput.cpp \
    formexit.cpp \
    usernew.cpp \
    useredit.cpp \
    userdele.cpp \
    usersele.cpp \
    sqlsear.cpp \
    userchan.cpp \
    tablebath.cpp \
    tablebathedit.cpp \
    tablebathdele.cpp \
    tablebathsele.cpp \
    curingnew.cpp \
    curingedit.cpp \
    curingdele.cpp \
    curingsele.cpp \
    resinnew.cpp \
    resinedit.cpp \
    resindele.cpp \
    resinsele.cpp \
    fibernew.cpp \
    fiberedit.cpp \
    fiberdele.cpp \
    fibersele.cpp \
    resincosnew.cpp \
    resincosedit.cpp \
    resincosdele.cpp \
    resincossele.cpp \
    curingcosnew.cpp \
    curingcosedit.cpp \
    curingcosdele.cpp \
    curingcossele.cpp \
    fibercosnew.cpp \
    fibercosedit.cpp \
    fibercosdele.cpp \
    fibercossele.cpp \
    userlogdele.cpp \
    userlogsele.cpp \
    robotnew.cpp \
    robotedit.cpp \
    robotdele.cpp \
    robotsele.cpp \
    workdata.cpp \
    workdataedit.cpp \
    workdatadele.cpp \
    workdatasele.cpp \
    qmysqlquerymodel.cpp \
    input.cpp \
    output.cpp \
    echarts.cpp \
    cJSON.c \
    report.cpp \
    setting.cpp

HEADERS += \
        mainwindow.h \
    databaselogin.h \
    formuser.h \
    formtable.h \
    forminput.h \
    formexit.h \
    usernew.h \
    useredit.h \
    userdele.h \
    usersele.h \
    sqlsear.h \
    userchan.h \
    tablebath.h \
    tablebathedit.h \
    tablebathdele.h \
    tablebathsele.h \
    curingnew.h \
    curingedit.h \
    curingdele.h \
    curingsele.h \
    resinnew.h \
    resinedit.h \
    resindele.h \
    resinsele.h \
    fibernew.h \
    fiberedit.h \
    fiberdele.h \
    fibersele.h \
    resincosnew.h \
    resincosedit.h \
    resincosdele.h \
    resincossele.h \
    curingcosnew.h \
    curingcosedit.h \
    curingcosdele.h \
    curingcossele.h \
    fibercosnew.h \
    fibercosedit.h \
    fibercosdele.h \
    fibercossele.h \
    userlogdele.h \
    userlogsele.h \
    robotnew.h \
    robotedit.h \
    robotdele.h \
    robotsele.h \
    workdata.h \
    workdataedit.h \
    workdatadele.h \
    workdatasele.h \
    qmysqlquerymodel.h \
    input.h \
    output.h \
    echarts.h \
    cJSON.h \
    report.h \
    setting.h

FORMS += \
        mainwindow.ui \
    databaselogin.ui \
    formuser.ui \
    formtable.ui \
    forminput.ui \
    formexit.ui \
    usernew.ui \
    useredit.ui \
    userdele.ui \
    usersele.ui \
    sqlsear.ui \
    userchan.ui \
    tablebath.ui \
    tablebathedit.ui \
    tablebathdele.ui \
    tablebathsele.ui \
    curingnew.ui \
    curingedit.ui \
    curingdele.ui \
    curingsele.ui \
    resinnew.ui \
    resinedit.ui \
    resindele.ui \
    resinsele.ui \
    fibernew.ui \
    fiberedit.ui \
    fiberdele.ui \
    fibersele.ui \
    resincosnew.ui \
    resincosedit.ui \
    resincosdele.ui \
    resincossele.ui \
    curingcosnew.ui \
    curingcosedit.ui \
    curingcosdele.ui \
    curingcossele.ui \
    fibercosnew.ui \
    fibercosedit.ui \
    fibercosdele.ui \
    fibercossele.ui \
    userlogdele.ui \
    userlogsele.ui \
    robotnew.ui \
    robotedit.ui \
    robotdele.ui \
    robotsele.ui \
    workdata.ui \
    workdataedit.ui \
    workdatadele.ui \
    workdatasele.ui \
    input.ui \
    output.ui \
    echarts.ui \
    report.ui \
    setting.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc \
    qss.qrc
