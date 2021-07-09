QT       += core gui

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
    Main.cpp \
    MainWindow.cpp \
    Programmer.cpp \
    TypeWriterLinux.cpp \
    TypeWriterMacOS.cpp \
    TypeWriterWindows.cpp

HEADERS += \
    MainWindow.h \
    Programmer.h \
    TypeWriter.h \
    TypeWriterLinux.h \
    TypeWriterMacOS.h \
    TypeWriterWindows.h \
    var.h

FORMS += \
    MainWindow.ui

RESOURCES += \
    MainWindow.qrc

linux:{
    QMAKE_LFLAGS += -static-libgcc -static-libstdc++
    QMAKE_LIBS += -lX11 -lXtst
}

unix:{
    isEmpty(PREFIX){
        PREFIX = /usr
    }
    target.path = $$PREFIX/bin

    shortcutfiles.files = duckiesqueui.desktop
    shortcutfiles.path = $$PREFIX/share/applications/
    data.files = Ducky.png
    data.path = $$PREFIX/share/pixmaps/

    INSTALLS += shortcutfiles
    INSTALLS += data
}

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /usr/bin
!isEmpty(target.path): INSTALLS += target

macx:{
    QMAKE_CFLAGS += -Xlinker -unexported_symbol -Xlinker "*"
    QMAKE_LIBS += -framework ApplicationServices
}

win32:{
    QMAKE_LFLAGS += -static -static-libgcc -static-libstdc++
}

