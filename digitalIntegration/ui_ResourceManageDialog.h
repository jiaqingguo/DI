/********************************************************************************
** Form generated from reading UI file 'ResourceManageDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RESOURCEMANAGEDIALOG_H
#define UI_RESOURCEMANAGEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ResourceManageDialog
{
public:
    QGridLayout *gridLayout_3;
    QWidget *widget_4;
    QHBoxLayout *horizontalLayout_9;
    QHBoxLayout *horizontalLayout;
    QPushButton *btnList;
    QPushButton *btnCurve;
    QSpacerItem *horizontalSpacer;
    QStackedWidget *stackedWidget;
    QWidget *pageList;
    QGridLayout *gridLayout_2;
    QWidget *widget;
    QGridLayout *gridLayout;
    QTableView *tableView;
    QWidget *pageCurve;
    QGridLayout *gridLayout_4;
    QWidget *widget_2;
    QGridLayout *gridLayout_10;
    QWidget *widget_3;
    QGridLayout *gridLayout_5;
    QLabel *label;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_2;
    QComboBox *comboBox1;
    QWidget *widgetCpu;
    QGridLayout *gridLayout_11;
    QWidget *widget_5;
    QGridLayout *gridLayout_6;
    QLabel *label_3;
    QSpacerItem *horizontalSpacer_3;
    QLabel *label_4;
    QComboBox *comboBox2;
    QWidget *widgetMemory;
    QGridLayout *gridLayout_12;
    QWidget *widget_6;
    QGridLayout *gridLayout_7;
    QLabel *label_5;
    QSpacerItem *horizontalSpacer_4;
    QLabel *label_6;
    QComboBox *comboBox3;
    QWidget *widgetDisk;
    QGridLayout *gridLayout_13;
    QWidget *widget_7;
    QGridLayout *gridLayout_8;
    QLabel *label_7;
    QSpacerItem *horizontalSpacer_5;
    QLabel *label_8;
    QComboBox *comboBox4;
    QWidget *widgetNet;
    QGridLayout *gridLayout_14;
    QWidget *widget_8;
    QGridLayout *gridLayout_9;
    QLabel *label_9;
    QSpacerItem *horizontalSpacer_6;
    QLabel *label_10;
    QComboBox *comboBox5;
    QWidget *widgetGpu;
    QGridLayout *gridLayout_15;
    QWidget *widget_9;

    void setupUi(QDialog *ResourceManageDialog)
    {
        if (ResourceManageDialog->objectName().isEmpty())
            ResourceManageDialog->setObjectName(QString::fromUtf8("ResourceManageDialog"));
        ResourceManageDialog->resize(905, 669);
        ResourceManageDialog->setStyleSheet(QString::fromUtf8(""));
        gridLayout_3 = new QGridLayout(ResourceManageDialog);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        widget_4 = new QWidget(ResourceManageDialog);
        widget_4->setObjectName(QString::fromUtf8("widget_4"));
        widget_4->setMinimumSize(QSize(0, 0));
        horizontalLayout_9 = new QHBoxLayout(widget_4);
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        horizontalLayout_9->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        btnList = new QPushButton(widget_4);
        btnList->setObjectName(QString::fromUtf8("btnList"));

        horizontalLayout->addWidget(btnList);

        btnCurve = new QPushButton(widget_4);
        btnCurve->setObjectName(QString::fromUtf8("btnCurve"));

        horizontalLayout->addWidget(btnCurve);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        horizontalLayout_9->addLayout(horizontalLayout);


        gridLayout_3->addWidget(widget_4, 0, 0, 1, 1);

        stackedWidget = new QStackedWidget(ResourceManageDialog);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        pageList = new QWidget();
        pageList->setObjectName(QString::fromUtf8("pageList"));
        gridLayout_2 = new QGridLayout(pageList);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        widget = new QWidget(pageList);
        widget->setObjectName(QString::fromUtf8("widget"));
        gridLayout = new QGridLayout(widget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        tableView = new QTableView(widget);
        tableView->setObjectName(QString::fromUtf8("tableView"));

        gridLayout->addWidget(tableView, 0, 0, 1, 1);


        gridLayout_2->addWidget(widget, 0, 0, 1, 1);

        stackedWidget->addWidget(pageList);
        pageCurve = new QWidget();
        pageCurve->setObjectName(QString::fromUtf8("pageCurve"));
        gridLayout_4 = new QGridLayout(pageCurve);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        gridLayout_4->setContentsMargins(0, 0, 0, 0);
        widget_2 = new QWidget(pageCurve);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        gridLayout_10 = new QGridLayout(widget_2);
        gridLayout_10->setObjectName(QString::fromUtf8("gridLayout_10"));
        widget_3 = new QWidget(widget_2);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        gridLayout_5 = new QGridLayout(widget_3);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        label = new QLabel(widget_3);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_5->addWidget(label, 0, 0, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(76, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_5->addItem(horizontalSpacer_2, 0, 1, 1, 1);

        label_2 = new QLabel(widget_3);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_5->addWidget(label_2, 0, 2, 1, 1);

        comboBox1 = new QComboBox(widget_3);
        comboBox1->setObjectName(QString::fromUtf8("comboBox1"));

        gridLayout_5->addWidget(comboBox1, 0, 3, 1, 1);

        widgetCpu = new QWidget(widget_3);
        widgetCpu->setObjectName(QString::fromUtf8("widgetCpu"));
        gridLayout_11 = new QGridLayout(widgetCpu);
        gridLayout_11->setObjectName(QString::fromUtf8("gridLayout_11"));

        gridLayout_5->addWidget(widgetCpu, 1, 0, 1, 4);


        gridLayout_10->addWidget(widget_3, 0, 0, 1, 1);

        widget_5 = new QWidget(widget_2);
        widget_5->setObjectName(QString::fromUtf8("widget_5"));
        gridLayout_6 = new QGridLayout(widget_5);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        label_3 = new QLabel(widget_5);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout_6->addWidget(label_3, 0, 0, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(69, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_6->addItem(horizontalSpacer_3, 0, 1, 1, 1);

        label_4 = new QLabel(widget_5);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_6->addWidget(label_4, 0, 2, 1, 1);

        comboBox2 = new QComboBox(widget_5);
        comboBox2->setObjectName(QString::fromUtf8("comboBox2"));

        gridLayout_6->addWidget(comboBox2, 0, 3, 1, 1);

        widgetMemory = new QWidget(widget_5);
        widgetMemory->setObjectName(QString::fromUtf8("widgetMemory"));
        gridLayout_12 = new QGridLayout(widgetMemory);
        gridLayout_12->setObjectName(QString::fromUtf8("gridLayout_12"));

        gridLayout_6->addWidget(widgetMemory, 1, 0, 1, 4);


        gridLayout_10->addWidget(widget_5, 0, 1, 1, 1);

        widget_6 = new QWidget(widget_2);
        widget_6->setObjectName(QString::fromUtf8("widget_6"));
        gridLayout_7 = new QGridLayout(widget_6);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        label_5 = new QLabel(widget_6);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout_7->addWidget(label_5, 0, 0, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(70, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_7->addItem(horizontalSpacer_4, 0, 1, 1, 1);

        label_6 = new QLabel(widget_6);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout_7->addWidget(label_6, 0, 2, 1, 1);

        comboBox3 = new QComboBox(widget_6);
        comboBox3->setObjectName(QString::fromUtf8("comboBox3"));

        gridLayout_7->addWidget(comboBox3, 0, 3, 1, 1);

        widgetDisk = new QWidget(widget_6);
        widgetDisk->setObjectName(QString::fromUtf8("widgetDisk"));
        gridLayout_13 = new QGridLayout(widgetDisk);
        gridLayout_13->setObjectName(QString::fromUtf8("gridLayout_13"));

        gridLayout_7->addWidget(widgetDisk, 1, 0, 1, 4);


        gridLayout_10->addWidget(widget_6, 0, 2, 1, 1);

        widget_7 = new QWidget(widget_2);
        widget_7->setObjectName(QString::fromUtf8("widget_7"));
        gridLayout_8 = new QGridLayout(widget_7);
        gridLayout_8->setObjectName(QString::fromUtf8("gridLayout_8"));
        label_7 = new QLabel(widget_7);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout_8->addWidget(label_7, 0, 0, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(70, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_8->addItem(horizontalSpacer_5, 0, 1, 1, 1);

        label_8 = new QLabel(widget_7);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        gridLayout_8->addWidget(label_8, 0, 2, 1, 1);

        comboBox4 = new QComboBox(widget_7);
        comboBox4->setObjectName(QString::fromUtf8("comboBox4"));

        gridLayout_8->addWidget(comboBox4, 0, 3, 1, 1);

        widgetNet = new QWidget(widget_7);
        widgetNet->setObjectName(QString::fromUtf8("widgetNet"));
        gridLayout_14 = new QGridLayout(widgetNet);
        gridLayout_14->setObjectName(QString::fromUtf8("gridLayout_14"));

        gridLayout_8->addWidget(widgetNet, 1, 0, 1, 4);


        gridLayout_10->addWidget(widget_7, 1, 0, 1, 1);

        widget_8 = new QWidget(widget_2);
        widget_8->setObjectName(QString::fromUtf8("widget_8"));
        gridLayout_9 = new QGridLayout(widget_8);
        gridLayout_9->setObjectName(QString::fromUtf8("gridLayout_9"));
        label_9 = new QLabel(widget_8);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        gridLayout_9->addWidget(label_9, 0, 0, 1, 1);

        horizontalSpacer_6 = new QSpacerItem(75, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_9->addItem(horizontalSpacer_6, 0, 1, 1, 1);

        label_10 = new QLabel(widget_8);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        gridLayout_9->addWidget(label_10, 0, 2, 1, 1);

        comboBox5 = new QComboBox(widget_8);
        comboBox5->setObjectName(QString::fromUtf8("comboBox5"));

        gridLayout_9->addWidget(comboBox5, 0, 3, 1, 1);

        widgetGpu = new QWidget(widget_8);
        widgetGpu->setObjectName(QString::fromUtf8("widgetGpu"));
        gridLayout_15 = new QGridLayout(widgetGpu);
        gridLayout_15->setObjectName(QString::fromUtf8("gridLayout_15"));

        gridLayout_9->addWidget(widgetGpu, 1, 0, 1, 4);


        gridLayout_10->addWidget(widget_8, 1, 1, 1, 1);

        widget_9 = new QWidget(widget_2);
        widget_9->setObjectName(QString::fromUtf8("widget_9"));

        gridLayout_10->addWidget(widget_9, 1, 2, 1, 1);


        gridLayout_4->addWidget(widget_2, 0, 0, 1, 1);

        stackedWidget->addWidget(pageCurve);

        gridLayout_3->addWidget(stackedWidget, 1, 0, 1, 1);


        retranslateUi(ResourceManageDialog);

        stackedWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(ResourceManageDialog);
    } // setupUi

    void retranslateUi(QDialog *ResourceManageDialog)
    {
        ResourceManageDialog->setWindowTitle(QCoreApplication::translate("ResourceManageDialog", "\350\265\204\346\272\220\347\256\241\347\220\206\345\231\250", nullptr));
        btnList->setText(QCoreApplication::translate("ResourceManageDialog", "\345\210\227\350\241\250", nullptr));
        btnCurve->setText(QCoreApplication::translate("ResourceManageDialog", "\346\233\262\347\272\277", nullptr));
        label->setText(QCoreApplication::translate("ResourceManageDialog", "CPU\344\275\277\347\224\250\347\216\207", nullptr));
        label_2->setText(QCoreApplication::translate("ResourceManageDialog", "\344\270\273\346\234\272\351\200\211\346\213\251", nullptr));
        label_3->setText(QCoreApplication::translate("ResourceManageDialog", "\345\206\205\345\255\230\344\275\277\347\224\250\347\216\207", nullptr));
        label_4->setText(QCoreApplication::translate("ResourceManageDialog", "\344\270\273\346\234\272\351\200\211\346\213\251", nullptr));
        label_5->setText(QCoreApplication::translate("ResourceManageDialog", "\347\243\201\347\233\230\344\275\277\347\224\250\347\216\207", nullptr));
        label_6->setText(QCoreApplication::translate("ResourceManageDialog", "\344\270\273\346\234\272\351\200\211\346\213\251", nullptr));
        label_7->setText(QCoreApplication::translate("ResourceManageDialog", "\347\275\221\347\273\234\345\220\236\345\220\220\351\207\217", nullptr));
        label_8->setText(QCoreApplication::translate("ResourceManageDialog", "\344\270\273\346\234\272\351\200\211\346\213\251", nullptr));
        label_9->setText(QCoreApplication::translate("ResourceManageDialog", "GPU\344\275\277\347\224\250\347\216\207", nullptr));
        label_10->setText(QCoreApplication::translate("ResourceManageDialog", "\344\270\273\346\234\272\351\200\211\346\213\251", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ResourceManageDialog: public Ui_ResourceManageDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RESOURCEMANAGEDIALOG_H
