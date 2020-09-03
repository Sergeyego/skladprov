#-------------------------------------------------
#
# Project created by QtCreator 2012-07-11T11:02:12
#
#-------------------------------------------------

QT       += core gui sql network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = skladprov
TEMPLATE = app

include(xlsx/qtxlsx.pri)

SOURCES += main.cpp\
        mainwidget.cpp \
    instockwidget.cpp \
    modelnakl.cpp \
    modelnaklitem.cpp \
    presencewidget.cpp \
    modelpresence.cpp \
    infoshipwidget.cpp \
    modelship.cpp \
    modelshipdata.cpp \
    chdatewidget.cpp \
    reportwidget.cpp \
    shipwidget.cpp \
    db/dbdelegate.cpp \
    db/dblogin.cpp \
    db/dbmapper.cpp \
    db/dbtablemodel.cpp \
    db/dbviewer.cpp \
    olap/axiswidget.cpp \
    olap/cubewidget.cpp \
    olap/cubic.cpp \
    olap/olapmodel.cpp \
    olap/tableview.cpp

HEADERS  += mainwidget.h \
    instockwidget.h \
    modelnakl.h \
    modelnaklitem.h \
    presencewidget.h \
    modelpresence.h \
    infoshipwidget.h \
    modelship.h \
    modelshipdata.h \
    chdatewidget.h \
    reportwidget.h \
    shipwidget.h \
    db/dbdelegate.h \
    db/dblogin.h \
    db/dbmapper.h \
    db/dbtablemodel.h \
    db/dbviewer.h \
    olap/axiswidget.h \
    olap/cubewidget.h \
    olap/cubic.h \
    olap/olapmodel.h \
    olap/tableview.h

FORMS    += mainwidget.ui \
    instockwidget.ui \
    presencewidget.ui \
    infoshipwidget.ui \
    chdatewidget.ui \
    reportwidget.ui \
    shipwidget.ui \
    db/dblogin.ui \
    olap/axiswidget.ui \
    olap/cubewidget.ui

RESOURCES += \
    res.qrc

RC_FILE = ico.rc

DISTFILES += \
    ico.rc
