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
    QGridLayout *gridLayout;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QGridLayout *gridLayout_2;
    QWidget *wgdBorder;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *lblUser;
    QSpacerItem *horizontalSpacer_9;
    QLineEdit *leUser;
    QHBoxLayout *horizontalLayout_4;
    QLabel *lblPwd;
    QSpacerItem *horizontalSpacer_8;
    QLineEdit *lePassword;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *btnLogin;
    QSpacerItem *horizontalSpacer_5;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *btnForgetPassword;
    QSpacerItem *horizontalSpacer_6;
    QPushButton *btnRegister;
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
        gridLayout = new QGridLayout(LoginDialog);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setVerticalSpacing(0);
        gridLayout->setContentsMargins(0, 0, 0, 0);
        stackedWidget = new QStackedWidget(LoginDialog);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        gridLayout_2 = new QGridLayout(page);
        gridLayout_2->setSpacing(0);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(-1, 12, -1, 0);
        wgdBorder = new QWidget(page);
        wgdBorder->setObjectName(QString::fromUtf8("wgdBorder"));
        wgdBorder->setMinimumSize(QSize(0, 0));
        wgdBorder->setMaximumSize(QSize(620, 540));
        verticalLayout_2 = new QVBoxLayout(wgdBorder);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(-1, 12, -1, 12);
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setSizeConstraint(QLayout::SetMinimumSize);
        lblUser = new QLabel(wgdBorder);
        lblUser->setObjectName(QString::fromUtf8("lblUser"));
        lblUser->setMinimumSize(QSize(36, 36));
        lblUser->setMaximumSize(QSize(36, 36));

        horizontalLayout_3->addWidget(lblUser);

        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_9);


        verticalLayout_2->addLayout(horizontalLayout_3);

        leUser = new QLineEdit(wgdBorder);
        leUser->setObjectName(QString::fromUtf8("leUser"));
        leUser->setMinimumSize(QSize(0, 31));
        leUser->setMaximumSize(QSize(1677215, 16777215));
        QFont font;
        font.setPointSize(24);
        leUser->setFont(font);

        verticalLayout_2->addWidget(leUser);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        lblPwd = new QLabel(wgdBorder);
        lblPwd->setObjectName(QString::fromUtf8("lblPwd"));
        lblPwd->setMinimumSize(QSize(36, 36));
        lblPwd->setMaximumSize(QSize(36, 36));

        horizontalLayout_4->addWidget(lblPwd);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_8);


        verticalLayout_2->addLayout(horizontalLayout_4);

        lePassword = new QLineEdit(wgdBorder);
        lePassword->setObjectName(QString::fromUtf8("lePassword"));
        lePassword->setMinimumSize(QSize(0, 31));
        lePassword->setFont(font);
        lePassword->setEchoMode(QLineEdit::Password);

        verticalLayout_2->addWidget(lePassword);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);

        btnLogin = new QPushButton(wgdBorder);
        btnLogin->setObjectName(QString::fromUtf8("btnLogin"));

        horizontalLayout->addWidget(btnLogin);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_5);


        verticalLayout_2->addLayout(horizontalLayout);

        widget = new QWidget(wgdBorder);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setMaximumSize(QSize(16777215, 20));
        horizontalLayout_5 = new QHBoxLayout(widget);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(-1, 0, 0, 0);
        btnForgetPassword = new QPushButton(widget);
        btnForgetPassword->setObjectName(QString::fromUtf8("btnForgetPassword"));

        horizontalLayout_5->addWidget(btnForgetPassword);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_6);

        btnRegister = new QPushButton(widget);
        btnRegister->setObjectName(QString::fromUtf8("btnRegister"));
        QFont font1;
        font1.setPointSize(6);
        btnRegister->setFont(font1);

        horizontalLayout_5->addWidget(btnRegister);


        verticalLayout_2->addWidget(widget);


        gridLayout_2->addWidget(wgdBorder, 0, 0, 1, 1);

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
        QFont font2;
        font2.setPointSize(11);
        label->setFont(font2);
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
        labelFingerprint->setFont(font1);

        horizontalLayout_2->addWidget(labelFingerprint);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout_2);

        btnFingerprint = new QPushButton(widget_2);
        btnFingerprint->setObjectName(QString::fromUtf8("btnFingerprint"));
        btnFingerprint->setMinimumSize(QSize(0, 28));
        QFont font3;
        font3.setPointSize(9);
        btnFingerprint->setFont(font3);

        verticalLayout->addWidget(btnFingerprint);


        horizontalLayout_6->addWidget(widget_2);

        horizontalSpacer_2 = new QSpacerItem(105, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_2);

        stackedWidget->addWidget(page_2);

        gridLayout->addWidget(stackedWidget, 0, 1, 1, 1);


        retranslateUi(LoginDialog);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(LoginDialog);
    } // setupUi

    void retranslateUi(QDialog *LoginDialog)
    {
        LoginDialog->setWindowTitle(QCoreApplication::translate("LoginDialog", "\346\254\242\350\277\216\344\275\277\347\224\250\346\225\260\345\255\227\346\240\267\346\234\272\347\241\254\344\273\266\344\270\200\344\275\223\345\214\226\345\271\263\345\217\260", nullptr));
        lblUser->setText(QString());
        leUser->setPlaceholderText(QCoreApplication::translate("LoginDialog", "\350\257\267\350\276\223\345\205\245\346\202\250\347\232\204\347\224\250\346\210\267\345\220\215", nullptr));
        lblPwd->setText(QString());
        lePassword->setPlaceholderText(QCoreApplication::translate("LoginDialog", "\350\257\267\350\276\223\345\205\245\346\202\250\347\232\204\345\257\206\347\240\201", nullptr));
        btnLogin->setText(QCoreApplication::translate("LoginDialog", "\347\231\273\345\275\225", nullptr));
        btnForgetPassword->setText(QCoreApplication::translate("LoginDialog", "\345\277\230\350\256\260\345\257\206\347\240\201\357\274\237", nullptr));
        btnRegister->setText(QCoreApplication::translate("LoginDialog", "\346\263\250\345\206\214", nullptr));
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
