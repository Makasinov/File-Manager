#-------------------------------------------------
#
# Project created by QtCreator 2017-10-04T19:46:09
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = newKursach
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
        mainwindow.cpp \
        customtree.cpp \
        prop.cpp

HEADERS += \
        mainwindow.h \
        customtree.h \
        prop.h \
    customtree (Конфликтующая копия с компьютера MAIN-PC 2017-11-01).h \
    customtree (Конфликтующая копия с компьютера maksimov 2017-11-04).h \
    customtree.h \
    mainwindow (Конфликтующая копия с компьютера maksimov 2017-11-04).h \
    mainwindow.h \
    prop.h

FORMS += \
        mainwindow.ui \
        prop.ui \
        prop.ui

DISTFILES += \
    search.png \
    search.png

#QMAKE_CXXFLAGS += -std=c++17

#CONFIG += c++17
#QMAKE_CXXFLAGS+= -std=c++17
#QMAKE_LFLAGS +=  -std=c++17
#CONFIG += c++1z

#INCLUDEPATH += B:/boost_1_65_1/
#LIBS += "-LB:/boost_1_65_1/libs/"

win32-g++ {
    INCLUDEPATH += B:/BOOST/boost_mingw530_32/include/boost-1_65_1
    LIBS += "-LB:/BOOST/boost_mingw530_32/lib" \
            -llibboost_filesystem-mgw53-mt-1_65_1.dll \
            -llibboost_filesystem-mgw53-mt-d-1_65_1.dll \
            -llibboost_system-mgw53-mt-1_65_1.dll \
            -llibboost_system-mgw53-mt-d-1_65_1
            #-llibboost_date_time-mgw53-mt-1_65_1.dll \
            #-llibboost_date_time-mgw53-mt-1_65_1.dll.a \
            #-llibboost_date_time-mgw53-mt-d-1_65_1.dll \
            #-llibboost_date_time-mgw53-mt-d-1_65_1.dll.a
            #-lboost_system

} else:win32-msvc* {
    INCLUDEPATH += B:/BOOST/boost_msvc/include/boost-1_65_1
    LIBS += "-LB:/BOOST/boost_msvc/lib" \
            #-llibboost_date_time-mgw53-mt-1_65_1.dll \
            #-llibboost_date_time-mgw53-mt-1_65_1.dll.a \
            #-llibboost_date_time-mgw53-mt-d-1_65_1.dll \
            #-llibboost_date_time-mgw53-mt-d-1_65_1.dll.a \

}
#CONFIG += console

