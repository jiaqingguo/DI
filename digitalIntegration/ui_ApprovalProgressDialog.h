/********************************************************************************
** Form generated from reading UI file 'ApprovalProgressDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_APPROVALPROGRESSDIALOG_H
#define UI_APPROVALPROGRESSDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "CLineEdit.h"

QT_BEGIN_NAMESPACE

class Ui_ApprovalProgressDialog
{
public:
    QVBoxLayout *verticalLayout_2;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QPushButton *btnData;
    QPushButton *btnUser;
    QSpacerItem *horizontalSpacer_2;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout2;
    QComboBox *comboBoxDataField;
    QLineEdit *lineEditDataQueryValue;
    QCheckBox *checkBox_1;
    QDateTimeEdit *dateTimeEdit1_start;
    QDateTimeEdit *dateTimeEdit2_end;
    QPushButton *btnDataQuery;
    QSpacerItem *horizontalSpacer_3;
    QTableView *tableView;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *btnFlushDownload;
    QPushButton *btnDataApprovalLast;
    QLabel *labelDataApprovalPageShow;
    QPushButton *btnDataApprovalNext;
    QLabel *labelApprovalGo;
    QLineEdit *lineEditDataApprovalPage;
    QLabel *labelApprovalYe;
    QWidget *page_2;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout5;
    QComboBox *comboBoxUserField;
    CLineEdit *lineEditUserQueryValue;
    QCheckBox *checkBox_2;
    QDateTimeEdit *dateTimeEdit3_start;
    QDateTimeEdit *dateTimeEdit4_end;
    QPushButton *btnUserQuery;
    QSpacerItem *horizontalSpacer_6;
    QTableView *tableViewUser;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *btnFlushUser;
    QPushButton *btnUserLast;
    QLabel *labelUserPage;
    QPushButton *btnUserNext;
    QLabel *labelUserGo;
    QLineEdit *lineEditUserPage;
    QLabel *labelUserYe;
    QButtonGroup *buttonGroup;

    void setupUi(QDialog *ApprovalProgressDialog)
    {
        if (ApprovalProgressDialog->objectName().isEmpty())
            ApprovalProgressDialog->setObjectName(QString::fromUtf8("ApprovalProgressDialog"));
        ApprovalProgressDialog->resize(1300, 625);
        ApprovalProgressDialog->setMinimumSize(QSize(1300, 625));
        ApprovalProgressDialog->setMaximumSize(QSize(16777215, 16777215));
        verticalLayout_2 = new QVBoxLayout(ApprovalProgressDialog);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        widget = new QWidget(ApprovalProgressDialog);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setMaximumSize(QSize(16777215, 56));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setSpacing(10);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        btnData = new QPushButton(widget);
        buttonGroup = new QButtonGroup(ApprovalProgressDialog);
        buttonGroup->setObjectName(QString::fromUtf8("buttonGroup"));
        buttonGroup->addButton(btnData);
        btnData->setObjectName(QString::fromUtf8("btnData"));
        btnData->setMinimumSize(QSize(138, 56));
        btnData->setMaximumSize(QSize(138, 56));

        horizontalLayout->addWidget(btnData);

        btnUser = new QPushButton(widget);
        buttonGroup->addButton(btnUser);
        btnUser->setObjectName(QString::fromUtf8("btnUser"));
        btnUser->setMinimumSize(QSize(138, 56));
        btnUser->setMaximumSize(QSize(138, 56));

        horizontalLayout->addWidget(btnUser);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout_2->addWidget(widget);

        stackedWidget = new QStackedWidget(ApprovalProgressDialog);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        verticalLayout = new QVBoxLayout(page);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout2 = new QHBoxLayout();
        horizontalLayout2->setObjectName(QString::fromUtf8("horizontalLayout2"));
        horizontalLayout2->setContentsMargins(-1, -1, -1, 9);
        comboBoxDataField = new QComboBox(page);
        comboBoxDataField->setObjectName(QString::fromUtf8("comboBoxDataField"));
        comboBoxDataField->setMinimumSize(QSize(0, 0));
        comboBoxDataField->setMaximumSize(QSize(16777215, 30));

        horizontalLayout2->addWidget(comboBoxDataField);

        lineEditDataQueryValue = new QLineEdit(page);
        lineEditDataQueryValue->setObjectName(QString::fromUtf8("lineEditDataQueryValue"));
        lineEditDataQueryValue->setMinimumSize(QSize(0, 30));
        lineEditDataQueryValue->setMaximumSize(QSize(250, 30));

        horizontalLayout2->addWidget(lineEditDataQueryValue);

        checkBox_1 = new QCheckBox(page);
        checkBox_1->setObjectName(QString::fromUtf8("checkBox_1"));
        checkBox_1->setMinimumSize(QSize(0, 30));
        checkBox_1->setMaximumSize(QSize(16777215, 30));

        horizontalLayout2->addWidget(checkBox_1);

        dateTimeEdit1_start = new QDateTimeEdit(page);
        dateTimeEdit1_start->setObjectName(QString::fromUtf8("dateTimeEdit1_start"));
        dateTimeEdit1_start->setMinimumSize(QSize(0, 30));
        dateTimeEdit1_start->setMaximumSize(QSize(16777215, 30));

        horizontalLayout2->addWidget(dateTimeEdit1_start);

        dateTimeEdit2_end = new QDateTimeEdit(page);
        dateTimeEdit2_end->setObjectName(QString::fromUtf8("dateTimeEdit2_end"));
        dateTimeEdit2_end->setMinimumSize(QSize(0, 30));
        dateTimeEdit2_end->setMaximumSize(QSize(16777215, 30));

        horizontalLayout2->addWidget(dateTimeEdit2_end);

        btnDataQuery = new QPushButton(page);
        btnDataQuery->setObjectName(QString::fromUtf8("btnDataQuery"));
        btnDataQuery->setMinimumSize(QSize(100, 40));

        horizontalLayout2->addWidget(btnDataQuery);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout2->addItem(horizontalSpacer_3);


        verticalLayout->addLayout(horizontalLayout2);

        tableView = new QTableView(page);
        tableView->setObjectName(QString::fromUtf8("tableView"));

        verticalLayout->addWidget(tableView);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_4);

        btnFlushDownload = new QPushButton(page);
        btnFlushDownload->setObjectName(QString::fromUtf8("btnFlushDownload"));
        btnFlushDownload->setMinimumSize(QSize(70, 30));
        btnFlushDownload->setMaximumSize(QSize(70, 30));

        horizontalLayout_3->addWidget(btnFlushDownload);

        btnDataApprovalLast = new QPushButton(page);
        btnDataApprovalLast->setObjectName(QString::fromUtf8("btnDataApprovalLast"));
        btnDataApprovalLast->setMinimumSize(QSize(70, 30));
        btnDataApprovalLast->setMaximumSize(QSize(70, 30));

        horizontalLayout_3->addWidget(btnDataApprovalLast);

        labelDataApprovalPageShow = new QLabel(page);
        labelDataApprovalPageShow->setObjectName(QString::fromUtf8("labelDataApprovalPageShow"));

        horizontalLayout_3->addWidget(labelDataApprovalPageShow);

        btnDataApprovalNext = new QPushButton(page);
        btnDataApprovalNext->setObjectName(QString::fromUtf8("btnDataApprovalNext"));
        btnDataApprovalNext->setMinimumSize(QSize(70, 30));
        btnDataApprovalNext->setMaximumSize(QSize(70, 30));

        horizontalLayout_3->addWidget(btnDataApprovalNext);

        labelApprovalGo = new QLabel(page);
        labelApprovalGo->setObjectName(QString::fromUtf8("labelApprovalGo"));

        horizontalLayout_3->addWidget(labelApprovalGo);

        lineEditDataApprovalPage = new QLineEdit(page);
        lineEditDataApprovalPage->setObjectName(QString::fromUtf8("lineEditDataApprovalPage"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lineEditDataApprovalPage->sizePolicy().hasHeightForWidth());
        lineEditDataApprovalPage->setSizePolicy(sizePolicy);
        lineEditDataApprovalPage->setMinimumSize(QSize(0, 30));
        lineEditDataApprovalPage->setMaximumSize(QSize(16777215, 30));

        horizontalLayout_3->addWidget(lineEditDataApprovalPage);

        labelApprovalYe = new QLabel(page);
        labelApprovalYe->setObjectName(QString::fromUtf8("labelApprovalYe"));

        horizontalLayout_3->addWidget(labelApprovalYe);


        verticalLayout->addLayout(horizontalLayout_3);

        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        verticalLayout_3 = new QVBoxLayout(page_2);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        horizontalLayout5 = new QHBoxLayout();
        horizontalLayout5->setObjectName(QString::fromUtf8("horizontalLayout5"));
        horizontalLayout5->setContentsMargins(-1, -1, -1, 9);
        comboBoxUserField = new QComboBox(page_2);
        comboBoxUserField->setObjectName(QString::fromUtf8("comboBoxUserField"));
        comboBoxUserField->setMaximumSize(QSize(16777215, 30));

        horizontalLayout5->addWidget(comboBoxUserField);

        lineEditUserQueryValue = new CLineEdit(page_2);
        lineEditUserQueryValue->setObjectName(QString::fromUtf8("lineEditUserQueryValue"));
        lineEditUserQueryValue->setMinimumSize(QSize(0, 30));
        lineEditUserQueryValue->setMaximumSize(QSize(250, 30));

        horizontalLayout5->addWidget(lineEditUserQueryValue);

        checkBox_2 = new QCheckBox(page_2);
        checkBox_2->setObjectName(QString::fromUtf8("checkBox_2"));
        checkBox_2->setMinimumSize(QSize(0, 30));
        checkBox_2->setMaximumSize(QSize(16777215, 30));
        checkBox_2->setChecked(false);
        checkBox_2->setTristate(false);

        horizontalLayout5->addWidget(checkBox_2);

        dateTimeEdit3_start = new QDateTimeEdit(page_2);
        dateTimeEdit3_start->setObjectName(QString::fromUtf8("dateTimeEdit3_start"));
        dateTimeEdit3_start->setMinimumSize(QSize(0, 30));
        dateTimeEdit3_start->setMaximumSize(QSize(16777215, 30));

        horizontalLayout5->addWidget(dateTimeEdit3_start);

        dateTimeEdit4_end = new QDateTimeEdit(page_2);
        dateTimeEdit4_end->setObjectName(QString::fromUtf8("dateTimeEdit4_end"));
        dateTimeEdit4_end->setMinimumSize(QSize(0, 30));
        dateTimeEdit4_end->setMaximumSize(QSize(16777215, 30));

        horizontalLayout5->addWidget(dateTimeEdit4_end);

        btnUserQuery = new QPushButton(page_2);
        btnUserQuery->setObjectName(QString::fromUtf8("btnUserQuery"));
        btnUserQuery->setMinimumSize(QSize(100, 40));

        horizontalLayout5->addWidget(btnUserQuery);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout5->addItem(horizontalSpacer_6);


        verticalLayout_3->addLayout(horizontalLayout5);

        tableViewUser = new QTableView(page_2);
        tableViewUser->setObjectName(QString::fromUtf8("tableViewUser"));

        verticalLayout_3->addWidget(tableViewUser);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_5);

        btnFlushUser = new QPushButton(page_2);
        btnFlushUser->setObjectName(QString::fromUtf8("btnFlushUser"));
        btnFlushUser->setMinimumSize(QSize(70, 30));
        btnFlushUser->setMaximumSize(QSize(70, 30));

        horizontalLayout_4->addWidget(btnFlushUser);

        btnUserLast = new QPushButton(page_2);
        btnUserLast->setObjectName(QString::fromUtf8("btnUserLast"));
        btnUserLast->setMinimumSize(QSize(70, 30));
        btnUserLast->setMaximumSize(QSize(70, 30));

        horizontalLayout_4->addWidget(btnUserLast);

        labelUserPage = new QLabel(page_2);
        labelUserPage->setObjectName(QString::fromUtf8("labelUserPage"));

        horizontalLayout_4->addWidget(labelUserPage);

        btnUserNext = new QPushButton(page_2);
        btnUserNext->setObjectName(QString::fromUtf8("btnUserNext"));
        btnUserNext->setMinimumSize(QSize(70, 30));
        btnUserNext->setMaximumSize(QSize(70, 30));

        horizontalLayout_4->addWidget(btnUserNext);

        labelUserGo = new QLabel(page_2);
        labelUserGo->setObjectName(QString::fromUtf8("labelUserGo"));

        horizontalLayout_4->addWidget(labelUserGo);

        lineEditUserPage = new QLineEdit(page_2);
        lineEditUserPage->setObjectName(QString::fromUtf8("lineEditUserPage"));
        sizePolicy.setHeightForWidth(lineEditUserPage->sizePolicy().hasHeightForWidth());
        lineEditUserPage->setSizePolicy(sizePolicy);
        lineEditUserPage->setMaximumSize(QSize(16777215, 30));

        horizontalLayout_4->addWidget(lineEditUserPage);

        labelUserYe = new QLabel(page_2);
        labelUserYe->setObjectName(QString::fromUtf8("labelUserYe"));

        horizontalLayout_4->addWidget(labelUserYe);


        verticalLayout_3->addLayout(horizontalLayout_4);

        stackedWidget->addWidget(page_2);

        verticalLayout_2->addWidget(stackedWidget);


        retranslateUi(ApprovalProgressDialog);

        stackedWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(ApprovalProgressDialog);
    } // setupUi

    void retranslateUi(QDialog *ApprovalProgressDialog)
    {
        ApprovalProgressDialog->setWindowTitle(QCoreApplication::translate("ApprovalProgressDialog", "\347\224\263\350\257\267\345\256\241\346\211\271", nullptr));
        btnData->setText(QCoreApplication::translate("ApprovalProgressDialog", "\346\225\260\346\215\256\345\256\241\346\211\271", nullptr));
        btnUser->setText(QCoreApplication::translate("ApprovalProgressDialog", "\347\224\250\346\210\267\345\256\241\346\211\271", nullptr));
        lineEditDataQueryValue->setText(QString());
        checkBox_1->setText(QCoreApplication::translate("ApprovalProgressDialog", "\346\227\245\346\234\237", nullptr));
        btnDataQuery->setText(QCoreApplication::translate("ApprovalProgressDialog", "\346\237\245\350\257\242", nullptr));
        btnFlushDownload->setText(QCoreApplication::translate("ApprovalProgressDialog", "\345\210\267\346\226\260", nullptr));
        btnDataApprovalLast->setText(QCoreApplication::translate("ApprovalProgressDialog", "<", nullptr));
        labelDataApprovalPageShow->setText(QCoreApplication::translate("ApprovalProgressDialog", "1/1", nullptr));
        btnDataApprovalNext->setText(QCoreApplication::translate("ApprovalProgressDialog", ">", nullptr));
        labelApprovalGo->setText(QCoreApplication::translate("ApprovalProgressDialog", "\345\211\215\345\276\200", nullptr));
        labelApprovalYe->setText(QCoreApplication::translate("ApprovalProgressDialog", "\351\241\265", nullptr));
        lineEditUserQueryValue->setText(QString());
        checkBox_2->setText(QCoreApplication::translate("ApprovalProgressDialog", "\346\227\245\346\234\237", nullptr));
        btnUserQuery->setText(QCoreApplication::translate("ApprovalProgressDialog", "\346\237\245\350\257\242", nullptr));
        btnFlushUser->setText(QCoreApplication::translate("ApprovalProgressDialog", "\345\210\267\346\226\260", nullptr));
        btnUserLast->setText(QCoreApplication::translate("ApprovalProgressDialog", "<", nullptr));
        labelUserPage->setText(QCoreApplication::translate("ApprovalProgressDialog", "1/1", nullptr));
        btnUserNext->setText(QCoreApplication::translate("ApprovalProgressDialog", ">", nullptr));
        labelUserGo->setText(QCoreApplication::translate("ApprovalProgressDialog", "\345\211\215\345\276\200", nullptr));
        labelUserYe->setText(QCoreApplication::translate("ApprovalProgressDialog", "\351\241\265", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ApprovalProgressDialog: public Ui_ApprovalProgressDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_APPROVALPROGRESSDIALOG_H
