/********************************************************************************
** Form generated from reading UI file 'AddIpInfoDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDIPINFODIALOG_H
#define UI_ADDIPINFODIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_AddIpInfoDialog
{
public:
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QLabel *label;
    QLineEdit *lineEditHost;
    QLabel *label_2;
    QLineEdit *lineEditIp;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnOK;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QDialog *AddIpInfoDialog)
    {
        if (AddIpInfoDialog->objectName().isEmpty())
            AddIpInfoDialog->setObjectName(QString::fromUtf8("AddIpInfoDialog"));
        AddIpInfoDialog->resize(243, 122);
        verticalLayout = new QVBoxLayout(AddIpInfoDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        formLayout = new QFormLayout();
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        label = new QLabel(AddIpInfoDialog);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        lineEditHost = new QLineEdit(AddIpInfoDialog);
        lineEditHost->setObjectName(QString::fromUtf8("lineEditHost"));

        formLayout->setWidget(0, QFormLayout::FieldRole, lineEditHost);

        label_2 = new QLabel(AddIpInfoDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        lineEditIp = new QLineEdit(AddIpInfoDialog);
        lineEditIp->setObjectName(QString::fromUtf8("lineEditIp"));

        formLayout->setWidget(1, QFormLayout::FieldRole, lineEditIp);


        verticalLayout->addLayout(formLayout);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        btnOK = new QPushButton(AddIpInfoDialog);
        btnOK->setObjectName(QString::fromUtf8("btnOK"));

        horizontalLayout->addWidget(btnOK);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(AddIpInfoDialog);

        QMetaObject::connectSlotsByName(AddIpInfoDialog);
    } // setupUi

    void retranslateUi(QDialog *AddIpInfoDialog)
    {
        AddIpInfoDialog->setWindowTitle(QCoreApplication::translate("AddIpInfoDialog", "\346\226\260\345\242\236ip\344\277\241\346\201\257", nullptr));
        label->setText(QCoreApplication::translate("AddIpInfoDialog", "\344\270\273\346\234\272\357\274\232", nullptr));
        label_2->setText(QCoreApplication::translate("AddIpInfoDialog", "ip\357\274\232", nullptr));
        btnOK->setText(QCoreApplication::translate("AddIpInfoDialog", "\347\241\256\345\256\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AddIpInfoDialog: public Ui_AddIpInfoDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDIPINFODIALOG_H
