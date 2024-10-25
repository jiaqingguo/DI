#include "widget.h"

#include <QApplication>
#include <windows.h>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Widget w;
    w.show();

    //w.hide();//窗口的隐藏

    w.showMinimized();//窗口的最小化
    return a.exec();
}
