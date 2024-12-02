#include "widget.h"
#include "ui_widget.h"

#include "Listen.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    m_pListen = new Listen;
    connect(ui->pushButton, &QPushButton::clicked, this, &Widget::slot_btnOpenExplorer);
  
}

Widget::~Widget()
{
    delete m_pListen;
    delete ui;
}

void Widget::StartProgram(const std::string& strPath)
{
    m_pListen->startProgram(strPath);
}

void Widget::HwndListen()
{
   // m_pListen->hwndListen();
    //  使用 std::bind 创建可调用对象
    auto boundFunction = std::bind(&Listen::hwndListen, m_pListen);
    std::thread t(boundFunction);
    t.detach(); // 分离线程，主线程不阻塞

}

void Widget::slot_btnOpenExplorer()
{
    // 打开文件资源管理器，显示计算机（所有驱动器）
    ShellExecute(NULL, "open", "explorer.exe", "::", NULL, SW_SHOW);

    // 打开文件资源管理器，显示C盘根目录
   // ShellExecute(NULL, "open", "explorer.exe", "C:\\", NULL, SW_SHOW);
}