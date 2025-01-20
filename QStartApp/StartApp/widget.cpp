#include "widget.h"
#include "ui_widget.h"

#include "GifDialog.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    setMaximumWidth(600);
    setMaximumHeight(400);
    setWindowFlags(windowFlags() & ~Qt::WindowMinMaxButtonsHint); // 移除最大最小化按钮
    ui->setupUi(this);

    m_pGifDialog = new GifDialog();
    m_pGifDialog->setTitleText(QString::fromLocal8Bit("正在加载"));
   
    m_pListen = new Listen;
    connect(ui->pushButton, &QPushButton::clicked, this, &Widget::slot_btnOpenExplorer);
    connect(ui->pushButton2, &QPushButton::clicked, this, &Widget::slot_btnAppShow);
}

Widget::~Widget()
{
    m_pListen->CancleResource();
    delete m_pListen;
    delete ui;
}

void Widget::StartProgram(const std::string& strPath, LoadingProgressCallBack callBack)
{
    m_pListen->setSuccessCallBack(callBack);
    int index = strPath.rfind(".");
    std::string suffix = strPath.substr(index + 1, strPath.size());

    auto boundFunction = std::bind([this,suffix,strPath]() {
        if (suffix == "exe")
        {
            m_pListen->startProgram(strPath);
        }
        else if (suffix == "bat")
        {
            m_pListen->startProgramFromBat(strPath);
        }
     });
    std::thread t(boundFunction);
    t.detach(); // 分离线程，主线程不阻塞
}

void Widget::HwndListen()
{
   // m_pListen->hwndListen();
    //  使用 std::bind 创建可调用对象
    auto boundFunction = std::bind(&Listen::hwndListen, m_pListen);
    std::thread t(boundFunction);
    t.detach(); // 分离线程，主线程不阻塞

}

void Widget::InitResource(const std::string& str)
{
    auto boundFunction = std::bind([this,&str]() {
        // 根据字符集调整 userName 的初始化
#ifdef UNICODE
    // 如果使用宽字符集，将 std::string 转换为 std::wstring
        std::wstring wUserName(str.begin(), str.end());
        std::vector<TCHAR> userName(wUserName.begin(), wUserName.end());
        userName.push_back(L'\0'); // 添加终止符
#else
    // 如果使用多字节字符集，直接转换为 char*
        std::vector<TCHAR> userName(str.begin(), str.end());
        userName.push_back('\0'); // 添加终止符
#endif

        //TCHAR userName[] = TEXT("user1");
        TCHAR password[] = TEXT("Atexcel@123");
        TCHAR localDrive[] = TEXT("Y:");  //本地驱动器映射
        TCHAR remotePath[] = TEXT("\\\\192.168.10.240\\share");  // 共享资源的路径

        m_pListen->InitResource(userName.data(), password, localDrive, remotePath);
    });
    std::thread t(boundFunction);
    t.detach(); // 分离线程，主线程不阻塞
}

void Widget::showGifDialog()
{
    if (_t == nullptr)
    {
        m_pGifDialog->showMaximized();
        //m_pGifDialog->show();
        _t = new QTimer(this);
        _t->setTimerType(Qt::PreciseTimer);
        _gifShow = true;
        connect(_t, &QTimer::timeout, this, [this]() {
            if (!_gifShow)
            {
                m_pGifDialog->close();
                _t->stop();
                delete _t;
                _t = nullptr;
            }
        });
        _t->start(100);
    }
}

void Widget::closeGifDialog()
{
    _gifShow = false;
}

void Widget::setCloseCallBack(LoadingProgressCallBack callBack)
{
    m_pListen->setClosCallBack(callBack);
}

void Widget::slot_btnOpenExplorer()
{
    // 打开文件资源管理器，显示计算机（所有驱动器）
    ShellExecute(NULL, "open", "explorer.exe", "::", NULL, SW_SHOW);

    // 打开文件资源管理器，显示C盘根目录
   // ShellExecute(NULL, "open", "explorer.exe", "C:\\", NULL, SW_SHOW);
}

void Widget::slot_btnAppShow()
{
    m_pListen->showProgram();
}