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
#include <QtWidgets/QGridLayout>
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
    QGridLayout *gridLayout;
    QLineEdit *lineEditToolName;
    QLineEdit *lineEditIP1;
    QLineEdit *lineEditIP4;
    QLineEdit *lineEditIconPath;
    QLabel *label;
    QLineEdit *lineEditToolPath;
    QLineEdit *lineEditIP2;
    QLineEdit *lineEditIP3;
    QLineEdit *lineEditIP5;
    QLineEdit *lineEditIP6;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *labelIP1;
    QLabel *labelIP2;
    QLabel *labelIP3;
    QLabel *labelIP4;
    QLabel *labelIP5;
    QLabel *labelIP6;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnOK;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QDialog *AddToolInfoDialog)
    {
        if (AddToolInfoDialog->objectName().isEmpty())
            AddToolInfoDialog->setObjectName(QString::fromUtf8("AddToolInfoDialog"));
        AddToolInfoDialog->resize(351, 294);
        verticalLayout = new QVBoxLayout(AddToolInfoDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        lineEditToolName = new QLineEdit(AddToolInfoDialog);
        lineEditToolName->setObjectName(QString::fromUtf8("lineEditToolName"));

        gridLayout->addWidget(lineEditToolName, 2, 1, 1, 1);

        lineEditIP1 = new QLineEdit(AddToolInfoDialog);
        lineEditIP1->setObjectName(QString::fromUtf8("lineEditIP1"));

        gridLayout->addWidget(lineEditIP1, 5, 1, 1, 1);

        lineEditIP4 = new QLineEdit(AddToolInfoDialog);
        lineEditIP4->setObjectName(QString::fromUtf8("lineEditIP4"));

        gridLayout->addWidget(lineEditIP4, 8, 1, 1, 1);

        lineEditIconPath = new QLineEdit(AddToolInfoDialog);
        lineEditIconPath->setObjectName(QString::fromUtf8("lineEditIconPath"));

        gridLayout->addWidget(lineEditIconPath, 4, 1, 1, 1);

        label = new QLabel(AddToolInfoDialog);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 2, 0, 1, 1);

        lineEditToolPath = new QLineEdit(AddToolInfoDialog);
        lineEditToolPath->setObjectName(QString::fromUtf8("lineEditToolPath"));

        gridLayout->addWidget(lineEditToolPath, 3, 1, 1, 1);

        lineEditIP2 = new QLineEdit(AddToolInfoDialog);
        lineEditIP2->setObjectName(QString::fromUtf8("lineEditIP2"));

        gridLayout->addWidget(lineEditIP2, 6, 1, 1, 1);

        lineEditIP3 = new QLineEdit(AddToolInfoDialog);
        lineEditIP3->setObjectName(QString::fromUtf8("lineEditIP3"));

        gridLayout->addWidget(lineEditIP3, 7, 1, 1, 1);

        lineEditIP5 = new QLineEdit(AddToolInfoDialog);
        lineEditIP5->setObjectName(QString::fromUtf8("lineEditIP5"));

        gridLayout->addWidget(lineEditIP5, 9, 1, 1, 1);

        lineEditIP6 = new QLineEdit(AddToolInfoDialog);
        lineEditIP6->setObjectName(QString::fromUtf8("lineEditIP6"));

        gridLayout->addWidget(lineEditIP6, 10, 1, 1, 1);

        label_2 = new QLabel(AddToolInfoDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 3, 0, 1, 1);

        label_3 = new QLabel(AddToolInfoDialog);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 4, 0, 1, 1);

        labelIP1 = new QLabel(AddToolInfoDialog);
        labelIP1->setObjectName(QString::fromUtf8("labelIP1"));

        gridLayout->addWidget(labelIP1, 5, 0, 1, 1);

        labelIP2 = new QLabel(AddToolInfoDialog);
        labelIP2->setObjectName(QString::fromUtf8("labelIP2"));

        gridLayout->addWidget(labelIP2, 6, 0, 1, 1);

        labelIP3 = new QLabel(AddToolInfoDialog);
        labelIP3->setObjectName(QString::fromUtf8("labelIP3"));

        gridLayout->addWidget(labelIP3, 7, 0, 1, 1);

        labelIP4 = new QLabel(AddToolInfoDialog);
        labelIP4->setObjectName(QString::fromUtf8("labelIP4"));

        gridLayout->addWidget(labelIP4, 8, 0, 1, 1);

        labelIP5 = new QLabel(AddToolInfoDialog);
        labelIP5->setObjectName(QString::fromUtf8("labelIP5"));

        gridLayout->addWidget(labelIP5, 9, 0, 1, 1);

        labelIP6 = new QLabel(AddToolInfoDialog);
        labelIP6->setObjectName(QString::fromUtf8("labelIP6"));

        gridLayout->addWidget(labelIP6, 10, 0, 1, 1);


        verticalLayout_3->addLayout(gridLayout);


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
        label->setText(QCoreApplication::translate("AddToolInfoDialog", "\345\267\245\345\205\267\345\220\215\347\247\260\357\274\232", nullptr));
        label_2->setText(QCoreApplication::translate("AddToolInfoDialog", "\345\267\245\345\205\267\350\267\257\345\276\204\357\274\232", nullptr));
        label_3->setText(QCoreApplication::translate("AddToolInfoDialog", "\345\233\276\346\240\207\350\267\257\345\276\204\357\274\232", nullptr));
        labelIP1->setText(QCoreApplication::translate("AddToolInfoDialog", "IP1\357\274\232", nullptr));
        labelIP2->setText(QCoreApplication::translate("AddToolInfoDialog", "IP2\357\274\232", nullptr));
        labelIP3->setText(QCoreApplication::translate("AddToolInfoDialog", "IP3\357\274\232", nullptr));
        labelIP4->setText(QCoreApplication::translate("AddToolInfoDialog", "IP4\357\274\232", nullptr));
        labelIP5->setText(QCoreApplication::translate("AddToolInfoDialog", "IP5\357\274\232", nullptr));
        labelIP6->setText(QCoreApplication::translate("AddToolInfoDialog", "IP6\357\274\232", nullptr));
        btnOK->setText(QCoreApplication::translate("AddToolInfoDialog", "\347\241\256\345\256\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AddToolInfoDialog: public Ui_AddToolInfoDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDTOOLINFODIALOG_H
