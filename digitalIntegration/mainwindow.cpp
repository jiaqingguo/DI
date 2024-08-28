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
#include "windows.h"

// 定义一个接口类，用于传递数据给HTML
//class EChartsBridge : public QObject {
//    Q_OBJECT
//public:
//    explicit EChartsBridge(QObject* parent = nullptr) : QObject(parent) {}
//
//signals:
//    void sendData(const QString& data);
//
//public slots:
//    void receiveMessage(const QString& message) {
//        qDebug() << "Received message from JavaScript:" << message;
//    }
//};

MainWindow* g_pMainWindow = NULL;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    g_pMainWindow = this;

    setWindowTitle(GBK_STRING("数字样机硬件一体化平台"));
    setWindowIcon(QIcon(":/image/tubiao.png"));

    // qss文件监控类
    m_pQssAutoLoader = new QssAutoLoader;
    QString strQssPath = QApplication::applicationDirPath() + "/qss/default.qss";
    strQssPath.replace("/", "\\\\");
    m_pQssAutoLoader->setAutoloadQss(strQssPath);

	this->m_fingerDlg = new fingerDlg();
	this->m_fingerDlg->finger_init();
    
    initInitface();
	
}


MainWindow::~MainWindow()
{
	//if (this->m_fingerDlg != nullptr)
		//delete this->m_fingerDlg;


    int loginStatus = 0;
    int userId = m_LoginDialog->GetUserID();
    db::databaseDI::Instance().update_user_LoginStatus(userId, loginStatus);

    if (!db::databaseDI::Instance().updata_ipusername(m_LoginDialog->GetUser().toStdString()))
        return;

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
        });
    connect(ui->btnModule2, &QPushButton::clicked, [this]() {
        ui->stackedWidget->setCurrentIndex(2);
        });
    connect(ui->btnModule3, &QPushButton::clicked, [this]() {
        ui->stackedWidget->setCurrentIndex(3);
        });
    connect(ui->btnModule4, &QPushButton::clicked, [this]() {
        ui->stackedWidget->setCurrentIndex(4);
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
    

    updateModuleToolIcon(1);
    updateModuleToolIcon(2);
    updateModuleToolIcon(3);
    updateModuleToolIcon(4);

    if (m_LoginDialog->exec() == QDialog::Accepted)
    {
        ui->labelUserName->setText(m_LoginDialog->GetUser());
        if (m_LoginDialog->GetPop())
        {
            ui->btnApprovalProgress->hide();
        }
        this->showMaximized();
        m_FilemangageDialog->initTableViewDownload();
    }
    else
    {
        this->close();
       // exit(1);
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
void MainWindow::slot_btnResourceManageClicked()
{
    m_ResourceManageDialog->startWebFlushTimer();
    m_ResourceManageDialog->exec();
    m_ResourceManageDialog->stopWebFlushTimer();
    ui->btnResourceManage->setChecked(false);
}
void MainWindow::slot_btnInformationConfihurationClicked()
{
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

void MainWindow::slot_btnAddToolTab()
{
    QPushButton* pButton = (QPushButton*)sender();
    int moduleNumber= pButton->property("module").toInt();

    if (bUserIp == true)
    {
        std::list<table_ip> listData;

        if (db::databaseDI::Instance().get_all_ip_data(listData))
        {
            for (auto& stData : listData)
            {
                if (stData.username.empty())
                {
                    db::databaseDI::Instance().updata_ip_username(1, m_LoginDialog->GetUser().toStdString(), stData.id);
                    break;
                }
                else if (!stData.username.empty())
                {
                    stData.id = stData.id + 1;
                    //db::databaseDI::Instance().updata_ip_username(1, user_name, stData.id);
                    //break;
                }
            }

            bUserIp = false;
        }
    }

    AddToolDialog addToooDialog(moduleNumber);
    if (addToooDialog.exec() == QDialog::Accepted)
    {
        QString toolName;
        QString tabName;
        int mode = -1;
        int displayMode = 0;
        addToooDialog.getToolData(tabName,toolName, mode, displayMode);
        QWidget* pWidget = new QWidget;
        if (moduleNumber == 1)
        { 
            WId winId = (WId)FindWindow(NULL, reinterpret_cast<LPCWSTR>(toolName.constData()));
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
            WId winId = (WId)FindWindow(NULL, L"VMware Workstation");
            if (winId != 0)
            {
                QWindow* window = QWindow::fromWinId(winId);
                QWidget* widget = QWidget::createWindowContainer(window);
                widget->setWindowTitle(tabName);
                if (displayMode == 0)
                {
                  
                    ui->tabWidgetModulel2->addTab(widget, tabName);
                }
                else
                {
                    widget->show();
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

    }
    
}

void MainWindow::slot_btnOneClickLoad()
{
   
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
    std::list<table_tools> listTools;
    if (db::databaseDI::Instance().get_tools(listTools, module))
    {
        for (const auto& stTool : listTools)
        {
            QToolButton* pBtn = new QToolButton();
            //QPushButton* pBtn = new QPushButton(QString::fromLocal8Bit("测试"));
            pBtn->setIcon(QIcon(QString::fromStdString(stTool.icoPath)));
            pBtn->setIconSize(QSize(50, 46));
            pBtn->setText(QString::fromStdString(stTool.name));
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
