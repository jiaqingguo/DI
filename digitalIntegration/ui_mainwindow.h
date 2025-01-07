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
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionshowM1;
    QWidget *centralwidget;
    QGridLayout *gridLayout_2;
    QWidget *widgetModules;
    QHBoxLayout *horizontalLayout;
    QPushButton *btnFunction;
    QPushButton *btnModule1;
    QPushButton *btnModule2;
    QPushButton *btnModule3;
    QPushButton *btnModule4;
    QSpacerItem *horizontalSpacer;
    QLabel *labelUserIcon;
    QLabel *labelUserName;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QVBoxLayout *verticalLayout;
    QWidget *widgetFunctionBtns;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *btnResourceManage;
    QPushButton *btnInformationConfihuration;
    QPushButton *btnDataManage;
    QPushButton *btnApprovalProgress;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer;
    QWidget *page2;
    QVBoxLayout *verticalLayout_5;
    QWidget *widgetM1;
    QHBoxLayout *horizontalLayout_4;
    QHBoxLayout *layoutM1ToolIcon;
    QPushButton *pushButton_6;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_7;
    QPushButton *pushButton_4;
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
    QWidget *page3;
    QVBoxLayout *verticalLayout_4;
    QWidget *widgetM2;
    QHBoxLayout *horizontalLayout_5;
    QHBoxLayout *layoutM2ToolIcon;
    QPushButton *pushButton_10;
    QPushButton *pushButton_21;
    QPushButton *pushButton_23;
    QPushButton *pushButton_24;
    QPushButton *pushButton_22;
    QPushButton *pushButton_11;
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
    QWidget *page4;
    QVBoxLayout *verticalLayout_3;
    QWidget *widgetM3;
    QHBoxLayout *horizontalLayout_7;
    QHBoxLayout *layoutM3ToolIcon;
    QPushButton *pushButton_14;
    QPushButton *pushButton_16;
    QPushButton *pushButton_17;
    QPushButton *pushButton_20;
    QPushButton *pushButton_19;
    QPushButton *pushButton_15;
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
    QWidget *page5;
    QVBoxLayout *verticalLayout_2;
    QWidget *widgetM4;
    QHBoxLayout *horizontalLayout_9;
    QHBoxLayout *layoutM4ToolIcon;
    QPushButton *pushButton_18;
    QPushButton *pushButton_5;
    QPushButton *pushButton_13;
    QPushButton *pushButton_12;
    QPushButton *pushButton_9;
    QPushButton *pushButton_8;
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
    QMenu *menu;
    QStatusBar *statusbar;
    QButtonGroup *buttonGroup;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(942, 790);
        MainWindow->setMinimumSize(QSize(710, 437));
        actionshowM1 = new QAction(MainWindow);
        actionshowM1->setObjectName(QString::fromUtf8("actionshowM1"));
        actionshowM1->setCheckable(true);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout_2 = new QGridLayout(centralwidget);
        gridLayout_2->setSpacing(0);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        widgetModules = new QWidget(centralwidget);
        widgetModules->setObjectName(QString::fromUtf8("widgetModules"));
        widgetModules->setMinimumSize(QSize(0, 40));
        widgetModules->setMaximumSize(QSize(16777215, 40));
        horizontalLayout = new QHBoxLayout(widgetModules);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 5, 0);
        btnFunction = new QPushButton(widgetModules);
        buttonGroup = new QButtonGroup(MainWindow);
        buttonGroup->setObjectName(QString::fromUtf8("buttonGroup"));
        buttonGroup->addButton(btnFunction);
        btnFunction->setObjectName(QString::fromUtf8("btnFunction"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(btnFunction->sizePolicy().hasHeightForWidth());
        btnFunction->setSizePolicy(sizePolicy);
        btnFunction->setMinimumSize(QSize(150, 25));
        btnFunction->setMaximumSize(QSize(150, 30));

        horizontalLayout->addWidget(btnFunction);

        btnModule1 = new QPushButton(widgetModules);
        buttonGroup->addButton(btnModule1);
        btnModule1->setObjectName(QString::fromUtf8("btnModule1"));
        sizePolicy.setHeightForWidth(btnModule1->sizePolicy().hasHeightForWidth());
        btnModule1->setSizePolicy(sizePolicy);
        btnModule1->setMinimumSize(QSize(150, 25));
        btnModule1->setMaximumSize(QSize(150, 30));

        horizontalLayout->addWidget(btnModule1);

        btnModule2 = new QPushButton(widgetModules);
        buttonGroup->addButton(btnModule2);
        btnModule2->setObjectName(QString::fromUtf8("btnModule2"));
        sizePolicy.setHeightForWidth(btnModule2->sizePolicy().hasHeightForWidth());
        btnModule2->setSizePolicy(sizePolicy);
        btnModule2->setMinimumSize(QSize(150, 25));
        btnModule2->setMaximumSize(QSize(150, 30));

        horizontalLayout->addWidget(btnModule2);

        btnModule3 = new QPushButton(widgetModules);
        buttonGroup->addButton(btnModule3);
        btnModule3->setObjectName(QString::fromUtf8("btnModule3"));
        sizePolicy.setHeightForWidth(btnModule3->sizePolicy().hasHeightForWidth());
        btnModule3->setSizePolicy(sizePolicy);
        btnModule3->setMinimumSize(QSize(150, 25));
        btnModule3->setMaximumSize(QSize(150, 30));

        horizontalLayout->addWidget(btnModule3);

        btnModule4 = new QPushButton(widgetModules);
        buttonGroup->addButton(btnModule4);
        btnModule4->setObjectName(QString::fromUtf8("btnModule4"));
        sizePolicy.setHeightForWidth(btnModule4->sizePolicy().hasHeightForWidth());
        btnModule4->setSizePolicy(sizePolicy);
        btnModule4->setMinimumSize(QSize(150, 25));
        btnModule4->setMaximumSize(QSize(150, 30));

        horizontalLayout->addWidget(btnModule4);

        horizontalSpacer = new QSpacerItem(343, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        labelUserIcon = new QLabel(widgetModules);
        labelUserIcon->setObjectName(QString::fromUtf8("labelUserIcon"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(labelUserIcon->sizePolicy().hasHeightForWidth());
        labelUserIcon->setSizePolicy(sizePolicy1);
        labelUserIcon->setMinimumSize(QSize(40, 25));
        labelUserIcon->setMaximumSize(QSize(40, 25));

        horizontalLayout->addWidget(labelUserIcon);

        labelUserName = new QLabel(widgetModules);
        labelUserName->setObjectName(QString::fromUtf8("labelUserName"));
        sizePolicy1.setHeightForWidth(labelUserName->sizePolicy().hasHeightForWidth());
        labelUserName->setSizePolicy(sizePolicy1);
        labelUserName->setMinimumSize(QSize(0, 25));
        labelUserName->setMaximumSize(QSize(16777215, 25));

        horizontalLayout->addWidget(labelUserName);


        gridLayout_2->addWidget(widgetModules, 0, 0, 1, 1);

        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        verticalLayout = new QVBoxLayout(page);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        widgetFunctionBtns = new QWidget(page);
        widgetFunctionBtns->setObjectName(QString::fromUtf8("widgetFunctionBtns"));
        widgetFunctionBtns->setMinimumSize(QSize(0, 65));
        widgetFunctionBtns->setMaximumSize(QSize(16777215, 65));
        horizontalLayout_2 = new QHBoxLayout(widgetFunctionBtns);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 2);
        btnResourceManage = new QPushButton(widgetFunctionBtns);
        btnResourceManage->setObjectName(QString::fromUtf8("btnResourceManage"));
        btnResourceManage->setMinimumSize(QSize(55, 60));
        btnResourceManage->setMaximumSize(QSize(55, 60));

        horizontalLayout_2->addWidget(btnResourceManage);

        btnInformationConfihuration = new QPushButton(widgetFunctionBtns);
        btnInformationConfihuration->setObjectName(QString::fromUtf8("btnInformationConfihuration"));
        btnInformationConfihuration->setMinimumSize(QSize(55, 60));
        btnInformationConfihuration->setMaximumSize(QSize(55, 60));

        horizontalLayout_2->addWidget(btnInformationConfihuration);

        btnDataManage = new QPushButton(widgetFunctionBtns);
        btnDataManage->setObjectName(QString::fromUtf8("btnDataManage"));
        btnDataManage->setMinimumSize(QSize(55, 60));
        btnDataManage->setMaximumSize(QSize(55, 60));

        horizontalLayout_2->addWidget(btnDataManage);

        btnApprovalProgress = new QPushButton(widgetFunctionBtns);
        btnApprovalProgress->setObjectName(QString::fromUtf8("btnApprovalProgress"));
        btnApprovalProgress->setMinimumSize(QSize(55, 60));
        btnApprovalProgress->setMaximumSize(QSize(55, 60));

        horizontalLayout_2->addWidget(btnApprovalProgress);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout->addWidget(widgetFunctionBtns);

        verticalSpacer = new QSpacerItem(20, 426, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        stackedWidget->addWidget(page);
        page2 = new QWidget();
        page2->setObjectName(QString::fromUtf8("page2"));
        verticalLayout_5 = new QVBoxLayout(page2);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        widgetM1 = new QWidget(page2);
        widgetM1->setObjectName(QString::fromUtf8("widgetM1"));
        widgetM1->setMinimumSize(QSize(0, 65));
        widgetM1->setMaximumSize(QSize(16777215, 65));
        horizontalLayout_4 = new QHBoxLayout(widgetM1);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        layoutM1ToolIcon = new QHBoxLayout();
        layoutM1ToolIcon->setObjectName(QString::fromUtf8("layoutM1ToolIcon"));
        pushButton_6 = new QPushButton(widgetM1);
        pushButton_6->setObjectName(QString::fromUtf8("pushButton_6"));
        pushButton_6->setMinimumSize(QSize(55, 60));
        pushButton_6->setMaximumSize(QSize(55, 60));

        layoutM1ToolIcon->addWidget(pushButton_6);

        pushButton = new QPushButton(widgetM1);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setMinimumSize(QSize(55, 60));
        pushButton->setMaximumSize(QSize(55, 60));

        layoutM1ToolIcon->addWidget(pushButton);

        pushButton_2 = new QPushButton(widgetM1);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setMinimumSize(QSize(55, 60));
        pushButton_2->setMaximumSize(QSize(55, 60));

        layoutM1ToolIcon->addWidget(pushButton_2);

        pushButton_3 = new QPushButton(widgetM1);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setMinimumSize(QSize(55, 60));
        pushButton_3->setMaximumSize(QSize(55, 60));

        layoutM1ToolIcon->addWidget(pushButton_3);

        pushButton_7 = new QPushButton(widgetM1);
        pushButton_7->setObjectName(QString::fromUtf8("pushButton_7"));
        pushButton_7->setMinimumSize(QSize(55, 60));
        pushButton_7->setMaximumSize(QSize(55, 60));

        layoutM1ToolIcon->addWidget(pushButton_7);

        pushButton_4 = new QPushButton(widgetM1);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        pushButton_4->setMinimumSize(QSize(55, 60));
        pushButton_4->setMaximumSize(QSize(55, 60));

        layoutM1ToolIcon->addWidget(pushButton_4);


        horizontalLayout_4->addLayout(layoutM1ToolIcon);

        horizontalSpacer_3 = new QSpacerItem(415, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_3);

        btnM1Load = new QPushButton(widgetM1);
        btnM1Load->setObjectName(QString::fromUtf8("btnM1Load"));
        btnM1Load->setMinimumSize(QSize(55, 60));
        btnM1Load->setMaximumSize(QSize(55, 60));

        horizontalLayout_4->addWidget(btnM1Load);

        btnM1Save = new QPushButton(widgetM1);
        btnM1Save->setObjectName(QString::fromUtf8("btnM1Save"));
        btnM1Save->setMinimumSize(QSize(55, 60));
        btnM1Save->setMaximumSize(QSize(55, 60));

        horizontalLayout_4->addWidget(btnM1Save);


        verticalLayout_5->addWidget(widgetM1);

        tabWidgetModulel1 = new QTabWidget(page2);
        tabWidgetModulel1->setObjectName(QString::fromUtf8("tabWidgetModulel1"));
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

        stackedWidget->addWidget(page2);
        page3 = new QWidget();
        page3->setObjectName(QString::fromUtf8("page3"));
        verticalLayout_4 = new QVBoxLayout(page3);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        widgetM2 = new QWidget(page3);
        widgetM2->setObjectName(QString::fromUtf8("widgetM2"));
        widgetM2->setMinimumSize(QSize(0, 62));
        widgetM2->setMaximumSize(QSize(16777215, 65));
        horizontalLayout_5 = new QHBoxLayout(widgetM2);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        layoutM2ToolIcon = new QHBoxLayout();
        layoutM2ToolIcon->setObjectName(QString::fromUtf8("layoutM2ToolIcon"));
        pushButton_10 = new QPushButton(widgetM2);
        pushButton_10->setObjectName(QString::fromUtf8("pushButton_10"));
        pushButton_10->setMinimumSize(QSize(55, 60));
        pushButton_10->setMaximumSize(QSize(55, 60));

        layoutM2ToolIcon->addWidget(pushButton_10);

        pushButton_21 = new QPushButton(widgetM2);
        pushButton_21->setObjectName(QString::fromUtf8("pushButton_21"));
        pushButton_21->setMinimumSize(QSize(55, 60));
        pushButton_21->setMaximumSize(QSize(55, 60));

        layoutM2ToolIcon->addWidget(pushButton_21);

        pushButton_23 = new QPushButton(widgetM2);
        pushButton_23->setObjectName(QString::fromUtf8("pushButton_23"));
        pushButton_23->setMinimumSize(QSize(55, 60));
        pushButton_23->setMaximumSize(QSize(55, 60));

        layoutM2ToolIcon->addWidget(pushButton_23);

        pushButton_24 = new QPushButton(widgetM2);
        pushButton_24->setObjectName(QString::fromUtf8("pushButton_24"));
        pushButton_24->setMinimumSize(QSize(55, 60));
        pushButton_24->setMaximumSize(QSize(55, 60));

        layoutM2ToolIcon->addWidget(pushButton_24);

        pushButton_22 = new QPushButton(widgetM2);
        pushButton_22->setObjectName(QString::fromUtf8("pushButton_22"));
        pushButton_22->setMinimumSize(QSize(55, 60));
        pushButton_22->setMaximumSize(QSize(55, 60));

        layoutM2ToolIcon->addWidget(pushButton_22);

        pushButton_11 = new QPushButton(widgetM2);
        pushButton_11->setObjectName(QString::fromUtf8("pushButton_11"));
        pushButton_11->setMinimumSize(QSize(55, 60));
        pushButton_11->setMaximumSize(QSize(55, 60));

        layoutM2ToolIcon->addWidget(pushButton_11);


        horizontalLayout_5->addLayout(layoutM2ToolIcon);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_4);

        btnM2Load = new QPushButton(widgetM2);
        btnM2Load->setObjectName(QString::fromUtf8("btnM2Load"));
        btnM2Load->setMinimumSize(QSize(55, 60));
        btnM2Load->setMaximumSize(QSize(55, 60));

        horizontalLayout_5->addWidget(btnM2Load);

        btnM2Save = new QPushButton(widgetM2);
        btnM2Save->setObjectName(QString::fromUtf8("btnM2Save"));
        btnM2Save->setMinimumSize(QSize(55, 60));
        btnM2Save->setMaximumSize(QSize(55, 60));

        horizontalLayout_5->addWidget(btnM2Save);


        verticalLayout_4->addWidget(widgetM2);

        tabWidgetModulel2 = new QTabWidget(page3);
        tabWidgetModulel2->setObjectName(QString::fromUtf8("tabWidgetModulel2"));
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

        stackedWidget->addWidget(page3);
        page4 = new QWidget();
        page4->setObjectName(QString::fromUtf8("page4"));
        verticalLayout_3 = new QVBoxLayout(page4);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        widgetM3 = new QWidget(page4);
        widgetM3->setObjectName(QString::fromUtf8("widgetM3"));
        widgetM3->setMinimumSize(QSize(0, 65));
        widgetM3->setMaximumSize(QSize(16777215, 65));
        horizontalLayout_7 = new QHBoxLayout(widgetM3);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        horizontalLayout_7->setContentsMargins(0, 0, 0, 0);
        layoutM3ToolIcon = new QHBoxLayout();
        layoutM3ToolIcon->setObjectName(QString::fromUtf8("layoutM3ToolIcon"));
        pushButton_14 = new QPushButton(widgetM3);
        pushButton_14->setObjectName(QString::fromUtf8("pushButton_14"));
        pushButton_14->setMinimumSize(QSize(55, 60));
        pushButton_14->setMaximumSize(QSize(55, 60));

        layoutM3ToolIcon->addWidget(pushButton_14);

        pushButton_16 = new QPushButton(widgetM3);
        pushButton_16->setObjectName(QString::fromUtf8("pushButton_16"));
        pushButton_16->setMinimumSize(QSize(55, 60));
        pushButton_16->setMaximumSize(QSize(55, 60));

        layoutM3ToolIcon->addWidget(pushButton_16);

        pushButton_17 = new QPushButton(widgetM3);
        pushButton_17->setObjectName(QString::fromUtf8("pushButton_17"));
        pushButton_17->setMinimumSize(QSize(55, 60));
        pushButton_17->setMaximumSize(QSize(55, 60));

        layoutM3ToolIcon->addWidget(pushButton_17);

        pushButton_20 = new QPushButton(widgetM3);
        pushButton_20->setObjectName(QString::fromUtf8("pushButton_20"));
        pushButton_20->setMinimumSize(QSize(55, 60));
        pushButton_20->setMaximumSize(QSize(55, 60));

        layoutM3ToolIcon->addWidget(pushButton_20);

        pushButton_19 = new QPushButton(widgetM3);
        pushButton_19->setObjectName(QString::fromUtf8("pushButton_19"));
        pushButton_19->setMinimumSize(QSize(55, 60));
        pushButton_19->setMaximumSize(QSize(55, 60));

        layoutM3ToolIcon->addWidget(pushButton_19);

        pushButton_15 = new QPushButton(widgetM3);
        pushButton_15->setObjectName(QString::fromUtf8("pushButton_15"));
        pushButton_15->setMinimumSize(QSize(55, 60));
        pushButton_15->setMaximumSize(QSize(55, 60));

        layoutM3ToolIcon->addWidget(pushButton_15);


        horizontalLayout_7->addLayout(layoutM3ToolIcon);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_5);

        btnM3Load = new QPushButton(widgetM3);
        btnM3Load->setObjectName(QString::fromUtf8("btnM3Load"));
        btnM3Load->setMinimumSize(QSize(55, 60));
        btnM3Load->setMaximumSize(QSize(55, 60));

        horizontalLayout_7->addWidget(btnM3Load);

        btnM3Save = new QPushButton(widgetM3);
        btnM3Save->setObjectName(QString::fromUtf8("btnM3Save"));
        btnM3Save->setMinimumSize(QSize(55, 60));
        btnM3Save->setMaximumSize(QSize(55, 60));

        horizontalLayout_7->addWidget(btnM3Save);


        verticalLayout_3->addWidget(widgetM3);

        tabWidgetModulel3 = new QTabWidget(page4);
        tabWidgetModulel3->setObjectName(QString::fromUtf8("tabWidgetModulel3"));
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

        stackedWidget->addWidget(page4);
        page5 = new QWidget();
        page5->setObjectName(QString::fromUtf8("page5"));
        verticalLayout_2 = new QVBoxLayout(page5);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        widgetM4 = new QWidget(page5);
        widgetM4->setObjectName(QString::fromUtf8("widgetM4"));
        horizontalLayout_9 = new QHBoxLayout(widgetM4);
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        horizontalLayout_9->setContentsMargins(0, 0, 0, 0);
        layoutM4ToolIcon = new QHBoxLayout();
        layoutM4ToolIcon->setObjectName(QString::fromUtf8("layoutM4ToolIcon"));
        pushButton_18 = new QPushButton(widgetM4);
        pushButton_18->setObjectName(QString::fromUtf8("pushButton_18"));
        pushButton_18->setMinimumSize(QSize(55, 60));
        pushButton_18->setMaximumSize(QSize(55, 60));

        layoutM4ToolIcon->addWidget(pushButton_18);

        pushButton_5 = new QPushButton(widgetM4);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));
        pushButton_5->setMinimumSize(QSize(55, 60));
        pushButton_5->setMaximumSize(QSize(55, 60));

        layoutM4ToolIcon->addWidget(pushButton_5);

        pushButton_13 = new QPushButton(widgetM4);
        pushButton_13->setObjectName(QString::fromUtf8("pushButton_13"));
        pushButton_13->setMinimumSize(QSize(55, 60));
        pushButton_13->setMaximumSize(QSize(55, 60));

        layoutM4ToolIcon->addWidget(pushButton_13);

        pushButton_12 = new QPushButton(widgetM4);
        pushButton_12->setObjectName(QString::fromUtf8("pushButton_12"));
        pushButton_12->setMinimumSize(QSize(55, 60));
        pushButton_12->setMaximumSize(QSize(55, 60));

        layoutM4ToolIcon->addWidget(pushButton_12);

        pushButton_9 = new QPushButton(widgetM4);
        pushButton_9->setObjectName(QString::fromUtf8("pushButton_9"));
        pushButton_9->setMinimumSize(QSize(55, 60));
        pushButton_9->setMaximumSize(QSize(55, 60));

        layoutM4ToolIcon->addWidget(pushButton_9);

        pushButton_8 = new QPushButton(widgetM4);
        pushButton_8->setObjectName(QString::fromUtf8("pushButton_8"));
        pushButton_8->setMinimumSize(QSize(55, 60));
        pushButton_8->setMaximumSize(QSize(55, 60));

        layoutM4ToolIcon->addWidget(pushButton_8);


        horizontalLayout_9->addLayout(layoutM4ToolIcon);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_6);

        btnM4Load = new QPushButton(widgetM4);
        btnM4Load->setObjectName(QString::fromUtf8("btnM4Load"));
        btnM4Load->setMinimumSize(QSize(55, 60));
        btnM4Load->setMaximumSize(QSize(55, 60));

        horizontalLayout_9->addWidget(btnM4Load);

        btnM4Save = new QPushButton(widgetM4);
        btnM4Save->setObjectName(QString::fromUtf8("btnM4Save"));
        btnM4Save->setMinimumSize(QSize(55, 60));
        btnM4Save->setMaximumSize(QSize(55, 60));

        horizontalLayout_9->addWidget(btnM4Save);


        verticalLayout_2->addWidget(widgetM4);

        tabWidgetModulel4 = new QTabWidget(page5);
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

        stackedWidget->addWidget(page5);

        gridLayout_2->addWidget(stackedWidget, 1, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 942, 23));
        menu = new QMenu(menubar);
        menu->setObjectName(QString::fromUtf8("menu"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menu->menuAction());
        menu->addAction(actionshowM1);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(1);
        tabWidgetModulel1->setCurrentIndex(0);
        tabWidgetModulel2->setCurrentIndex(0);
        tabWidgetModulel4->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionshowM1->setText(QCoreApplication::translate("MainWindow", "\345\212\237\350\203\275\346\240\267\346\234\272", nullptr));
        btnFunction->setText(QCoreApplication::translate("MainWindow", "\345\212\237\350\203\275", nullptr));
        btnModule1->setText(QCoreApplication::translate("MainWindow", "\345\212\237\350\203\275\346\240\267\346\234\272", nullptr));
        btnModule2->setText(QCoreApplication::translate("MainWindow", "\345\207\240\344\275\225\346\240\267\346\234\272", nullptr));
        btnModule3->setText(QCoreApplication::translate("MainWindow", "\346\200\247\350\203\275\346\240\267\346\234\272", nullptr));
        btnModule4->setText(QCoreApplication::translate("MainWindow", "\347\224\237\344\272\247\346\240\267\346\234\272", nullptr));
        labelUserIcon->setText(QString());
        labelUserName->setText(QCoreApplication::translate("MainWindow", "\347\224\250\346\210\2671", nullptr));
        btnResourceManage->setText(QCoreApplication::translate("MainWindow", "\350\265\204\346\272\220\347\256\241\347\220\206", nullptr));
        btnInformationConfihuration->setText(QCoreApplication::translate("MainWindow", "\344\277\241\346\201\257\351\205\215\347\275\256", nullptr));
        btnDataManage->setText(QCoreApplication::translate("MainWindow", " \346\226\207\344\273\266\347\256\241\347\220\206", nullptr));
        btnApprovalProgress->setText(QCoreApplication::translate("MainWindow", "\345\256\241\346\211\271\350\277\233\345\272\246", nullptr));
        pushButton_6->setText(QCoreApplication::translate("MainWindow", "AE", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "AI", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "AE", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "PS", nullptr));
        pushButton_7->setText(QCoreApplication::translate("MainWindow", "ID", nullptr));
        pushButton_4->setText(QCoreApplication::translate("MainWindow", "XD", nullptr));
        btnM1Load->setText(QCoreApplication::translate("MainWindow", "\344\270\200\351\224\256\345\212\240\350\275\275", nullptr));
        btnM1Save->setText(QCoreApplication::translate("MainWindow", "\344\270\200\351\224\256\344\277\235\345\255\230", nullptr));
        btnAddTab1->setText(QCoreApplication::translate("MainWindow", "+", nullptr));
        tabWidgetModulel1->setTabText(tabWidgetModulel1->indexOf(tab), QCoreApplication::translate("MainWindow", "\346\240\207\347\255\2761", nullptr));
        tabWidgetModulel1->setTabText(tabWidgetModulel1->indexOf(tab_2), QCoreApplication::translate("MainWindow", "Tab 2", nullptr));
        pushButton_10->setText(QCoreApplication::translate("MainWindow", "AE", nullptr));
        pushButton_21->setText(QCoreApplication::translate("MainWindow", "Ai", nullptr));
        pushButton_23->setText(QCoreApplication::translate("MainWindow", "Ae", nullptr));
        pushButton_24->setText(QCoreApplication::translate("MainWindow", "Ps", nullptr));
        pushButton_22->setText(QCoreApplication::translate("MainWindow", " Id", nullptr));
        pushButton_11->setText(QCoreApplication::translate("MainWindow", "Xd", nullptr));
        btnM2Load->setText(QCoreApplication::translate("MainWindow", "\344\270\200\351\224\256\345\212\240\350\275\275", nullptr));
        btnM2Save->setText(QCoreApplication::translate("MainWindow", "\344\270\200\351\224\256\344\277\235\345\255\230", nullptr));
        btnAddTab2->setText(QCoreApplication::translate("MainWindow", "+", nullptr));
        tabWidgetModulel2->setTabText(tabWidgetModulel2->indexOf(tab_3), QCoreApplication::translate("MainWindow", "\346\240\207\347\255\2761", nullptr));
        tabWidgetModulel2->setTabText(tabWidgetModulel2->indexOf(tab_4), QCoreApplication::translate("MainWindow", "Tab 2", nullptr));
        pushButton_14->setText(QCoreApplication::translate("MainWindow", "AE", nullptr));
        pushButton_16->setText(QCoreApplication::translate("MainWindow", " AI", nullptr));
        pushButton_17->setText(QCoreApplication::translate("MainWindow", "AE", nullptr));
        pushButton_20->setText(QCoreApplication::translate("MainWindow", "Ps", nullptr));
        pushButton_19->setText(QCoreApplication::translate("MainWindow", "Id", nullptr));
        pushButton_15->setText(QCoreApplication::translate("MainWindow", "Xd", nullptr));
        btnM3Load->setText(QCoreApplication::translate("MainWindow", "\344\270\200\351\224\256\345\212\240\350\275\275", nullptr));
        btnM3Save->setText(QCoreApplication::translate("MainWindow", "\344\270\200\351\224\256\344\277\235\345\255\230", nullptr));
        btnAddTab3->setText(QCoreApplication::translate("MainWindow", "+", nullptr));
        tabWidgetModulel3->setTabText(tabWidgetModulel3->indexOf(tab_5), QCoreApplication::translate("MainWindow", "\346\240\207\347\255\2761", nullptr));
        tabWidgetModulel3->setTabText(tabWidgetModulel3->indexOf(tab_6), QCoreApplication::translate("MainWindow", "Tab 2", nullptr));
        pushButton_18->setText(QCoreApplication::translate("MainWindow", "AE", nullptr));
        pushButton_5->setText(QCoreApplication::translate("MainWindow", "Ai", nullptr));
        pushButton_13->setText(QCoreApplication::translate("MainWindow", "Ae", nullptr));
        pushButton_12->setText(QCoreApplication::translate("MainWindow", "Ps", nullptr));
        pushButton_9->setText(QCoreApplication::translate("MainWindow", "Id", nullptr));
        pushButton_8->setText(QCoreApplication::translate("MainWindow", "Xd", nullptr));
        btnM4Load->setText(QCoreApplication::translate("MainWindow", "\344\270\200\351\224\256\345\212\240\350\275\275", nullptr));
        btnM4Save->setText(QCoreApplication::translate("MainWindow", "\344\270\200\351\224\256\344\277\235\345\255\230", nullptr));
        btnAddTab4->setText(QCoreApplication::translate("MainWindow", "+", nullptr));
        tabWidgetModulel4->setTabText(tabWidgetModulel4->indexOf(tab_7), QCoreApplication::translate("MainWindow", "\346\240\207\347\255\2761", nullptr));
        tabWidgetModulel4->setTabText(tabWidgetModulel4->indexOf(tab_8), QCoreApplication::translate("MainWindow", "Tab 2", nullptr));
        menu->setTitle(QCoreApplication::translate("MainWindow", "\350\247\206\345\233\276", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
