/********************************************************************************
** Form generated from reading UI file 'DataManageDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DATAMANAGEDIALOG_H
#define UI_DATAMANAGEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DataManageDialog
{
public:
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *btn1;
    QPushButton *btn2;
    QPushButton *btn3;
    QPushButton *btn4;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *lineEdit;
    QComboBox *comboBox;
    QLabel *label;
    QDateTimeEdit *dateTimeEdit;
    QPushButton *pushButton_5;
    QSpacerItem *horizontalSpacer_3;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QVBoxLayout *verticalLayout_5;
    QTableView *tableView1;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *pushButton_6;
    QSpinBox *spinBox;
    QPushButton *pushButton_7;
    QWidget *page_2;
    QVBoxLayout *verticalLayout_4;
    QTableView *tableView2;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_6;
    QPushButton *pushButton_10;
    QSpinBox *spinBox_3;
    QPushButton *pushButton_11;
    QWidget *page_3;
    QVBoxLayout *verticalLayout_3;
    QTableView *tableView3;
    QHBoxLayout *horizontalLayout_6;
    QSpacerItem *horizontalSpacer_7;
    QPushButton *pushButton_12;
    QSpinBox *spinBox_4;
    QPushButton *pushButton_13;
    QWidget *page_4;
    QVBoxLayout *verticalLayout;
    QTableView *tableView4;
    QHBoxLayout *horizontalLayout_7;
    QSpacerItem *horizontalSpacer_8;
    QPushButton *pushButton_14;
    QSpinBox *spinBox_5;
    QPushButton *pushButton_15;
    QButtonGroup *buttonGroup;

    void setupUi(QDialog *DataManageDialog)
    {
        if (DataManageDialog->objectName().isEmpty())
            DataManageDialog->setObjectName(QString::fromUtf8("DataManageDialog"));
        DataManageDialog->resize(724, 534);
        verticalLayout_2 = new QVBoxLayout(DataManageDialog);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        btn1 = new QPushButton(DataManageDialog);
        buttonGroup = new QButtonGroup(DataManageDialog);
        buttonGroup->setObjectName(QString::fromUtf8("buttonGroup"));
        buttonGroup->addButton(btn1);
        btn1->setObjectName(QString::fromUtf8("btn1"));

        horizontalLayout->addWidget(btn1);

        btn2 = new QPushButton(DataManageDialog);
        buttonGroup->addButton(btn2);
        btn2->setObjectName(QString::fromUtf8("btn2"));

        horizontalLayout->addWidget(btn2);

        btn3 = new QPushButton(DataManageDialog);
        buttonGroup->addButton(btn3);
        btn3->setObjectName(QString::fromUtf8("btn3"));

        horizontalLayout->addWidget(btn3);

        btn4 = new QPushButton(DataManageDialog);
        buttonGroup->addButton(btn4);
        btn4->setObjectName(QString::fromUtf8("btn4"));

        horizontalLayout->addWidget(btn4);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout_2->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        lineEdit = new QLineEdit(DataManageDialog);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        horizontalLayout_2->addWidget(lineEdit);

        comboBox = new QComboBox(DataManageDialog);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        horizontalLayout_2->addWidget(comboBox);

        label = new QLabel(DataManageDialog);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_2->addWidget(label);

        dateTimeEdit = new QDateTimeEdit(DataManageDialog);
        dateTimeEdit->setObjectName(QString::fromUtf8("dateTimeEdit"));

        horizontalLayout_2->addWidget(dateTimeEdit);

        pushButton_5 = new QPushButton(DataManageDialog);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));

        horizontalLayout_2->addWidget(pushButton_5);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);


        verticalLayout_2->addLayout(horizontalLayout_2);

        stackedWidget = new QStackedWidget(DataManageDialog);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        verticalLayout_5 = new QVBoxLayout(page);
        verticalLayout_5->setSpacing(0);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        tableView1 = new QTableView(page);
        tableView1->setObjectName(QString::fromUtf8("tableView1"));

        verticalLayout_5->addWidget(tableView1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_4);

        pushButton_6 = new QPushButton(page);
        pushButton_6->setObjectName(QString::fromUtf8("pushButton_6"));

        horizontalLayout_3->addWidget(pushButton_6);

        spinBox = new QSpinBox(page);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));

        horizontalLayout_3->addWidget(spinBox);

        pushButton_7 = new QPushButton(page);
        pushButton_7->setObjectName(QString::fromUtf8("pushButton_7"));

        horizontalLayout_3->addWidget(pushButton_7);


        verticalLayout_5->addLayout(horizontalLayout_3);

        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        verticalLayout_4 = new QVBoxLayout(page_2);
        verticalLayout_4->setSpacing(0);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        tableView2 = new QTableView(page_2);
        tableView2->setObjectName(QString::fromUtf8("tableView2"));

        verticalLayout_4->addWidget(tableView2);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_6);

        pushButton_10 = new QPushButton(page_2);
        pushButton_10->setObjectName(QString::fromUtf8("pushButton_10"));

        horizontalLayout_5->addWidget(pushButton_10);

        spinBox_3 = new QSpinBox(page_2);
        spinBox_3->setObjectName(QString::fromUtf8("spinBox_3"));

        horizontalLayout_5->addWidget(spinBox_3);

        pushButton_11 = new QPushButton(page_2);
        pushButton_11->setObjectName(QString::fromUtf8("pushButton_11"));

        horizontalLayout_5->addWidget(pushButton_11);


        verticalLayout_4->addLayout(horizontalLayout_5);

        stackedWidget->addWidget(page_2);
        page_3 = new QWidget();
        page_3->setObjectName(QString::fromUtf8("page_3"));
        verticalLayout_3 = new QVBoxLayout(page_3);
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        tableView3 = new QTableView(page_3);
        tableView3->setObjectName(QString::fromUtf8("tableView3"));

        verticalLayout_3->addWidget(tableView3);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_7);

        pushButton_12 = new QPushButton(page_3);
        pushButton_12->setObjectName(QString::fromUtf8("pushButton_12"));

        horizontalLayout_6->addWidget(pushButton_12);

        spinBox_4 = new QSpinBox(page_3);
        spinBox_4->setObjectName(QString::fromUtf8("spinBox_4"));

        horizontalLayout_6->addWidget(spinBox_4);

        pushButton_13 = new QPushButton(page_3);
        pushButton_13->setObjectName(QString::fromUtf8("pushButton_13"));

        horizontalLayout_6->addWidget(pushButton_13);


        verticalLayout_3->addLayout(horizontalLayout_6);

        stackedWidget->addWidget(page_3);
        page_4 = new QWidget();
        page_4->setObjectName(QString::fromUtf8("page_4"));
        verticalLayout = new QVBoxLayout(page_4);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        tableView4 = new QTableView(page_4);
        tableView4->setObjectName(QString::fromUtf8("tableView4"));

        verticalLayout->addWidget(tableView4);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_8);

        pushButton_14 = new QPushButton(page_4);
        pushButton_14->setObjectName(QString::fromUtf8("pushButton_14"));

        horizontalLayout_7->addWidget(pushButton_14);

        spinBox_5 = new QSpinBox(page_4);
        spinBox_5->setObjectName(QString::fromUtf8("spinBox_5"));

        horizontalLayout_7->addWidget(spinBox_5);

        pushButton_15 = new QPushButton(page_4);
        pushButton_15->setObjectName(QString::fromUtf8("pushButton_15"));

        horizontalLayout_7->addWidget(pushButton_15);


        verticalLayout->addLayout(horizontalLayout_7);

        stackedWidget->addWidget(page_4);

        verticalLayout_2->addWidget(stackedWidget);


        retranslateUi(DataManageDialog);

        stackedWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(DataManageDialog);
    } // setupUi

    void retranslateUi(QDialog *DataManageDialog)
    {
        DataManageDialog->setWindowTitle(QCoreApplication::translate("DataManageDialog", "\344\277\241\346\201\257\351\205\215\347\275\256", nullptr));
        btn1->setText(QCoreApplication::translate("DataManageDialog", "\346\250\241\345\235\2271", nullptr));
        btn2->setText(QCoreApplication::translate("DataManageDialog", "\346\250\241\345\235\2272", nullptr));
        btn3->setText(QCoreApplication::translate("DataManageDialog", "\346\250\241\345\235\2273", nullptr));
        btn4->setText(QCoreApplication::translate("DataManageDialog", "\346\250\241\345\235\2274", nullptr));
        lineEdit->setText(QCoreApplication::translate("DataManageDialog", "\346\220\234\347\264\242\345\205\263\351\224\256\345\255\227", nullptr));
        label->setText(QCoreApplication::translate("DataManageDialog", "\346\227\245\346\234\237\357\274\232", nullptr));
        pushButton_5->setText(QCoreApplication::translate("DataManageDialog", "\346\237\245\350\257\242", nullptr));
        pushButton_6->setText(QCoreApplication::translate("DataManageDialog", "<", nullptr));
        pushButton_7->setText(QCoreApplication::translate("DataManageDialog", ">", nullptr));
        pushButton_10->setText(QCoreApplication::translate("DataManageDialog", "<", nullptr));
        pushButton_11->setText(QCoreApplication::translate("DataManageDialog", ">", nullptr));
        pushButton_12->setText(QCoreApplication::translate("DataManageDialog", "<", nullptr));
        pushButton_13->setText(QCoreApplication::translate("DataManageDialog", ">", nullptr));
        pushButton_14->setText(QCoreApplication::translate("DataManageDialog", "<", nullptr));
        pushButton_15->setText(QCoreApplication::translate("DataManageDialog", ">", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DataManageDialog: public Ui_DataManageDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DATAMANAGEDIALOG_H
