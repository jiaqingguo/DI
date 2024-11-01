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
#include "CWidget.h"

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
        // ��ԭ������Ƕ�뵽 Qt �� QWidget ��
        m_windowContainer = QWidget::createWindowContainer(QWindow::fromWinId((WId)m_hwnd), this);
        m_windowContainer->setFocusPolicy(Qt::StrongFocus);  // ȷ��Ƕ�봰�ڿ��Ի�ȡ����

        // ����ԭ�����ڴ�С��ʹ������ QWidget
        adjustEmbeddedWindowSize();
    }

    // ����Ƕ�봰�ڵĴ�СΪ QWidget �Ĵ�С
void EmbeddedWidget::adjustEmbeddedWindowSize() 
{
    if (m_hwnd) {
        // ��ȡ QWidget �Ĵ�С
        QRect geometry = this->geometry();
        int width = geometry.width();
        int height = geometry.height();

        // �����ⲿ���ڵĴ�С��λ��
        SetWindowPos(m_hwnd, HWND_TOP, 0, 0, width, height, SWP_NOZORDER | SWP_SHOWWINDOW);
    }
}


    // ��д resizeEvent���Է� QWidget �Ĵ�С�ı�ʱ��Ҫ���µ����ⲿ���ڵĴ�С
void EmbeddedWidget::resizeEvent(QResizeEvent* event)  {
    QWidget::resizeEvent(event);
    adjustEmbeddedWindowSize();
}

//CWidget::CWidget(HWND hwnd, QWidget* parent) : QWidget(parent), m_hwnd(hwnd) {
//    // ��ԭ������Ƕ�뵽 Qt �� QWidget ��
//   QWindow *window= QWindow::fromWinId((WId)m_hwnd);
//
//   this->resize(window->width(), window->height());
//    m_windowContainer = QWidget::createWindowContainer(window);
//    m_windowContainer->setFocusPolicy(Qt::StrongFocus);  // ȷ��Ƕ�봰�ڿ��Ի�ȡ����
//    
//    QGridLayout* layout = new QGridLayout;
//    layout->addWidget(m_windowContainer);
//    this->setLayout(layout);
//    
//}
//void CWidget::mousePressEvent(QMouseEvent* event)
//{
//   
//        // ����������¼�λ��ת��Ϊȫ������
//        QPoint globalPos = event->globalPos();
//
//        // ��ȫ������ת��Ϊ�����ڵ�����
//        QPoint localPos = this->mapFromGlobal(globalPos);
//
//        // ������Ϣ��ԭ������, ����ʹ�� SendMessage ����
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

    setWindowTitle(GBK_STRING("��������Ӳ��һ�廯ƽ̨"));
    setWindowIcon(QIcon(":/image/tubiao.png"));
    //QString command = "cmdkey /add:192.168.1.247 /user:Administrator /pass:Ate123";

    //// ���� QProcess ����
    //QProcess process;

    //// ���� cmd ���̲�ִ������
    //process.start("cmd.exe", QStringList() << "/C" << command);

    //// �ȴ�����ִ�����
    //if (process.waitForFinished())
    //{
    //    // ��ȡ������������ڵ��Ի�鿴�����
    //    QString output = process.readAllStandardOutput();
    //    QString error = process.readAllStandardError();

    //    // ��ӡ���������̨
    //    qDebug() << "Output:" << output;
    //    qDebug() << "Error:" << error;
    //}
    //else
    //{
    //    qDebug() << "Process failed to start or execute.";
    //}
    // qss�ļ������
    m_pQssAutoLoader = new QssAutoLoader;
    QString strQssPath = QApplication::applicationDirPath() + "/qss/default.qss";
    strQssPath.replace("/", "\\\\");
    m_pQssAutoLoader->setAutoloadQss(strQssPath);

	initInitface();

    //QString target = "\\\\192.168.0.250\\"; // ʵ��·��
    //QString username = "share"; // ʵ���û���
    //QString password = "Share123"; // ʵ������

    //common::addNetworkCredential(target, username, password);
    initAccount();
   
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
	connect(m_OneClickLoadDialog, &OneClickLoadDialog::one_load_tools, this, &MainWindow::slot_one_load_tools);

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

  
    // ��ʼ��ģ��1-4����;
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
    
    ui->tabWidgetModulel1->setTabsClosable(true);
    ui->tabWidgetModulel2->setTabsClosable(true);
    ui->tabWidgetModulel3->setTabsClosable(true);
    ui->tabWidgetModulel4->setTabsClosable(true);
    // ���ӹر������źŵ��ۺ���
    connect(ui->tabWidgetModulel1, &QTabWidget::tabCloseRequested, this, &MainWindow::slot_tabModule1closeTab);
    connect(ui->tabWidgetModulel2, &QTabWidget::tabCloseRequested, this, &MainWindow::slot_tabModule2closeTab);
    connect(ui->tabWidgetModulel3, &QTabWidget::tabCloseRequested, this, &MainWindow::slot_tabModule3closeTab);
    connect(ui->tabWidgetModulel4, &QTabWidget::tabCloseRequested, this, &MainWindow::slot_tabModule4closeTab);
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
void MainWindow::udpStartExeThread(const QString strData, const QString strIp, const int port)
{ 
    const char* sendData= strData.toStdString().c_str();// = data.c_str();
   
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
        std::cout << " sendData: " << sendData << std::endl;
    }

    // ��������;
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

      /* Json jsonData = Json::parse(s_buf);
        std::cout << " recvData : " << s_buf << std::endl;
        int jsonArraySize = jsonData["plcdata"].size();
        if (jsonArraySize > m_inputNames.size())
            return;*/
        return;
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

		//ui->stackedWidget->setCurrentIndex(1);
		//ui->stackedWidget->setCurrentIndex(0);

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



void MainWindow::initAccount()
{
    m_mapAccauntData.clear();
    if (common::iLoginNum <= 3)
    {
        m_vecAccount.append("user1");
        m_vecAccount.append("user2");
        m_vecAccount.append("user3");
    }
    else
    {
        m_vecAccount.append("user4");
        m_vecAccount.append("user5");
        m_vecAccount.append("user6");
    }
}

QString MainWindow::getAccaunt(const QString& strIP, const QString strSoft)
{
    QString strAccaunt = "";
    if (m_mapAccauntData.contains(strIP))
    {
        QMap<QString, QVector<QString>>& mapData = m_mapAccauntData[strIP];
        if (mapData.contains(strSoft))
        {
            QVector<QString>& vecData = mapData[strSoft];
            if (vecData.size() <= 0)
            {
                return strAccaunt;
            }
            strAccaunt = vecData.takeFirst();
          
        }
        else
        {
            QVector<QString>  vecData = m_vecAccount;
            strAccaunt = vecData.takeFirst();
            mapData.insert(strSoft, vecData);
            
        }


    }
    else
    {
        QVector<QString>  vecData = m_vecAccount;
        strAccaunt = vecData.takeFirst();
        m_mapAccauntData[strIP].insert(strSoft, vecData);
    }
    return strAccaunt;
}

void MainWindow::addAccaunt(const QString& strIP, const QString& strSoft, const QString& strAcc)
{
    QVector<QString>& vecUserName = m_mapAccauntData[strIP][strSoft];

    if (!vecUserName.contains(strAcc))
    {
        vecUserName.append(strAcc);
    }
}

//void MainWindow::addAccaunt(const int& module, const int& index)
//{
//    const auto& stUesdData = m_usedAccaunt[module][index];
//    if (!stUesdData.account.isEmpty())
//    {
//        QVector<QString>& vecUserName = m_mapAccauntData[stUesdData.ip][stUesdData.software];
//
//        if (!vecUserName.contains(stUesdData.account))
//        {
//            vecUserName.append(stUesdData.account);
//        }
//    }
//    m_usedAccaunt[module].remove(index);
//}



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
        QString  toolPath = -1;
        addToooDialog.getToolData(tabName,toolName, toolPath,mode, displayMode);
        //QWidget* pWidget = new QWidget;
        //table_tools stTool;
      //  db::databaseDI::Instance().get_tool(stTool, toolID);


        table_ip stipToolData;
        if (!db::databaseDI::Instance().get_one_ip_data(stipToolData, toolName.toStdString(), common::iLoginNum))
        {
            return;
        }
        QString strAccount = getAccaunt(QString::fromStdString(stipToolData.ip), toolName);
        if (strAccount.isEmpty())
        {
            QMessageBox::warning(this, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("Զ������û��������㣡"));
            return;
        }
  
       QString strPwd = "123456";
       CWidget* axTabWidget = new CWidget();
        if (moduleNumber == 1)
        {

            if (displayMode == 0)
            {
             
                axTabWidget->m_account = strAccount;
                axTabWidget->m_ip = QString::fromStdString(stipToolData.ip);
                axTabWidget->m_softwareName = toolName;

                startLongDistanceSoftware(tabName, moduleNumber,stipToolData.ip, strAccount.toStdString(), strPwd.toStdString(), stipToolData.toolPath, axTabWidget, ui->tabWidgetModulel1);
            }
            else
            {
                axTabWidget->m_account = strAccount;
                axTabWidget->m_ip = QString::fromStdString(stipToolData.ip);
                axTabWidget->m_softwareName = toolName;
                startLongDistanceSoftware(tabName, moduleNumber,stipToolData.ip, strAccount.toStdString(), strPwd.toStdString(), stipToolData.toolPath, axTabWidget);
            }


        }
        else if(moduleNumber==2)
        {

            QString exeDir = QCoreApplication::applicationDirPath();
            int i = common::iSoftStartHostNum %3;
            if (common::setHostIps.size() >= i)
            {
                auto it = std::next(common::setHostIps.begin(), i); // �ƶ�����i��Ԫ��
                std::string strIP = *it;
                common::iSoftStartHostNum++;

			
                if (displayMode == 0)
                {
                    /*st_account_data stUsedData;
                    stUsedData.account = strAccount;
                    stUsedData.ip = ;
                    stUsedData.software = toolName;
                    m_usedAccaunt[2].insert(ui->tabWidgetModulel2->count(), stUsedData);*/
                   
                    axTabWidget->m_account = strAccount;
                    axTabWidget->m_ip = QString::fromStdString(strIP);
                    axTabWidget->m_softwareName = toolName;
                  
                    startLongDistanceSoftware(tabName, moduleNumber,strIP, strAccount.toStdString(), strPwd.toStdString(),  stipToolData.toolPath, axTabWidget, ui->tabWidgetModulel2);
                }
                else
                {
                    axTabWidget->m_account = strAccount;
                    axTabWidget->m_ip = QString::fromStdString(strIP);
                    axTabWidget->m_softwareName = toolName;

                    startLongDistanceSoftware(tabName, moduleNumber,strIP, strAccount.toStdString(), strPwd.toStdString(), stipToolData.toolPath, axTabWidget);
                }
         
               
              
            }

        }
        else if (moduleNumber == 3)
        {

            QString exeDir = QCoreApplication::applicationDirPath();
            int i = common::iSoftStartHostNum % 3;
            if (common::setHostIps.size() >= i)
            {
                auto it = std::next(common::setHostIps.begin(), i); // �ƶ�����i��Ԫ��
                std::string strIP = *it;
                common::iSoftStartHostNum++;


                if (displayMode == 0)
                {
                   
                    axTabWidget->m_account = strAccount;
                    axTabWidget->m_ip = QString::fromStdString(strIP);
                    axTabWidget->m_softwareName = toolName;
                    startLongDistanceSoftware(tabName, moduleNumber,strIP, strAccount.toStdString(), strPwd.toStdString(), stipToolData.toolPath,  axTabWidget,ui->tabWidgetModulel3);
                }
                else
                {
                    axTabWidget->m_account = strAccount;
                    axTabWidget->m_ip = QString::fromStdString(strIP);
                    axTabWidget->m_softwareName = toolName;
                    startLongDistanceSoftware(tabName, moduleNumber,strIP, strAccount.toStdString(), strPwd.toStdString(), stipToolData.toolPath, axTabWidget);
                }
              }
         }
        else if(moduleNumber == 4)
        {
            QString exeDir = QCoreApplication::applicationDirPath();
            int i = common::iSoftStartHostNum % 3;
            if (common::setHostIps.size() >= i)
            {
                auto it = std::next(common::setHostIps.begin(), i); // �ƶ�����i��Ԫ��
                std::string strIP = *it;
                common::iSoftStartHostNum++;


                if (displayMode == 0)
                {
                   
                    axTabWidget->m_account = strAccount;
                    axTabWidget->m_ip = QString::fromStdString(strIP);
                    axTabWidget->m_softwareName = toolName;
                    startLongDistanceSoftware(tabName, moduleNumber,strIP, strAccount.toStdString(), strPwd.toStdString(), stipToolData.toolPath, axTabWidget,ui->tabWidgetModulel4);
                }
                else
                {
                    axTabWidget->m_account = strAccount;
                    axTabWidget->m_ip = QString::fromStdString(strIP);
                    axTabWidget->m_softwareName = toolName;
                    startLongDistanceSoftware(tabName, moduleNumber,strIP, strAccount.toStdString(), strPwd.toStdString(), stipToolData.toolPath, axTabWidget);
                }
            }
        }
    }
    
}

void MainWindow::slot_btnOneClickLoad()
{
	QPushButton* pButton1 = (QPushButton*)sender();
	
	common::index = getBtnLoadIndex(pButton1);

	if (!m_OneClickLoadDialog->m_model->rowCount())
	{
		std::list<table_one_load_software> listData;
		if (db::databaseDI::Instance().get_load_software(listData))
		{
			for (auto &stData : listData)
			{
				if (stData.userID == common::iUserID)
				{
					int newRowIndex = m_OneClickLoadDialog->m_model->rowCount(); // ��ȡ��ǰ����
					m_OneClickLoadDialog->m_model->insertRow(newRowIndex); // ��������

					QStandardItem* item = new QStandardItem(QString::number(newRowIndex + 1));
					m_OneClickLoadDialog->m_model->setItem(newRowIndex, 0, item);
					QModelIndex index = m_OneClickLoadDialog->m_model->index(newRowIndex, 0);
					// item->setTextAlignment(Qt::AlignCenter);  // �����ı����ж���
					//m_model->setData(index, stIp.id, Qt::UserRole);  // ����id;

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

void MainWindow::slot_tabModule1closeTab(int index)
{
    if (index <= 0)
    {
        return;
    }
 // ������Ϣ��
    QMessageBox msgBox;
    // ������Ϣ�������
    msgBox.setText(QString::fromLocal8Bit("��ȷ�ϱ��湤��֮���ٹر�Tabҳ:"));
    // �����Զ��尴ť
    QPushButton* button1 = msgBox.addButton(QString::fromLocal8Bit("��ֹر�"), QMessageBox::ActionRole);
    QPushButton* button3 = msgBox.addButton(QString::fromLocal8Bit("ȡ���ر�"), QMessageBox::RejectRole);
    // ������Ϣ���ͼ��
    msgBox.setIcon(QMessageBox::Information);
    // ��ʾ��Ϣ��
    msgBox.exec();
    // �жϰ��µ����ĸ���ť
    if (msgBox.clickedButton() != button1) {
        //qDebug() << "�û�ѡ���� ѡ�� 1";
        return;
    }

    // ͨ�� axTabWidget ��ȡ rdp ��ָ��
    CWidget* axTabWidget = (CWidget*)ui->tabWidgetModulel1->widget(index);
    if (!axTabWidget)
    {
        return;
    }
   
    if (axTabWidget->m_pAxWidget)
    {
        axTabWidget->m_pAxWidget->dynamicCall("Disconnect()");
        axTabWidget->m_pAxWidget->dynamicCall("RequestClose()");//�رղ��
    }
    QString strAcc = axTabWidget->m_account;
    QString strIp = axTabWidget->m_ip;
    addAccaunt(axTabWidget->m_ip, axTabWidget->m_softwareName, axTabWidget->m_account);
    
    ui->tabWidgetModulel1->removeTab(index); // �Ƴ���ǩ
}

void MainWindow::slot_tabModule2closeTab(int index)
{
    if (index <= 0)
    {
        return;
    }
 // ������Ϣ��
    QMessageBox msgBox;
    // ������Ϣ�������
    msgBox.setText(QString::fromLocal8Bit("��ȷ�ϱ��湤��֮���ٹر�Tabҳ:"));
    // �����Զ��尴ť
    QPushButton* button1 = msgBox.addButton(QString::fromLocal8Bit("��ֹر�"), QMessageBox::ActionRole);
    QPushButton* button3 = msgBox.addButton(QString::fromLocal8Bit("ȡ���ر�"), QMessageBox::RejectRole);
    // ������Ϣ���ͼ��
    msgBox.setIcon(QMessageBox::Information);
    // ��ʾ��Ϣ��
    msgBox.exec();
    // �жϰ��µ����ĸ���ť
    if (msgBox.clickedButton() != button1) {
        //qDebug() << "�û�ѡ���� ѡ�� 1";
        return;
    }
   
    // ͨ�� axTabWidget ��ȡ rdp ��ָ��
    CWidget* axTabWidget = (CWidget*)ui->tabWidgetModulel2->widget(index);
    if (!axTabWidget)
    {
        return;
    }
    if (axTabWidget->m_pAxWidget)
    {
        axTabWidget->m_pAxWidget->dynamicCall("Disconnect()");
        axTabWidget->m_pAxWidget->dynamicCall("RequestClose()");//�رղ��
    }
    QString strAcc = axTabWidget->m_account;
    QString strIp = axTabWidget->m_ip;
    addAccaunt(axTabWidget->m_ip, axTabWidget->m_softwareName, axTabWidget->m_account);
    ui->tabWidgetModulel2->removeTab(index); // �Ƴ���ǩ
}

void MainWindow::slot_tabModule3closeTab(int index)
{
    if (index <= 0)
    {
        return;
    }
 // ������Ϣ��
    QMessageBox msgBox;
    // ������Ϣ�������
    msgBox.setText(QString::fromLocal8Bit("��ȷ�ϱ��湤��֮���ٹر�Tabҳ:"));
    // �����Զ��尴ť
    QPushButton* button1 = msgBox.addButton(QString::fromLocal8Bit("��ֹر�"), QMessageBox::ActionRole);
    QPushButton* button3 = msgBox.addButton(QString::fromLocal8Bit("ȡ���ر�"), QMessageBox::RejectRole);
    // ������Ϣ���ͼ��
    msgBox.setIcon(QMessageBox::Information);
    // ��ʾ��Ϣ��
    msgBox.exec();
    // �жϰ��µ����ĸ���ť
    if (msgBox.clickedButton() != button1) {
      
        return;
    }
   
    // ͨ�� axTabWidget ��ȡ rdp ��ָ��
    CWidget* axTabWidget = (CWidget*)ui->tabWidgetModulel3->widget(index);
    if (!axTabWidget)
    {
        return;
    }
    if (axTabWidget->m_pAxWidget)
    {
        axTabWidget->m_pAxWidget->dynamicCall("Disconnect()");
        axTabWidget->m_pAxWidget->dynamicCall("RequestClose()");//�رղ��
    }
    QString strAcc = axTabWidget->m_account;
    QString strIp = axTabWidget->m_ip;
    addAccaunt(axTabWidget->m_ip, axTabWidget->m_softwareName, axTabWidget->m_account);
    ui->tabWidgetModulel3->removeTab(index); // �Ƴ���ǩ   
}

void MainWindow::slot_tabModule4closeTab(int index)
{
    if (index <= 0)
    {
        return;
    }
 // ������Ϣ��
    QMessageBox msgBox;
    // ������Ϣ�������
    msgBox.setText(QString::fromLocal8Bit("��ȷ�ϱ��湤��֮���ٹر�Tabҳ:"));
    // �����Զ��尴ť
    QPushButton* button1 = msgBox.addButton(QString::fromLocal8Bit("��ֹر�"), QMessageBox::ActionRole);
    QPushButton* button3 = msgBox.addButton(QString::fromLocal8Bit("ȡ���ر�"), QMessageBox::RejectRole);
    // ������Ϣ���ͼ��
    msgBox.setIcon(QMessageBox::Information);
    // ��ʾ��Ϣ��
    msgBox.exec();
    // �жϰ��µ����ĸ���ť
    if (msgBox.clickedButton() != button1) {
        //qDebug() << "�û�ѡ���� ѡ�� 1";
        return;
    }
   
    // ͨ�� axTabWidget ��ȡ rdp ��ָ��
    CWidget* axTabWidget = (CWidget*)ui->tabWidgetModulel4->widget(index);
    if (!axTabWidget)
    {
        return;
    }
    if (axTabWidget->m_pAxWidget)
    {
        axTabWidget->m_pAxWidget->dynamicCall("Disconnect()");
        axTabWidget->m_pAxWidget->dynamicCall("RequestClose()");//�رղ��
    }
    QString strAcc = axTabWidget->m_account;
    QString strIp = axTabWidget->m_ip;
    addAccaunt(axTabWidget->m_ip, axTabWidget->m_softwareName, axTabWidget->m_account);
    ui->tabWidgetModulel4->removeTab(index); // �Ƴ���ǩ    
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
				//QPushButton* pBtn = new QPushButton(QString::fromLocal8Bit("����"));
				pBtn->setIcon(QIcon(QString::fromStdString(data.icoPath)));
				pBtn->setIconSize(QSize(50, 46));
				pBtn->setText(QString::fromStdString(software));
				pBtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
				pBtn->setStyleSheet("background-color:rgba(0,0,0,0);font-size: 12px;");
				pBtn->setFocusPolicy(Qt::NoFocus);
				pBtn->setFixedSize(55, 64);
				//   pBtn->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);  // ���ð�ť�Ĵ�С����

				pBtn->setEnabled(true);

				pLayout->addWidget(pBtn);
			}
        }
    }
}

void MainWindow::startUdpRdp(const QString ip)
{
    QAxWidget* rdp = new QAxWidget;
    rdp->setControl(QString::fromUtf8("{1DF7C823-B2D4-4B54-975A-F2AC5D7CF8B8}")); // ��Ӧ��RDP��CLSID
    bool b = rdp->setProperty("Server", "192.168.1.248"); // Զ�������IP��ַ
    b = rdp->setProperty("UserName", "Administrator"); // �û���
    b = rdp->setProperty("Password", "Ate123"); // ����

    b = rdp->setProperty("DesktopWidth", this->width());         //ָ�����
    b = rdp->setProperty("DesktopHeight", this->height());        //ָ���߶�
    b = rdp->setProperty("ConnectingText", QString::fromUtf8("MATLAB"));
    b = rdp->setProperty("DisconnectedText", QString::fromUtf8("����ʧ��"));

    //��ͨ����,��ѡ��
    rdp->setFocusPolicy(Qt::StrongFocus);        //���ÿؼ����ռ��̽���ķ�ʽ����굥����Tab��
    b = rdp->setProperty("DisplayAlerts", false);    //����ʾ�κξ�����Ϣ
    b = rdp->setProperty("DisplayScrollBars", true); //��ʾ������
    b = rdp->setProperty("ColorDepth", 32);          //����/λ��,32/24/16/15/8


    //�߼�����
    QAxObject* pAdvancedObject = rdp->querySubObject("AdvancedSettings7");
    if (pAdvancedObject)
    {
        b = pAdvancedObject->setProperty("ClearTextPassword", "Ate123");     //�û�����(���ַ�ʽÿ�ζ�����Ҫ�ֶ���������)
        b = pAdvancedObject->setProperty("EnableCredSspSupport", true); //��������,����Զ������ʧ��

        b = pAdvancedObject->setProperty("PublicMode", false);
        //�߼�����,��ѡ��
        b = pAdvancedObject->setProperty("BitmapPeristence", 1);         //λͼ����
        b = pAdvancedObject->setProperty("Compress", 1);                 //����ѹ��,��С����
        b = pAdvancedObject->setProperty("singleConnectionTimeout", 10); //��ʱʱ��,s


    }

    QAxObject* pSecuredmObject = rdp->querySubObject("SecuredSettings3");
    if (pSecuredmObject)
    {

        b = pSecuredmObject->setProperty("WorkDir", "C:/Program Files/Polyspace/R2021a/bin/");
        b = pSecuredmObject->setProperty("StartProgram", "matlab.exe");
    }
    QAxObject* pRdpClientShell = rdp->querySubObject("MsRdpClientShell");
    if (pRdpClientShell)
    {
    	pRdpClientShell->dynamicCall("SetRdpProperty(string,int)", "screen mode id", 1);
    	pRdpClientShell->dynamicCall("SetRdpProperty(string,int)", "redirectclipboard", 1);
    	pRdpClientShell->dynamicCall("SetRdpProperty(string,int)", "redirectprinters", 0);
    	pRdpClientShell->dynamicCall("SetRdpProperty(string,int)", "redirectcomports", 0);
    	pRdpClientShell->dynamicCall("SetRdpProperty(string,int)", "redirectsmartcards", 1);
    	pRdpClientShell->dynamicCall("SetRdpProperty(string,string)", "devicestoredirect", "*");
    	pRdpClientShell->dynamicCall("SetRdpProperty(string,string)", "drivestoredirect", "*");
    	pRdpClientShell->dynamicCall("SetRdpProperty(string,int)", "redirectdrives", 1);
    	pRdpClientShell->dynamicCall("SetRdpProperty(string,int)", "session bpp", 32);
    	pRdpClientShell->dynamicCall("SetRdpProperty(string,int)", "prompt for credentials on client", 1);
    	pRdpClientShell->dynamicCall("SetRdpProperty(string,int)", "span monitors", 1);
    	pRdpClientShell->dynamicCall("SetRdpProperty(string,int)", "use multimon", 1);
    	pRdpClientShell->dynamicCall("SetRdpProperty(string,int)", "remoteapplicationmode", 1);
    	pRdpClientShell->dynamicCall("SetRdpProperty(string,int)", "server port", 3389);
    	pRdpClientShell->dynamicCall("SetRdpProperty(string,int)", "allow font smoothing", 1);
    	pRdpClientShell->dynamicCall("SetRdpProperty(string,int)", "promptcredentialonce", 0);
    	pRdpClientShell->dynamicCall("SetRdpProperty(string,int)", "videoplaybackmode", 1);
    	pRdpClientShell->dynamicCall("SetRdpProperty(string,int)", "audiocapturemode", 1);
    	pRdpClientShell->dynamicCall("SetRdpProperty(string,int)", "gatewayusagemethod", 0);
    	pRdpClientShell->dynamicCall("SetRdpProperty(string,int)", "gatewayprofileusagemethod", 1);
    	pRdpClientShell->dynamicCall("SetRdpProperty(string,int)", "gatewaycredentialssource", 0);
    	pRdpClientShell->dynamicCall("SetRdpProperty(string,string)", "full address", ip);
    	pRdpClientShell->dynamicCall("SetRdpProperty(string,string)", "alternate shell", "||devenv");
    	pRdpClientShell->dynamicCall("SetRdpProperty(string,string)", "remoteapplicationprogram", "||devenv");
    	pRdpClientShell->dynamicCall("SetRdpProperty(string,string)", "remoteapplicationname", "Visual Studio 2017");
    	pRdpClientShell->dynamicCall("SetRdpProperty(string,string)", "workspace id", "AD.jhapp.com");
    	pRdpClientShell->dynamicCall("SetRdpProperty(string,int)", "use redirection server name", 1);
    	pRdpClientShell->dynamicCall("SetRdpProperty(string,string)", "loadbalanceinfo", "tsv://MS Terminal Services Plugin.1.RDAPP");
    	b = pRdpClientShell->setProperty("PublicMode", true);
    	pRdpClientShell->dynamicCall("Launch()");
    }
}

void MainWindow::startLongDistanceSoftware(const QString tabName, const int &module, const std::string strIp, const std::string strAccaunt, const std::string pwd, const  std::string path, CWidget* widget, QTabWidget* tabWidget)
{
    connect(widget, &CWidget::signal_softwareClose, this,&MainWindow::slot_widgetAboutToQuit);
   
   
   
    // Ƕ��Զ�˽���;
    QAxWidget* rdp = new QAxWidget;
    rdp->setControl(QString::fromUtf8("{1DF7C823-B2D4-4B54-975A-F2AC5D7CF8B8}")); // ��Ӧ��RDP��CLSID

    bool b = rdp->setProperty("Server", strIp.c_str()); // Զ�������IP��ַ
    b = rdp->setProperty("UserName", strAccaunt.c_str()); // �û���
    b = rdp->setProperty("Password", pwd.c_str()); // ����
    //b = rdp->setProperty("FullScreen", true); // �Ƿ�ȫ��
    //b = rdp->setProperty("DesktopWidth", this->width()-29);         //ָ�����
    //b = rdp->setProperty("DesktopHeight", this->height()-29);        //ָ���߶�
    int height = this->width() - 29;
    int width = this->height() - 29;

    if (tabWidget != nullptr)
    {
        if (module == 1)
        {
			QWidget* TabWidget = ui->tabWidgetModulel1->widget(0);
			if (TabWidget)
			{
				height = TabWidget->height();
				width = TabWidget->width();
			}
           
		}
		else if (module == 2)
		{
			QWidget* TabWidget = ui->tabWidgetModulel2->widget(0);
			if (TabWidget)
			{

				height = TabWidget->height();
				width = TabWidget->width();

			}
		}
		else if (module == 3)
		{
			QWidget* TabWidget = ui->tabWidgetModulel3->widget(0);
			if (TabWidget)
			{
				height = TabWidget->height();
				width = TabWidget->width();
			}
		}
		else if (module == 4)
		{
			//height = ui->widgetSize4->height() - 26;
			//width = ui->widgetSize4->width() - 26;
			QWidget* TabWidget = ui->tabWidgetModulel4->widget(0);
			if (TabWidget)
			{
				height = TabWidget->height();
				width = TabWidget->width();
			}
		}
		b = rdp->setProperty("DesktopWidth", width);         //ָ�����
		b = rdp->setProperty("DesktopHeight", height);        //ָ���߶�
		qDebug() << "1111" << "width :" << width << "height : " << height;
    }
    else
    {
		b = rdp->setProperty("DesktopWidth", this->width()-29);         //ָ�����
		b = rdp->setProperty("DesktopHeight", this->height()-29);        //ָ���߶�
    }
      
    //b = rdp->setProperty("ConnectingText", QString::fromUtf8("Visual Studio 2017"));
    b = rdp->setProperty("DisconnectedText", QString::fromLocal8Bit("Զ�������ѶϿ�����رձ�ǩҳ"));
    //b = rdp->setProperty("Domain", QString::fromUtf8("AD.jhapp.com"));
    b = rdp->setProperty("LoadBalanceInfo", QString::fromUtf8("tsv://MS Terminal Services Plugin.1.RDAPP"));
    //b = rdp->setProperty("LaunchedViaClientShellInterface", true);

    //��ͨ����,��ѡ��
    rdp->setFocusPolicy(Qt::StrongFocus);        //���ÿؼ����ռ��̽���ķ�ʽ����굥����Tab��
    b = rdp->setProperty("ColorDepth", 32);          //����/λ��,32/24/16/15/8

    //�߼�����
    QAxObject* pAdvancedObject = rdp->querySubObject("AdvancedSettings2");
    if (pAdvancedObject)
    {
        b = pAdvancedObject->setProperty("ClearTextPassword", pwd.c_str());     //�û�����(���ַ�ʽÿ�ζ�����Ҫ�ֶ���������)
        b = pAdvancedObject->setProperty("EnableCredSspSupport", true); //��������,����Զ������ʧ��

        //�߼�����,��ѡ��
        b = pAdvancedObject->setProperty("BitmapPeristence", 1);         //λͼ����
        b = pAdvancedObject->setProperty("Compress", 1);                 //����ѹ��,��С����
        b = pAdvancedObject->setProperty("singleConnectionTimeout", 10); //��ʱʱ��,s
        b = pAdvancedObject->setProperty("RedirectDrives", true);
        //b = pAdvancedObject->setProperty("keepAliveInterval", 30000); 
        //b = pAdvancedObject->setProperty("MaximizeShell", 0); 
        b = pAdvancedObject->setProperty("RedirectSmartCards", true);
        b = pAdvancedObject->setProperty("DisableCtrlAltDel", 1);
        //b = pAdvancedObject->setProperty("AuthenticationLevel", 2);
    }

    QAxObject* pTransportObject = rdp->querySubObject("TransportSettings4");
    if (pTransportObject)
    {
        b = pTransportObject->setProperty("GatewayProfileUsageMethod", 1);
        //b = pTransportObject->setProperty("GatewayUserSelectedCredsSource", 0x4);
        //b = pTransportObject->setProperty("GatewayProfileUsageMethod", 1);
    }

    bool securedSettingsEnabled = rdp->property("SecuredSettingsEnabled").value<bool>();
    QAxObject* pSecuredmObject = rdp->querySubObject("SecuredSettings3");
    // QString strArguments1 = QString::fromUtf8("C:\\StartApp\\StartAppUdp.exe \"C:\\Program Files (x86)\\Microsoft Visual Studio\\2017\\Enterprise\\Common7\\IDE\\devenv.exe\"");
    QString strArguments1 = QString::fromUtf8("C:\\StartApp\\StartAppUdp.exe ");
    //   stipToolData.toolPath="\"C:\\Program Files (x86)\\Microsoft Visual Studio\\2017\\Enterprise\\Common7\\IDE\\devenv.exe\"";
    //QString path2 = QString::fromUtf8("C:\\Program Files (x86)\\Microsoft Visual Studio\\2017\\Enterprise\\Common7\\IDE\\devenv.exe");
   
    QString strArguments = strArguments1 + " \"" + QString::fromStdString(path) + "\"";

    if (pSecuredmObject)
    {
        b = pSecuredmObject->setProperty("Fullscreen", true);
        //b = pSecuredmObject->setProperty("StartProgram", QString::fromUtf8("C:\\StartApp\\StartAppUdp.exe \"C:\\Program Files\\Polyspace\\R2021a\\bin\\win64\\MATLAB.exe\""));
        //b = pSecuredmObject->setProperty("StartProgram", QString::fromUtf8("C:\\StartApp\\StartAppUdp.exe \"C:\\Program Files (x86)\\National Instruments\\Circuit Design Suite 14.0\\multisim.exe\""));
        b = pSecuredmObject->setProperty("StartProgram", strArguments);
        //b = pSecuredmObject->setProperty("StartProgram", QString::fromUtf8("C:\\StartApp\\StartAppUdp.exe \"C:\\MentorGraphics\\EEVX.2.8\\SDD_HOME\\common\\win64\\bin\\viewdraw.exe\""));
        //b = pSecuredmObject->setProperty("StartProgram", QString::fromUtf8("C:\\StartApp\\StartAppUdp.exe \"C:\\MentorGraphics\\EEVX.2.8\\SDD_HOME\\common\\win64\\bin\\systemvision.bat\""));
        //b = pSecuredmObject->setProperty("StartProgram", QString::fromUtf8("C:\\StartApp\\StartAppUdp.exe"));
        b = pSecuredmObject->setProperty("AudioRedirectionMode", true);
        b = pSecuredmObject->setProperty("KeyboardHookMode", true);
        //b = pSecuredmObject->setProperty("PCB", "2013");
    }
    QVariant v2 = rdp->dynamicCall("Connect()"); //����
 
    QVBoxLayout* layout = new QVBoxLayout(widget);
    layout->addWidget(rdp);
	layout->setMargin(0);
    widget->setLayout(layout);
    widget->m_pAxWidget = rdp;
    if (tabWidget != nullptr)
    {
        tabWidget->addTab(widget, tabName);
    }
    else
    {
		widget->setWindowTitle(tabName);
        widget->showMaximized();
        widget->show();
    }
}

int MainWindow::getBtnLoadIndex(QPushButton *btn)
{
	if (btn->objectName() == "btnM1Load")
	{
		return 1;
	}
	else if(btn->objectName() == "btnM2Load")
	{
		return 2;
	}
	else if (btn->objectName() == "btnM3Load")
	{
		return 3;
	}
	else if (btn->objectName() == "btnM4Load")
	{
		return 4;
	}
}


void MainWindow::slot_one_load_tools(int moduleNum,const QString &toolsName)
{
	table_ip stipToolData;
	if (!db::databaseDI::Instance().get_one_ip_data(stipToolData, toolsName.toStdString(), common::iLoginNum))
	{
		return;
	}
	QString strAccount = getAccaunt(QString::fromStdString(stipToolData.ip), toolsName);
	if (strAccount.isEmpty())
	{
		QMessageBox::warning(this, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("Զ������û��������㣡"));
		return;
	}

	QString strPwd = "123456";
	CWidget* axTabWidget = new CWidget();
   
	if (moduleNum == 1)
	{
        
		axTabWidget->m_account = strAccount;
		axTabWidget->m_ip = QString::fromStdString(stipToolData.ip);
		axTabWidget->m_softwareName = toolsName;
		startLongDistanceSoftware(toolsName,common::index,stipToolData.ip, strAccount.toStdString(), strPwd.toStdString(), stipToolData.toolPath, axTabWidget, ui->tabWidgetModulel1);
	}
	else if(moduleNum == 2)
	{
		QString exeDir = QCoreApplication::applicationDirPath();
		int i = common::iSoftStartHostNum % 3;
		if (common::setHostIps.size() >= i)
		{
			auto it = std::next(common::setHostIps.begin(), i); // �ƶ�����i��Ԫ��
			std::string strIP = *it;
			common::iSoftStartHostNum++;

			axTabWidget->m_account = strAccount;
			axTabWidget->m_ip = QString::fromStdString(strIP);
			axTabWidget->m_softwareName = toolsName;
			startLongDistanceSoftware(toolsName, common::index,strIP, strAccount.toStdString(), strPwd.toStdString(), stipToolData.toolPath, axTabWidget, ui->tabWidgetModulel2);
		}
	}
	else if (moduleNum == 3)
	{
		QString exeDir = QCoreApplication::applicationDirPath();
		int i = common::iSoftStartHostNum % 3;
		if (common::setHostIps.size() >= i)
		{
			auto it = std::next(common::setHostIps.begin(), i); // �ƶ�����i��Ԫ��
			std::string strIP = *it;
			common::iSoftStartHostNum++;

			axTabWidget->m_account = strAccount;
			axTabWidget->m_ip = QString::fromStdString(strIP);
			axTabWidget->m_softwareName = toolsName;
			startLongDistanceSoftware(toolsName, common::index,strIP, strAccount.toStdString(), strPwd.toStdString(), stipToolData.toolPath, axTabWidget,ui->tabWidgetModulel3);
		}
	}
	else
	{
		QString exeDir = QCoreApplication::applicationDirPath();
		int i = common::iSoftStartHostNum % 3;
		if (common::setHostIps.size() >= i)
		{
			auto it = std::next(common::setHostIps.begin(), i); // �ƶ�����i��Ԫ��
			std::string strIP = *it;
			common::iSoftStartHostNum++;

			axTabWidget->m_account = strAccount;
			axTabWidget->m_ip = QString::fromStdString(strIP);
			axTabWidget->m_softwareName = toolsName;
			startLongDistanceSoftware(toolsName, common::index,strIP, strAccount.toStdString(), strPwd.toStdString(), stipToolData.toolPath, axTabWidget, ui->tabWidgetModulel4);
		}
	}
}

void MainWindow::slot_widgetAboutToQuit()
{
    CWidget* axTabWidget = (CWidget*)sender();

    if (axTabWidget)
    {
        QString strAcc = axTabWidget->m_account;
  
        addAccaunt(axTabWidget->m_ip, axTabWidget->m_softwareName, axTabWidget->m_account);
    }
}

