/********************************************************************************
** Form generated from reading UI file 'SoftwareWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SOFTWAREWINDOW_H
#define UI_SOFTWAREWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SoftwareWindow
{
public:

    void setupUi(QWidget *SoftwareWindow)
    {
        if (SoftwareWindow->objectName().isEmpty())
            SoftwareWindow->setObjectName(QString::fromUtf8("SoftwareWindow"));
        SoftwareWindow->resize(626, 513);

        retranslateUi(SoftwareWindow);

        QMetaObject::connectSlotsByName(SoftwareWindow);
    } // setupUi

    void retranslateUi(QWidget *SoftwareWindow)
    {
        SoftwareWindow->setWindowTitle(QCoreApplication::translate("SoftwareWindow", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SoftwareWindow: public Ui_SoftwareWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SOFTWAREWINDOW_H
