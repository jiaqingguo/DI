QT       += core gui webengine webenginewidgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
#

CONFIG += c++17

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
    AddIpInfoDialog.cpp \
    AddToolDialog.cpp \
    AddToolInfoDialog.cpp \
    ApprovalProgressDialog.cpp \
    CLineEdit.cpp \
    CTableView.cpp \
    DataManageDialog.cpp \
    FilemangageDialog.cpp \
    FtpClientClass.cpp \
    InformationConfihurationDialog.cpp \
    LoginDialog.cpp \
    OneClickLoadDialog.cpp \
    OneClickSaveDialog.cpp \
    RegisterDialog.cpp \
    ResourceManageDialog.cpp \
    SoftwareWindow.cpp \
    common.cpp \
    database.cpp \
    databaseDI.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    AddIpInfoDialog.h \
    AddToolDialog.h \
    AddToolInfoDialog.h \
    ApprovalProgressDialog.h \
    CLineEdit.h \
    CPagedTableModel.h \
    CTableView.h \
    DataManageDialog.h \
    FilemangageDialog.h \
    FtpClientClass.h \
    InformationConfihurationDialog.h \
    LoginDialog.h \
    OneClickLoadDialog.h \
    OneClickSaveDialog.h \
    RegisterDialog.h \
    ResourceManageDialog.h \
    SoftwareWindow.h \
    Util/UtilTool.h \
    common.h \
    database.h \
    databaseDI.h \
    globel.h \
    mainwindow.h

FORMS += \
    AddIpInfoDialog.ui \
    AddToolDialog.ui \
    AddToolInfoDialog.ui \
    ApprovalProgressDialog.ui \
    DataManageDialog.ui \
    FilemangageDialog.ui \
    InformationConfihurationDialog.ui \
    LoginDialog.ui \
    OneClickLoadDialog.ui \
    OneClickSaveDialog.ui \
    RegisterDialog.ui \
    ResourceManageDialog.ui \
    SoftwareWindow.ui \
    mainwindow.ui


RC_FILE = icon.rc
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resoirce.qrc


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/mysql/lib/ -llibmysql
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/mysql/lib/ -llibmysql
else:unix: LIBS += -L$$PWD/mysql/lib/ -llibmysql

INCLUDEPATH += $$PWD/mysql/include
DEPENDPATH += $$PWD/mysql/include

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/mysql/lib/libmysql.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/mysql/lib/libmysql.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/mysql/lib/libmysql.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/mysql/lib/libmysql.lib
else:unix: PRE_TARGETDEPS += $$PWD/mysql/lib/libmysql.a
