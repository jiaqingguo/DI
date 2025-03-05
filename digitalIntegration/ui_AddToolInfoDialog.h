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
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AddToolInfoDialog
{
public:
    QGridLayout *gridLayout_3;
    QWidget *widget;
    QGridLayout *gridLayout;
    QLabel *label4;
    QComboBox *IpcomboBox1;
    QSpacerItem *horizontalSpacer;
    QLabel *label5;
    QComboBox *IpcomboBox2;
    QSpacerItem *horizontalSpacer_4;
    QLabel *label6;
    QComboBox *IpcomboBox3;
    QSpacerItem *horizontalSpacer_5;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *horizontalLayout;
    QPushButton *btnOK;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_3;
    QRadioButton *accelerateRadioButton;
    QRadioButton *nodeRadioButton;
    QGridLayout *gridLayout_2;
    QLineEdit *lineEditToolPath;
    QLabel *label_4;
    QPushButton *btnChooseImage;
    QLabel *label_2;
    QLineEdit *lineEdit;
    QLabel *label;
    QLineEdit *lineEditToolName;

    void setupUi(QDialog *AddToolInfoDialog)
    {
        if (AddToolInfoDialog->objectName().isEmpty())
            AddToolInfoDialog->setObjectName(QString::fromUtf8("AddToolInfoDialog"));
        AddToolInfoDialog->resize(274, 328);
        gridLayout_3 = new QGridLayout(AddToolInfoDialog);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_3->setContentsMargins(0, 9, 0, 0);
        widget = new QWidget(AddToolInfoDialog);
        widget->setObjectName(QString::fromUtf8("widget"));
        gridLayout = new QGridLayout(widget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(-1, 0, -1, 0);
        label4 = new QLabel(widget);
        label4->setObjectName(QString::fromUtf8("label4"));

        gridLayout->addWidget(label4, 0, 0, 1, 1);

        IpcomboBox1 = new QComboBox(widget);
        IpcomboBox1->setObjectName(QString::fromUtf8("IpcomboBox1"));
        IpcomboBox1->setMinimumSize(QSize(90, 0));

        gridLayout->addWidget(IpcomboBox1, 0, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 2, 1, 1);

        label5 = new QLabel(widget);
        label5->setObjectName(QString::fromUtf8("label5"));

        gridLayout->addWidget(label5, 1, 0, 1, 1);

        IpcomboBox2 = new QComboBox(widget);
        IpcomboBox2->setObjectName(QString::fromUtf8("IpcomboBox2"));
        IpcomboBox2->setMinimumSize(QSize(90, 0));

        gridLayout->addWidget(IpcomboBox2, 1, 1, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_4, 1, 2, 1, 1);

        label6 = new QLabel(widget);
        label6->setObjectName(QString::fromUtf8("label6"));

        gridLayout->addWidget(label6, 2, 0, 1, 1);

        IpcomboBox3 = new QComboBox(widget);
        IpcomboBox3->setObjectName(QString::fromUtf8("IpcomboBox3"));
        IpcomboBox3->setMinimumSize(QSize(90, 0));

        gridLayout->addWidget(IpcomboBox3, 2, 1, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_5, 2, 2, 1, 1);


        gridLayout_3->addWidget(widget, 2, 0, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_3);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(9, 0, 9, 9);
        btnOK = new QPushButton(AddToolInfoDialog);
        btnOK->setObjectName(QString::fromUtf8("btnOK"));
        btnOK->setMinimumSize(QSize(110, 50));

        horizontalLayout->addWidget(btnOK);


        horizontalLayout_4->addLayout(horizontalLayout);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_2);


        gridLayout_3->addLayout(horizontalLayout_4, 3, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(9, 0, 9, 0);
        accelerateRadioButton = new QRadioButton(AddToolInfoDialog);
        accelerateRadioButton->setObjectName(QString::fromUtf8("accelerateRadioButton"));
        accelerateRadioButton->setMinimumSize(QSize(0, 0));

        horizontalLayout_3->addWidget(accelerateRadioButton);

        nodeRadioButton = new QRadioButton(AddToolInfoDialog);
        nodeRadioButton->setObjectName(QString::fromUtf8("nodeRadioButton"));
        nodeRadioButton->setMinimumSize(QSize(0, 0));

        horizontalLayout_3->addWidget(nodeRadioButton);


        gridLayout_3->addLayout(horizontalLayout_3, 1, 0, 1, 1);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(9, 0, 9, 9);
        lineEditToolPath = new QLineEdit(AddToolInfoDialog);
        lineEditToolPath->setObjectName(QString::fromUtf8("lineEditToolPath"));
        lineEditToolPath->setMinimumSize(QSize(0, 0));

        gridLayout_2->addWidget(lineEditToolPath, 1, 1, 1, 2);

        label_4 = new QLabel(AddToolInfoDialog);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_2->addWidget(label_4, 2, 0, 1, 1);

        btnChooseImage = new QPushButton(AddToolInfoDialog);
        btnChooseImage->setObjectName(QString::fromUtf8("btnChooseImage"));
        btnChooseImage->setMinimumSize(QSize(90, 30));

        gridLayout_2->addWidget(btnChooseImage, 2, 2, 1, 1);

        label_2 = new QLabel(AddToolInfoDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_2->addWidget(label_2, 0, 0, 1, 1);

        lineEdit = new QLineEdit(AddToolInfoDialog);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setMinimumSize(QSize(0, 0));

        gridLayout_2->addWidget(lineEdit, 2, 1, 1, 1);

        label = new QLabel(AddToolInfoDialog);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_2->addWidget(label, 1, 0, 1, 1);

        lineEditToolName = new QLineEdit(AddToolInfoDialog);
        lineEditToolName->setObjectName(QString::fromUtf8("lineEditToolName"));
        lineEditToolName->setMinimumSize(QSize(0, 0));

        gridLayout_2->addWidget(lineEditToolName, 0, 1, 1, 2);


        gridLayout_3->addLayout(gridLayout_2, 0, 0, 1, 1);


        retranslateUi(AddToolInfoDialog);

        QMetaObject::connectSlotsByName(AddToolInfoDialog);
    } // setupUi

    void retranslateUi(QDialog *AddToolInfoDialog)
    {
        AddToolInfoDialog->setWindowTitle(QCoreApplication::translate("AddToolInfoDialog", "\345\242\236\345\212\240\345\267\245\345\205\267\344\277\241\346\201\257", nullptr));
        label4->setText(QCoreApplication::translate("AddToolInfoDialog", "\350\212\202\347\202\271", nullptr));
        label5->setText(QCoreApplication::translate("AddToolInfoDialog", "\350\212\202\347\202\271", nullptr));
        label6->setText(QCoreApplication::translate("AddToolInfoDialog", "\350\212\202\347\202\271", nullptr));
        btnOK->setText(QCoreApplication::translate("AddToolInfoDialog", "\347\241\256\345\256\232", nullptr));
        accelerateRadioButton->setText(QCoreApplication::translate("AddToolInfoDialog", "\346\214\207\345\256\232\350\212\202\347\202\271", nullptr));
        nodeRadioButton->setText(QCoreApplication::translate("AddToolInfoDialog", "\350\256\241\347\256\227\350\212\202\347\202\271", nullptr));
        label_4->setText(QCoreApplication::translate("AddToolInfoDialog", "\345\233\276\346\240\207\350\267\257\345\276\204", nullptr));
        btnChooseImage->setText(QCoreApplication::translate("AddToolInfoDialog", "\351\200\211\346\213\251", nullptr));
        label_2->setText(QCoreApplication::translate("AddToolInfoDialog", "\345\267\245\345\205\267\345\220\215\347\247\260", nullptr));
        label->setText(QCoreApplication::translate("AddToolInfoDialog", "\345\267\245\345\205\267\350\267\257\345\276\204", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AddToolInfoDialog: public Ui_AddToolInfoDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDTOOLINFODIALOG_H
