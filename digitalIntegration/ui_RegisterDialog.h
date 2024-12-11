/********************************************************************************
** Form generated from reading UI file 'RegisterDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGISTERDIALOG_H
#define UI_REGISTERDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RegisterDialog
{
public:
    QGridLayout *gridLayout;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QGridLayout *gridLayout_3;
    QGridLayout *gridLayout_2;
    QLabel *label_4;
    QLineEdit *lineEditPassword;
    QLabel *labelPassword;
    QLabel *labelName;
    QLabel *label_3;
    QLabel *labelUser;
    QLineEdit *lineEditDepartment;
    QLineEdit *lineEditName;
    QLabel *label_5;
    QLineEdit *lineEditUserName;
    QLineEdit *lineEditPhoneNumber;
    QLineEdit *lineEditJobTtile;
    QLabel *label_8;
    QComboBox *comboBox;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnRegister;
    QSpacerItem *horizontalSpacer_2;
    QWidget *page_2;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_3;
    QVBoxLayout *verticalLayout;
    QLabel *label_7;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_5;
    QLabel *labelFingerprint;
    QSpacerItem *horizontalSpacer_6;
    QPushButton *btnFingerprintInput;
    QSpacerItem *horizontalSpacer_4;

    void setupUi(QDialog *RegisterDialog)
    {
        if (RegisterDialog->objectName().isEmpty())
            RegisterDialog->setObjectName(QString::fromUtf8("RegisterDialog"));
        RegisterDialog->resize(283, 299);
        gridLayout = new QGridLayout(RegisterDialog);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        stackedWidget = new QStackedWidget(RegisterDialog);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        gridLayout_3 = new QGridLayout(page);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setHorizontalSpacing(10);
        gridLayout_2->setVerticalSpacing(15);
        label_4 = new QLabel(page);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_2->addWidget(label_4, 4, 0, 1, 1);

        lineEditPassword = new QLineEdit(page);
        lineEditPassword->setObjectName(QString::fromUtf8("lineEditPassword"));

        gridLayout_2->addWidget(lineEditPassword, 1, 1, 1, 1);

        labelPassword = new QLabel(page);
        labelPassword->setObjectName(QString::fromUtf8("labelPassword"));

        gridLayout_2->addWidget(labelPassword, 1, 0, 1, 1);

        labelName = new QLabel(page);
        labelName->setObjectName(QString::fromUtf8("labelName"));

        gridLayout_2->addWidget(labelName, 2, 0, 1, 1);

        label_3 = new QLabel(page);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout_2->addWidget(label_3, 3, 0, 1, 1);

        labelUser = new QLabel(page);
        labelUser->setObjectName(QString::fromUtf8("labelUser"));

        gridLayout_2->addWidget(labelUser, 0, 0, 1, 1);

        lineEditDepartment = new QLineEdit(page);
        lineEditDepartment->setObjectName(QString::fromUtf8("lineEditDepartment"));

        gridLayout_2->addWidget(lineEditDepartment, 3, 1, 1, 1);

        lineEditName = new QLineEdit(page);
        lineEditName->setObjectName(QString::fromUtf8("lineEditName"));

        gridLayout_2->addWidget(lineEditName, 2, 1, 1, 1);

        label_5 = new QLabel(page);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout_2->addWidget(label_5, 5, 0, 1, 1);

        lineEditUserName = new QLineEdit(page);
        lineEditUserName->setObjectName(QString::fromUtf8("lineEditUserName"));

        gridLayout_2->addWidget(lineEditUserName, 0, 1, 1, 1);

        lineEditPhoneNumber = new QLineEdit(page);
        lineEditPhoneNumber->setObjectName(QString::fromUtf8("lineEditPhoneNumber"));

        gridLayout_2->addWidget(lineEditPhoneNumber, 5, 1, 1, 1);

        lineEditJobTtile = new QLineEdit(page);
        lineEditJobTtile->setObjectName(QString::fromUtf8("lineEditJobTtile"));

        gridLayout_2->addWidget(lineEditJobTtile, 4, 1, 1, 1);

        label_8 = new QLabel(page);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        gridLayout_2->addWidget(label_8, 6, 0, 1, 1);

        comboBox = new QComboBox(page);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        gridLayout_2->addWidget(comboBox, 6, 1, 1, 1);


        gridLayout_3->addLayout(gridLayout_2, 0, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        btnRegister = new QPushButton(page);
        btnRegister->setObjectName(QString::fromUtf8("btnRegister"));
        btnRegister->setMaximumSize(QSize(50, 16777215));

        horizontalLayout->addWidget(btnRegister);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        gridLayout_3->addLayout(horizontalLayout, 1, 0, 1, 1);

        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        horizontalLayout_3 = new QHBoxLayout(page_2);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label_7 = new QLabel(page_2);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setMinimumSize(QSize(0, 30));
        label_7->setMaximumSize(QSize(16777215, 80));
        QFont font;
        font.setPointSize(11);
        label_7->setFont(font);
        label_7->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_7);

        widget = new QWidget(page_2);
        widget->setObjectName(QString::fromUtf8("widget"));
        horizontalLayout_2 = new QHBoxLayout(widget);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer_5 = new QSpacerItem(37, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_5);

        labelFingerprint = new QLabel(widget);
        labelFingerprint->setObjectName(QString::fromUtf8("labelFingerprint"));
        labelFingerprint->setMinimumSize(QSize(55, 60));
        labelFingerprint->setMaximumSize(QSize(55, 60));
        QFont font1;
        font1.setPointSize(6);
        labelFingerprint->setFont(font1);

        horizontalLayout_2->addWidget(labelFingerprint);

        horizontalSpacer_6 = new QSpacerItem(37, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_6);


        verticalLayout->addWidget(widget);

        btnFingerprintInput = new QPushButton(page_2);
        btnFingerprintInput->setObjectName(QString::fromUtf8("btnFingerprintInput"));

        verticalLayout->addWidget(btnFingerprintInput);


        horizontalLayout_3->addLayout(verticalLayout);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_4);

        stackedWidget->addWidget(page_2);

        gridLayout->addWidget(stackedWidget, 0, 0, 1, 1);


        retranslateUi(RegisterDialog);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(RegisterDialog);
    } // setupUi

    void retranslateUi(QDialog *RegisterDialog)
    {
        RegisterDialog->setWindowTitle(QCoreApplication::translate("RegisterDialog", "Dialog", nullptr));
        label_4->setText(QCoreApplication::translate("RegisterDialog", "\350\201\214\344\275\215", nullptr));
        labelPassword->setText(QCoreApplication::translate("RegisterDialog", "\345\257\206\347\240\201", nullptr));
        labelName->setText(QCoreApplication::translate("RegisterDialog", "\344\275\277\347\224\250\344\272\272", nullptr));
        label_3->setText(QCoreApplication::translate("RegisterDialog", "\351\203\250\351\227\250", nullptr));
        labelUser->setText(QCoreApplication::translate("RegisterDialog", "\347\224\250\346\210\267\345\220\215", nullptr));
        label_5->setText(QCoreApplication::translate("RegisterDialog", "\346\211\213\346\234\272\345\217\267", nullptr));
        label_8->setText(QCoreApplication::translate("RegisterDialog", "\346\235\203\351\231\220", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("RegisterDialog", "\347\256\241\347\220\206\345\221\230", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("RegisterDialog", "\346\231\256\351\200\232\347\224\250\346\210\267", nullptr));

        btnRegister->setText(QCoreApplication::translate("RegisterDialog", "\346\263\250\345\206\214", nullptr));
        label_7->setText(QCoreApplication::translate("RegisterDialog", "\346\263\250\345\206\214\346\214\207\347\272\271", nullptr));
        labelFingerprint->setText(QString());
        btnFingerprintInput->setText(QCoreApplication::translate("RegisterDialog", "\345\274\200\345\247\213\345\275\225\345\205\245", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RegisterDialog: public Ui_RegisterDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTERDIALOG_H
