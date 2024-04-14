#-------------------------------------------------
#
# Project created by QtCreator 2024-03-11T20:07:41
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RollTable
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CHSimPath = D:\CHSim-TKE_GBBExplorer

DESTDIR += $${CHSimPath}/Applications/SSGProduct/bin/x64/Release

DEPENDPATH += $${CHSimPath}/3rdParty/boost/bin.v2/libs/x64/Release

LIBS += -L$${CHSimPath}/3rdParty/boost/bin.v2/libs/x64/Release/ \
        -L$${CHSimPath}/Infra/Lib/x64/Release/ -lConfigurationManager -lTKB -lTKBSchemaManager -lGBB -lFilesystemWrapper -lGBBMonitorManager -lGBBManager \
        -L$${CHSimPath}/3rdParty/log4cxx/projects/release.64/ -llog4cxx


INCLUDEPATH += $${CHSimPath}/Infra \
        $${CHSimPath}/Infra/Inc \
        $${CHSimPath}/InfraSim \
        $${CHSimPath}/InfraSim/Inc \
        $${CHSimPath}/Infra/GBB \
        $${CHSimPath}/Infra/GBB/Inc \
        $${CHSimPath}/Applications/SSGProduct \
        $${CHSimPath}/Applications/SSGProduct/Inc \
        $${CHSimPath}/3rdParty/xerces/include \
        $${CHSimPath}/3rdParty/boost \
        $${CHSimPath}/3rdParty/log4cxx/src/main/include \
        $${CHSimPath}/3rdParty/boost/bin.v2/libs/x64/release


SOURCES += \
        main.cpp \
    Widget.cpp \
    detail.cpp

HEADERS += \
    Widget.h \
    detail.h

FORMS += \
        widget.ui \
    detail.ui


