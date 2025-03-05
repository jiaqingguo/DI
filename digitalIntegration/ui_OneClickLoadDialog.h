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
    QHBoxLayout *horizontalLayout_9;
    QTableView *tableViewOneLoad;
    QVBoxLayout *verticalLayout_9;
    QPushButton *btnAdd;
    QPushButton *btnDel;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnOk;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QDialog *OneClickLoadDialog)
    {
        if (OneClickLoadDialog->objectName().isEmpty())
            OneClickLoadDialog->setObjectName(QString::fromUtf8("OneClickLoadDialog"));
        OneClickLoadDialog->resize(452, 296);
        verticalLayout = new QVBoxLayout(OneClickLoadDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(-1, -1, 0, 9);
        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        horizontalLayout_9->setContentsMargins(9, 9, 9, 5);
        tableViewOneLoad = new QTableView(OneClickLoadDialog);
        tableViewOneLoad->setObjectName(QString::fromUtf8("tableViewOneLoad"));

        horizontalLayout_9->addWidget(tableViewOneLoad);

        verticalLayout_9 = new QVBoxLayout();
        verticalLayout_9->setSpacing(15);
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        verticalLayout_9->setContentsMargins(0, 5, 0, 0);
        btnAdd = new QPushButton(OneClickLoadDialog);
        btnAdd->setObjectName(QString::fromUtf8("btnAdd"));
        btnAdd->setMinimumSize(QSize(90, 30));

        verticalLayout_9->addWidget(btnAdd);

        btnDel = new QPushButton(OneClickLoadDialog);
        btnDel->setObjectName(QString::fromUtf8("btnDel"));
        btnDel->setMinimumSize(QSize(90, 30));

        verticalLayout_9->addWidget(btnDel);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_9->addItem(verticalSpacer);


        horizontalLayout_9->addLayout(verticalLayout_9);


        verticalLayout->addLayout(horizontalLayout_9);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 5);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        btnOk = new QPushButton(OneClickLoadDialog);
        btnOk->setObjectName(QString::fromUtf8("btnOk"));
        btnOk->setMinimumSize(QSize(120, 50));

        horizontalLayout->addWidget(btnOk);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(OneClickLoadDialog);

        QMetaObject::connectSlotsByName(OneClickLoadDialog);
    } // setupUi

    void retranslateUi(QDialog *OneClickLoadDialog)
    {
        OneClickLoadDialog->setWindowTitle(QCoreApplication::translate("OneClickLoadDialog", "\344\270\200\351\224\256\345\212\240\350\275\275", nullptr));
        btnAdd->setText(QCoreApplication::translate("OneClickLoadDialog", "\345\242\236\345\212\240", nullptr));
        btnDel->setText(QCoreApplication::translate("OneClickLoadDialog", "\345\210\240\351\231\244", nullptr));
        btnOk->setText(QCoreApplication::translate("OneClickLoadDialog", "\345\212\240\350\275\275", nullptr));
    } // retranslateUi

};

namespace Ui {
    class OneClickLoadDialog: public Ui_OneClickLoadDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ONECLICKLOADDIALOG_H
