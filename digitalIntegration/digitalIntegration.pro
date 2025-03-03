QT       += core gui webengine webenginewidgets multimedia axcontainer network winextras
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
    C7Zip.cpp \
    CAxWidget.cpp \
    CDoublePushButton.cpp \
    CLineEdit.cpp \
    CTableView.cpp \
    CWidget.cpp \
    ChangePwdDialog.cpp \
    CtrlNetwork.cpp \
    CustomTitleWidget.cpp \
    DataManageDialog.cpp \
    FilemangageDialog.cpp \
    FtpClientClass.cpp \
    FtpClientWidget.cpp \
    FtpDialog.cpp \
    GifDialog.cpp \
    GifThread.cpp \
    Global.cpp \
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
    fingerDlg.cpp \
    main.cpp \
    mainwindow.cpp \
    progressDialog.cpp

HEADERS += \
    AddIpInfoDialog.h \
    AddToolDialog.h \
    AddToolInfoDialog.h \
    ApprovalProgressDialog.h \
    C7Zip.h \
    CAxWidget.h \
    CDoublePushButton.h \
    CLineEdit.h \
    CPagedTableModel.h \
    CTableView.h \
    CWidget.h \
    ChangePwdDialog.h \
    CtrlNetwork.h \
    CustomTitleWidget.h \
    DataManageDialog.h \
    FilemangageDialog.h \
    FtpClientClass.h \
    FtpClientWidget.h \
    FtpDialog.h \
    GifDialog.h \
    GifThread.h \
    Global.h \
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
    fingerDlg.h \
    globel.h \
    mainwindow.h \
    progressDialog.h

FORMS += \
    AddIpInfoDialog.ui \
    AddToolDialog.ui \
    AddToolInfoDialog.ui \
    ApprovalProgressDialog.ui \
    ChangePwdDialog.ui \
    CustomTitleWidget.ui \
    DataManageDialog.ui \
    FilemangageDialog.ui \
    FtpClientWidget.ui \
    FtpDialog.ui \
    GifDialog.ui \
    InformationConfihurationDialog.ui \
    LoginDialog.ui \
    OneClickLoadDialog.ui \
    OneClickSaveDialog.ui \
    RegisterDialog.ui \
    ResourceManageDialog.ui \
    SoftwareWindow.ui \
    mainwindow.ui \
    progressDialog.ui


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

#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/libxzkfp/x64lib/ -llibzkfp
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/libxzkfp/x64lib/ -llibzkfp
#else:unix: LIBS += -L$$PWD/libxzkfp/x64lib/ -llibzkfp

#INCLUDEPATH += $$PWD/libxzkfp/include
#DEPENDPATH += $$PWD/libxzkfp/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/libFtp/Release/ -lQt5Ftp
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/libFtp/Debug/ -lQt5Ftpd
else:unix: LIBS += -L$$PWD/libFtp/unix/ -lQt5Ftp

INCLUDEPATH += $$PWD/libFtp/include
DEPENDPATH += $$PWD/libFtp/include

