#include "widget.h"
#include "ui_widget.h"

#include "GifDialog.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
	ui->setupUi(this);
    //setMaximumWidth(600);
    //setMaximumHeight(400);
	
    setWindowFlags(windowFlags() & ~Qt::WindowMinMaxButtonsHint); // 移除最大最小化按钮
	// 取消标题栏（无边框窗口）
	setWindowFlags(Qt::FramelessWindowHint);
	this->showMaximized();
	
	this->setAttribute(Qt::WA_StyledBackground, true);
    m_pGifDialog = new GifDialog();
    m_pGifDialog->setTitleText(QString::fromLocal8Bit("正在加载"));
   
    m_pListen = new Listen;
	ui->pushButton->hide();
	ui->pushButton2->hide();
    //connect(ui->pushButton, &QPushButton::clicked, this, &Widget::slot_btnOpenExplorer);
    //connect(ui->pushButton2, &QPushButton::clicked, this, &Widget::slot_btnAppShow);


    m_Menu = new QMenu();

    // 添加菜单项
    QAction* action1 = m_Menu->addAction(QString::fromLocal8Bit("保存"));
    QAction* action2 = m_Menu->addAction(QString::fromLocal8Bit("显示软件"));

    // 创建带图标的 Action
    //QAction *copyAction = new QAction(QIcon(":/image/save.png"), QString::fromLocal8Bit("保存"), this);
    //QAction *pasteAction = new QAction(QIcon(":/image/label.png"), QString::fromLocal8Bit("显示软件"), this);
    /*m_Menu->addAction(copyAction);
    m_Menu->addAction(pasteAction);*/

    // 连接菜单项的信号槽
    connect(action1, &QAction::triggered, this, &Widget::slot_btnOpenExplorer);
    connect(action2, &QAction::triggered, this, &Widget::slot_btnAppShow);

	this->setStyleSheet(
		"QWidget#Widget{"
		"    background-image: url(:/image/Logo_background.png);"
		"    background-position: center;"
		"    background-size: cover;"
		"    border-image: url(:/image/Mainwindow-background.jpg) 0 stretch;"
		"    border-top: 3px solid #0078d7;"
		"    border-left: none;"
		"    border-right: none;"
		"    border-bottom: none;"
		"}"
	);
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

void Widget::contextMenuEvent(QContextMenuEvent *event)
{
	

	// 在鼠标位置弹出菜单
	m_Menu->exec(event->globalPos());
}
//重写paintEvent使两张图片同时加载
void Widget::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);

	// 绘制边框图
	QPixmap borderPixmap(":/image/Mainwindow-background.jpg");
	painter.drawPixmap(rect(), borderPixmap);

	// 绘制顶部边框
	painter.setPen(QPen(QColor("#0078d7"), 3));
	painter.drawLine(0, 0, width(), 0);

	// 绘制背景图
	QPixmap bgPixmap(":/image/Logo_background.png");
	QRect bgRect = bgPixmap.rect();
	bgRect.moveCenter(rect().center());
	painter.drawPixmap(bgRect, bgPixmap);

	QWidget::paintEvent(event);
}