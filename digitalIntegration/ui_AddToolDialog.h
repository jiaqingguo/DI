/********************************************************************************
** Form generated from reading UI file 'AddToolDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDTOOLDIALOG_H
#define UI_ADDTOOLDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_AddToolDialog
{
public:
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QComboBox *comboBoxDisplayMode;
    QLabel *label;
    QComboBox *comboBoxToolNames;
    QComboBox *comboBoxHost;
    QLabel *label_5;
    QLabel *label_3;
    QLabel *label_2;
    QLineEdit *lineEditTabName;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnAdd;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QDialog *AddToolDialog)
    {
        if (AddToolDialog->objectName().isEmpty())
            AddToolDialog->setObjectName(QString::fromUtf8("AddToolDialog"));
        AddToolDialog->resize(269, 214);
        verticalLayout = new QVBoxLayout(AddToolDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(9, 9, 9, 9);
        comboBoxDisplayMode = new QComboBox(AddToolDialog);
        comboBoxDisplayMode->addItem(QString());
        comboBoxDisplayMode->addItem(QString());
        comboBoxDisplayMode->setObjectName(QString::fromUtf8("comboBoxDisplayMode"));
        comboBoxDisplayMode->setMinimumSize(QSize(180, 25));
        QFont font;
        font.setFamily(QString::fromUtf8("\351\273\221\344\275\223"));
        font.setPointSize(11);
        comboBoxDisplayMode->setFont(font);

        gridLayout->addWidget(comboBoxDisplayMode, 1, 1, 1, 2);

        label = new QLabel(AddToolDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setFont(font);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        comboBoxToolNames = new QComboBox(AddToolDialog);
        comboBoxToolNames->setObjectName(QString::fromUtf8("comboBoxToolNames"));
        comboBoxToolNames->setMinimumSize(QSize(180, 25));
        comboBoxToolNames->setFont(font);

        gridLayout->addWidget(comboBoxToolNames, 2, 1, 1, 2);

        comboBoxHost = new QComboBox(AddToolDialog);
        comboBoxHost->setObjectName(QString::fromUtf8("comboBoxHost"));
        comboBoxHost->setMinimumSize(QSize(180, 25));
        comboBoxHost->setFont(font);

        gridLayout->addWidget(comboBoxHost, 3, 1, 1, 2);

        label_5 = new QLabel(AddToolDialog);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setFont(font);

        gridLayout->addWidget(label_5, 3, 0, 1, 1);

        label_3 = new QLabel(AddToolDialog);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setMinimumSize(QSize(65, 0));
        label_3->setMaximumSize(QSize(65, 16777215));
        label_3->setFont(font);

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        label_2 = new QLabel(AddToolDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setMinimumSize(QSize(65, 0));
        label_2->setMaximumSize(QSize(65, 16777215));
        label_2->setFont(font);

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        lineEditTabName = new QLineEdit(AddToolDialog);
        lineEditTabName->setObjectName(QString::fromUtf8("lineEditTabName"));
        lineEditTabName->setMinimumSize(QSize(180, 25));
        lineEditTabName->setFont(font);

        gridLayout->addWidget(lineEditTabName, 0, 1, 1, 2);


        verticalLayout->addLayout(gridLayout);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(9, 9, 9, 9);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        btnAdd = new QPushButton(AddToolDialog);
        btnAdd->setObjectName(QString::fromUtf8("btnAdd"));
        btnAdd->setMinimumSize(QSize(100, 35));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\351\273\221\344\275\223"));
        font1.setPointSize(14);
        btnAdd->setFont(font1);

        horizontalLayout->addWidget(btnAdd);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(AddToolDialog);

        QMetaObject::connectSlotsByName(AddToolDialog);
    } // setupUi

    void retranslateUi(QDialog *AddToolDialog)
    {
        AddToolDialog->setWindowTitle(QCoreApplication::translate("AddToolDialog", "\346\226\260\345\242\236\345\267\245\345\205\267\347\224\273\351\235\242", nullptr));
        comboBoxDisplayMode->setItemText(0, QCoreApplication::translate("AddToolDialog", "Tab\351\241\265", nullptr));
        comboBoxDisplayMode->setItemText(1, QCoreApplication::translate("AddToolDialog", "\345\274\271\347\252\227", nullptr));

        label->setText(QCoreApplication::translate("AddToolDialog", "<html><head/><body><p><span style=\" color:#808080;\">\346\240\207\347\255\276\345\220\215\347\247\260</span></p></body></html>", nullptr));
        label_5->setText(QCoreApplication::translate("AddToolDialog", "<html><head/><body><p><span style=\" color:#808080;\">\345\220\257\345\212\250\344\270\273\346\234\272</span></p></body></html>", nullptr));
        label_3->setText(QCoreApplication::translate("AddToolDialog", "<html><head/><body><p><span style=\" color:#808080;\">\345\267\245\345\205\267\345\220\215\347\247\260</span></p></body></html>", nullptr));
        label_2->setText(QCoreApplication::translate("AddToolDialog", "<html><head/><body><p><span style=\" color:#808080;\">\345\261\225\347\244\272\346\226\271\345\274\217</span></p></body></html>", nullptr));
        btnAdd->setText(QCoreApplication::translate("AddToolDialog", "\346\226\260\345\242\236", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AddToolDialog: public Ui_AddToolDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDTOOLDIALOG_H
