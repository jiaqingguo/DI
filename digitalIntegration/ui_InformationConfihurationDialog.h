/********************************************************************************
** Form generated from reading UI file 'InformationConfihurationDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INFORMATIONCONFIHURATIONDIALOG_H
#define UI_INFORMATIONCONFIHURATIONDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_InformationConfihurationDialog
{
public:
    QVBoxLayout *verticalLayout_13;
    QSplitter *splitter;
    QTabWidget *tabWidget;
    QWidget *tab;
    QVBoxLayout *verticalLayout_9;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout_2;
    QTableView *tableViewTool1;
    QVBoxLayout *verticalLayout;
    QPushButton *btnToolAdd1;
    QPushButton *btnToolDel1;
    QSpacerItem *verticalSpacer;
    QWidget *tab_2;
    QVBoxLayout *verticalLayout_10;
    QGroupBox *groupBox_3;
    QHBoxLayout *horizontalLayout_3;
    QTableView *tableViewTool2;
    QVBoxLayout *verticalLayout_3;
    QPushButton *btnToolAdd2;
    QPushButton *btnToolDel2;
    QSpacerItem *verticalSpacer_3;
    QWidget *tab_3;
    QVBoxLayout *verticalLayout_11;
    QGroupBox *groupBox_5;
    QHBoxLayout *horizontalLayout_5;
    QTableView *tableViewTool3;
    QVBoxLayout *verticalLayout_5;
    QPushButton *btnToolAdd3;
    QPushButton *btnToolDel3;
    QSpacerItem *verticalSpacer_5;
    QGroupBox *groupBox_6;
    QHBoxLayout *horizontalLayout_6;
    QVBoxLayout *verticalLayout_6;
    QWidget *tab_4;
    QVBoxLayout *verticalLayout_12;
    QGroupBox *groupBox_7;
    QHBoxLayout *horizontalLayout_7;
    QTableView *tableViewTool4;
    QVBoxLayout *verticalLayout_7;
    QPushButton *btnToolAdd4;
    QPushButton *btnToolDel4;
    QSpacerItem *verticalSpacer_7;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout;
    QTableView *tableViewIP1;
    QVBoxLayout *verticalLayout_2;
    QPushButton *btnIpAdd1;
    QPushButton *btnIpDel1;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QDialog *InformationConfihurationDialog)
    {
        if (InformationConfihurationDialog->objectName().isEmpty())
            InformationConfihurationDialog->setObjectName(QString::fromUtf8("InformationConfihurationDialog"));
        InformationConfihurationDialog->resize(791, 719);
        verticalLayout_13 = new QVBoxLayout(InformationConfihurationDialog);
        verticalLayout_13->setObjectName(QString::fromUtf8("verticalLayout_13"));
        splitter = new QSplitter(InformationConfihurationDialog);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Vertical);
        tabWidget = new QTabWidget(splitter);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        verticalLayout_9 = new QVBoxLayout(tab);
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        groupBox = new QGroupBox(tab);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        horizontalLayout_2 = new QHBoxLayout(groupBox);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        tableViewTool1 = new QTableView(groupBox);
        tableViewTool1->setObjectName(QString::fromUtf8("tableViewTool1"));

        horizontalLayout_2->addWidget(tableViewTool1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        btnToolAdd1 = new QPushButton(groupBox);
        btnToolAdd1->setObjectName(QString::fromUtf8("btnToolAdd1"));

        verticalLayout->addWidget(btnToolAdd1);

        btnToolDel1 = new QPushButton(groupBox);
        btnToolDel1->setObjectName(QString::fromUtf8("btnToolDel1"));

        verticalLayout->addWidget(btnToolDel1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        horizontalLayout_2->addLayout(verticalLayout);


        verticalLayout_9->addWidget(groupBox);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        verticalLayout_10 = new QVBoxLayout(tab_2);
        verticalLayout_10->setObjectName(QString::fromUtf8("verticalLayout_10"));
        groupBox_3 = new QGroupBox(tab_2);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        horizontalLayout_3 = new QHBoxLayout(groupBox_3);
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        tableViewTool2 = new QTableView(groupBox_3);
        tableViewTool2->setObjectName(QString::fromUtf8("tableViewTool2"));

        horizontalLayout_3->addWidget(tableViewTool2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        btnToolAdd2 = new QPushButton(groupBox_3);
        btnToolAdd2->setObjectName(QString::fromUtf8("btnToolAdd2"));

        verticalLayout_3->addWidget(btnToolAdd2);

        btnToolDel2 = new QPushButton(groupBox_3);
        btnToolDel2->setObjectName(QString::fromUtf8("btnToolDel2"));

        verticalLayout_3->addWidget(btnToolDel2);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_3);


        horizontalLayout_3->addLayout(verticalLayout_3);


        verticalLayout_10->addWidget(groupBox_3);

        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        verticalLayout_11 = new QVBoxLayout(tab_3);
        verticalLayout_11->setObjectName(QString::fromUtf8("verticalLayout_11"));
        groupBox_5 = new QGroupBox(tab_3);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        horizontalLayout_5 = new QHBoxLayout(groupBox_5);
        horizontalLayout_5->setSpacing(0);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        tableViewTool3 = new QTableView(groupBox_5);
        tableViewTool3->setObjectName(QString::fromUtf8("tableViewTool3"));

        horizontalLayout_5->addWidget(tableViewTool3);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        btnToolAdd3 = new QPushButton(groupBox_5);
        btnToolAdd3->setObjectName(QString::fromUtf8("btnToolAdd3"));

        verticalLayout_5->addWidget(btnToolAdd3);

        btnToolDel3 = new QPushButton(groupBox_5);
        btnToolDel3->setObjectName(QString::fromUtf8("btnToolDel3"));

        verticalLayout_5->addWidget(btnToolDel3);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_5->addItem(verticalSpacer_5);


        horizontalLayout_5->addLayout(verticalLayout_5);


        verticalLayout_11->addWidget(groupBox_5);

        groupBox_6 = new QGroupBox(tab_3);
        groupBox_6->setObjectName(QString::fromUtf8("groupBox_6"));
        horizontalLayout_6 = new QHBoxLayout(groupBox_6);
        horizontalLayout_6->setSpacing(0);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalLayout_6->setContentsMargins(0, 0, 0, 0);
        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));

        horizontalLayout_6->addLayout(verticalLayout_6);


        verticalLayout_11->addWidget(groupBox_6);

        tabWidget->addTab(tab_3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QString::fromUtf8("tab_4"));
        verticalLayout_12 = new QVBoxLayout(tab_4);
        verticalLayout_12->setObjectName(QString::fromUtf8("verticalLayout_12"));
        groupBox_7 = new QGroupBox(tab_4);
        groupBox_7->setObjectName(QString::fromUtf8("groupBox_7"));
        horizontalLayout_7 = new QHBoxLayout(groupBox_7);
        horizontalLayout_7->setSpacing(0);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        horizontalLayout_7->setContentsMargins(0, 0, 0, 0);
        tableViewTool4 = new QTableView(groupBox_7);
        tableViewTool4->setObjectName(QString::fromUtf8("tableViewTool4"));

        horizontalLayout_7->addWidget(tableViewTool4);

        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        btnToolAdd4 = new QPushButton(groupBox_7);
        btnToolAdd4->setObjectName(QString::fromUtf8("btnToolAdd4"));

        verticalLayout_7->addWidget(btnToolAdd4);

        btnToolDel4 = new QPushButton(groupBox_7);
        btnToolDel4->setObjectName(QString::fromUtf8("btnToolDel4"));

        verticalLayout_7->addWidget(btnToolDel4);

        verticalSpacer_7 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_7->addItem(verticalSpacer_7);


        horizontalLayout_7->addLayout(verticalLayout_7);


        verticalLayout_12->addWidget(groupBox_7);

        tabWidget->addTab(tab_4, QString());
        splitter->addWidget(tabWidget);
        groupBox_2 = new QGroupBox(splitter);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        horizontalLayout = new QHBoxLayout(groupBox_2);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        tableViewIP1 = new QTableView(groupBox_2);
        tableViewIP1->setObjectName(QString::fromUtf8("tableViewIP1"));

        horizontalLayout->addWidget(tableViewIP1);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        btnIpAdd1 = new QPushButton(groupBox_2);
        btnIpAdd1->setObjectName(QString::fromUtf8("btnIpAdd1"));

        verticalLayout_2->addWidget(btnIpAdd1);

        btnIpDel1 = new QPushButton(groupBox_2);
        btnIpDel1->setObjectName(QString::fromUtf8("btnIpDel1"));

        verticalLayout_2->addWidget(btnIpDel1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_2);


        horizontalLayout->addLayout(verticalLayout_2);

        splitter->addWidget(groupBox_2);

        verticalLayout_13->addWidget(splitter);


        retranslateUi(InformationConfihurationDialog);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(InformationConfihurationDialog);
    } // setupUi

    void retranslateUi(QDialog *InformationConfihurationDialog)
    {
        InformationConfihurationDialog->setWindowTitle(QCoreApplication::translate("InformationConfihurationDialog", " \344\277\241\346\201\257\351\205\215\347\275\256", nullptr));
        groupBox->setTitle(QCoreApplication::translate("InformationConfihurationDialog", "\345\267\245\345\205\267\345\210\227\350\241\250", nullptr));
        btnToolAdd1->setText(QCoreApplication::translate("InformationConfihurationDialog", "\346\267\273\345\212\240", nullptr));
        btnToolDel1->setText(QCoreApplication::translate("InformationConfihurationDialog", "\345\210\240\351\231\244", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("InformationConfihurationDialog", "\346\250\241\345\235\2271", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("InformationConfihurationDialog", "\345\267\245\345\205\267\345\210\227\350\241\250", nullptr));
        btnToolAdd2->setText(QCoreApplication::translate("InformationConfihurationDialog", "\346\267\273\345\212\240", nullptr));
        btnToolDel2->setText(QCoreApplication::translate("InformationConfihurationDialog", "\345\210\240\351\231\244", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("InformationConfihurationDialog", "\346\250\241\345\235\2272", nullptr));
        groupBox_5->setTitle(QCoreApplication::translate("InformationConfihurationDialog", "\345\267\245\345\205\267\345\210\227\350\241\250", nullptr));
        btnToolAdd3->setText(QCoreApplication::translate("InformationConfihurationDialog", "\346\267\273\345\212\240", nullptr));
        btnToolDel3->setText(QCoreApplication::translate("InformationConfihurationDialog", "\345\210\240\351\231\244", nullptr));
        groupBox_6->setTitle(QCoreApplication::translate("InformationConfihurationDialog", "ip\345\210\227\350\241\250", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QCoreApplication::translate("InformationConfihurationDialog", "\346\250\241\345\235\2273", nullptr));
        groupBox_7->setTitle(QCoreApplication::translate("InformationConfihurationDialog", "\345\267\245\345\205\267\345\210\227\350\241\250", nullptr));
        btnToolAdd4->setText(QCoreApplication::translate("InformationConfihurationDialog", "\346\267\273\345\212\240", nullptr));
        btnToolDel4->setText(QCoreApplication::translate("InformationConfihurationDialog", "\345\210\240\351\231\244", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QCoreApplication::translate("InformationConfihurationDialog", "\346\250\241\345\235\2274", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("InformationConfihurationDialog", "ip\345\210\227\350\241\250", nullptr));
        btnIpAdd1->setText(QCoreApplication::translate("InformationConfihurationDialog", "\346\267\273\345\212\240", nullptr));
        btnIpDel1->setText(QCoreApplication::translate("InformationConfihurationDialog", "\345\210\240\351\231\244", nullptr));
    } // retranslateUi

};

namespace Ui {
    class InformationConfihurationDialog: public Ui_InformationConfihurationDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INFORMATIONCONFIHURATIONDIALOG_H
