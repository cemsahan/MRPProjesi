#-------------------------------------------------
#
# Project created by QtCreator 2018-07-23T14:02:19
#
#-------------------------------------------------

QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Bom
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


SOURCES += \
        main.cpp \
    connect.cpp \
    VeriTabaniIslemleri.cpp \
    MainWindow.cpp \
    AnaEkran.cpp \
    guncelleForm.cpp \
    UrunStruct.cpp \
    depoekrani.cpp \
    SirketEkrani.cpp \
    DepoBilgi.cpp \
    BildirimEkraniDepo.cpp

HEADERS += \
    connect.h \
    VeriTabaniIslemleri.h \
    MainWindow.h \
    AnaEkran.h \
    guncelleForm.h \
    UrunStruct.h \
    depoekrani.h \
    SirketEkrani.h \
    DepoBilgi.h \
    BildirimEkraniDepo.h

FORMS += \
    MainWindow.ui \
    AnaEkran.ui \
    guncelleForm.ui \
    depoekrani.ui \
    SirketEkrani.ui \
    BildirimEkraniDepo.ui


win32: LIBS += -L$$PWD/../../../Desktop/mysql-connector-c-6.1.6-win32/lib/ -llibmysql

INCLUDEPATH += $$PWD/../../../Desktop/mysql-connector-c-6.1.6-win32/include
DEPENDPATH += $$PWD/../../../Desktop/mysql-connector-c-6.1.6-win32/include

win32: LIBS += -L$$PWD/../mysql-connector-c-6.1.6-win32/lib/ -llibmysql

INCLUDEPATH += $$PWD/../mysql-connector-c-6.1.6-win32/include
DEPENDPATH += $$PWD/../mysql-connector-c-6.1.6-win32/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../mysql-connector-c-6.1.6-win32/lib/ -llibmysql
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../mysql-connector-c-6.1.6-win32/lib/ -llibmysqld
else:unix: LIBS += -L$$PWD/../../mysql-connector-c-6.1.6-win32/lib/ -llibmysql

INCLUDEPATH += $$PWD/../../mysql-connector-c-6.1.6-win32/include
DEPENDPATH += $$PWD/../../mysql-connector-c-6.1.6-win32/include
