#-------------------------------------------------
#
# Project created by QtCreator 2012-04-25T09:46:57
#
#-------------------------------------------------

QT       += core gui

TARGET = targettracking2
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    ttmap.cpp \
    settingdialog.cpp \
    matrixtcl/matrix.cc \
    model/TargetGroup.cpp \
    model/SystemModel.cpp \
    model/State.cpp \
    model/MeasureModel.cpp \
    comm.cpp \
    model/singletarget.cpp \
    datasource/targetgenerator.cpp \
    view/singletargetview.cpp \
    view/targetgroupview.cpp \
    tablemodels/groupinfotablemodel.cpp \
    grouplistwindow.cpp \
    groupinfowindow.cpp

HEADERS  += mainwindow.h \
    ttmap.h \
    settingdialog.h \
    matrixtcl/matrix2.hxx \
    model/TargetGroup.h \
    model/SystemModel.h \
    model/State.h \
    model/MeasureModel.h \
    comm.h \
    matrixtcl/cmatrix \
    model/singletarget.h \
    datasource/targetgenerator.h \
    view/singletargetview.h \
    view/targetgroupview.h \
    filter/KalmanFilter.h \
    filter/IMMFilter.h \
    grouplistwindow.h \
    groupinfowindow.h \
    tablemodels/grouplisttablemodel.h

FORMS    += mainwindow.ui \
    settingdialog.ui \
    grouplistwindow.ui \
    groupinfowindow.ui
