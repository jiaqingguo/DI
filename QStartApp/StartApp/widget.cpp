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
    m_pListen->CancleResource();
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

void Widget::InitResource(const std::string& str)
{

    // �����ַ������� userName �ĳ�ʼ��
#ifdef UNICODE
    // ���ʹ�ÿ��ַ������� std::string ת��Ϊ std::wstring
    std::wstring wUserName(str.begin(), str.end());
    std::vector<TCHAR> userName(wUserName.begin(), wUserName.end());
    userName.push_back(L'\0'); // �����ֹ��
#else
    // ���ʹ�ö��ֽ��ַ�����ֱ��ת��Ϊ char*
    std::vector<TCHAR> userName(str.begin(), str.end());
    userName.push_back('\0'); // �����ֹ��
#endif

    //TCHAR userName[] = TEXT("user1");
    TCHAR password[] = TEXT("123456");
    TCHAR localDrive[] = TEXT("Y:");  //����������ӳ��
    TCHAR remotePath[] = TEXT("\\\\192.168.10.240\\share");  // ������Դ��·��
    //TCHAR remotePath[] = TEXT("\\\\192.168.10.3\\admin �������");  // ������Դ��·��
  //  InitResource(userName, password, localDrive, remotePath);
    m_pListen->InitResource(userName.data(), password, localDrive, remotePath);
}

void Widget::slot_btnOpenExplorer()
{
    // ���ļ���Դ����������ʾ�������������������
    ShellExecute(NULL, "open", "explorer.exe", "::", NULL, SW_SHOW);

    // ���ļ���Դ����������ʾC�̸�Ŀ¼
   // ShellExecute(NULL, "open", "explorer.exe", "C:\\", NULL, SW_SHOW);
}