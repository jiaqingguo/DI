/********************************************************************************
** Form generated from reading UI file 'LoginWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINWIDGET_H
#define UI_LOGINWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoginWidget
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *wdgLoginBg;
    QGridLayout *gridLayout_2;
    QSpacerItem *verticalSpacer_2;
    QLabel *lblAppName;
    QSpacerItem *horizontalSpacer_2;
    QWidget *wgdBorder;
    QGridLayout *gridLayout;
    QLabel *lblUser;
    QLabel *lblPwd;
    QPushButton *btnLogin;
    QLineEdit *lePassword;
    QLineEdit *leUser;
    QRadioButton *rbGeneral;
    QPushButton *btnExit;
    QSpacerItem *horizontalSpacer;
    QRadioButton *rbAdmin;
    QLabel *lblTitle;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *LoginWidget)
    {
        if (LoginWidget->objectName().isEmpty())
            LoginWidget->setObjectName(QString::fromUtf8("LoginWidget"));
        LoginWidget->resize(1181, 809);
        verticalLayout = new QVBoxLayout(LoginWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        wdgLoginBg = new QWidget(LoginWidget);
        wdgLoginBg->setObjectName(QString::fromUtf8("wdgLoginBg"));
        gridLayout_2 = new QGridLayout(wdgLoginBg);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setVerticalSpacing(72);
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalSpacer_2 = new QSpacerItem(20, 89, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_2, 0, 1, 1, 1);

        lblAppName = new QLabel(wdgLoginBg);
        lblAppName->setObjectName(QString::fromUtf8("lblAppName"));
        QFont font;
        font.setPointSize(40);
        lblAppName->setFont(font);
        lblAppName->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(lblAppName, 1, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(419, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_2, 2, 0, 1, 1);

        wgdBorder = new QWidget(wdgLoginBg);
        wgdBorder->setObjectName(QString::fromUtf8("wgdBorder"));
        wgdBorder->setMinimumSize(QSize(620, 540));
        wgdBorder->setMaximumSize(QSize(620, 540));
        gridLayout = new QGridLayout(wgdBorder);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setHorizontalSpacing(26);
        gridLayout->setVerticalSpacing(28);
        gridLayout->setContentsMargins(60, 36, 60, 36);
        lblUser = new QLabel(wgdBorder);
        lblUser->setObjectName(QString::fromUtf8("lblUser"));
        lblUser->setMinimumSize(QSize(36, 36));
        lblUser->setMaximumSize(QSize(36, 36));

        gridLayout->addWidget(lblUser, 1, 0, 1, 1);

        lblPwd = new QLabel(wgdBorder);
        lblPwd->setObjectName(QString::fromUtf8("lblPwd"));
        lblPwd->setMinimumSize(QSize(36, 36));
        lblPwd->setMaximumSize(QSize(36, 36));

        gridLayout->addWidget(lblPwd, 2, 0, 1, 1);

        btnLogin = new QPushButton(wgdBorder);
        btnLogin->setObjectName(QString::fromUtf8("btnLogin"));
        btnLogin->setMinimumSize(QSize(0, 28));
        QFont font1;
        font1.setPointSize(28);
        btnLogin->setFont(font1);
        btnLogin->setStyleSheet(QString::fromUtf8(""));

        gridLayout->addWidget(btnLogin, 4, 0, 1, 4);

        lePassword = new QLineEdit(wgdBorder);
        lePassword->setObjectName(QString::fromUtf8("lePassword"));
        lePassword->setMinimumSize(QSize(0, 31));
        QFont font2;
        font2.setPointSize(24);
        lePassword->setFont(font2);
        lePassword->setEchoMode(QLineEdit::Password);

        gridLayout->addWidget(lePassword, 2, 1, 1, 3);

        leUser = new QLineEdit(wgdBorder);
        leUser->setObjectName(QString::fromUtf8("leUser"));
        leUser->setMinimumSize(QSize(0, 31));
        leUser->setMaximumSize(QSize(1677215, 16777215));
        leUser->setFont(font2);

        gridLayout->addWidget(leUser, 1, 1, 1, 3);

        rbGeneral = new QRadioButton(wgdBorder);
        rbGeneral->setObjectName(QString::fromUtf8("rbGeneral"));
        QFont font3;
        font3.setPointSize(20);
        rbGeneral->setFont(font3);
        rbGeneral->setChecked(true);

        gridLayout->addWidget(rbGeneral, 3, 3, 1, 1);

        btnExit = new QPushButton(wgdBorder);
        btnExit->setObjectName(QString::fromUtf8("btnExit"));
        btnExit->setMinimumSize(QSize(0, 28));
        btnExit->setFont(font1);

        gridLayout->addWidget(btnExit, 5, 0, 1, 4);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 3, 2, 1, 1);

        rbAdmin = new QRadioButton(wgdBorder);
        rbAdmin->setObjectName(QString::fromUtf8("rbAdmin"));
        rbAdmin->setFont(font3);

        gridLayout->addWidget(rbAdmin, 3, 0, 1, 2);

        lblTitle = new QLabel(wgdBorder);
        lblTitle->setObjectName(QString::fromUtf8("lblTitle"));
        QFont font4;
        font4.setPointSize(36);
        lblTitle->setFont(font4);
        lblTitle->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(lblTitle, 0, 0, 1, 4);


        gridLayout_2->addWidget(wgdBorder, 2, 1, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(81, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_3, 2, 2, 1, 1);

        verticalSpacer = new QSpacerItem(20, 90, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer, 3, 1, 1, 1);

        gridLayout_2->setColumnStretch(0, 5);
        gridLayout_2->setColumnStretch(1, 2);
        gridLayout_2->setColumnStretch(2, 1);

        verticalLayout->addWidget(wdgLoginBg);

        QWidget::setTabOrder(leUser, lePassword);
        QWidget::setTabOrder(lePassword, rbAdmin);
        QWidget::setTabOrder(rbAdmin, rbGeneral);
        QWidget::setTabOrder(rbGeneral, btnLogin);
        QWidget::setTabOrder(btnLogin, btnExit);

        retranslateUi(LoginWidget);

        QMetaObject::connectSlotsByName(LoginWidget);
    } // setupUi

    void retranslateUi(QWidget *LoginWidget)
    {
        LoginWidget->setWindowTitle(QCoreApplication::translate("LoginWidget", "\347\231\273\345\275\225", nullptr));
        lblAppName->setText(QCoreApplication::translate("LoginWidget", "\350\275\257\344\273\266\351\203\250\347\275\262\347\256\241\347\220\206\347\263\273\347\273\237-\346\230\276\346\216\247\350\275\257\344\273\266", nullptr));
        lblUser->setText(QString());
        lblPwd->setText(QString());
        btnLogin->setText(QCoreApplication::translate("LoginWidget", "\347\231\273\345\275\225", nullptr));
        lePassword->setPlaceholderText(QCoreApplication::translate("LoginWidget", "\350\257\267\350\276\223\345\205\245\346\202\250\347\232\204\345\257\206\347\240\201", nullptr));
        leUser->setPlaceholderText(QCoreApplication::translate("LoginWidget", "\350\257\267\350\276\223\345\205\245\346\202\250\347\232\204\347\224\250\346\210\267\345\220\215", nullptr));
        rbGeneral->setText(QCoreApplication::translate("LoginWidget", "\346\231\256\351\200\232\347\224\250\346\210\267", nullptr));
        btnExit->setText(QCoreApplication::translate("LoginWidget", "\351\200\200\345\207\272", nullptr));
        rbAdmin->setText(QCoreApplication::translate("LoginWidget", "\347\256\241\347\220\206\345\221\230", nullptr));
        lblTitle->setText(QCoreApplication::translate("LoginWidget", "\347\224\250\346\210\267\347\231\273\345\275\225", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoginWidget: public Ui_LoginWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINWIDGET_H
