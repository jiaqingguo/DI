/********************************************************************************
** Form generated from reading UI file 'LoginDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINDIALOG_H
#define UI_LOGINDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
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

class Ui_LoginDialog
{
public:
    QGridLayout *gridLayout_2;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *btnChangePassword;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *btnRegister;
    QPushButton *btnLogin;
    QWidget *widgetTitle;
    QHBoxLayout *horizontalLayout_4;
    QLabel *LabelTitle;
    QSpacerItem *horizontalSpacer_6;
    QPushButton *BtnClose;
    QLineEdit *lePassword;
    QHBoxLayout *horizontalLayout_3;
    QLabel *lblUser;
    QSpacerItem *horizontalSpacer_5;
    QLineEdit *leUser;
    QWidget *page_2;
    QHBoxLayout *horizontalLayout_6;
    QSpacerItem *horizontalSpacer_3;
    QWidget *widget_2;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_7;
    QLabel *labelFingerprint;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnFingerprint;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QDialog *LoginDialog)
    {
        if (LoginDialog->objectName().isEmpty())
            LoginDialog->setObjectName(QString::fromUtf8("LoginDialog"));
        LoginDialog->resize(450, 350);
        LoginDialog->setMinimumSize(QSize(450, 350));
        gridLayout_2 = new QGridLayout(LoginDialog);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        stackedWidget = new QStackedWidget(LoginDialog);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        stackedWidget->setMinimumSize(QSize(425, 325));
        stackedWidget->setMaximumSize(QSize(425, 325));
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        gridLayout = new QGridLayout(page);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(9, -1, 9, -1);
        btnChangePassword = new QPushButton(page);
        btnChangePassword->setObjectName(QString::fromUtf8("btnChangePassword"));

        horizontalLayout->addWidget(btnChangePassword);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);

        btnRegister = new QPushButton(page);
        btnRegister->setObjectName(QString::fromUtf8("btnRegister"));

        horizontalLayout->addWidget(btnRegister);


        gridLayout->addLayout(horizontalLayout, 7, 0, 1, 2);

        btnLogin = new QPushButton(page);
        btnLogin->setObjectName(QString::fromUtf8("btnLogin"));
        btnLogin->setMinimumSize(QSize(0, 55));

        gridLayout->addWidget(btnLogin, 6, 0, 1, 2);

        widgetTitle = new QWidget(page);
        widgetTitle->setObjectName(QString::fromUtf8("widgetTitle"));
        horizontalLayout_4 = new QHBoxLayout(widgetTitle);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        LabelTitle = new QLabel(widgetTitle);
        LabelTitle->setObjectName(QString::fromUtf8("LabelTitle"));

        horizontalLayout_4->addWidget(LabelTitle);

        horizontalSpacer_6 = new QSpacerItem(222, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_6);

        BtnClose = new QPushButton(widgetTitle);
        BtnClose->setObjectName(QString::fromUtf8("BtnClose"));
        BtnClose->setMinimumSize(QSize(44, 36));
        BtnClose->setMaximumSize(QSize(44, 36));

        horizontalLayout_4->addWidget(BtnClose);


        gridLayout->addWidget(widgetTitle, 0, 0, 1, 2);

        lePassword = new QLineEdit(page);
        lePassword->setObjectName(QString::fromUtf8("lePassword"));
        lePassword->setMinimumSize(QSize(0, 45));

        gridLayout->addWidget(lePassword, 3, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, -1, -1, -1);
        lblUser = new QLabel(page);
        lblUser->setObjectName(QString::fromUtf8("lblUser"));
        lblUser->setMaximumSize(QSize(16777215, 40));

        horizontalLayout_3->addWidget(lblUser);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_5);


        gridLayout->addLayout(horizontalLayout_3, 1, 0, 1, 2);

        leUser = new QLineEdit(page);
        leUser->setObjectName(QString::fromUtf8("leUser"));
        leUser->setMinimumSize(QSize(0, 45));

        gridLayout->addWidget(leUser, 2, 0, 1, 1);

        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        horizontalLayout_6 = new QHBoxLayout(page_2);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalSpacer_3 = new QSpacerItem(100, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_3);

        widget_2 = new QWidget(page_2);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        verticalLayout = new QVBoxLayout(widget_2);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(widget_2);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMinimumSize(QSize(0, 20));
        label->setMaximumSize(QSize(16777215, 25));
        QFont font;
        font.setPointSize(11);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_7);

        labelFingerprint = new QLabel(widget_2);
        labelFingerprint->setObjectName(QString::fromUtf8("labelFingerprint"));
        labelFingerprint->setMinimumSize(QSize(55, 60));
        labelFingerprint->setMaximumSize(QSize(55, 60));
        QFont font1;
        font1.setPointSize(6);
        labelFingerprint->setFont(font1);

        horizontalLayout_2->addWidget(labelFingerprint);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout_2);

        btnFingerprint = new QPushButton(widget_2);
        btnFingerprint->setObjectName(QString::fromUtf8("btnFingerprint"));
        btnFingerprint->setMinimumSize(QSize(0, 28));
        QFont font2;
        font2.setPointSize(9);
        btnFingerprint->setFont(font2);

        verticalLayout->addWidget(btnFingerprint);


        horizontalLayout_6->addWidget(widget_2);

        horizontalSpacer_2 = new QSpacerItem(105, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_2);

        stackedWidget->addWidget(page_2);

        gridLayout_2->addWidget(stackedWidget, 0, 0, 1, 1);


        retranslateUi(LoginDialog);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(LoginDialog);
    } // setupUi

    void retranslateUi(QDialog *LoginDialog)
    {
        LoginDialog->setWindowTitle(QCoreApplication::translate("LoginDialog", "\346\225\260\345\255\227\346\240\267\346\234\272\344\270\200\344\275\223\345\214\226\345\271\263\345\217\260", nullptr));
        btnChangePassword->setText(QCoreApplication::translate("LoginDialog", "\344\277\256\346\224\271\345\257\206\347\240\201", nullptr));
        btnRegister->setText(QCoreApplication::translate("LoginDialog", "\346\263\250\345\206\214", nullptr));
        btnLogin->setText(QCoreApplication::translate("LoginDialog", "\347\231\273 \345\275\225", nullptr));
        LabelTitle->setText(QCoreApplication::translate("LoginDialog", "\346\225\260\345\255\227\346\240\267\346\234\272\344\270\200\344\275\223\345\214\226\345\271\263\345\217\260", nullptr));
        BtnClose->setText(QString());
        lblUser->setText(QCoreApplication::translate("LoginDialog", "\346\254\242\350\277\216\347\231\273\345\275\225", nullptr));
        label->setText(QCoreApplication::translate("LoginDialog", "\346\214\207\347\272\271\351\252\214\350\257\201", nullptr));
        labelFingerprint->setText(QString());
        btnFingerprint->setText(QCoreApplication::translate("LoginDialog", "\345\274\200\345\247\213\351\252\214\350\257\201", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoginDialog: public Ui_LoginDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINDIALOG_H
