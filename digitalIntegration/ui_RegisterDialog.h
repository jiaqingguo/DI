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
    QGridLayout *gridLayout_3;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QGridLayout *gridLayout;
    QGridLayout *gridLayout_2;
    QLabel *labelJobTtile;
    QLabel *labelUser;
    QLabel *labelPassword;
    QLineEdit *lineEditDepartment;
    QLineEdit *lineEditJobTtile;
    QComboBox *comboBoxRoot;
    QLineEdit *lineEditPhoneNumber;
    QLineEdit *lineEditName;
    QLabel *labelDepartment;
    QLabel *labelRoot;
    QLabel *labelName;
    QLineEdit *lineEditUserName;
    QLineEdit *lineEditPassword;
    QLabel *labelPhoneNum;
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
        RegisterDialog->setEnabled(true);
        RegisterDialog->resize(301, 339);
        RegisterDialog->setMinimumSize(QSize(0, 0));
        gridLayout_3 = new QGridLayout(RegisterDialog);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        stackedWidget = new QStackedWidget(RegisterDialog);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        stackedWidget->setMinimumSize(QSize(0, 0));
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        gridLayout = new QGridLayout(page);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setHorizontalSpacing(10);
        gridLayout_2->setVerticalSpacing(15);
        labelJobTtile = new QLabel(page);
        labelJobTtile->setObjectName(QString::fromUtf8("labelJobTtile"));

        gridLayout_2->addWidget(labelJobTtile, 4, 0, 1, 1);

        labelUser = new QLabel(page);
        labelUser->setObjectName(QString::fromUtf8("labelUser"));

        gridLayout_2->addWidget(labelUser, 0, 0, 1, 1);

        labelPassword = new QLabel(page);
        labelPassword->setObjectName(QString::fromUtf8("labelPassword"));

        gridLayout_2->addWidget(labelPassword, 1, 0, 1, 1);

        lineEditDepartment = new QLineEdit(page);
        lineEditDepartment->setObjectName(QString::fromUtf8("lineEditDepartment"));
        lineEditDepartment->setMinimumSize(QSize(0, 0));

        gridLayout_2->addWidget(lineEditDepartment, 3, 1, 1, 1);

        lineEditJobTtile = new QLineEdit(page);
        lineEditJobTtile->setObjectName(QString::fromUtf8("lineEditJobTtile"));
        lineEditJobTtile->setMinimumSize(QSize(0, 0));

        gridLayout_2->addWidget(lineEditJobTtile, 4, 1, 1, 1);

        comboBoxRoot = new QComboBox(page);
        comboBoxRoot->addItem(QString());
        comboBoxRoot->addItem(QString());
        comboBoxRoot->setObjectName(QString::fromUtf8("comboBoxRoot"));
        comboBoxRoot->setMinimumSize(QSize(0, 0));

        gridLayout_2->addWidget(comboBoxRoot, 6, 1, 1, 1);

        lineEditPhoneNumber = new QLineEdit(page);
        lineEditPhoneNumber->setObjectName(QString::fromUtf8("lineEditPhoneNumber"));
        lineEditPhoneNumber->setMinimumSize(QSize(0, 0));

        gridLayout_2->addWidget(lineEditPhoneNumber, 5, 1, 1, 1);

        lineEditName = new QLineEdit(page);
        lineEditName->setObjectName(QString::fromUtf8("lineEditName"));
        lineEditName->setMinimumSize(QSize(0, 0));

        gridLayout_2->addWidget(lineEditName, 2, 1, 1, 1);

        labelDepartment = new QLabel(page);
        labelDepartment->setObjectName(QString::fromUtf8("labelDepartment"));

        gridLayout_2->addWidget(labelDepartment, 3, 0, 1, 1);

        labelRoot = new QLabel(page);
        labelRoot->setObjectName(QString::fromUtf8("labelRoot"));

        gridLayout_2->addWidget(labelRoot, 6, 0, 1, 1);

        labelName = new QLabel(page);
        labelName->setObjectName(QString::fromUtf8("labelName"));

        gridLayout_2->addWidget(labelName, 2, 0, 1, 1);

        lineEditUserName = new QLineEdit(page);
        lineEditUserName->setObjectName(QString::fromUtf8("lineEditUserName"));
        lineEditUserName->setMinimumSize(QSize(0, 0));

        gridLayout_2->addWidget(lineEditUserName, 0, 1, 1, 1);

        lineEditPassword = new QLineEdit(page);
        lineEditPassword->setObjectName(QString::fromUtf8("lineEditPassword"));
        lineEditPassword->setMinimumSize(QSize(0, 0));

        gridLayout_2->addWidget(lineEditPassword, 1, 1, 1, 1);

        labelPhoneNum = new QLabel(page);
        labelPhoneNum->setObjectName(QString::fromUtf8("labelPhoneNum"));

        gridLayout_2->addWidget(labelPhoneNum, 5, 0, 1, 1);


        gridLayout->addLayout(gridLayout_2, 0, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        btnRegister = new QPushButton(page);
        btnRegister->setObjectName(QString::fromUtf8("btnRegister"));
        btnRegister->setMinimumSize(QSize(110, 50));
        btnRegister->setMaximumSize(QSize(16777215, 16777215));

        horizontalLayout->addWidget(btnRegister);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        gridLayout->addLayout(horizontalLayout, 1, 0, 1, 1);

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

        gridLayout_3->addWidget(stackedWidget, 0, 0, 1, 1);


        retranslateUi(RegisterDialog);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(RegisterDialog);
    } // setupUi

    void retranslateUi(QDialog *RegisterDialog)
    {
        RegisterDialog->setWindowTitle(QCoreApplication::translate("RegisterDialog", "Dialog", nullptr));
        labelJobTtile->setText(QCoreApplication::translate("RegisterDialog", "\350\201\214\344\275\215", nullptr));
        labelUser->setText(QCoreApplication::translate("RegisterDialog", "<html><head/><body><p>\347\224\250\346\210\267\345\220\215<span style=\" color:#ff0000;\">*</span></p></body></html>", nullptr));
        labelPassword->setText(QCoreApplication::translate("RegisterDialog", "<html><head/><body><p>\345\257\206\347\240\201<span style=\" color:#ff0000;\">*</span></p></body></html>", nullptr));
        comboBoxRoot->setItemText(0, QCoreApplication::translate("RegisterDialog", "\347\256\241\347\220\206\345\221\230", nullptr));
        comboBoxRoot->setItemText(1, QCoreApplication::translate("RegisterDialog", "\346\231\256\351\200\232\347\224\250\346\210\267", nullptr));

        labelDepartment->setText(QCoreApplication::translate("RegisterDialog", "<html><head/><body><p>\351\203\250\351\227\250</p></body></html>", nullptr));
        labelRoot->setText(QCoreApplication::translate("RegisterDialog", "\346\235\203\351\231\220", nullptr));
        labelName->setText(QCoreApplication::translate("RegisterDialog", "<html><head/><body><p>\344\275\277\347\224\250\344\272\272<span style=\" color:#ff0000;\">*</span></p></body></html>", nullptr));
        labelPhoneNum->setText(QCoreApplication::translate("RegisterDialog", "\346\211\213\346\234\272\345\217\267", nullptr));
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
