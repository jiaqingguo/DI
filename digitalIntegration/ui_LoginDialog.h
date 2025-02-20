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
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *lblUser;
    QSpacerItem *horizontalSpacer_9;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout_2;
    QLineEdit *leUser;
    QLineEdit *lePassword;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_3;
    QPushButton *btnLogin;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *btnChangePassword;
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
        LoginDialog->resize(453, 350);
        LoginDialog->setMinimumSize(QSize(450, 350));
        gridLayout = new QGridLayout(LoginDialog);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        stackedWidget = new QStackedWidget(LoginDialog);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        gridLayout_2 = new QGridLayout(page);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(-1, 0, -1, -1);
        wgdBorder = new QWidget(page);
        wgdBorder->setObjectName(QString::fromUtf8("wgdBorder"));
        wgdBorder->setMinimumSize(QSize(0, 0));
        wgdBorder->setMaximumSize(QSize(620, 540));
        horizontalLayoutWidget = new QWidget(wgdBorder);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(10, -10, 421, 96));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        lblUser = new QLabel(horizontalLayoutWidget);
        lblUser->setObjectName(QString::fromUtf8("lblUser"));
        lblUser->setMinimumSize(QSize(100, 36));
        lblUser->setMaximumSize(QSize(36, 36));

        horizontalLayout->addWidget(lblUser);

        horizontalSpacer_9 = new QSpacerItem(405, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_9);

        verticalLayoutWidget = new QWidget(wgdBorder);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(10, 50, 421, 171));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        leUser = new QLineEdit(verticalLayoutWidget);
        leUser->setObjectName(QString::fromUtf8("leUser"));
        leUser->setMinimumSize(QSize(0, 43));
        leUser->setMaximumSize(QSize(1677215, 16777215));
        QFont font;
        font.setPointSize(24);
        leUser->setFont(font);

        verticalLayout_2->addWidget(leUser);

        lePassword = new QLineEdit(verticalLayoutWidget);
        lePassword->setObjectName(QString::fromUtf8("lePassword"));
        lePassword->setMinimumSize(QSize(0, 43));
        lePassword->setFont(font);
        lePassword->setEchoMode(QLineEdit::Password);

        verticalLayout_2->addWidget(lePassword);

        verticalLayoutWidget_2 = new QWidget(wgdBorder);
        verticalLayoutWidget_2->setObjectName(QString::fromUtf8("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(10, 240, 417, 85));
        verticalLayout_3 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        btnLogin = new QPushButton(verticalLayoutWidget_2);
        btnLogin->setObjectName(QString::fromUtf8("btnLogin"));
        btnLogin->setMinimumSize(QSize(415, 45));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\351\273\221\344\275\223"));
        font1.setPointSize(16);
        btnLogin->setFont(font1);
        btnLogin->setAutoFillBackground(false);

        verticalLayout_3->addWidget(btnLogin);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        btnChangePassword = new QPushButton(verticalLayoutWidget_2);
        btnChangePassword->setObjectName(QString::fromUtf8("btnChangePassword"));
        btnChangePassword->setMinimumSize(QSize(0, 30));
        QFont font2;
        font2.setFamily(QString::fromUtf8("\351\273\221\344\275\223"));
        font2.setPointSize(14);
        font2.setBold(false);
        font2.setWeight(50);
        btnChangePassword->setFont(font2);

        horizontalLayout_3->addWidget(btnChangePassword);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_6);

        btnRegister = new QPushButton(verticalLayoutWidget_2);
        btnRegister->setObjectName(QString::fromUtf8("btnRegister"));
        btnRegister->setMinimumSize(QSize(0, 30));
        QFont font3;
        font3.setFamily(QString::fromUtf8("\351\273\221\344\275\223"));
        font3.setPointSize(14);
        btnRegister->setFont(font3);

        horizontalLayout_3->addWidget(btnRegister);


        verticalLayout_3->addLayout(horizontalLayout_3);


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
        QFont font4;
        font4.setPointSize(11);
        label->setFont(font4);
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
        QFont font5;
        font5.setPointSize(6);
        labelFingerprint->setFont(font5);

        horizontalLayout_2->addWidget(labelFingerprint);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout_2);

        btnFingerprint = new QPushButton(widget_2);
        btnFingerprint->setObjectName(QString::fromUtf8("btnFingerprint"));
        btnFingerprint->setMinimumSize(QSize(0, 28));
        QFont font6;
        font6.setPointSize(9);
        btnFingerprint->setFont(font6);

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
        LoginDialog->setWindowTitle(QCoreApplication::translate("LoginDialog", "\346\225\260\345\255\227\346\240\267\346\234\272\344\270\200\344\275\223\345\214\226\345\271\263\345\217\260", nullptr));
        lblUser->setText(QCoreApplication::translate("LoginDialog", "<html><head/><body><p><span style=\" font-size:18pt; font-weight:600;\">\346\254\242\350\277\216\347\231\273\345\275\225</span></p></body></html>", nullptr));
        leUser->setPlaceholderText(QString());
        lePassword->setPlaceholderText(QString());
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
