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

QT_BEGIN_NAMESPACE

class Ui_AddToolInfoDialog
{
public:
    QGridLayout *gridLayout;
    QLabel *labelIP1;
    QLineEdit *lineEditIP6;
    QSpacerItem *horizontalSpacer_2;
    QLineEdit *lineEditIP4;
    QLabel *labelIP2;
    QLineEdit *lineEditIP1;
    QLabel *label_4;
    QLineEdit *lineEditToolName;
    QLabel *labelIP5;
    QLineEdit *lineEditIP5;
    QLabel *labelIP6;
    QLineEdit *lineEditIP2;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *lineEdit;
    QPushButton *btnChooseImage;
    QLabel *labelIP4;
    QLineEdit *lineEditToolPath;
    QLabel *labelIP3;
    QLabel *label_2;
    QLabel *label;
    QLineEdit *lineEditIP3;
    QHBoxLayout *horizontalLayout;
    QPushButton *btnOK;
    QSpacerItem *horizontalSpacer_3;

    void setupUi(QDialog *AddToolInfoDialog)
    {
        if (AddToolInfoDialog->objectName().isEmpty())
            AddToolInfoDialog->setObjectName(QString::fromUtf8("AddToolInfoDialog"));
        AddToolInfoDialog->resize(310, 282);
        gridLayout = new QGridLayout(AddToolInfoDialog);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        labelIP1 = new QLabel(AddToolInfoDialog);
        labelIP1->setObjectName(QString::fromUtf8("labelIP1"));

        gridLayout->addWidget(labelIP1, 3, 0, 1, 1);

        lineEditIP6 = new QLineEdit(AddToolInfoDialog);
        lineEditIP6->setObjectName(QString::fromUtf8("lineEditIP6"));

        gridLayout->addWidget(lineEditIP6, 8, 1, 1, 3);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 9, 3, 1, 1);

        lineEditIP4 = new QLineEdit(AddToolInfoDialog);
        lineEditIP4->setObjectName(QString::fromUtf8("lineEditIP4"));

        gridLayout->addWidget(lineEditIP4, 6, 1, 1, 3);

        labelIP2 = new QLabel(AddToolInfoDialog);
        labelIP2->setObjectName(QString::fromUtf8("labelIP2"));

        gridLayout->addWidget(labelIP2, 4, 0, 1, 1);

        lineEditIP1 = new QLineEdit(AddToolInfoDialog);
        lineEditIP1->setObjectName(QString::fromUtf8("lineEditIP1"));

        gridLayout->addWidget(lineEditIP1, 3, 1, 1, 3);

        label_4 = new QLabel(AddToolInfoDialog);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 2, 0, 1, 1);

        lineEditToolName = new QLineEdit(AddToolInfoDialog);
        lineEditToolName->setObjectName(QString::fromUtf8("lineEditToolName"));

        gridLayout->addWidget(lineEditToolName, 0, 1, 1, 3);

        labelIP5 = new QLabel(AddToolInfoDialog);
        labelIP5->setObjectName(QString::fromUtf8("labelIP5"));

        gridLayout->addWidget(labelIP5, 7, 0, 1, 1);

        lineEditIP5 = new QLineEdit(AddToolInfoDialog);
        lineEditIP5->setObjectName(QString::fromUtf8("lineEditIP5"));

        gridLayout->addWidget(lineEditIP5, 7, 1, 1, 3);

        labelIP6 = new QLabel(AddToolInfoDialog);
        labelIP6->setObjectName(QString::fromUtf8("labelIP6"));

        gridLayout->addWidget(labelIP6, 8, 0, 1, 1);

        lineEditIP2 = new QLineEdit(AddToolInfoDialog);
        lineEditIP2->setObjectName(QString::fromUtf8("lineEditIP2"));

        gridLayout->addWidget(lineEditIP2, 4, 1, 1, 3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        lineEdit = new QLineEdit(AddToolInfoDialog);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        horizontalLayout_2->addWidget(lineEdit);

        btnChooseImage = new QPushButton(AddToolInfoDialog);
        btnChooseImage->setObjectName(QString::fromUtf8("btnChooseImage"));

        horizontalLayout_2->addWidget(btnChooseImage);


        gridLayout->addLayout(horizontalLayout_2, 2, 1, 1, 3);

        labelIP4 = new QLabel(AddToolInfoDialog);
        labelIP4->setObjectName(QString::fromUtf8("labelIP4"));

        gridLayout->addWidget(labelIP4, 6, 0, 1, 1);

        lineEditToolPath = new QLineEdit(AddToolInfoDialog);
        lineEditToolPath->setObjectName(QString::fromUtf8("lineEditToolPath"));

        gridLayout->addWidget(lineEditToolPath, 1, 1, 1, 3);

        labelIP3 = new QLabel(AddToolInfoDialog);
        labelIP3->setObjectName(QString::fromUtf8("labelIP3"));

        gridLayout->addWidget(labelIP3, 5, 0, 1, 1);

        label_2 = new QLabel(AddToolInfoDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 0, 0, 1, 1);

        label = new QLabel(AddToolInfoDialog);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 1, 0, 1, 1);

        lineEditIP3 = new QLineEdit(AddToolInfoDialog);
        lineEditIP3->setObjectName(QString::fromUtf8("lineEditIP3"));

        gridLayout->addWidget(lineEditIP3, 5, 1, 1, 3);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        btnOK = new QPushButton(AddToolInfoDialog);
        btnOK->setObjectName(QString::fromUtf8("btnOK"));

        horizontalLayout->addWidget(btnOK);


        gridLayout->addLayout(horizontalLayout, 9, 1, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 9, 0, 1, 1);


        retranslateUi(AddToolInfoDialog);

        QMetaObject::connectSlotsByName(AddToolInfoDialog);
    } // setupUi

    void retranslateUi(QDialog *AddToolInfoDialog)
    {
        AddToolInfoDialog->setWindowTitle(QCoreApplication::translate("AddToolInfoDialog", "\345\242\236\345\212\240\345\267\245\345\205\267\344\277\241\346\201\257", nullptr));
        labelIP1->setText(QCoreApplication::translate("AddToolInfoDialog", "IP1\357\274\232", nullptr));
        labelIP2->setText(QCoreApplication::translate("AddToolInfoDialog", "IP2:", nullptr));
        label_4->setText(QCoreApplication::translate("AddToolInfoDialog", "\345\233\276\346\240\207\350\267\257\345\276\204:", nullptr));
        labelIP5->setText(QCoreApplication::translate("AddToolInfoDialog", "IP5:", nullptr));
        labelIP6->setText(QCoreApplication::translate("AddToolInfoDialog", "IP6:", nullptr));
        btnChooseImage->setText(QCoreApplication::translate("AddToolInfoDialog", "\351\200\211\346\213\251", nullptr));
        labelIP4->setText(QCoreApplication::translate("AddToolInfoDialog", "IP4:", nullptr));
        labelIP3->setText(QCoreApplication::translate("AddToolInfoDialog", "IP3:", nullptr));
        label_2->setText(QCoreApplication::translate("AddToolInfoDialog", "\345\267\245\345\205\267\345\220\215\347\247\260:", nullptr));
        label->setText(QCoreApplication::translate("AddToolInfoDialog", "\345\267\245\345\205\267\350\267\257\345\276\204\357\274\232", nullptr));
        btnOK->setText(QCoreApplication::translate("AddToolInfoDialog", "\347\241\256\345\256\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AddToolInfoDialog: public Ui_AddToolInfoDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDTOOLINFODIALOG_H
