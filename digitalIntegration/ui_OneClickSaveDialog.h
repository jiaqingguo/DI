/********************************************************************************
** Form generated from reading UI file 'OneClickSaveDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ONECLICKSAVEDIALOG_H
#define UI_ONECLICKSAVEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_OneClickSaveDialog
{
public:
    QVBoxLayout *verticalLayout;
    QTableView *tableView;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnOk;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QDialog *OneClickSaveDialog)
    {
        if (OneClickSaveDialog->objectName().isEmpty())
            OneClickSaveDialog->setObjectName(QString::fromUtf8("OneClickSaveDialog"));
        OneClickSaveDialog->resize(530, 301);
        verticalLayout = new QVBoxLayout(OneClickSaveDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        tableView = new QTableView(OneClickSaveDialog);
        tableView->setObjectName(QString::fromUtf8("tableView"));

        verticalLayout->addWidget(tableView);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        btnOk = new QPushButton(OneClickSaveDialog);
        btnOk->setObjectName(QString::fromUtf8("btnOk"));

        horizontalLayout->addWidget(btnOk);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(OneClickSaveDialog);

        QMetaObject::connectSlotsByName(OneClickSaveDialog);
    } // setupUi

    void retranslateUi(QDialog *OneClickSaveDialog)
    {
        OneClickSaveDialog->setWindowTitle(QCoreApplication::translate("OneClickSaveDialog", "\344\270\200\351\224\256\344\277\235\345\255\230", nullptr));
        btnOk->setText(QCoreApplication::translate("OneClickSaveDialog", "\347\241\256\345\256\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class OneClickSaveDialog: public Ui_OneClickSaveDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ONECLICKSAVEDIALOG_H
