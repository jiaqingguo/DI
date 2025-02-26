/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "ApprovalProgressDialog.h"
#include "FtpDialog.h"
#include "InformationConfihurationDialog.h"
#include "ResourceManageDialog.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionM1;
    QAction *actionM2;
    QAction *actionM3;
    QAction *actionM4;
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout_8;
    QSplitter *splitter;
    QWidget *widgetLeftMenu;
    QVBoxLayout *verticalLayout_8;
    QWidget *widgetLOGO;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_8;
    QPushButton *btnTitleIcon;
    QSpacerItem *horizontalSpacer_9;
    QTreeWidget *treeWidget;
    QWidget *widget;
    QVBoxLayout *verticalLayout_6;
    QWidget *widgetTital;
    QHBoxLayout *horizontalLayout_6;
    QLabel *btnChildTitle;
    QSpacerItem *horizontalSpacer;
    QLabel *labelUserIcon;
    QLabel *labelUserName;
    QPushButton *btnMinimize;
    QPushButton *btnMaximize;
    QPushButton *btnClose;
    QStackedWidget *stackedWidget;
    ResourceManageDialog *m_ResourceManageDialog;
    InformationConfihurationDialog *m_InforConfihurationDialog;
    FtpDialog *m_FtpDialog;
    ApprovalProgressDialog *m_ApprovalProgressDialog;
    QVBoxLayout *verticalLayout;
    QWidget *page4;
    QVBoxLayout *verticalLayout_5;
    QWidget *widgetM1;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *btnM1Load;
    QPushButton *btnM1Save;
    QTabWidget *tabWidgetModulel1;
    QWidget *tab;
    QGridLayout *gridLayout_6;
    QWidget *widgetSize1;
    QGridLayout *gridLayout_5;
    QPushButton *btnAddTab1;
    QWidget *tab_2;
    QWidget *page5;
    QVBoxLayout *verticalLayout_4;
    QWidget *widgetM2;
    QHBoxLayout *horizontalLayout_5;
    QHBoxLayout *layoutM2ToolIcon;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *btnM2Load;
    QPushButton *btnM2Save;
    QTabWidget *tabWidgetModulel2;
    QWidget *tab_3;
    QGridLayout *gridLayout_4;
    QWidget *widgetSize2;
    QGridLayout *gridLayout_7;
    QPushButton *btnAddTab2;
    QWidget *tab_4;
    QWidget *page6;
    QVBoxLayout *verticalLayout_3;
    QWidget *widgetM3;
    QHBoxLayout *horizontalLayout_7;
    QHBoxLayout *layoutM3ToolIcon;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *btnM3Load;
    QPushButton *btnM3Save;
    QTabWidget *tabWidgetModulel3;
    QWidget *tab_5;
    QGridLayout *gridLayout_3;
    QWidget *widgetSize3;
    QGridLayout *gridLayout_8;
    QPushButton *btnAddTab3;
    QWidget *tab_6;
    QWidget *page7;
    QVBoxLayout *verticalLayout_2;
    QWidget *widgetM4;
    QHBoxLayout *horizontalLayout_9;
    QSpacerItem *horizontalSpacer_6;
    QPushButton *btnM4Load;
    QPushButton *btnM4Save;
    QTabWidget *tabWidgetModulel4;
    QWidget *tab_7;
    QGridLayout *gridLayout;
    QWidget *widgetSize4;
    QGridLayout *gridLayout_9;
    QPushButton *btnAddTab4;
    QWidget *tab_8;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1184, 735);
        MainWindow->setMinimumSize(QSize(710, 437));
        actionM1 = new QAction(MainWindow);
        actionM1->setObjectName(QString::fromUtf8("actionM1"));
        actionM1->setCheckable(true);
        actionM2 = new QAction(MainWindow);
        actionM2->setObjectName(QString::fromUtf8("actionM2"));
        actionM2->setCheckable(true);
        actionM3 = new QAction(MainWindow);
        actionM3->setObjectName(QString::fromUtf8("actionM3"));
        actionM3->setCheckable(true);
        actionM4 = new QAction(MainWindow);
        actionM4->setObjectName(QString::fromUtf8("actionM4"));
        actionM4->setCheckable(true);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayout_8 = new QHBoxLayout(centralwidget);
        horizontalLayout_8->setSpacing(0);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        horizontalLayout_8->setContentsMargins(0, 0, 0, 0);
        splitter = new QSplitter(centralwidget);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        splitter->setOpaqueResize(true);
        widgetLeftMenu = new QWidget(splitter);
        widgetLeftMenu->setObjectName(QString::fromUtf8("widgetLeftMenu"));
        verticalLayout_8 = new QVBoxLayout(widgetLeftMenu);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        verticalLayout_8->setContentsMargins(-1, -1, 0, -1);
        widgetLOGO = new QWidget(widgetLeftMenu);
        widgetLOGO->setObjectName(QString::fromUtf8("widgetLOGO"));
        horizontalLayout = new QHBoxLayout(widgetLOGO);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer_8 = new QSpacerItem(45, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_8);

        btnTitleIcon = new QPushButton(widgetLOGO);
        btnTitleIcon->setObjectName(QString::fromUtf8("btnTitleIcon"));
        btnTitleIcon->setMinimumSize(QSize(155, 86));
        btnTitleIcon->setMaximumSize(QSize(1111111, 11111));

        horizontalLayout->addWidget(btnTitleIcon);

        horizontalSpacer_9 = new QSpacerItem(45, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_9);


        verticalLayout_8->addWidget(widgetLOGO);

        treeWidget = new QTreeWidget(widgetLeftMenu);
        treeWidget->setObjectName(QString::fromUtf8("treeWidget"));

        verticalLayout_8->addWidget(treeWidget);

        splitter->addWidget(widgetLeftMenu);
        widget = new QWidget(splitter);
        widget->setObjectName(QString::fromUtf8("widget"));
        verticalLayout_6 = new QVBoxLayout(widget);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        widgetTital = new QWidget(widget);
        widgetTital->setObjectName(QString::fromUtf8("widgetTital"));
        horizontalLayout_6 = new QHBoxLayout(widgetTital);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        btnChildTitle = new QLabel(widgetTital);
        btnChildTitle->setObjectName(QString::fromUtf8("btnChildTitle"));

        horizontalLayout_6->addWidget(btnChildTitle);

        horizontalSpacer = new QSpacerItem(343, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer);

        labelUserIcon = new QLabel(widgetTital);
        labelUserIcon->setObjectName(QString::fromUtf8("labelUserIcon"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(labelUserIcon->sizePolicy().hasHeightForWidth());
        labelUserIcon->setSizePolicy(sizePolicy);
        labelUserIcon->setMinimumSize(QSize(40, 25));
        labelUserIcon->setMaximumSize(QSize(40, 25));

        horizontalLayout_6->addWidget(labelUserIcon);

        labelUserName = new QLabel(widgetTital);
        labelUserName->setObjectName(QString::fromUtf8("labelUserName"));
        sizePolicy.setHeightForWidth(labelUserName->sizePolicy().hasHeightForWidth());
        labelUserName->setSizePolicy(sizePolicy);
        labelUserName->setMinimumSize(QSize(0, 25));
        labelUserName->setMaximumSize(QSize(16777215, 25));

        horizontalLayout_6->addWidget(labelUserName);

        btnMinimize = new QPushButton(widgetTital);
        btnMinimize->setObjectName(QString::fromUtf8("btnMinimize"));
        btnMinimize->setMinimumSize(QSize(44, 36));
        btnMinimize->setMaximumSize(QSize(44, 36));

        horizontalLayout_6->addWidget(btnMinimize);

        btnMaximize = new QPushButton(widgetTital);
        btnMaximize->setObjectName(QString::fromUtf8("btnMaximize"));
        btnMaximize->setMinimumSize(QSize(44, 36));
        btnMaximize->setMaximumSize(QSize(44, 36));

        horizontalLayout_6->addWidget(btnMaximize);

        btnClose = new QPushButton(widgetTital);
        btnClose->setObjectName(QString::fromUtf8("btnClose"));
        btnClose->setMinimumSize(QSize(44, 36));
        btnClose->setMaximumSize(QSize(44, 36));

        horizontalLayout_6->addWidget(btnClose);


        verticalLayout_6->addWidget(widgetTital);

        stackedWidget = new QStackedWidget(widget);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        m_ResourceManageDialog = new ResourceManageDialog();
        m_ResourceManageDialog->setObjectName(QString::fromUtf8("m_ResourceManageDialog"));
        stackedWidget->addWidget(m_ResourceManageDialog);
        m_InforConfihurationDialog = new InformationConfihurationDialog();
        m_InforConfihurationDialog->setObjectName(QString::fromUtf8("m_InforConfihurationDialog"));
        stackedWidget->addWidget(m_InforConfihurationDialog);
        m_FtpDialog = new FtpDialog();
        m_FtpDialog->setObjectName(QString::fromUtf8("m_FtpDialog"));
        stackedWidget->addWidget(m_FtpDialog);
        m_ApprovalProgressDialog = new ApprovalProgressDialog();
        m_ApprovalProgressDialog->setObjectName(QString::fromUtf8("m_ApprovalProgressDialog"));
        verticalLayout = new QVBoxLayout(m_ApprovalProgressDialog);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        stackedWidget->addWidget(m_ApprovalProgressDialog);
        page4 = new QWidget();
        page4->setObjectName(QString::fromUtf8("page4"));
        verticalLayout_5 = new QVBoxLayout(page4);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        widgetM1 = new QWidget(page4);
        widgetM1->setObjectName(QString::fromUtf8("widgetM1"));
        widgetM1->setMinimumSize(QSize(0, 65));
        widgetM1->setMaximumSize(QSize(16777215, 65));
        horizontalLayout_4 = new QHBoxLayout(widgetM1);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer_3 = new QSpacerItem(415, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_3);

        btnM1Load = new QPushButton(widgetM1);
        btnM1Load->setObjectName(QString::fromUtf8("btnM1Load"));
        btnM1Load->setMinimumSize(QSize(132, 52));
        btnM1Load->setMaximumSize(QSize(132, 52));

        horizontalLayout_4->addWidget(btnM1Load);

        btnM1Save = new QPushButton(widgetM1);
        btnM1Save->setObjectName(QString::fromUtf8("btnM1Save"));
        btnM1Save->setMinimumSize(QSize(55, 52));
        btnM1Save->setMaximumSize(QSize(52, 52));

        horizontalLayout_4->addWidget(btnM1Save);


        verticalLayout_5->addWidget(widgetM1);

        tabWidgetModulel1 = new QTabWidget(page4);
        tabWidgetModulel1->setObjectName(QString::fromUtf8("tabWidgetModulel1"));
        tabWidgetModulel1->setTabShape(QTabWidget::Rounded);
        tabWidgetModulel1->setElideMode(Qt::ElideMiddle);
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        gridLayout_6 = new QGridLayout(tab);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        gridLayout_6->setHorizontalSpacing(0);
        gridLayout_6->setContentsMargins(0, 0, 0, 0);
        widgetSize1 = new QWidget(tab);
        widgetSize1->setObjectName(QString::fromUtf8("widgetSize1"));
        gridLayout_5 = new QGridLayout(widgetSize1);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        btnAddTab1 = new QPushButton(widgetSize1);
        btnAddTab1->setObjectName(QString::fromUtf8("btnAddTab1"));
        btnAddTab1->setMinimumSize(QSize(80, 80));
        btnAddTab1->setMaximumSize(QSize(80, 80));
        QFont font;
        font.setFamily(QString::fromUtf8("Bauhaus 93"));
        font.setPointSize(35);
        btnAddTab1->setFont(font);

        gridLayout_5->addWidget(btnAddTab1, 0, 0, 1, 1);


        gridLayout_6->addWidget(widgetSize1, 0, 0, 1, 1);

        tabWidgetModulel1->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        tabWidgetModulel1->addTab(tab_2, QString());

        verticalLayout_5->addWidget(tabWidgetModulel1);

        stackedWidget->addWidget(page4);
        page5 = new QWidget();
        page5->setObjectName(QString::fromUtf8("page5"));
        verticalLayout_4 = new QVBoxLayout(page5);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        widgetM2 = new QWidget(page5);
        widgetM2->setObjectName(QString::fromUtf8("widgetM2"));
        widgetM2->setMinimumSize(QSize(0, 65));
        widgetM2->setMaximumSize(QSize(16777215, 65));
        horizontalLayout_5 = new QHBoxLayout(widgetM2);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        layoutM2ToolIcon = new QHBoxLayout();
        layoutM2ToolIcon->setObjectName(QString::fromUtf8("layoutM2ToolIcon"));

        horizontalLayout_5->addLayout(layoutM2ToolIcon);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_4);

        btnM2Load = new QPushButton(widgetM2);
        btnM2Load->setObjectName(QString::fromUtf8("btnM2Load"));
        btnM2Load->setMinimumSize(QSize(55, 52));
        btnM2Load->setMaximumSize(QSize(55, 52));

        horizontalLayout_5->addWidget(btnM2Load);

        btnM2Save = new QPushButton(widgetM2);
        btnM2Save->setObjectName(QString::fromUtf8("btnM2Save"));
        btnM2Save->setMinimumSize(QSize(55, 52));
        btnM2Save->setMaximumSize(QSize(55, 52));

        horizontalLayout_5->addWidget(btnM2Save);


        verticalLayout_4->addWidget(widgetM2);

        tabWidgetModulel2 = new QTabWidget(page5);
        tabWidgetModulel2->setObjectName(QString::fromUtf8("tabWidgetModulel2"));
        tabWidgetModulel2->setElideMode(Qt::ElideMiddle);
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        gridLayout_4 = new QGridLayout(tab_3);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        widgetSize2 = new QWidget(tab_3);
        widgetSize2->setObjectName(QString::fromUtf8("widgetSize2"));
        gridLayout_7 = new QGridLayout(widgetSize2);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        btnAddTab2 = new QPushButton(widgetSize2);
        btnAddTab2->setObjectName(QString::fromUtf8("btnAddTab2"));
        btnAddTab2->setMinimumSize(QSize(80, 80));
        btnAddTab2->setMaximumSize(QSize(80, 80));
        btnAddTab2->setFont(font);

        gridLayout_7->addWidget(btnAddTab2, 0, 0, 1, 1);


        gridLayout_4->addWidget(widgetSize2, 0, 0, 1, 1);

        tabWidgetModulel2->addTab(tab_3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QString::fromUtf8("tab_4"));
        tabWidgetModulel2->addTab(tab_4, QString());

        verticalLayout_4->addWidget(tabWidgetModulel2);

        stackedWidget->addWidget(page5);
        page6 = new QWidget();
        page6->setObjectName(QString::fromUtf8("page6"));
        verticalLayout_3 = new QVBoxLayout(page6);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        widgetM3 = new QWidget(page6);
        widgetM3->setObjectName(QString::fromUtf8("widgetM3"));
        widgetM3->setMinimumSize(QSize(0, 65));
        widgetM3->setMaximumSize(QSize(16777215, 65));
        horizontalLayout_7 = new QHBoxLayout(widgetM3);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        horizontalLayout_7->setContentsMargins(0, 0, 0, 0);
        layoutM3ToolIcon = new QHBoxLayout();
        layoutM3ToolIcon->setObjectName(QString::fromUtf8("layoutM3ToolIcon"));

        horizontalLayout_7->addLayout(layoutM3ToolIcon);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_5);

        btnM3Load = new QPushButton(widgetM3);
        btnM3Load->setObjectName(QString::fromUtf8("btnM3Load"));
        btnM3Load->setMinimumSize(QSize(55, 52));
        btnM3Load->setMaximumSize(QSize(55, 52));

        horizontalLayout_7->addWidget(btnM3Load);

        btnM3Save = new QPushButton(widgetM3);
        btnM3Save->setObjectName(QString::fromUtf8("btnM3Save"));
        btnM3Save->setMinimumSize(QSize(55, 52));
        btnM3Save->setMaximumSize(QSize(55, 52));

        horizontalLayout_7->addWidget(btnM3Save);


        verticalLayout_3->addWidget(widgetM3);

        tabWidgetModulel3 = new QTabWidget(page6);
        tabWidgetModulel3->setObjectName(QString::fromUtf8("tabWidgetModulel3"));
        QFont font1;
        font1.setPointSize(9);
        tabWidgetModulel3->setFont(font1);
        tab_5 = new QWidget();
        tab_5->setObjectName(QString::fromUtf8("tab_5"));
        gridLayout_3 = new QGridLayout(tab_5);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        widgetSize3 = new QWidget(tab_5);
        widgetSize3->setObjectName(QString::fromUtf8("widgetSize3"));
        gridLayout_8 = new QGridLayout(widgetSize3);
        gridLayout_8->setObjectName(QString::fromUtf8("gridLayout_8"));
        btnAddTab3 = new QPushButton(widgetSize3);
        btnAddTab3->setObjectName(QString::fromUtf8("btnAddTab3"));
        btnAddTab3->setMinimumSize(QSize(80, 80));
        btnAddTab3->setMaximumSize(QSize(80, 80));
        btnAddTab3->setFont(font);

        gridLayout_8->addWidget(btnAddTab3, 0, 0, 1, 1);


        gridLayout_3->addWidget(widgetSize3, 0, 0, 1, 1);

        tabWidgetModulel3->addTab(tab_5, QString());
        tab_6 = new QWidget();
        tab_6->setObjectName(QString::fromUtf8("tab_6"));
        tabWidgetModulel3->addTab(tab_6, QString());

        verticalLayout_3->addWidget(tabWidgetModulel3);

        stackedWidget->addWidget(page6);
        page7 = new QWidget();
        page7->setObjectName(QString::fromUtf8("page7"));
        verticalLayout_2 = new QVBoxLayout(page7);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        widgetM4 = new QWidget(page7);
        widgetM4->setObjectName(QString::fromUtf8("widgetM4"));
        widgetM4->setMinimumSize(QSize(0, 65));
        widgetM4->setMaximumSize(QSize(16777215, 65));
        horizontalLayout_9 = new QHBoxLayout(widgetM4);
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        horizontalLayout_9->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_6);

        btnM4Load = new QPushButton(widgetM4);
        btnM4Load->setObjectName(QString::fromUtf8("btnM4Load"));
        btnM4Load->setMinimumSize(QSize(55, 52));
        btnM4Load->setMaximumSize(QSize(55, 52));

        horizontalLayout_9->addWidget(btnM4Load);

        btnM4Save = new QPushButton(widgetM4);
        btnM4Save->setObjectName(QString::fromUtf8("btnM4Save"));
        btnM4Save->setMinimumSize(QSize(55, 52));
        btnM4Save->setMaximumSize(QSize(55, 52));

        horizontalLayout_9->addWidget(btnM4Save);


        verticalLayout_2->addWidget(widgetM4);

        tabWidgetModulel4 = new QTabWidget(page7);
        tabWidgetModulel4->setObjectName(QString::fromUtf8("tabWidgetModulel4"));
        tab_7 = new QWidget();
        tab_7->setObjectName(QString::fromUtf8("tab_7"));
        gridLayout = new QGridLayout(tab_7);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        widgetSize4 = new QWidget(tab_7);
        widgetSize4->setObjectName(QString::fromUtf8("widgetSize4"));
        gridLayout_9 = new QGridLayout(widgetSize4);
        gridLayout_9->setObjectName(QString::fromUtf8("gridLayout_9"));
        btnAddTab4 = new QPushButton(widgetSize4);
        btnAddTab4->setObjectName(QString::fromUtf8("btnAddTab4"));
        btnAddTab4->setMinimumSize(QSize(80, 80));
        btnAddTab4->setMaximumSize(QSize(80, 80));
        btnAddTab4->setFont(font);

        gridLayout_9->addWidget(btnAddTab4, 0, 0, 1, 1);


        gridLayout->addWidget(widgetSize4, 0, 0, 1, 1);

        tabWidgetModulel4->addTab(tab_7, QString());
        tab_8 = new QWidget();
        tab_8->setObjectName(QString::fromUtf8("tab_8"));
        tabWidgetModulel4->addTab(tab_8, QString());

        verticalLayout_2->addWidget(tabWidgetModulel4);

        stackedWidget->addWidget(page7);

        verticalLayout_6->addWidget(stackedWidget);

        splitter->addWidget(widget);

        horizontalLayout_8->addWidget(splitter);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1184, 23));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(3);
        tabWidgetModulel1->setCurrentIndex(0);
        tabWidgetModulel2->setCurrentIndex(0);
        tabWidgetModulel3->setCurrentIndex(0);
        tabWidgetModulel4->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionM1->setText(QCoreApplication::translate("MainWindow", "\345\212\237\350\203\275\346\240\267\346\234\272", nullptr));
        actionM2->setText(QCoreApplication::translate("MainWindow", "\345\207\240\344\275\225\346\240\267\346\234\272", nullptr));
        actionM3->setText(QCoreApplication::translate("MainWindow", "\346\200\247\350\203\275\346\240\267\346\234\272", nullptr));
        actionM4->setText(QCoreApplication::translate("MainWindow", "\347\224\237\344\272\247\346\240\267\346\234\272", nullptr));
        btnTitleIcon->setText(QString());
        QTreeWidgetItem *___qtreewidgetitem = treeWidget->headerItem();
        ___qtreewidgetitem->setText(0, QCoreApplication::translate("MainWindow", "1", nullptr));
        btnChildTitle->setText(QString());
        labelUserIcon->setText(QString());
        labelUserName->setText(QCoreApplication::translate("MainWindow", "\347\224\250\346\210\2671", nullptr));
        btnMinimize->setText(QString());
        btnMaximize->setText(QString());
        btnClose->setText(QString());
        btnM1Load->setText(QString());
        btnM1Save->setText(QCoreApplication::translate("MainWindow", "\344\270\200\351\224\256\344\277\235\345\255\230", nullptr));
        btnAddTab1->setText(QCoreApplication::translate("MainWindow", "+", nullptr));
        tabWidgetModulel1->setTabText(tabWidgetModulel1->indexOf(tab), QCoreApplication::translate("MainWindow", "+", nullptr));
        tabWidgetModulel1->setTabText(tabWidgetModulel1->indexOf(tab_2), QCoreApplication::translate("MainWindow", "Tab 2", nullptr));
        btnM2Load->setText(QCoreApplication::translate("MainWindow", "\344\270\200\351\224\256\345\212\240\350\275\275", nullptr));
        btnM2Save->setText(QCoreApplication::translate("MainWindow", "\344\270\200\351\224\256\344\277\235\345\255\230", nullptr));
        btnAddTab2->setText(QCoreApplication::translate("MainWindow", "+", nullptr));
        tabWidgetModulel2->setTabText(tabWidgetModulel2->indexOf(tab_3), QCoreApplication::translate("MainWindow", "+", nullptr));
        tabWidgetModulel2->setTabText(tabWidgetModulel2->indexOf(tab_4), QCoreApplication::translate("MainWindow", "Tab 2", nullptr));
        btnM3Load->setText(QCoreApplication::translate("MainWindow", "\344\270\200\351\224\256\345\212\240\350\275\275", nullptr));
        btnM3Save->setText(QCoreApplication::translate("MainWindow", "\344\270\200\351\224\256\344\277\235\345\255\230", nullptr));
        btnAddTab3->setText(QCoreApplication::translate("MainWindow", "+", nullptr));
        tabWidgetModulel3->setTabText(tabWidgetModulel3->indexOf(tab_5), QCoreApplication::translate("MainWindow", "+", nullptr));
        tabWidgetModulel3->setTabText(tabWidgetModulel3->indexOf(tab_6), QCoreApplication::translate("MainWindow", "Tab 2", nullptr));
        btnM4Load->setText(QCoreApplication::translate("MainWindow", "\344\270\200\351\224\256\345\212\240\350\275\275", nullptr));
        btnM4Save->setText(QCoreApplication::translate("MainWindow", "\344\270\200\351\224\256\344\277\235\345\255\230", nullptr));
        btnAddTab4->setText(QCoreApplication::translate("MainWindow", "+", nullptr));
        tabWidgetModulel4->setTabText(tabWidgetModulel4->indexOf(tab_7), QCoreApplication::translate("MainWindow", "+", nullptr));
        tabWidgetModulel4->setTabText(tabWidgetModulel4->indexOf(tab_8), QCoreApplication::translate("MainWindow", "Tab 2", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
