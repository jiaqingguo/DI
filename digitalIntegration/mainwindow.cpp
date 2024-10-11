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

#include <QtWidgets/QApplication>
#include <QApplication>
#include <QVBoxLayout>
#include <QLabel>
#include <qwidget.h>
#include <QtWebEngineWidgets>
#include <QAxWidget>
#include "windows.h"

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
    m_ResourceManageDialog->exec();
    m_ResourceManageDialog->stopWebFlushTimer();
    ui->btnResourceManage->setChecked(false);
}
void MainWindow::slot_btnInformationConfihurationClicked()
{
	m_InforConfihurationDialog->initFaceData();
    m_InforConfihurationDialog->exec();
    ui->btnInformationConfihuration->setChecked(false);
}

void MainWindow::slot_btnDataManageClicked()
{
    //m_DataManageDialog->exec();
    m_FilemangageDialog->exec();
    ui->btnDataManage->setChecked(false);
}

void MainWindow::slot_btnApprovalProgressClicked()
{
    m_ApprovalProgressDialog->init();
    m_ApprovalProgressDialog->exec();
    ui->btnApprovalProgress->setChecked(false);
}
QWidget* main_widget = nullptr;
QWindow* main_window = nullptr;
HWND      main_wid;
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
        addToooDialog.getToolData(tabName,toolName, mode, displayMode);
        QWidget* pWidget = new QWidget;

        if (1)
        {

       
        if (moduleNumber == 1)
        {
            auto WNID = (WId)FindWindow(L"WeChatMainWndForPC", L"微信");
           

            WId winId = (WId)WNID;
          
            //WId winId = (WId)FindWindow(NULL, reinterpret_cast<LPCWSTR>(toolName.constData()));
            if (winId != 0)
            {
                QWindow* window = QWindow::fromWinId(winId);
                QWidget* widget = QWidget::createWindowContainer(window);
                
                widget->setWindowTitle(tabName);
                if (displayMode == 0)
                {
                    ui->tabWidgetModulel1->addTab(widget, tabName);
                }
                else
                {
                    widget->show();
                }
            }
            else
            {
                QWidget* pWidget = new QWidget;
                pWidget->setWindowTitle(tabName);
                ui->tabWidgetModulel1->addTab(pWidget, tabName);
            }
           
        }
        else if (moduleNumber == 2)
        {


            QString strDspPath = "D:\Visual Studio 2017.rdp";

            // 启动bsp 
            common::startDspExe(strDspPath);

            QString  className = "RAIL_WINDOW";
            // 窗口句柄
          
            HWND WNID;
            HWND temp = NULL;
          
            int i = 0;
            WNID = common::getHWND(className, i);
           // WId winId = (WId)WNID;
            //WNID=FindWindow(NULL, L" (AD.jhapp.com)");
            WId winId = (WId)WNID;
            if (winId != 0)
            {
               
                if (displayMode == 0)
                {
                    
                   
                    /*QRect geometry = ui->tabWidgetModulel2->widget(0)->geometry();
                    int width = geometry.width();
                    int height = geometry.height();
                    SetWindowPos(WNID, HWND_TOP, 0, 0, width, height, SWP_NOZORDER | SWP_SHOWWINDOW);*/

                    QWindow* window = QWindow::fromWinId(winId);
                    int width = window->width();
                    int height = window->height();
                    QWidget* widget = QWidget::createWindowContainer(window,this);
                   //widget->setFixedWidth(width);
                   // widget->setFixedHeight(height);
                  //  widget->resize(width, height);
                    // 创建一个新的 QWidget
                  
                    widget->setWindowTitle(tabName);
                    ui->tabWidgetModulel2->addTab(widget, tabName);
                }
                else
                {
                  //SetWindowPos(WNID, HWND_TOP, 0, 0, 650, 480, SWP_NOZORDER | SWP_SHOWWINDOW);
                    QWindow* window = QWindow::fromWinId(winId);
                    window->setFlags(window->flags()| Qt::ForeignWindow);
                    int width = window->width();
                    int height = window->height();
                   // window->show();
                   QWidget* widget = QWidget::createWindowContainer(window,nullptr,Qt::Widget|Qt::WindowStaysOnTopHint);
                    //main_widget = QWidget::createWindowContainer(window);
                  //window->setGeometry(0, 0, widget->width(), widget->height());
                  //widget->setFixedWidth(width);
                  // widget->setFixedHeight(height);
                    
                   // main_widget->show();
                   widget->show();
                    // 创建一个嵌入窗口类，将原生窗口嵌入 Qt Widget
                   /* CWidget* embeddedWidget = new CWidget(WNID);
                    embeddedWidget->show();*/

                    //QWindow* window = QWindow::fromWinId(winId);
                    //QWidget* widget = QWidget::createWindowContainer(window);
                    ////widget->showMaximized();
                    //  SetWindowPos(WNID, HWND_TOP, 0, 0, 2500, 1300, SWP_NOZORDER | SWP_SHOWWINDOW);
                    //  widget->resize(2500, 1300);
                    //// 获取 QWidget 的大小
                    //QRect geometry = widget->geometry();
                    //int width = geometry.width();
                    //int height = geometry.height();

                    // 调整外部窗口的大小和位置
                  //  SetWindowPos(WNID, HWND_TOP, 0, 0, width, height, SWP_NOZORDER | SWP_SHOWWINDOW);
                    // 创建一个QAxWidget对象
                 
                }
               
            }
        }
        else if (moduleNumber == 3)
        {
            WId winId = (WId)FindWindow(NULL, reinterpret_cast<LPCWSTR>(toolName.constData()));
           
            if (winId != 0)
            {
                QWindow* window = QWindow::fromWinId(winId);
                QWidget* widget = QWidget::createWindowContainer(window);
                widget->setWindowTitle(tabName);
                if (displayMode == 0)
                {
                    ui->tabWidgetModulel3->addTab(widget, tabName);
                }
                else
                {
                    widget->show();
                }
             
            }
            
        }
        else if (moduleNumber == 4)
        {
            WId winId = (WId)FindWindow(NULL, reinterpret_cast<LPCWSTR>(toolName.constData()));
            if (winId != 0)
            {
                QWindow* window = QWindow::fromWinId(winId);
                QWidget* widget = QWidget::createWindowContainer(window);
                widget->setWindowTitle(tabName);
                if (displayMode == 0)
                {
                   
                    ui->tabWidgetModulel4->addTab(widget, tabName);
                }
                else
                {
                    widget->show();
                }
               
            }
        }
         };

        if (moduleNumber == 1)
        {
            QString exeDir = QCoreApplication::applicationDirPath();
            QString strDspPath = exeDir + "/dsp/" + QString::number(common::iLoginNum) + "/" + toolName + ".rdp";

            // 启动bsp 
            common::startDspExe(strDspPath);
           // 嵌入
        }
        else
        {
            QString exeDir = QCoreApplication::applicationDirPath();
            int i = common::iSoftStartHostNum %3;
            if (common::setHostIps.size() >= i)
            {
                auto it = std::next(common::setHostIps.begin(), i); // 移动到第i个元素
                std::string strValue = *it;


                QString strDspPath = exeDir + "/dsp/" + QString::number(common::iLoginNum) + "/"
                    +QString::fromStdString(strValue) + "/"+toolName + ".rdp";

               
                common::iSoftStartHostNum++;

                strDspPath = "D:\\Visual Studio 2017.rdp";
                // 启动bsp 
                common::startDspExe(strDspPath);
                // 嵌入
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

<<<<<<< HEAD
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
=======
//bool MainWindow::event(QEvent* event)
//{
//    if(main_widget)
//        main_widget->update();
//    return QMainWindow::paintEvent(event);;
//}

void MainWindow::paintEvent(QPaintEvent* event)
{
    if (main_widget)
        main_widget->update();

    QMainWindow::paintEvent(event);
}

void MainWindow::mousePressEvent(QMouseEvent* event)
{
    if (main_widget != nullptr)
    {
        // 将鼠标点击的事件位置转换为全局坐标
        QPoint globalPos = event->globalPos();

        // 将全局坐标转换为容器内的坐标
        QPoint localPos = main_widget->mapFromGlobal(globalPos);

        // 发送消息到原生窗口, 这里使用 SendMessage 函数
        SendMessage((HWND)main_widget->winId(), WM_LBUTTONDOWN, MK_LBUTTON, MAKELPARAM(localPos.x(), localPos.y()));
    }

    QMainWindow::mousePressEvent(event);
}

void MainWindow::slot_login_succ()
{
    int loginStatus = 1;
    db::databaseDI::Instance().update_user_LoginStatus(common::iUserID, loginStatus);

	db::databaseDI::Instance().get_user_login_number(common::iLoginNum);
    db::databaseDI::Instance().get_ip_data_by_number(common::setHostIps, common::iLoginNum);

	this->m_LoginDialog->accept();

	if (m_fingerDlg != nullptr)
		delete m_fingerDlg;
}
>>>>>>> e376e73ed533169646b12d0d499e15aeadbaf08f

