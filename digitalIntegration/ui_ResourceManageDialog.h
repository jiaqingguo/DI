/********************************************************************************
** Form generated from reading UI file 'ResourceManageDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RESOURCEMANAGEDIALOG_H
#define UI_RESOURCEMANAGEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ResourceManageDialog
{
public:
    QGridLayout *gridLayout;
    QTabWidget *tabWidget;
    QWidget *tab;
    QGridLayout *gridLayout_2;
    QTableView *tableView;
    QWidget *tab_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QLabel *label;
    QComboBox *comboBox;
    QTabWidget *tabWidgetCurve;
    QWidget *tab_3;
    QWidget *tab_4;

    void setupUi(QDialog *ResourceManageDialog)
    {
        if (ResourceManageDialog->objectName().isEmpty())
            ResourceManageDialog->setObjectName(QString::fromUtf8("ResourceManageDialog"));
        ResourceManageDialog->resize(575, 400);
        gridLayout = new QGridLayout(ResourceManageDialog);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        tabWidget = new QTabWidget(ResourceManageDialog);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setTabBarAutoHide(false);
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        gridLayout_2 = new QGridLayout(tab);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        tableView = new QTableView(tab);
        tableView->setObjectName(QString::fromUtf8("tableView"));

        gridLayout_2->addWidget(tableView, 0, 0, 1, 1);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        verticalLayout = new QVBoxLayout(tab_2);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        label = new QLabel(tab_2);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        comboBox = new QComboBox(tab_2);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        horizontalLayout->addWidget(comboBox);


        verticalLayout->addLayout(horizontalLayout);

        tabWidgetCurve = new QTabWidget(tab_2);
        tabWidgetCurve->setObjectName(QString::fromUtf8("tabWidgetCurve"));
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        tabWidgetCurve->addTab(tab_3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QString::fromUtf8("tab_4"));
        tabWidgetCurve->addTab(tab_4, QString());

        verticalLayout->addWidget(tabWidgetCurve);

        tabWidget->addTab(tab_2, QString());

        gridLayout->addWidget(tabWidget, 0, 0, 1, 1);


        retranslateUi(ResourceManageDialog);

        tabWidget->setCurrentIndex(1);
        tabWidgetCurve->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(ResourceManageDialog);
    } // setupUi

    void retranslateUi(QDialog *ResourceManageDialog)
    {
        ResourceManageDialog->setWindowTitle(QCoreApplication::translate("ResourceManageDialog", "\350\265\204\346\272\220\347\256\241\347\220\206\345\231\250", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("ResourceManageDialog", "\345\210\227\350\241\250", nullptr));
        label->setText(QCoreApplication::translate("ResourceManageDialog", "\344\270\273\346\234\272 \351\200\211\346\213\251:", nullptr));
        tabWidgetCurve->setTabText(tabWidgetCurve->indexOf(tab_3), QCoreApplication::translate("ResourceManageDialog", "Tab 1", nullptr));
        tabWidgetCurve->setTabText(tabWidgetCurve->indexOf(tab_4), QCoreApplication::translate("ResourceManageDialog", "Tab 2", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("ResourceManageDialog", "\346\233\262\347\272\277", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ResourceManageDialog: public Ui_ResourceManageDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RESOURCEMANAGEDIALOG_H
