QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    person.pb.cc

HEADERS += \
    mainwindow.h \
    person.pb.h

INCLUDEPATH += /usr/include \
                /usr/include/x86_64-linux-gnu \
                /usr/include/c++/8
LIBS += -L/usr/lib/x86_64-linux-gnu -lprotobuf

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
