#pragma comment  (lib, "User32.lib")
#include "fingerDlg.h"

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "globel.h"
#include "LoginDialog.h"
#include "RegisterDialog.h"
#include "ResourceManageDialog.h"
#include "InformationConfihurationDialog.h"
#include "DataManageDialog.h"
#include "FilemangageDialog.h"
#include "ApprovalProgressDialog.h"
#include "AddToolDialog.h"
#include "OneClickSaveDialog.h"
#include "OneClickLoadDialog.h"
#include "databaseDI.h"
#include "CustomButton.h"
#include "common.h"
#include "GifDialog.h"
#include "CtrlNetwork.h"

#include <QtWidgets/QApplication>
#include <QApplication>
#include <QVBoxLayout>
#include <QLabel>
#include <qwidget.h>
#include <QtWebEngineWidgets>
#include <QAxWidget>
#include <QAxObject>
#include "windows.h"

#include <thread>
#include <functional>

EmbeddedWidget::EmbeddedWidget(HWND hwnd, QWidget* parent) : QWidget(parent), m_hwnd(hwnd) {
        // 将原生窗口嵌入到 Qt 的 QWidget 中
        m_windowContainer = QWidget::createWindowContainer(QWindow::fromWinId((WId)m_hwnd), this);
        m_windowContainer->setFocusPolicy(Qt::StrongFocus);  // 确保嵌入窗口可以获取焦点

        // 调整原生窗口大小，使其铺满 QWidget
        adjustEmbeddedWindowSize();
    }

    // 调整嵌入窗口的大小为 QWidget 的大小
void EmbeddedWidget::adjustEmbeddedWindowSize() 
{
    if (m_hwnd) {
        // 获取 QWidget 的大小
        QRect geometry = this->geometry();
        int width = geometry.width();
        int height = geometry.height();

        // 调整外部窗口的大小和位置
        SetWindowPos(m_hwnd, HWND_TOP, 0, 0, width, height, SWP_NOZORDER | SWP_SHOWWINDOW);
    }
}


    // 重写 resizeEvent，以防 QWidget 的大小改变时需要重新调整外部窗口的大小
void EmbeddedWidget::resizeEvent(QResizeEvent* event)  {
    QWidget::resizeEvent(event);
    adjustEmbeddedWindowSize();
}

//CWidget::CWidget(HWND hwnd, QWidget* parent) : QWidget(parent), m_hwnd(hwnd) {
//    // 将原生窗口嵌入到 Qt 的 QWidget 中
//   QWindow *window= QWindow::fromWinId((WId)m_hwnd);
//
//   this->resize(window->width(), window->height());
//    m_windowContainer = QWidget::createWindowContainer(window);
//    m_windowContainer->setFocusPolicy(Qt::StrongFocus);  // 确保嵌入窗口可以获取焦点
//    
//    QGridLayout* layout = new QGridLayout;
//    layout->addWidget(m_windowContainer);
//    this->setLayout(layout);
//    
//}
//void CWidget::mousePressEvent(QMouseEvent* event)
//{
//   
//        // 将鼠标点击的事件位置转换为全局坐标
//        QPoint globalPos = event->globalPos();
//
//        // 将全局坐标转换为容器内的坐标
//        QPoint localPos = this->mapFromGlobal(globalPos);
//
//        // 发送消息到原生窗口, 这里使用 SendMessage 函数
//        SendMessage((HWND)this->winId(), WM_LBUTTONDOWN, MK_LBUTTON, MAKELPARAM(localPos.x(), localPos.y()));
//    
//    QWidget::mousePressEvent(event);
//
//}
MainWindow* g_pMainWindow = NULL;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    g_pMainWindow = this;

    setWindowTitle(GBK_STRING("数字样机硬件一体化平台"));
    setWindowIcon(QIcon(":/image/tubiao.png"));
    QString command = "cmdkey /add:192.168.1.247 /user:Administrator /pass:Ate123";

    // 创建 QProcess 对象
    QProcess process;

    // 启动 cmd 进程并执行命令
    process.start("cmd.exe", QStringList() << "/C" << command);

    // 等待命令执行完成
    if (process.waitForFinished())
    {
        // 获取命令输出（用于调试或查看结果）
        QString output = process.readAllStandardOutput();
        QString error = process.readAllStandardError();

        // 打印输出到控制台
        qDebug() << "Output:" << output;
        qDebug() << "Error:" << error;
    }
    else
    {
        qDebug() << "Process failed to start or execute.";
    }
    // qss文件监控类
    m_pQssAutoLoader = new QssAutoLoader;
    QString strQssPath = QApplication::applicationDirPath() + "/qss/default.qss";
    strQssPath.replace("/", "\\\\");
    m_pQssAutoLoader->setAutoloadQss(strQssPath);

	initInitface();

    QString target = "\\\\192.168.0.250\\"; // 实际路径
    QString username = "share"; // 实际用户名
    QString password = "Share123"; // 实际密码

    common::addNetworkCredential(target, username, password);

   
}


MainWindow::~MainWindow()
{
    int loginStatus = 0;
    int userId = m_LoginDialog->GetUserID();
    db::databaseDI::Instance().update_user_LoginStatus(userId, loginStatus);

    /*if (!db::databaseDI::Instance().updata_ipusername(m_LoginDialog->GetUser().toStdString()))
        return;*/

    if (!db::databaseDI::Instance().update_ip_all_status())
        return;

    if (m_LoginDialog != nullptr)
        delete m_LoginDialog;
    if (m_RegisterDialog != nullptr)
        delete m_RegisterDialog;
    
    if (m_ResourceManageDialog != nullptr)
        delete m_ResourceManageDialog;
    if (m_DataManageDialog != nullptr)
        delete m_DataManageDialog;
    if (m_InforConfihurationDialog != nullptr)
        delete m_InforConfihurationDialog;
    if (m_ApprovalProgressDialog != nullptr)
        delete m_ApprovalProgressDialog; 
    if (m_FilemangageDialog != nullptr)
        delete m_FilemangageDialog;
    delete ui;
}

void MainWindow::initInitface()
{
	/*this->m_fingerDlg = new fingerDlg();
	this->m_fingerDlg->finger_init();
	connect(this->m_fingerDlg, &fingerDlg::login_succ, this, &MainWindow::slot_login_succ);*/


    m_LoginDialog = new LoginDialog(this);
  
    m_GifDialog = new GifDialog;
    
    m_RegisterDialog = new RegisterDialog(this);

    m_ResourceManageDialog = new ResourceManageDialog(this);

    m_InforConfihurationDialog = new InformationConfihurationDialog(this);
    connect(m_InforConfihurationDialog, &InformationConfihurationDialog::signal_updateToolIcon, this, &MainWindow::slot_updateModuleToolIcon);

    m_DataManageDialog = new DataManageDialog(this);

    m_FilemangageDialog = new FilemangageDialog(this);
  
    m_ApprovalProgressDialog = new ApprovalProgressDialog(this);

    m_OneClickLoadDialog = new OneClickLoadDialog(this);

    m_OneClickSaveDialog = new OneClickSaveDialog(this);

    ui->btnFunction->setCheckable(true);
    ui->btnModule1->setCheckable(true);
    ui->btnModule2->setCheckable(true);
    ui->btnModule3->setCheckable(true);
    ui->btnModule4->setCheckable(true);

    ui->btnFunction->setChecked(true);
    ui->stackedWidget->setCurrentIndex(0);

    connect(ui->btnFunction, &QPushButton::clicked, [this]() {
        ui->stackedWidget->setCurrentIndex(0);
        });
    connect(ui->btnModule1, &QPushButton::clicked, [this]() {
        ui->stackedWidget->setCurrentIndex(1);
		updateModuleToolIcon(1);
        });
    connect(ui->btnModule2, &QPushButton::clicked, [this]() {
        ui->stackedWidget->setCurrentIndex(2);
		updateModuleToolIcon(2);
        });
    connect(ui->btnModule3, &QPushButton::clicked, [this]() {
        ui->stackedWidget->setCurrentIndex(3);
		updateModuleToolIcon(3);
        });
    connect(ui->btnModule4, &QPushButton::clicked, [this]() {
        ui->stackedWidget->setCurrentIndex(4);
		updateModuleToolIcon(4);
        });

    ui->btnResourceManage->setCheckable(true);
    ui->btnInformationConfihuration->setCheckable(true);
    ui->btnDataManage->setCheckable(true);
    ui->btnApprovalProgress->setCheckable(true);
    connect(ui->btnResourceManage, &QPushButton::clicked, this, &MainWindow::slot_btnResourceManageClicked);
    connect(ui->btnInformationConfihuration, &QPushButton::clicked, this, &MainWindow::slot_btnInformationConfihurationClicked);
    connect(ui->btnDataManage, &QPushButton::clicked, this, &MainWindow::slot_btnDataManageClicked);
    connect(ui->btnApprovalProgress, &QPushButton::clicked, this, &MainWindow::slot_btnApprovalProgressClicked);

    // 初始化模块1-4界面;
    ui->tabWidgetModulel1->removeTab(1);
    ui->tabWidgetModulel2->removeTab(1);
    ui->tabWidgetModulel3->removeTab(1);
    ui->tabWidgetModulel4->removeTab(1);
    ui->btnAddTab1->setProperty("module", 1);
    ui->btnAddTab2->setProperty("module", 2);
    ui->btnAddTab3->setProperty("module", 3);
    ui->btnAddTab4->setProperty("module", 4);
    connect(ui->btnAddTab1, &QPushButton::clicked, this, &MainWindow::slot_btnAddToolTab);
    connect(ui->btnAddTab2, &QPushButton::clicked, this, &MainWindow::slot_btnAddToolTab);
    connect(ui->btnAddTab3, &QPushButton::clicked, this, &MainWindow::slot_btnAddToolTab);
    connect(ui->btnAddTab4, &QPushButton::clicked, this, &MainWindow::slot_btnAddToolTab);

    ui->btnM1Load->setCheckable(true);
    ui->btnM2Load->setCheckable(true);
    ui->btnM3Load->setCheckable(true);
    ui->btnM4Load->setCheckable(true);
    ui->btnM1Load->setProperty("module", 1);
    ui->btnM2Load->setProperty("module", 2);
    ui->btnM3Load->setProperty("module", 3);
    ui->btnM4Load->setProperty("module", 4);
    ui->btnM1Save->setCheckable(true);
    ui->btnM2Save->setCheckable(true);
    ui->btnM3Save->setCheckable(true);
    ui->btnM4Save->setCheckable(true);
    ui->btnM1Save->setProperty("module", 1);
    ui->btnM2Save->setProperty("module", 2);
    ui->btnM3Save->setProperty("module", 3);
    ui->btnM4Save->setProperty("module", 4);
    connect(ui->btnM1Load, &QPushButton::clicked, this, &MainWindow::slot_btnOneClickLoad);
    connect(ui->btnM2Load, &QPushButton::clicked, this, &MainWindow::slot_btnOneClickLoad);
    connect(ui->btnM3Load, &QPushButton::clicked, this, &MainWindow::slot_btnOneClickLoad);
    connect(ui->btnM4Load, &QPushButton::clicked, this, &MainWindow::slot_btnOneClickLoad);
    connect(ui->btnM1Save, &QPushButton::clicked, this, &MainWindow::slot_btnOneClickSave);
    connect(ui->btnM2Save, &QPushButton::clicked, this, &MainWindow::slot_btnOneClickSave);
    connect(ui->btnM3Save, &QPushButton::clicked, this, &MainWindow::slot_btnOneClickSave);
    connect(ui->btnM4Save, &QPushButton::clicked, this, &MainWindow::slot_btnOneClickSave);
    

    /*updateModuleToolIcon(1);
    updateModuleToolIcon(2);
    updateModuleToolIcon(3);
    updateModuleToolIcon(4);
*/
    //if (m_LoginDialog->exec() == QDialog::Accepted)
    //{
    //    ui->labelUserName->setText(m_LoginDialog->GetUser());
    //    if (m_LoginDialog->GetPop())
    //    {
    //        ui->btnApprovalProgress->hide();
    //    }
    //    this->showMaximized();
    //    m_FilemangageDialog->initTableViewDownload();
    //}
    //else
    //{
    //    this->close();
    //    //exit(1);
    //}
   
    

   
}


void MainWindow::initUdp()
{
    m_udp = new CCtrlNetwork();
    m_udp->init(5555);
}
void MainWindow::udpStartExeThread(const QString strIp, const int port)
{
   
    const char* sendData;// = data.c_str();
   
    sockaddr_in m_sockaddr_in;
    m_sockaddr_in.sin_family = AF_INET;
    m_sockaddr_in.sin_addr.S_un.S_addr = inet_addr(strIp.toStdString().c_str());
    m_sockaddr_in.sin_port = htons(port);
    int sendSize = m_udp->sendDataTo(sendData, strlen(sendData), (sockaddr*)&m_sockaddr_in);
    if (sendSize == -1) {
        std::cout << "Failed to send data: " << strerror(errno) << std::endl;
    }
    else
    {
        std::cout << " sendData : " << sendData << std::endl;
    }

    // 接收数据;
    if (!m_udp) return;
    const int BUF_LEN = 1024 * 100;
    static char s_buf[BUF_LEN];
    while (true)
    {

        int nLen = m_udp->recvData(s_buf, sizeof(s_buf));
        if (nLen <= 0)
        {
            break;
        }

      /*  Json jsonData = Json::parse(s_buf);
        std::cout << " recvData : " << s_buf << std::endl;
        int jsonArraySize = jsonData["plcdata"].size();
        if (jsonArraySize > m_inputNames.size())
            return;*/
    }
}

void MainWindow::showRegisterDialog()
{
    m_RegisterDialog->exec();
}
void MainWindow::setUserNameText(const QString& userName)
{
    ui->labelUserName->setText(userName);
}
void MainWindow::showGif()
{
   // m_FilemangageDialog->hide();
    m_GifDialog->show();
    //m_GifDialog->update();
}
void MainWindow::closeGif()
{
    m_GifDialog->close();
   // m_FilemangageDialog->exec();
}
bool MainWindow::showLoginDialog()
{
    if (m_LoginDialog->exec() == QDialog::Accepted)
    {
        ui->labelUserName->setText(m_LoginDialog->GetUser());
        if (m_LoginDialog->GetPop())
        {
            ui->btnApprovalProgress->hide();
        }
        this->showMaximized();
        m_FilemangageDialog->initTableViewDownload();
        connect(m_OneClickSaveDialog, &OneClickSaveDialog::signals_zipMultPath, m_FilemangageDialog, &FilemangageDialog::slot_compressMultPath);
        return true;
    }
    else
    {
        this->close();
        return false;
    }
    return false;
}

void MainWindow::slot_btnResourceManageClicked()
{
    m_ResourceManageDialog->startWebFlushTimer();
    int  x = 0;
    int  y = 0;
    common::getScreenCenterPos(x,y,m_ResourceManageDialog->width(), m_ResourceManageDialog->height());
    m_ResourceManageDialog->move(x, y);
    m_ResourceManageDialog->exec();
    m_ResourceManageDialog->stopWebFlushTimer();
    ui->btnResourceManage->setChecked(false);
}
void MainWindow::slot_btnInformationConfihurationClicked()
{
	m_InforConfihurationDialog->initFaceData();
    int  x = 0;
    int  y = 0;
    common::getScreenCenterPos(x, y, m_InforConfihurationDialog->width(), m_InforConfihurationDialog->height());
    m_InforConfihurationDialog->move(x, y);
    m_InforConfihurationDialog->exec();
    ui->btnInformationConfihuration->setChecked(false);
}

void MainWindow::slot_btnDataManageClicked()
{
    //m_DataManageDialog->exec();
    int  x = 0;
    int  y = 0;
    common::getScreenCenterPos(x, y, m_FilemangageDialog->width(), m_FilemangageDialog->height());
    m_FilemangageDialog->move(x, y);
    m_FilemangageDialog->exec();
    ui->btnDataManage->setChecked(false);
}

void MainWindow::slot_btnApprovalProgressClicked()
{
    m_ApprovalProgressDialog->init();
    int  x = 0;
    int  y = 0;
    common::getScreenCenterPos(x, y, m_ApprovalProgressDialog->width(), m_ApprovalProgressDialog->height());
    m_ApprovalProgressDialog->move(x, y);
    m_ApprovalProgressDialog->exec();
    ui->btnApprovalProgress->setChecked(false);
}

void MainWindow::slot_btnAddToolTab()
{
    QPushButton* pButton = (QPushButton*)sender();
    int moduleNumber= pButton->property("module").toInt();

    
    AddToolDialog addToooDialog(moduleNumber);
    if (addToooDialog.exec() == QDialog::Accepted)
    {
        QString toolName;
        QString tabName;
        int mode = -1;
        int displayMode = 0;
        int toolID = -1;
        addToooDialog.getToolData(tabName,toolName, toolID,mode, displayMode);
        //QWidget* pWidget = new QWidget;
        table_tools stTool;
        db::databaseDI::Instance().get_tool(stTool, toolID);

        if (moduleNumber == 1)
        {
            
            QString exeDir = QCoreApplication::applicationDirPath();
            QString strDspPath = exeDir + "/dsp/" + QString::number(common::iLoginNum) + "/" + toolName + ".rdp";

            // 启动bsp  
            // 使用 std::bind 绑定参数
            //auto boundFunction = std::bind(&MainWindow::udpStartExeThread, this, stTool.ip, 5556);
            QString strIp = QString::fromStdString(stTool.ip);
            QString userName= "Administrator";
            QString password = "Ate123";
            std::thread t(&MainWindow::udpStartExeThread, this, strIp, 5556);

            QAxWidget* rdp = new QAxWidget;
            //connect(&rdp, &QAxWidget::4
            connect(rdp, SIGNAL(ActiveXEvent()), this, SLOT(onActiveXEvent()));
         //   rdp->dynamicCall("MethodName()");
            rdp->setControl(QString::fromUtf8("{1DF7C823-B2D4-4B54-975A-F2AC5D7CF8B8}")); // 对应于RDP的CLSID
          //  bool b = rdp->setProperty("Server", "192.168.1.247"); // 远程桌面的IP地址
            //b = rdp->setProperty("UserName", "Administrator"); // 用户名
            //b = rdp->setProperty("Password", "Ate123"); // 密码
            bool b = rdp->setProperty("Server", strIp); // 远程桌面的IP地址
            b = rdp->setProperty("UserName", userName); // 用户名
            b = rdp->setProperty("Password", password); // 密码

            b = rdp->setProperty("DesktopWidth", this->width());         //指定宽度
            b = rdp->setProperty("DesktopHeight", this->height());        //指定高度
          //  b = rdp->setProperty("ConnectingText", QString::fromUtf8("Visual Studio 2017"));
            b = rdp->setProperty("DisconnectedText", QString::fromUtf8("启动失败"));

            //普通参数,可选项
            rdp->setFocusPolicy(Qt::StrongFocus);        //设置控件接收键盘焦点的方式：鼠标单击、Tab键
            b = rdp->setProperty("DisplayAlerts", false);    //不显示任何警告信息
            b = rdp->setProperty("DisplayScrollBars", true); //显示滚动条
            b = rdp->setProperty("ColorDepth", 32);          //画质/位深,32/24/16/15/8


            //高级参数
            QAxObject* pAdvancedObject = rdp->querySubObject("AdvancedSettings7");
            if (pAdvancedObject)
            {
                b = pAdvancedObject->setProperty("ClearTextPassword", password);     //用户密码(这种方式每次都不需要手动输入密码)
                b = pAdvancedObject->setProperty("EnableCredSspSupport", true); //必须设置,否则远程连接失败
                b = pAdvancedObject->setProperty("PublicMode", true);
                //高级参数,可选项
                b = pAdvancedObject->setProperty("BitmapPeristence", 1);         //位图缓存
                b = pAdvancedObject->setProperty("Compress", 1);                 //启用压缩,减小带宽
                b = pAdvancedObject->setProperty("singleConnectionTimeout", 10); //超时时间,s
            }

            QAxObject* pSecuredmObject = rdp->querySubObject("SecuredSettings3");
            if (pSecuredmObject)
            {

                b = pSecuredmObject->setProperty("WorkDir", "C:/Program Files (x86)/Microsoft Visual Studio/2017/Enterprise/Common7/IDE/");
                b = pSecuredmObject->setProperty("StartProgram", "devenv.exe");
            }


            QVariant v2 = rdp->dynamicCall("Connect()"); //连接
            QWidget* axTabWidget = new QWidget();
            QVBoxLayout* layout = new QVBoxLayout(axTabWidget);
            layout->addWidget(rdp);
            axTabWidget->setLayout(layout);
               
            if (displayMode == 0)
            {
                ui->tabWidgetModulel1->addTab(axTabWidget, tabName);
            }
            else
            {
                axTabWidget->show();
            }

        }
        else if(moduleNumber==2)
        {
            QString exeDir = QCoreApplication::applicationDirPath();
            //int i = common::iSoftStartHostNum %3;
           // if (common::setHostIps.size() >= i)
            {
                //auto it = std::next(common::setHostIps.begin(), i); // 移动到第i个元素
                //std::string strValue = *it;


                //QString strDspPath = exeDir + "/dsp/" + QString::number(common::iLoginNum) + "/"
                //    +QString::fromStdString(strValue) + "/"+toolName + ".rdp";

               
                //common::iSoftStartHostNum++;

               // strDspPath = "D:\\Visual Studio 2017.rdp";
                // 启动bsp 
              //  common::startDspExe(strDspPath);
                // 嵌入

                QAxWidget* rdp = new QAxWidget;
                rdp->setControl(QString::fromUtf8("{1DF7C823-B2D4-4B54-975A-F2AC5D7CF8B8}")); // 对应于RDP的CLSID
                bool b = rdp->setProperty("Server", "192.168.1.248"); // 远程桌面的IP地址
                b = rdp->setProperty("UserName", "Administrator"); // 用户名
                b = rdp->setProperty("Password", "Ate123"); // 密码

                b = rdp->setProperty("DesktopWidth", this->width());         //指定宽度
                b = rdp->setProperty("DesktopHeight", this->height());        //指定高度
                b = rdp->setProperty("ConnectingText", QString::fromUtf8("MATLAB"));
                b = rdp->setProperty("DisconnectedText", QString::fromUtf8("启动失败"));

                //普通参数,可选项
                rdp->setFocusPolicy(Qt::StrongFocus);        //设置控件接收键盘焦点的方式：鼠标单击、Tab键
                b = rdp->setProperty("DisplayAlerts", false);    //不显示任何警告信息
                b = rdp->setProperty("DisplayScrollBars", true); //显示滚动条
                b = rdp->setProperty("ColorDepth", 32);          //画质/位深,32/24/16/15/8


                //高级参数
                QAxObject* pAdvancedObject = rdp->querySubObject("AdvancedSettings7");
                if (pAdvancedObject)
                {
                    b = pAdvancedObject->setProperty("ClearTextPassword", "Ate123");     //用户密码(这种方式每次都不需要手动输入密码)
                    b = pAdvancedObject->setProperty("EnableCredSspSupport", true); //必须设置,否则远程连接失败

                    b = pAdvancedObject->setProperty("PublicMode", false);
                    //高级参数,可选项
                    b = pAdvancedObject->setProperty("BitmapPeristence", 1);         //位图缓存
                    b = pAdvancedObject->setProperty("Compress", 1);                 //启用压缩,减小带宽
                    b = pAdvancedObject->setProperty("singleConnectionTimeout", 10); //超时时间,s

                  
                }

                QAxObject* pSecuredmObject = rdp->querySubObject("SecuredSettings3");
                if (pSecuredmObject)
                {

                    b = pSecuredmObject->setProperty("WorkDir", "C:/Program Files/Polyspace/R2021a/bin/");
                    b = pSecuredmObject->setProperty("StartProgram", "matlab.exe");
                }


                QVariant v2 = rdp->dynamicCall("Connect()"); //连接
                QWidget* axTabWidget = new QWidget();
                QVBoxLayout* layout = new QVBoxLayout(axTabWidget);
                layout->addWidget(rdp);
                axTabWidget->setLayout(layout);

                if (displayMode == 0)
                {
                    ui->tabWidgetModulel2->addTab(axTabWidget, tabName);
                }
                else
                {
                    axTabWidget->show();
                }
            }

        }

    }
    
}

void MainWindow::slot_btnOneClickLoad()
{
	if (!m_OneClickLoadDialog->m_model->rowCount())
	{
		std::list<table_one_load_software> listData;
		if (db::databaseDI::Instance().get_load_software(listData))
		{
			for (auto &stData : listData)
			{
				if (stData.userID == common::iUserID)
				{
					int newRowIndex = m_OneClickLoadDialog->m_model->rowCount(); // 获取当前行数
					m_OneClickLoadDialog->m_model->insertRow(newRowIndex); // 插入新行

					QStandardItem* item = new QStandardItem(QString::number(newRowIndex + 1));
					m_OneClickLoadDialog->m_model->setItem(newRowIndex, 0, item);
					QModelIndex index = m_OneClickLoadDialog->m_model->index(newRowIndex, 0);
					// item->setTextAlignment(Qt::AlignCenter);  // 设置文本居中对齐
					//m_model->setData(index, stIp.id, Qt::UserRole);  // 设置id;

					m_OneClickLoadDialog->m_model->setItem(newRowIndex, 1, new QStandardItem(QString::fromStdString(stData.projectPath)));
					m_OneClickLoadDialog->m_model->setItem(newRowIndex, 2, new QStandardItem(QString::number(stData.module)));
				}
			}
		}
	}
   
    m_OneClickLoadDialog->exec();
    QPushButton* pButton = (QPushButton*)sender();
    int module=pButton->property("module").toInt();
    if (module == 1)
    {
        ui->btnM1Load->setChecked(false);
    }
    else if (module == 2)
    {
        ui->btnM2Load->setChecked(false);
    }
    else if (module == 3)
    {
        ui->btnM3Load->setChecked(false);
    }
    else if (module == 4)
    {
        ui->btnM4Load->setChecked(false);
    }

}

void MainWindow::slot_btnOneClickSave()
{
    m_OneClickSaveDialog->exec();
    QPushButton* pButton = (QPushButton*)sender();
    int module = pButton->property("module").toInt();
    if (module == 1)
    {
        ui->btnM1Save->setChecked(false);
    }
    else if (module == 2)
    {
        ui->btnM2Save->setChecked(false);
    }
    else if (module == 3)
    {
        ui->btnM3Save->setChecked(false);
    }
    else if (module == 4)
    {
        ui->btnM4Save->setChecked(false);
    }
}

void MainWindow::slot_updateModuleToolIcon(int module)
{

    updateModuleToolIcon(module);

}

void MainWindow::slot_downlaodFinsh()
{
    closeGif();
}

void MainWindow::updateModuleToolIcon(int module)
{
 
    QLayout* pLayout = nullptr;
    if (module == 1)
    {
        pLayout = ui->layoutM1ToolIcon;
    }
    else if (module == 2)
    {
        pLayout = ui->layoutM2ToolIcon;
    }
    else if (module == 3)
    {
        pLayout = ui->layoutM3ToolIcon;
    }
    else if (module == 4)
    {
        pLayout = ui->layoutM4ToolIcon;
    }

    common::clearLayout(pLayout);
	std::map<std::string, table_ip> ipMap;
    if (db::databaseDI::Instance().get_ip_data(ipMap, module,common::iLoginNum))
    {
        for (const auto& stTool : ipMap)
        {
			const std::string& software = stTool.first;
			const table_ip& data = stTool.second;
			//if (stTool.username == std::to_string(common::iUserID))
			{
				QToolButton* pBtn = new QToolButton();
				//QPushButton* pBtn = new QPushButton(QString::fromLocal8Bit("测试"));
				pBtn->setIcon(QIcon(QString::fromStdString(data.icoPath)));
				pBtn->setIconSize(QSize(50, 46));
				pBtn->setText(QString::fromStdString(software));
				pBtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
				pBtn->setStyleSheet("background-color:rgba(0,0,0,0);font-size: 12px;");
				pBtn->setFocusPolicy(Qt::NoFocus);
				pBtn->setFixedSize(55, 64);
				//   pBtn->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);  // 设置按钮的大小策略

				pBtn->setEnabled(true);

				pLayout->addWidget(pBtn);
			}
        }
    }
}


//void MainWindow::slot_login_succ()
//{
//    int loginStatus = 1;
//    db::databaseDI::Instance().update_user_LoginStatus(common::iUserID, loginStatus);
//
//	db::databaseDI::Instance().get_user_login_number(common::iLoginNum);
//    db::databaseDI::Instance().get_ip_data_by_number(common::setHostIps, common::iLoginNum);
//
//	this->m_LoginDialog->accept();
//
//	if (m_fingerDlg != nullptr)
//		delete m_fingerDlg;
//}

