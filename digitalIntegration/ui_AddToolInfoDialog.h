/********************************************************************************
** Form generated from reading UI file 'AddToolInfoDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDTOOLINFODIALOG_H
#define UI_ADDTOOLINFODIALOG_H

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

class Ui_AddToolInfoDialog
{
public:
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QLabel *label_2;
    QLineEdit *lineEditToolName;
    QLabel *label_4;
    QLineEdit *lineEditIconPath;
    QLineEdit *lineEditHost;
    QLabel *label;
    QLabel *label_3;
    QLineEdit *lineEdit_2;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnOK;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QDialog *AddToolInfoDialog)
    {
        if (AddToolInfoDialog->objectName().isEmpty())
            AddToolInfoDialog->setObjectName(QString::fromUtf8("AddToolInfoDialog"));
        AddToolInfoDialog->resize(363, 178);
        verticalLayout = new QVBoxLayout(AddToolInfoDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        formLayout = new QFormLayout();
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        label_2 = new QLabel(AddToolInfoDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        lineEditToolName = new QLineEdit(AddToolInfoDialog);
        lineEditToolName->setObjectName(QString::fromUtf8("lineEditToolName"));

        formLayout->setWidget(1, QFormLayout::FieldRole, lineEditToolName);

        label_4 = new QLabel(AddToolInfoDialog);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        formLayout->setWidget(3, QFormLayout::LabelRole, label_4);

        lineEditIconPath = new QLineEdit(AddToolInfoDialog);
        lineEditIconPath->setObjectName(QString::fromUtf8("lineEditIconPath"));

        formLayout->setWidget(3, QFormLayout::FieldRole, lineEditIconPath);

        lineEditHost = new QLineEdit(AddToolInfoDialog);
        lineEditHost->setObjectName(QString::fromUtf8("lineEditHost"));

        formLayout->setWidget(0, QFormLayout::FieldRole, lineEditHost);

        label = new QLabel(AddToolInfoDialog);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        label_3 = new QLabel(AddToolInfoDialog);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_3);

        lineEdit_2 = new QLineEdit(AddToolInfoDialog);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));

        formLayout->setWidget(2, QFormLayout::FieldRole, lineEdit_2);


        verticalLayout->addLayout(formLayout);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        btnOK = new QPushButton(AddToolInfoDialog);
        btnOK->setObjectName(QString::fromUtf8("btnOK"));

        horizontalLayout->addWidget(btnOK);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(AddToolInfoDialog);

        QMetaObject::connectSlotsByName(AddToolInfoDialog);
    } // setupUi

    void retranslateUi(QDialog *AddToolInfoDialog)
    {
        AddToolInfoDialog->setWindowTitle(QCoreApplication::translate("AddToolInfoDialog", "\345\242\236\345\212\240\345\267\245\345\205\267\344\277\241\346\201\257", nullptr));
        label_2->setText(QCoreApplication::translate("AddToolInfoDialog", "\345\267\245\345\205\267\345\220\215\347\247\260:", nullptr));
        label_4->setText(QCoreApplication::translate("AddToolInfoDialog", "\345\233\276\346\240\207\350\267\257\345\276\204:", nullptr));
        label->setText(QCoreApplication::translate("AddToolInfoDialog", "\344\270\273\346\234\272\357\274\232", nullptr));
        label_3->setText(QCoreApplication::translate("AddToolInfoDialog", "\345\267\245\345\205\267\350\267\257\345\276\204\357\274\232", nullptr));
        btnOK->setText(QCoreApplication::translate("AddToolInfoDialog", "\347\241\256\345\256\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AddToolInfoDialog: public Ui_AddToolInfoDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDTOOLINFODIALOG_H
