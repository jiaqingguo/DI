QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

LIBS += -liphlpapi
LIBS += -lPdh

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += gethostinformation.cpp \
    CPerformHelper.cpp \
    Win32Utils/CDeviceHelper.cpp \
    Win32Utils/CStrUtils.cpp \
    Win32Utils/CWmiQueryHelper.cpp \
    ZipFunction.cpp \
    main.cpp \
    widget.cpp

HEADERS += gethostinformation.h \
    CPerformHelper.h \
    Win32Utils/CDeviceHelper.h \
    Win32Utils/CStrUtils.h \
    Win32Utils/CWmiQueryHelper.h \
    ZipFunction.h \
    widget.h \


FORMS += \
    widget.ui




# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/libzip/lib/ -lzip
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/libzip/lib/ -lzip
else:unix: LIBS += -L$$PWD/libzip/lib/ -lzip

INCLUDEPATH += $$PWD/libzip/include
DEPENDPATH += $$PWD/libzip/include

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/libzip/lib/zip.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/libzip/lib/zip.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/libzip/lib/zip.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/libzip/lib/zip.lib
else:unix: PRE_TARGETDEPS += $$PWD/libzip/lib/zip.a
