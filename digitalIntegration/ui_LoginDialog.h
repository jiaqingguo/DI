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
    QGridLayout *gridLayout_3;
    QWidget *widgetTitle;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *BtnIcon;
    QLabel *LabelTitle;
    QSpacerItem *horizontalSpacer_6;
    QPushButton *BtnClose;
    QGridLayout *gridLayout_2;
    QLabel *lblUser;
    QSpacerItem *horizontalSpacer_5;
    QLineEdit *leUser;
    QLineEdit *lePassword;
    QVBoxLayout *verticalLayout_2;
    QPushButton *btnLogin;
    QHBoxLayout *horizontalLayout;
    QPushButton *btnChangePassword;
    QSpacerItem *horizontalSpacer_4;
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
        LoginDialog->resize(484, 365);
        LoginDialog->setMinimumSize(QSize(450, 350));
        gridLayout = new QGridLayout(LoginDialog);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(-1, 0, -1, 0);
        stackedWidget = new QStackedWidget(LoginDialog);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        stackedWidget->setMinimumSize(QSize(450, 350));
        stackedWidget->setMaximumSize(QSize(450, 350));
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        gridLayout_3 = new QGridLayout(page);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_3->setContentsMargins(0, 0, 9, 0);
        widgetTitle = new QWidget(page);
        widgetTitle->setObjectName(QString::fromUtf8("widgetTitle"));
        widgetTitle->setMinimumSize(QSize(0, 46));
        widgetTitle->setMaximumSize(QSize(16777215, 46));
        horizontalLayout_3 = new QHBoxLayout(widgetTitle);
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, -1);
        BtnIcon = new QPushButton(widgetTitle);
        BtnIcon->setObjectName(QString::fromUtf8("BtnIcon"));
        BtnIcon->setMinimumSize(QSize(46, 46));
        BtnIcon->setMaximumSize(QSize(46, 46));

        horizontalLayout_3->addWidget(BtnIcon);

        LabelTitle = new QLabel(widgetTitle);
        LabelTitle->setObjectName(QString::fromUtf8("LabelTitle"));
        LabelTitle->setMaximumSize(QSize(16777215, 16777215));

        horizontalLayout_3->addWidget(LabelTitle);

        horizontalSpacer_6 = new QSpacerItem(222, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_6);

        BtnClose = new QPushButton(widgetTitle);
        BtnClose->setObjectName(QString::fromUtf8("BtnClose"));
        BtnClose->setMinimumSize(QSize(46, 46));
        BtnClose->setMaximumSize(QSize(46, 46));

        horizontalLayout_3->addWidget(BtnClose);


        gridLayout_3->addWidget(widgetTitle, 0, 0, 1, 1);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setHorizontalSpacing(0);
        gridLayout_2->setVerticalSpacing(20);
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        lblUser = new QLabel(page);
        lblUser->setObjectName(QString::fromUtf8("lblUser"));
        lblUser->setMaximumSize(QSize(16777215, 40));

        gridLayout_2->addWidget(lblUser, 0, 0, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(375, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_5, 0, 1, 1, 1);

        leUser = new QLineEdit(page);
        leUser->setObjectName(QString::fromUtf8("leUser"));
        leUser->setMinimumSize(QSize(0, 45));

        gridLayout_2->addWidget(leUser, 1, 0, 1, 2);

        lePassword = new QLineEdit(page);
        lePassword->setObjectName(QString::fromUtf8("lePassword"));
        lePassword->setMinimumSize(QSize(0, 45));

        gridLayout_2->addWidget(lePassword, 2, 0, 1, 2);


        gridLayout_3->addLayout(gridLayout_2, 1, 0, 1, 1);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 20, 0, 10);
        btnLogin = new QPushButton(page);
        btnLogin->setObjectName(QString::fromUtf8("btnLogin"));
        btnLogin->setMinimumSize(QSize(450, 65));

        verticalLayout_2->addWidget(btnLogin);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, -1, 0, 0);
        btnChangePassword = new QPushButton(page);
        btnChangePassword->setObjectName(QString::fromUtf8("btnChangePassword"));

        horizontalLayout->addWidget(btnChangePassword);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);

        btnRegister = new QPushButton(page);
        btnRegister->setObjectName(QString::fromUtf8("btnRegister"));

        horizontalLayout->addWidget(btnRegister);


        verticalLayout_2->addLayout(horizontalLayout);


        gridLayout_3->addLayout(verticalLayout_2, 2, 0, 1, 1);

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

        gridLayout->addWidget(stackedWidget, 0, 0, 1, 1);


        retranslateUi(LoginDialog);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(LoginDialog);
    } // setupUi

    void retranslateUi(QDialog *LoginDialog)
    {
        LoginDialog->setWindowTitle(QCoreApplication::translate("LoginDialog", "\346\225\260\345\255\227\346\240\267\346\234\272\344\270\200\344\275\223\345\214\226\345\271\263\345\217\260", nullptr));
        BtnIcon->setText(QString());
        LabelTitle->setText(QCoreApplication::translate("LoginDialog", "\346\225\260\345\255\227\346\240\267\346\234\272\344\270\200\344\275\223\345\214\226\345\271\263\345\217\260", nullptr));
        BtnClose->setText(QString());
        lblUser->setText(QCoreApplication::translate("LoginDialog", "\346\254\242\350\277\216\347\231\273\345\275\225", nullptr));
        btnLogin->setText(QCoreApplication::translate("LoginDialog", "\347\231\273 \345\275\225", nullptr));
        btnChangePassword->setText(QCoreApplication::translate("LoginDialog", "\344\277\256\346\224\271\345\257\206\347\240\201", nullptr));
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
