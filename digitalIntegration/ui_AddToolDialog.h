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
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_AddToolDialog
{
public:
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *lineEditTabName;
    QLabel *label_4;
    QLabel *label;
    QComboBox *comboBoxToolNames;
    QComboBox *comboBoxDisplayMode;
    QCheckBox *allocationAllocation;
    QCheckBox *checkBoxNoAllocate;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QTableView *tableViewIpSet;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnAdd;
    QSpacerItem *horizontalSpacer_2;
    QButtonGroup *buttonGroup;

    void setupUi(QDialog *AddToolDialog)
    {
        if (AddToolDialog->objectName().isEmpty())
            AddToolDialog->setObjectName(QString::fromUtf8("AddToolDialog"));
        AddToolDialog->resize(447, 360);
        verticalLayout = new QVBoxLayout(AddToolDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_2 = new QLabel(AddToolDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setMinimumSize(QSize(65, 0));
        label_2->setMaximumSize(QSize(65, 16777215));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        label_3 = new QLabel(AddToolDialog);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setMinimumSize(QSize(65, 0));
        label_3->setMaximumSize(QSize(65, 16777215));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        lineEditTabName = new QLineEdit(AddToolDialog);
        lineEditTabName->setObjectName(QString::fromUtf8("lineEditTabName"));

        gridLayout->addWidget(lineEditTabName, 0, 1, 1, 3);

        label_4 = new QLabel(AddToolDialog);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setMinimumSize(QSize(65, 0));
        label_4->setMaximumSize(QSize(65, 16777215));

        gridLayout->addWidget(label_4, 3, 0, 1, 1);

        label = new QLabel(AddToolDialog);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        comboBoxToolNames = new QComboBox(AddToolDialog);
        comboBoxToolNames->setObjectName(QString::fromUtf8("comboBoxToolNames"));

        gridLayout->addWidget(comboBoxToolNames, 2, 1, 1, 2);

        comboBoxDisplayMode = new QComboBox(AddToolDialog);
        comboBoxDisplayMode->addItem(QString());
        comboBoxDisplayMode->addItem(QString());
        comboBoxDisplayMode->setObjectName(QString::fromUtf8("comboBoxDisplayMode"));

        gridLayout->addWidget(comboBoxDisplayMode, 1, 1, 1, 2);

        allocationAllocation = new QCheckBox(AddToolDialog);
        buttonGroup = new QButtonGroup(AddToolDialog);
        buttonGroup->setObjectName(QString::fromUtf8("buttonGroup"));
        buttonGroup->addButton(allocationAllocation);
        allocationAllocation->setObjectName(QString::fromUtf8("allocationAllocation"));

        gridLayout->addWidget(allocationAllocation, 3, 1, 1, 1);

        checkBoxNoAllocate = new QCheckBox(AddToolDialog);
        buttonGroup->addButton(checkBoxNoAllocate);
        checkBoxNoAllocate->setObjectName(QString::fromUtf8("checkBoxNoAllocate"));

        gridLayout->addWidget(checkBoxNoAllocate, 3, 2, 1, 1);


        verticalLayout->addLayout(gridLayout);

        groupBox = new QGroupBox(AddToolDialog);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(-1, 0, -1, 0);
        tableViewIpSet = new QTableView(groupBox);
        tableViewIpSet->setObjectName(QString::fromUtf8("tableViewIpSet"));

        gridLayout_2->addWidget(tableViewIpSet, 0, 0, 1, 1);


        verticalLayout->addWidget(groupBox);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        btnAdd = new QPushButton(AddToolDialog);
        btnAdd->setObjectName(QString::fromUtf8("btnAdd"));

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
        label_2->setText(QCoreApplication::translate("AddToolDialog", "\345\261\225\347\244\272\346\226\271\345\274\217\357\274\232", nullptr));
        label_3->setText(QCoreApplication::translate("AddToolDialog", "\345\267\245\345\205\267\345\220\215\347\247\260\357\274\232", nullptr));
        label_4->setText(QCoreApplication::translate("AddToolDialog", "\347\275\221\347\273\234\345\210\206\351\205\215:", nullptr));
        label->setText(QCoreApplication::translate("AddToolDialog", "\346\240\207\347\255\276\345\220\215\347\247\260\357\274\232", nullptr));
        comboBoxDisplayMode->setItemText(0, QCoreApplication::translate("AddToolDialog", "Tab\351\241\265", nullptr));
        comboBoxDisplayMode->setItemText(1, QCoreApplication::translate("AddToolDialog", "\345\274\271\347\252\227", nullptr));

        allocationAllocation->setText(QCoreApplication::translate("AddToolDialog", "\345\210\206\351\205\215", nullptr));
        checkBoxNoAllocate->setText(QCoreApplication::translate("AddToolDialog", "\344\270\215\345\210\206\351\205\215", nullptr));
        groupBox->setTitle(QCoreApplication::translate("AddToolDialog", "ip\350\256\276\347\275\256\357\274\232", nullptr));
        btnAdd->setText(QCoreApplication::translate("AddToolDialog", "\346\226\260\345\242\236", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AddToolDialog: public Ui_AddToolDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDTOOLDIALOG_H
