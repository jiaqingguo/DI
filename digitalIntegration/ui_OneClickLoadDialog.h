/********************************************************************************
** Form generated from reading UI file 'OneClickLoadDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ONECLICKLOADDIALOG_H
#define UI_ONECLICKLOADDIALOG_H

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

class Ui_OneClickLoadDialog
{
public:
    QVBoxLayout *verticalLayout;
    QTableView *tableView;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnOK;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QDialog *OneClickLoadDialog)
    {
        if (OneClickLoadDialog->objectName().isEmpty())
            OneClickLoadDialog->setObjectName(QString::fromUtf8("OneClickLoadDialog"));
        OneClickLoadDialog->resize(532, 292);
        verticalLayout = new QVBoxLayout(OneClickLoadDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        tableView = new QTableView(OneClickLoadDialog);
        tableView->setObjectName(QString::fromUtf8("tableView"));

        verticalLayout->addWidget(tableView);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        btnOK = new QPushButton(OneClickLoadDialog);
        btnOK->setObjectName(QString::fromUtf8("btnOK"));

        horizontalLayout->addWidget(btnOK);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(OneClickLoadDialog);

        QMetaObject::connectSlotsByName(OneClickLoadDialog);
    } // setupUi

    void retranslateUi(QDialog *OneClickLoadDialog)
    {
        OneClickLoadDialog->setWindowTitle(QCoreApplication::translate("OneClickLoadDialog", "\344\270\200\351\224\256\345\212\240\350\275\275", nullptr));
        btnOK->setText(QCoreApplication::translate("OneClickLoadDialog", "\347\241\256\345\256\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class OneClickLoadDialog: public Ui_OneClickLoadDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ONECLICKLOADDIALOG_H
