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
    QVBoxLayout *verticalLayout_3;
    QFormLayout *formLayout_2;
    QLabel *label_2;
    QLineEdit *lineEditToolName;
    QLabel *label;
    QLineEdit *lineEditToolPath;
    QLabel *label_4;
    QLineEdit *lineEditIconPath;
    QLabel *labelIP1;
    QLineEdit *lineEditIP1;
    QLabel *labelIP2;
    QLineEdit *lineEditIP2;
    QLabel *labelIP3;
    QLineEdit *lineEditIP3;
    QLabel *labelIP4;
    QLineEdit *lineEditIP4;
    QLabel *labelIP5;
    QLineEdit *lineEditIP5;
    QLabel *labelIP6;
    QLineEdit *lineEditIP6;
    QHBoxLayout *horizontalLayout_2;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnOK;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QDialog *AddToolInfoDialog)
    {
        if (AddToolInfoDialog->objectName().isEmpty())
            AddToolInfoDialog->setObjectName(QString::fromUtf8("AddToolInfoDialog"));
        AddToolInfoDialog->resize(351, 335);
        verticalLayout = new QVBoxLayout(AddToolInfoDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        formLayout_2 = new QFormLayout();
        formLayout_2->setObjectName(QString::fromUtf8("formLayout_2"));
        label_2 = new QLabel(AddToolInfoDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        formLayout_2->setWidget(1, QFormLayout::LabelRole, label_2);

        lineEditToolName = new QLineEdit(AddToolInfoDialog);
        lineEditToolName->setObjectName(QString::fromUtf8("lineEditToolName"));

        formLayout_2->setWidget(1, QFormLayout::FieldRole, lineEditToolName);

        label = new QLabel(AddToolInfoDialog);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout_2->setWidget(2, QFormLayout::LabelRole, label);

        lineEditToolPath = new QLineEdit(AddToolInfoDialog);
        lineEditToolPath->setObjectName(QString::fromUtf8("lineEditToolPath"));

        formLayout_2->setWidget(2, QFormLayout::FieldRole, lineEditToolPath);

        label_4 = new QLabel(AddToolInfoDialog);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        formLayout_2->setWidget(3, QFormLayout::LabelRole, label_4);

        lineEditIconPath = new QLineEdit(AddToolInfoDialog);
        lineEditIconPath->setObjectName(QString::fromUtf8("lineEditIconPath"));

        formLayout_2->setWidget(3, QFormLayout::FieldRole, lineEditIconPath);

        labelIP1 = new QLabel(AddToolInfoDialog);
        labelIP1->setObjectName(QString::fromUtf8("labelIP1"));

        formLayout_2->setWidget(4, QFormLayout::LabelRole, labelIP1);

        lineEditIP1 = new QLineEdit(AddToolInfoDialog);
        lineEditIP1->setObjectName(QString::fromUtf8("lineEditIP1"));

        formLayout_2->setWidget(4, QFormLayout::FieldRole, lineEditIP1);

        labelIP2 = new QLabel(AddToolInfoDialog);
        labelIP2->setObjectName(QString::fromUtf8("labelIP2"));

        formLayout_2->setWidget(5, QFormLayout::LabelRole, labelIP2);

        lineEditIP2 = new QLineEdit(AddToolInfoDialog);
        lineEditIP2->setObjectName(QString::fromUtf8("lineEditIP2"));

        formLayout_2->setWidget(5, QFormLayout::FieldRole, lineEditIP2);

        labelIP3 = new QLabel(AddToolInfoDialog);
        labelIP3->setObjectName(QString::fromUtf8("labelIP3"));

        formLayout_2->setWidget(6, QFormLayout::LabelRole, labelIP3);

        lineEditIP3 = new QLineEdit(AddToolInfoDialog);
        lineEditIP3->setObjectName(QString::fromUtf8("lineEditIP3"));

        formLayout_2->setWidget(6, QFormLayout::FieldRole, lineEditIP3);

        labelIP4 = new QLabel(AddToolInfoDialog);
        labelIP4->setObjectName(QString::fromUtf8("labelIP4"));

        formLayout_2->setWidget(7, QFormLayout::LabelRole, labelIP4);

        lineEditIP4 = new QLineEdit(AddToolInfoDialog);
        lineEditIP4->setObjectName(QString::fromUtf8("lineEditIP4"));

        formLayout_2->setWidget(7, QFormLayout::FieldRole, lineEditIP4);

        labelIP5 = new QLabel(AddToolInfoDialog);
        labelIP5->setObjectName(QString::fromUtf8("labelIP5"));

        formLayout_2->setWidget(8, QFormLayout::LabelRole, labelIP5);

        lineEditIP5 = new QLineEdit(AddToolInfoDialog);
        lineEditIP5->setObjectName(QString::fromUtf8("lineEditIP5"));

        formLayout_2->setWidget(8, QFormLayout::FieldRole, lineEditIP5);

        labelIP6 = new QLabel(AddToolInfoDialog);
        labelIP6->setObjectName(QString::fromUtf8("labelIP6"));

        formLayout_2->setWidget(9, QFormLayout::LabelRole, labelIP6);

        lineEditIP6 = new QLineEdit(AddToolInfoDialog);
        lineEditIP6->setObjectName(QString::fromUtf8("lineEditIP6"));

        formLayout_2->setWidget(9, QFormLayout::FieldRole, lineEditIP6);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));

        formLayout_2->setLayout(0, QFormLayout::LabelRole, horizontalLayout_2);


        verticalLayout_3->addLayout(formLayout_2);


        verticalLayout->addLayout(verticalLayout_3);

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
        label->setText(QCoreApplication::translate("AddToolInfoDialog", "\345\267\245\345\205\267\350\267\257\345\276\204\357\274\232", nullptr));
        label_4->setText(QCoreApplication::translate("AddToolInfoDialog", "\345\233\276\346\240\207\350\267\257\345\276\204:", nullptr));
        labelIP1->setText(QCoreApplication::translate("AddToolInfoDialog", "IP1\357\274\232", nullptr));
        labelIP2->setText(QCoreApplication::translate("AddToolInfoDialog", "IP2:", nullptr));
        labelIP3->setText(QCoreApplication::translate("AddToolInfoDialog", "IP3:", nullptr));
        labelIP4->setText(QCoreApplication::translate("AddToolInfoDialog", "IP4:", nullptr));
        labelIP5->setText(QCoreApplication::translate("AddToolInfoDialog", "IP5:", nullptr));
        labelIP6->setText(QCoreApplication::translate("AddToolInfoDialog", "IP6:", nullptr));
        btnOK->setText(QCoreApplication::translate("AddToolInfoDialog", "\347\241\256\345\256\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AddToolInfoDialog: public Ui_AddToolInfoDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDTOOLINFODIALOG_H
