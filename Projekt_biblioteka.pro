QT       += core gui
QT += sql

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
    clientwindow.cpp \
    main.cpp \
    mainwindow.cpp \
    sqlconsole.cpp \
    src/address.cpp \
    src/author.cpp \
    src/book.cpp \
    src/client.cpp \
    src/color.cpp \
    src/dbmanager.cpp \
    src/publisher.cpp \
    src/rent.cpp \
    src/table.cpp \
    src/user.cpp \
    src/worker.cpp \
    workerwindow.cpp

HEADERS += \
    clientwindow.h \
    lib/address.h \
    lib/author.h \
    lib/book.h \
    lib/client.h \
    lib/color.h \
    lib/dbmanager.h \
    lib/publisher.h \
    lib/rent.h \
    lib/table.h \
    lib/user.h \
    lib/worker.h \
    mainwindow.h \
    sqlconsole.h \
    workerwindow.h

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    MyResources.qrc
