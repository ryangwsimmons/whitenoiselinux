QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

VERSION_MAJOR = 2
VERSION_MINOR = 0

DEFINES += "VERSION_MAJOR=$$VERSION_MAJOR"\
        "VERSION_MINOR=$$VERSION_MINOR"

SOURCES += \
    main.cpp \
    wnlaboutdialog.cpp \
    wnlmainwindow.cpp

HEADERS += \
    wnlaboutdialog.h \
    wnlmainwindow.h

FORMS += \
    wnlaboutdialog.ui \
    wnlmainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources_WhiteNoiseLinux.qrc
