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
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_InformationConfihurationDialog
{
public:
    QWidget *widget;
    QGridLayout *gridLayout_2;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *btnModule1;
    QPushButton *btnModule2;
    QPushButton *btnModule3;
    QPushButton *btnModule4;
    QSpacerItem *horizontalSpacer_5;
    QSplitter *splitter;
    QStackedWidget *stackedWidget;
    QWidget *stackedWidgetPage1;
    QVBoxLayout *verticalLayout_6;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_3;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnToolAdd1;
    QPushButton *btnToolDel1;
    QTableView *tableViewTool1;
    QWidget *stackedWidgetPage2;
    QVBoxLayout *verticalLayout_10;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout_8;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_4;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *btnToolAdd2;
    QPushButton *btnToolDel2;
    QTableView *tableViewTool2;
    QWidget *stackedWidgetPage3;
    QVBoxLayout *verticalLayout_11;
    QGroupBox *groupBox_5;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_5;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *btnToolAdd3;
    QPushButton *btnToolDel3;
    QTableView *tableViewTool3;
    QWidget *stackedWidgetPage4;
    QVBoxLayout *verticalLayout_12;
    QGroupBox *groupBox_7;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *btnToolAdd4;
    QPushButton *btnToolDel4;
    QTableView *tableViewTool4;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_2;
    QTableView *tableViewIP1;

    void setupUi(QDialog *InformationConfihurationDialog)
    {
        if (InformationConfihurationDialog->objectName().isEmpty())
            InformationConfihurationDialog->setObjectName(QString::fromUtf8("InformationConfihurationDialog"));
        InformationConfihurationDialog->resize(791, 715);
        widget = new QWidget(InformationConfihurationDialog);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(9, 9, 781, 51));
        gridLayout_2 = new QGridLayout(widget);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        btnModule1 = new QPushButton(widget);
        btnModule1->setObjectName(QString::fromUtf8("btnModule1"));

        horizontalLayout_4->addWidget(btnModule1);

        btnModule2 = new QPushButton(widget);
        btnModule2->setObjectName(QString::fromUtf8("btnModule2"));

        horizontalLayout_4->addWidget(btnModule2);

        btnModule3 = new QPushButton(widget);
        btnModule3->setObjectName(QString::fromUtf8("btnModule3"));

        horizontalLayout_4->addWidget(btnModule3);

        btnModule4 = new QPushButton(widget);
        btnModule4->setObjectName(QString::fromUtf8("btnModule4"));

        horizontalLayout_4->addWidget(btnModule4);


        gridLayout_2->addLayout(horizontalLayout_4, 0, 0, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_5, 0, 1, 1, 1);

        splitter = new QSplitter(InformationConfihurationDialog);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setGeometry(QRect(9, 57, 771, 651));
        splitter->setOrientation(Qt::Horizontal);
        stackedWidget = new QStackedWidget(splitter);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        stackedWidgetPage1 = new QWidget();
        stackedWidgetPage1->setObjectName(QString::fromUtf8("stackedWidgetPage1"));
        verticalLayout_6 = new QVBoxLayout(stackedWidgetPage1);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        groupBox = new QGroupBox(stackedWidgetPage1);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_6->addWidget(label_3);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer);

        btnToolAdd1 = new QPushButton(groupBox);
        btnToolAdd1->setObjectName(QString::fromUtf8("btnToolAdd1"));

        horizontalLayout_6->addWidget(btnToolAdd1);

        btnToolDel1 = new QPushButton(groupBox);
        btnToolDel1->setObjectName(QString::fromUtf8("btnToolDel1"));

        horizontalLayout_6->addWidget(btnToolDel1);


        verticalLayout->addLayout(horizontalLayout_6);

        tableViewTool1 = new QTableView(groupBox);
        tableViewTool1->setObjectName(QString::fromUtf8("tableViewTool1"));

        verticalLayout->addWidget(tableViewTool1);


        verticalLayout_6->addWidget(groupBox);

        stackedWidget->addWidget(stackedWidgetPage1);
        stackedWidgetPage2 = new QWidget();
        stackedWidgetPage2->setObjectName(QString::fromUtf8("stackedWidgetPage2"));
        verticalLayout_10 = new QVBoxLayout(stackedWidgetPage2);
        verticalLayout_10->setObjectName(QString::fromUtf8("verticalLayout_10"));
        groupBox_3 = new QGroupBox(stackedWidgetPage2);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        verticalLayout_8 = new QVBoxLayout(groupBox_3);
        verticalLayout_8->setSpacing(0);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        verticalLayout_8->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_4 = new QLabel(groupBox_3);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_2->addWidget(label_4);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        btnToolAdd2 = new QPushButton(groupBox_3);
        btnToolAdd2->setObjectName(QString::fromUtf8("btnToolAdd2"));

        horizontalLayout_2->addWidget(btnToolAdd2);

        btnToolDel2 = new QPushButton(groupBox_3);
        btnToolDel2->setObjectName(QString::fromUtf8("btnToolDel2"));

        horizontalLayout_2->addWidget(btnToolDel2);


        verticalLayout_8->addLayout(horizontalLayout_2);

        tableViewTool2 = new QTableView(groupBox_3);
        tableViewTool2->setObjectName(QString::fromUtf8("tableViewTool2"));

        verticalLayout_8->addWidget(tableViewTool2);


        verticalLayout_10->addWidget(groupBox_3);

        stackedWidget->addWidget(stackedWidgetPage2);
        stackedWidgetPage3 = new QWidget();
        stackedWidgetPage3->setObjectName(QString::fromUtf8("stackedWidgetPage3"));
        verticalLayout_11 = new QVBoxLayout(stackedWidgetPage3);
        verticalLayout_11->setObjectName(QString::fromUtf8("verticalLayout_11"));
        groupBox_5 = new QGroupBox(stackedWidgetPage3);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        verticalLayout_3 = new QVBoxLayout(groupBox_5);
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_5 = new QLabel(groupBox_5);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout_3->addWidget(label_5);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);

        btnToolAdd3 = new QPushButton(groupBox_5);
        btnToolAdd3->setObjectName(QString::fromUtf8("btnToolAdd3"));

        horizontalLayout_3->addWidget(btnToolAdd3);

        btnToolDel3 = new QPushButton(groupBox_5);
        btnToolDel3->setObjectName(QString::fromUtf8("btnToolDel3"));

        horizontalLayout_3->addWidget(btnToolDel3);


        verticalLayout_3->addLayout(horizontalLayout_3);

        tableViewTool3 = new QTableView(groupBox_5);
        tableViewTool3->setObjectName(QString::fromUtf8("tableViewTool3"));

        verticalLayout_3->addWidget(tableViewTool3);


        verticalLayout_11->addWidget(groupBox_5);

        stackedWidget->addWidget(stackedWidgetPage3);
        stackedWidgetPage4 = new QWidget();
        stackedWidgetPage4->setObjectName(QString::fromUtf8("stackedWidgetPage4"));
        verticalLayout_12 = new QVBoxLayout(stackedWidgetPage4);
        verticalLayout_12->setObjectName(QString::fromUtf8("verticalLayout_12"));
        groupBox_7 = new QGroupBox(stackedWidgetPage4);
        groupBox_7->setObjectName(QString::fromUtf8("groupBox_7"));
        verticalLayout_5 = new QVBoxLayout(groupBox_7);
        verticalLayout_5->setSpacing(0);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label = new QLabel(groupBox_7);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_5->addWidget(label);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_4);

        btnToolAdd4 = new QPushButton(groupBox_7);
        btnToolAdd4->setObjectName(QString::fromUtf8("btnToolAdd4"));

        horizontalLayout_5->addWidget(btnToolAdd4);

        btnToolDel4 = new QPushButton(groupBox_7);
        btnToolDel4->setObjectName(QString::fromUtf8("btnToolDel4"));

        horizontalLayout_5->addWidget(btnToolDel4);


        verticalLayout_5->addLayout(horizontalLayout_5);

        tableViewTool4 = new QTableView(groupBox_7);
        tableViewTool4->setObjectName(QString::fromUtf8("tableViewTool4"));

        verticalLayout_5->addWidget(tableViewTool4);


        verticalLayout_12->addWidget(groupBox_7);

        stackedWidget->addWidget(stackedWidgetPage4);
        splitter->addWidget(stackedWidget);
        groupBox_2 = new QGroupBox(splitter);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        horizontalLayout = new QHBoxLayout(groupBox_2);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout_2->addWidget(label_2);

        tableViewIP1 = new QTableView(groupBox_2);
        tableViewIP1->setObjectName(QString::fromUtf8("tableViewIP1"));

        verticalLayout_2->addWidget(tableViewIP1);


        horizontalLayout->addLayout(verticalLayout_2);

        splitter->addWidget(groupBox_2);

        retranslateUi(InformationConfihurationDialog);

        QMetaObject::connectSlotsByName(InformationConfihurationDialog);
    } // setupUi

    void retranslateUi(QDialog *InformationConfihurationDialog)
    {
        InformationConfihurationDialog->setWindowTitle(QCoreApplication::translate("InformationConfihurationDialog", " \344\277\241\346\201\257\351\205\215\347\275\256", nullptr));
        btnModule1->setText(QCoreApplication::translate("InformationConfihurationDialog", "\345\212\237\350\203\275\346\240\267\346\234\272", nullptr));
        btnModule2->setText(QCoreApplication::translate("InformationConfihurationDialog", "\345\207\240\344\275\225\346\240\267\346\234\272", nullptr));
        btnModule3->setText(QCoreApplication::translate("InformationConfihurationDialog", "\346\200\247\350\203\275\346\240\267\346\234\272", nullptr));
        btnModule4->setText(QCoreApplication::translate("InformationConfihurationDialog", "\347\224\237\344\272\247\346\240\267\346\234\272", nullptr));
        groupBox->setTitle(QString());
        label_3->setText(QCoreApplication::translate("InformationConfihurationDialog", "\345\267\245\345\205\267\345\210\227\350\241\250", nullptr));
        btnToolAdd1->setText(QCoreApplication::translate("InformationConfihurationDialog", "\346\267\273\345\212\240", nullptr));
        btnToolDel1->setText(QCoreApplication::translate("InformationConfihurationDialog", "\345\210\240\351\231\244", nullptr));
        groupBox_3->setTitle(QString());
        label_4->setText(QCoreApplication::translate("InformationConfihurationDialog", "\345\267\245\345\205\267\345\210\227\350\241\250", nullptr));
        btnToolAdd2->setText(QCoreApplication::translate("InformationConfihurationDialog", "\346\267\273\345\212\240", nullptr));
        btnToolDel2->setText(QCoreApplication::translate("InformationConfihurationDialog", "\345\210\240\351\231\244", nullptr));
        groupBox_5->setTitle(QString());
        label_5->setText(QCoreApplication::translate("InformationConfihurationDialog", "\345\267\245\345\205\267\345\210\227\350\241\250", nullptr));
        btnToolAdd3->setText(QCoreApplication::translate("InformationConfihurationDialog", "\346\267\273\345\212\240", nullptr));
        btnToolDel3->setText(QCoreApplication::translate("InformationConfihurationDialog", "\345\210\240\351\231\244", nullptr));
        groupBox_7->setTitle(QString());
        label->setText(QCoreApplication::translate("InformationConfihurationDialog", "\345\267\245\345\205\267\345\210\227\350\241\250", nullptr));
        btnToolAdd4->setText(QCoreApplication::translate("InformationConfihurationDialog", "\346\267\273\345\212\240", nullptr));
        btnToolDel4->setText(QCoreApplication::translate("InformationConfihurationDialog", "\345\210\240\351\231\244", nullptr));
        groupBox_2->setTitle(QString());
        label_2->setText(QCoreApplication::translate("InformationConfihurationDialog", "IP\345\210\227\350\241\250", nullptr));
    } // retranslateUi

};

namespace Ui {
    class InformationConfihurationDialog: public Ui_InformationConfihurationDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INFORMATIONCONFIHURATIONDIALOG_H
