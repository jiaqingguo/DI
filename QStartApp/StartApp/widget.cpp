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
    //  ʹ�� std::bind �����ɵ��ö���
    auto boundFunction = std::bind(&Listen::hwndListen, m_pListen);
    std::thread t(boundFunction);
    t.detach(); // �����̣߳����̲߳�����

}

void Widget::slot_btnOpenExplorer()
{
    // ���ļ���Դ����������ʾ�������������������
    ShellExecute(NULL, "open", "explorer.exe", "::", NULL, SW_SHOW);

    // ���ļ���Դ����������ʾC�̸�Ŀ¼
   // ShellExecute(NULL, "open", "explorer.exe", "C:\\", NULL, SW_SHOW);
}