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
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_OneClickSaveDialog
{
public:
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QTableView *tableView;
    QVBoxLayout *verticalLayout;
    QPushButton *btnAdd;
    QPushButton *btnDel;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QLineEdit *lineEditDirPath;
    QPushButton *btnPaste;
    QLabel *label;
    QLineEdit *lineEditZipName;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnOk;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QDialog *OneClickSaveDialog)
    {
        if (OneClickSaveDialog->objectName().isEmpty())
            OneClickSaveDialog->setObjectName(QString::fromUtf8("OneClickSaveDialog"));
        OneClickSaveDialog->resize(530, 301);
        verticalLayout_2 = new QVBoxLayout(OneClickSaveDialog);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        tableView = new QTableView(OneClickSaveDialog);
        tableView->setObjectName(QString::fromUtf8("tableView"));

        horizontalLayout_2->addWidget(tableView);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        btnAdd = new QPushButton(OneClickSaveDialog);
        btnAdd->setObjectName(QString::fromUtf8("btnAdd"));

        verticalLayout->addWidget(btnAdd);

        btnDel = new QPushButton(OneClickSaveDialog);
        btnDel->setObjectName(QString::fromUtf8("btnDel"));

        verticalLayout->addWidget(btnDel);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        horizontalLayout_2->addLayout(verticalLayout);


        verticalLayout_2->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_2 = new QLabel(OneClickSaveDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_3->addWidget(label_2);

        lineEditDirPath = new QLineEdit(OneClickSaveDialog);
        lineEditDirPath->setObjectName(QString::fromUtf8("lineEditDirPath"));

        horizontalLayout_3->addWidget(lineEditDirPath);

        btnPaste = new QPushButton(OneClickSaveDialog);
        btnPaste->setObjectName(QString::fromUtf8("btnPaste"));

        horizontalLayout_3->addWidget(btnPaste);

        label = new QLabel(OneClickSaveDialog);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_3->addWidget(label);

        lineEditZipName = new QLineEdit(OneClickSaveDialog);
        lineEditZipName->setObjectName(QString::fromUtf8("lineEditZipName"));

        horizontalLayout_3->addWidget(lineEditZipName);


        verticalLayout_2->addLayout(horizontalLayout_3);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        btnOk = new QPushButton(OneClickSaveDialog);
        btnOk->setObjectName(QString::fromUtf8("btnOk"));

        horizontalLayout->addWidget(btnOk);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout_2->addLayout(horizontalLayout);


        retranslateUi(OneClickSaveDialog);

        QMetaObject::connectSlotsByName(OneClickSaveDialog);
    } // setupUi

    void retranslateUi(QDialog *OneClickSaveDialog)
    {
        OneClickSaveDialog->setWindowTitle(QCoreApplication::translate("OneClickSaveDialog", "\344\270\200\351\224\256\344\277\235\345\255\230", nullptr));
        btnAdd->setText(QCoreApplication::translate("OneClickSaveDialog", "\345\242\236\345\212\240", nullptr));
        btnDel->setText(QCoreApplication::translate("OneClickSaveDialog", "\345\210\240\351\231\244", nullptr));
        label_2->setText(QCoreApplication::translate("OneClickSaveDialog", "\345\216\213\347\274\251\350\267\257\345\276\204\357\274\232", nullptr));
        btnPaste->setText(QCoreApplication::translate("OneClickSaveDialog", "\347\262\230\350\264\264\347\233\256\345\275\225", nullptr));
        label->setText(QCoreApplication::translate("OneClickSaveDialog", "\345\216\213\347\274\251\345\220\215\347\247\260\357\274\232", nullptr));
        btnOk->setText(QCoreApplication::translate("OneClickSaveDialog", "\347\241\256\345\256\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class OneClickSaveDialog: public Ui_OneClickSaveDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ONECLICKSAVEDIALOG_H
