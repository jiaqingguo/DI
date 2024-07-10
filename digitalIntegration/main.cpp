
#include <QApplication>

#include <QtWidgets/QApplication>
#include <QApplication>
#include <QVBoxLayout>
#include <QLabel>
#include <QWindow>


#include "mainwindow.h"


#include "databaseDI.h"
#include "LoginDialog.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

   /* WId winId = (WId)FindWindow(NULL, L"QQ");
    QWindow* window = QWindow::fromWinId(winId);
    QWidget* widget = QWidget::createWindowContainer(window);
    widget->show();*/
    db::databaseDI::Instance().open();
    MainWindow w;
  //  w.show();

  /*  db::databaseDI::Instance().open();
    LoginDialog loginDialog;
    if (loginDialog.exec() == QDialog::Accepted)
    {
        MainWindow w;
        w.showMaximized();
    }*/
    return a.exec();
}
