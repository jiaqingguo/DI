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
#include "CustomTitleWidget.h"
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
    CustomTitleWidget *widgetTital;
    QStackedWidget *stackedWidget;
    ResourceManageDialog *m_ResourceManageDialog;
    InformationConfihurationDialog *m_InforConfihurationDialog;
    FtpDialog *m_FtpDialog;
    ApprovalProgressDialog *m_ApprovalProgressDialog;
    QVBoxLayout *verticalLayout;
    QWidget *page4;
    QVBoxLayout *verticalLayout_5;
    QTabWidget *tabWidgetModulel1;
    QWidget *tab;
    QGridLayout *gridLayout_6;
    QWidget *widgetSize1;
    QGridLayout *gridLayout_5;
    QWidget *tab_2;
    QWidget *page5;
    QVBoxLayout *verticalLayout_4;
    QTabWidget *tabWidgetModulel2;
    QWidget *tab_3;
    QGridLayout *gridLayout_4;
    QWidget *widgetSize2;
    QGridLayout *gridLayout_7;
    QWidget *tab_4;
    QWidget *page6;
    QVBoxLayout *verticalLayout_3;
    QTabWidget *tabWidgetModulel3;
    QWidget *tab_5;
    QGridLayout *gridLayout_3;
    QWidget *widgetSize3;
    QGridLayout *gridLayout_8;
    QWidget *tab_6;
    QWidget *page7;
    QVBoxLayout *verticalLayout_2;
    QTabWidget *tabWidgetModulel4;
    QWidget *tab_7;
    QGridLayout *gridLayout;
    QWidget *widgetSize4;
    QGridLayout *gridLayout_9;
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
        splitter->setChildrenCollapsible(false);
        widgetLeftMenu = new QWidget(splitter);
        widgetLeftMenu->setObjectName(QString::fromUtf8("widgetLeftMenu"));
        widgetLeftMenu->setMinimumSize(QSize(150, 0));
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
        widgetTital = new CustomTitleWidget(widget);
        widgetTital->setObjectName(QString::fromUtf8("widgetTital"));

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
        tabWidgetModulel1 = new QTabWidget(page4);
        tabWidgetModulel1->setObjectName(QString::fromUtf8("tabWidgetModulel1"));
        tabWidgetModulel1->setTabShape(QTabWidget::Rounded);
        tabWidgetModulel1->setIconSize(QSize(16, 16));
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
        tabWidgetModulel3 = new QTabWidget(page6);
        tabWidgetModulel3->setObjectName(QString::fromUtf8("tabWidgetModulel3"));
        QFont font;
        font.setPointSize(9);
        tabWidgetModulel3->setFont(font);
        tab_5 = new QWidget();
        tab_5->setObjectName(QString::fromUtf8("tab_5"));
        gridLayout_3 = new QGridLayout(tab_5);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        widgetSize3 = new QWidget(tab_5);
        widgetSize3->setObjectName(QString::fromUtf8("widgetSize3"));
        gridLayout_8 = new QGridLayout(widgetSize3);
        gridLayout_8->setObjectName(QString::fromUtf8("gridLayout_8"));

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

        stackedWidget->setCurrentIndex(0);
        tabWidgetModulel1->setCurrentIndex(0);
        tabWidgetModulel2->setCurrentIndex(0);
        tabWidgetModulel3->setCurrentIndex(1);
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
        tabWidgetModulel1->setTabText(tabWidgetModulel1->indexOf(tab), QCoreApplication::translate("MainWindow", "+", nullptr));
        tabWidgetModulel1->setTabText(tabWidgetModulel1->indexOf(tab_2), QCoreApplication::translate("MainWindow", "Tab 2", nullptr));
        tabWidgetModulel2->setTabText(tabWidgetModulel2->indexOf(tab_3), QCoreApplication::translate("MainWindow", "+", nullptr));
        tabWidgetModulel2->setTabText(tabWidgetModulel2->indexOf(tab_4), QCoreApplication::translate("MainWindow", "Tab 2", nullptr));
        tabWidgetModulel3->setTabText(tabWidgetModulel3->indexOf(tab_5), QCoreApplication::translate("MainWindow", "+", nullptr));
        tabWidgetModulel3->setTabText(tabWidgetModulel3->indexOf(tab_6), QCoreApplication::translate("MainWindow", "Tab 2", nullptr));
        tabWidgetModulel4->setTabText(tabWidgetModulel4->indexOf(tab_7), QCoreApplication::translate("MainWindow", "+", nullptr));
        tabWidgetModulel4->setTabText(tabWidgetModulel4->indexOf(tab_8), QCoreApplication::translate("MainWindow", "Tab 2", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
