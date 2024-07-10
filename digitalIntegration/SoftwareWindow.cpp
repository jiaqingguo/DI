#include "SoftwareWindow.h"
#include "ui_SoftwareWindow.h"

#include "windows.h"

SoftwareWindow::SoftwareWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SoftwareWindow)
{
    //ui->setupUi(this);
    //WId winId = (WId)FindWindow(NULL, L"QQ");
    //QWindow* window = QWindow::fromWinId(winId);
    //QWidget* widget = QWidget::createWindowContainer(window);
    //widget->show();
}

SoftwareWindow::~SoftwareWindow()
{
    delete ui;
}
