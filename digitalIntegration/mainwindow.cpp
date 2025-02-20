#pragma comment  (lib, "User32.lib")
//#include "fingerDlg.h"

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "globel.h"
#include "LoginDialog.h"
#include "RegisterDialog.h"
#include "ResourceManageDialog.h"
#include "InformationConfihurationDialog.h"
#include "DataManageDialog.h"
#include "FilemangageDialog.h"
#include "FtpDialog.h"
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
#include "CAxWidget.h"

#include "ui_OneClickLoadDialog.h"

#include <QtWidgets/QApplication>
#include <QApplication>
#include <QVBoxLayout>
#include <QLabel>
#include <qwidget.h>
#include <QtWebEngineWidgets>
#include <QAxWidget>
#include <QAxObject>
#include <iostream>
#include "windows.h"


#include <thread>
#include <functional>

//EmbeddedWidget::EmbeddedWidget(HWND hwnd, QWidget* parent) : QWidget(parent), m_hwnd(hwnd) {
//	// 将原生窗口嵌入到 Qt 的 QWidget 中
//	m_windowContainer = QWidget::createWindowContainer(QWindow::fromWinId((WId)m_hwnd), this);
//	m_windowContainer->setFocusPolicy(Qt::StrongFocus);  // 确保嵌入窗口可以获取焦点
//
//	// 调整原生窗口大小，使其铺满 QWidget
//	adjustEmbeddedWindowSize();
//}
//
//// 调整嵌入窗口的大小为 QWidget 的大小
//void EmbeddedWidget::adjustEmbeddedWindowSize()
//{
//	if (m_hwnd) {
//		// 获取 QWidget 的大小
//		QRect geometry = this->geometry();
//		int width = geometry.width();
//		int height = geometry.height();
//
//		// 调整外部窗口的大小和位置
//		SetWindowPos(m_hwnd, HWND_TOP, 0, 0, width, height, SWP_NOZORDER | SWP_SHOWWINDOW);
//	}
//}
//
//
//// 重写 resizeEvent，以防 QWidget 的大小改变时需要重新调整外部窗口的大小
//void EmbeddedWidget::resizeEvent(QResizeEvent* event) {
//	QWidget::resizeEvent(event);
//	adjustEmbeddedWindowSize();
//}


MainWindow* g_pMainWindow = NULL;

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	g_pMainWindow = this;

	setWindowTitle(GBK_STRING("数字样机一体化平台"));
	setWindowIcon(QIcon(":/image/CASC.png"));

	//m_pC7Zip = new C7Zip;
//	m_pC7Zip->ExtractFile(QString::fromLocal8Bit("D:\\Download\\��װ��\\navicat150_premium_cs_x64.rar"), "D:\\CS\\1998\\");
//	m_pC7Zip->Compress(QString::fromLocal8Bit("D:\\CS\\1998\\C1.zip"), QString::fromLocal8Bit("D:\\Download\\��װ��\\navicat150_premium_cs_x64"));
	//QString command = "cmdkey /add:192.168.1.247 /user:Administrator /pass:Ate123";

	//// 创建 QProcess 对象
	//QProcess process;

	//// 启动 cmd 进程并执行命令
	//process.start("cmd.exe", QStringList() << "/C" << command);

	//// 等待命令执行完成
	//if (process.waitForFinished())
	//{
	//    // 获取命令输出（用于调试或查看结果）
	//    QString output = process.readAllStandardOutput();
	//    QString error = process.readAllStandardError();

	//    // 打印输出到控制台
	//    qDebug() << "Output:" << output;
	//    qDebug() << "Error:" << error;
	//}
	//else
	//{
	//    qDebug() << "Process failed to start or execute.";
	//}
	// qss文件监控类
	m_pQssAutoLoader = new QssAutoLoader;
	QString strQssPath = QApplication::applicationDirPath() + "/qss/default.qss";
	strQssPath.replace("/", "\\\\");
	m_pQssAutoLoader->setAutoloadQss(strQssPath);
	ui->actionM1->setChecked(true);
	ui->actionM2->setChecked(true);
	ui->actionM3->setChecked(true);
	ui->actionM4->setChecked(true);

	/*connect(ui->actionM1, &QAction::triggered, ui->widgetM1, &QWidget::setVisible);
	connect(ui->actionM2, &QAction::triggered, ui->widgetM2, &QWidget::setVisible);
	connect(ui->actionM3, &QAction::triggered, ui->widgetM3, &QWidget::setVisible);
	connect(ui->actionM4, &QAction::triggered, ui->widgetM4, &QWidget::setVisible);*/

	// 隐藏用户登录后的图标
	ui->labelUserIcon->hide();
	initInitface();

	//QString target = "\\\\192.168.0.250\\"; // 实际路径
	//QString username = "share"; // 实际用户名
	//QString password = "Share123"; // 实际密码

	//common::addNetworkCredential(target, username, password);
	getBladeComputerData(common::setHostData);
	//initAccount();

	m_reconnectTimer = new QTimer(this);
	// 将定时器的超时信号连接到槽函数
	connect(m_reconnectTimer, &QTimer::timeout, this, &MainWindow::slot_reconnnectTimerOut);

	// 设置时间间隔并启动定时器
	//m_reconnectTimer->start(2000); // 每隔 10 (10000)秒触发一次
}


MainWindow::~MainWindow()
{
	int loginStatus = 0;
	int userId = m_LoginDialog->GetUserID();
	db::databaseDI::Instance().update_user_LoginStatus(userId, loginStatus);

	/*if (!db::databaseDI::Instance().updata_ipusername(m_LoginDialog->GetUser().toStdString()))
		return;*/

		/*if (!db::databaseDI::Instance().update_ip_all_status())
			return;*/

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
	/*if (m_FilemangageDialog != nullptr)
		delete m_FilemangageDialog;*/
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

	//m_FilemangageDialog = new FilemangageDialog(this);
	m_FtpDialog = new FtpDialog();

	m_ApprovalProgressDialog = new ApprovalProgressDialog(this);

	connect(m_ApprovalProgressDialog, &ApprovalProgressDialog::signal_createFtpUserDir, m_FtpDialog, &FtpDialog::slot_createUserDir);
	connect(m_ResourceManageDialog, &ResourceManageDialog::signal_udpOrderFinsh, m_FtpDialog, &FtpDialog::slot_orderFinsh);
	connect(m_ApprovalProgressDialog, &ApprovalProgressDialog::signal_ftpDownlaod, m_FtpDialog, &FtpDialog::slot_signalFtpDownlaod);
	//m_OneClickLoadDialog = new OneClickLoadDialog(this);
	//connect(m_OneClickLoadDialog, &OneClickLoadDialog::one_load_tools, this, &MainWindow::slot_one_load_tools);

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
		common::indexNum = 1;
	});
	connect(ui->btnModule2, &QPushButton::clicked, [this]() {
		ui->stackedWidget->setCurrentIndex(2);
		updateModuleToolIcon(2);
		common::indexNum = 2;
	});
	connect(ui->btnModule3, &QPushButton::clicked, [this]() {
		ui->stackedWidget->setCurrentIndex(3);
		updateModuleToolIcon(3);
		common::indexNum = 3;
	});
	connect(ui->btnModule4, &QPushButton::clicked, [this]() {
		ui->stackedWidget->setCurrentIndex(4);
		updateModuleToolIcon(4);
		common::indexNum = 4;
	});



	connect(ui->btnModule1, &CDoublePushButton::signal_doubleClicked, [this]() {
		ui->widgetM1->setVisible(!ui->widgetM1->isVisible());
	});
	connect(ui->btnModule2, &CDoublePushButton::signal_doubleClicked, [this]() {
		ui->widgetM2->setVisible(!ui->widgetM2->isVisible());
	});
	connect(ui->btnModule3, &CDoublePushButton::signal_doubleClicked, [this]() {
		ui->widgetM3->setVisible(!ui->widgetM3->isVisible());
	});
	connect(ui->btnModule4, &CDoublePushButton::signal_doubleClicked, [this]() {
		ui->widgetM4->setVisible(!ui->widgetM4->isVisible());
	});

	/*connect(ui->actionM1, &QAction::triggered, ui->widgetM1, &QWidget::setVisible);
	connect(ui->actionM2, &QAction::triggered, ui->widgetM2, &QWidget::setVisible);
	connect(ui->actionM3, &QAction::triggered, ui->widgetM3, &QWidget::setVisible);
	connect(ui->actionM4, &QAction::triggered, ui->widgetM4, &QWidget::setVisible);*/

	ui->btnResourceManage->setCheckable(true);
	ui->btnInformationConfihuration->setCheckable(true);
	ui->btnDataManage->setCheckable(true);
	ui->btnApprovalProgress->setCheckable(true);
	connect(ui->btnResourceManage, &QPushButton::clicked, this, &MainWindow::slot_btnResourceManageClicked);
	connect(ui->btnInformationConfihuration, &QPushButton::clicked, this, &MainWindow::slot_btnInformationConfihurationClicked);
	connect(ui->btnDataManage, &QPushButton::clicked, this, &MainWindow::slot_btnDataManageClicked);
	connect(ui->btnApprovalProgress, &QPushButton::clicked, this, &MainWindow::slot_btnApprovalProgressClicked);


	// 初始化模块1-4界面;
	ui->btnM2Load->hide();
	ui->btnM3Load->hide();
	ui->btnM4Load->hide();
	ui->btnM1Save->hide();
	ui->btnM2Save->hide();
	ui->btnM3Save->hide();
	ui->btnM4Save->hide();

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
	// 连接关闭请求信号到槽函数
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
	const char* sendData = strData.toStdString().c_str();// = data.c_str();

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
	//m_LoginDialog->setWindowFlags(windowFlags() | Qt::FramelessWindowHint);
	if (m_LoginDialog->exec() == QDialog::Accepted)
	{
		ui->labelUserName->setText(m_LoginDialog->GetUser());
		common::strLoginUserName = m_LoginDialog->GetUser();
		if (m_LoginDialog->GetPop())
		{
			ui->btnApprovalProgress->hide();
		}
		this->showMaximized();

		//ui->stackedWidget->setCurrentIndex(1);
		//ui->stackedWidget->setCurrentIndex(0);

		//m_FilemangageDialog->initTableViewDownload();
		//connect(m_OneClickSaveDialog, &OneClickSaveDialog::signals_zipMultPath, m_FilemangageDialog, &FilemangageDialog::slot_compressMultPath);
		common::getHostNameData();
		m_FtpDialog->initConnectFtp();
		// 设置时间间隔并启动定时器
		m_reconnectTimer->start(2000); // 每隔 10 (10000)秒触发一次
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
	common::getScreenCenterPos(x, y, m_ResourceManageDialog->width(), m_ResourceManageDialog->height());
	m_ResourceManageDialog->move(x, y);
	m_ResourceManageDialog->exec();
	m_ResourceManageDialog->stopWebFlushTimer();
	ui->btnResourceManage->setChecked(false);
}
void MainWindow::slot_btnInformationConfihurationClicked()
{
	/*int pop = 0;
	db::databaseDI::Instance().get_pop(pop, common::iUserID);
	if (pop == 1)
	{
		QPushButton *add1 = m_InforConfihurationDialog->getbtnToolAdd1();
		QPushButton *add2 = m_InforConfihurationDialog->getbtnToolAdd2();
		QPushButton *add3 = m_InforConfihurationDialog->getbtnToolAdd3();
		QPushButton *add4 = m_InforConfihurationDialog->getbtnToolAdd4();
		QPushButton *del1 = m_InforConfihurationDialog->getbtnToolDel1();
		QPushButton *del2 = m_InforConfihurationDialog->getbtnToolDel2();
		QPushButton *del3 = m_InforConfihurationDialog->getbtnToolDel3();
		QPushButton *del4 = m_InforConfihurationDialog->getbtnToolDel4();
		add1->setHidden(true);
		add2->setHidden(true);
		add3->setHidden(true);
		add4->setHidden(true);
		del1->setHidden(true);
		del2->setHidden(true);
		del3->setHidden(true);
		del4->setHidden(true);
	}*/
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
	//common::getScreenCenterPos(x, y, m_FilemangageDialog->width(), m_FilemangageDialog->height());
	//m_FilemangageDialog->move(x, y);
	//m_FilemangageDialog->show();

	m_FtpDialog->exec();
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
	int moduleNumber = pButton->property("module").toInt();


	QString strAssignIP = "";// 指定ip 主机;
	QString strAssignHostName = "";
	AddToolDialog addToooDialog(moduleNumber);
	if (addToooDialog.exec() == QDialog::Accepted)
	{
		QString toolName;
		QString tabName;
		int mode = -1;
		int displayMode = 0;
		QString  toolPath = -1;



		addToooDialog.getToolData(tabName, toolName, toolPath, mode, displayMode, strAssignIP, strAssignHostName);

		table_ip stipToolData;
		if (!db::databaseDI::Instance().get_ip_by_software(stipToolData, toolName.toStdString(), common::iLoginNum, moduleNumber))
		{
			return;
		}
		if (moduleNumber == 1 && stipToolData.used == 1)
		{

			strAssignIP = QString::fromStdString(stipToolData.ip);
			strAssignHostName = QString::fromStdString(stipToolData.host);


			QString hostname = QString::fromStdString(stipToolData.host);
			tabName = tabName + " " + hostname;
		}
		else
		{
			//QString hostname = QString::fromStdString(strAssignHostName);


			if (strAssignIP == "") // 模块234 下是指定还是CPu随机
			{
				table_ip_configure st;
				common::findIpWithGpuMinValue(st);

				strAssignIP = QString::fromStdString(st.ip);
				strAssignHostName = QString::fromStdString(st.hostname);
			}
			tabName = tabName + " " + strAssignHostName;
			//else
			//{
			//	//st.ip = strAssignIP.toStdString();
			//	//st.hostname = strAssignHostName.toStdString();
			//}
		}
		std::string strIP = strAssignIP.toStdString();
		if (strIP.empty())
		{
			QMessageBox::warning(this, QString::fromLocal8Bit("警告"), QString::fromLocal8Bit("ip错误 请检查代码！"));
			return;
		}

		QString strPwd;
		if (common::bAdministrator)
		{
			strPwd = common::strFtpAdminPwd;
		}
		else
		{
			strPwd = common::strFtpPwd;
		}
		CWidget* axTabWidget = new CWidget();
		//if (!db::databaseDI::Instance().get_one_ip_data(stipToolData, toolName.toStdString(), common::iLoginNum))
		//QString strAccount = getAccaunt(QString::fromStdString(strIP), toolName);
		QString str = "app\\";
		QString strAccount = str + common::strLoginUserName;
		if (strAccount.isEmpty())
		{
			QMessageBox::warning(this, QString::fromLocal8Bit("警告"), QString::fromLocal8Bit("远程软件用户数量不足！"));
			return;
		}
		if (moduleNumber == 1)
		{
			if (displayMode == 0)
			{
				axTabWidget->m_account = strAccount;
				axTabWidget->m_ip = strAssignIP;
				axTabWidget->m_softwareName = toolName;

				if (isHardwareAccelerator(strAssignHostName.toStdString()))
				{
					startLongDistanceHost(tabName, moduleNumber, strIP, strAccount.toStdString(), strPwd.toStdString(), axTabWidget, ui->tabWidgetModulel1);
				}
				else
				{
					startLongDistanceSoftware(tabName, moduleNumber, strIP, strAccount.toStdString(), strPwd.toStdString(), stipToolData.toolPath, axTabWidget, ui->tabWidgetModulel1);
				}
			}
			else
			{
				axTabWidget->m_account = strAccount;
				axTabWidget->m_ip = QString::fromStdString(strIP);
				axTabWidget->m_softwareName = toolName;

				if (isHardwareAccelerator(strAssignHostName.toStdString()))
				{
					startLongDistanceHost(tabName, moduleNumber, strIP, strAccount.toStdString(), strPwd.toStdString(), axTabWidget);
				}
				else
				{
					startLongDistanceSoftware(tabName, moduleNumber, strIP, strAccount.toStdString(), strPwd.toStdString(), stipToolData.toolPath, axTabWidget);
				}
			}
		}
		else if (moduleNumber == 2)
		{
			if (displayMode == 0)
			{

				axTabWidget->m_account = strAccount;
				axTabWidget->m_ip = QString::fromStdString(strIP);
				axTabWidget->m_softwareName = toolName;

				if (isHardwareAccelerator(strAssignHostName.toStdString()))
				{
					startLongDistanceHost(tabName, moduleNumber, strIP, strAccount.toStdString(), strPwd.toStdString(), axTabWidget, ui->tabWidgetModulel2);
				}
				else
				{
					startLongDistanceSoftware(tabName, moduleNumber, strIP, strAccount.toStdString(), strPwd.toStdString(), stipToolData.toolPath, axTabWidget, ui->tabWidgetModulel2);
				}

			}
			else
			{
				axTabWidget->m_account = strAccount;
				axTabWidget->m_ip = QString::fromStdString(strIP);
				axTabWidget->m_softwareName = toolName;
				if (isHardwareAccelerator(strAssignHostName.toStdString()))
				{
					startLongDistanceHost(tabName, moduleNumber, strIP, strAccount.toStdString(), strPwd.toStdString(), axTabWidget);
				}
				else
				{
					startLongDistanceSoftware(tabName, moduleNumber, strIP, strAccount.toStdString(), strPwd.toStdString(), stipToolData.toolPath, axTabWidget);
				}
			}
		}
		else if (moduleNumber == 3)
		{

			if (displayMode == 0)
			{

				axTabWidget->m_account = strAccount;
				axTabWidget->m_ip = QString::fromStdString(strIP);
				axTabWidget->m_softwareName = toolName;
				if (isHardwareAccelerator(strAssignHostName.toStdString()))
				{
					startLongDistanceHost(tabName, moduleNumber, strIP, strAccount.toStdString(), strPwd.toStdString(), axTabWidget, ui->tabWidgetModulel3);
				}
				else
				{
					startLongDistanceSoftware(tabName, moduleNumber, strIP, strAccount.toStdString(), strPwd.toStdString(), stipToolData.toolPath, axTabWidget, ui->tabWidgetModulel3);

				}
			}
			else
			{
				axTabWidget->m_account = strAccount;
				axTabWidget->m_ip = QString::fromStdString(strIP);
				axTabWidget->m_softwareName = toolName;
				if (isHardwareAccelerator(strAssignHostName.toStdString()))
				{
					startLongDistanceHost(tabName, moduleNumber, strIP, strAccount.toStdString(), strPwd.toStdString(), axTabWidget);
				}
				else
				{
					startLongDistanceSoftware(tabName, moduleNumber, strIP, strAccount.toStdString(), strPwd.toStdString(), stipToolData.toolPath, axTabWidget);
				}
			}
		}
		else if (moduleNumber == 4)
		{

			if (displayMode == 0)
			{

				axTabWidget->m_account = strAccount;
				axTabWidget->m_ip = QString::fromStdString(strIP);
				axTabWidget->m_softwareName = toolName;
				if (isHardwareAccelerator(strAssignHostName.toStdString()))
				{
					startLongDistanceHost(tabName, moduleNumber, strIP, strAccount.toStdString(), strPwd.toStdString(), axTabWidget, ui->tabWidgetModulel4);
				}
				else
				{
					startLongDistanceSoftware(tabName, moduleNumber, strIP, strAccount.toStdString(), strPwd.toStdString(), stipToolData.toolPath, axTabWidget, ui->tabWidgetModulel4);
				}
			}
			else
			{
				axTabWidget->m_account = strAccount;
				axTabWidget->m_ip = QString::fromStdString(strIP);
				axTabWidget->m_softwareName = toolName;
				if (isHardwareAccelerator(strAssignHostName.toStdString()))
				{
					startLongDistanceHost(tabName, moduleNumber, strIP, strAccount.toStdString(), strPwd.toStdString(), axTabWidget);
				}
				else
				{
					startLongDistanceSoftware(tabName, moduleNumber, strIP, strAccount.toStdString(), strPwd.toStdString(), stipToolData.toolPath, axTabWidget);
				}
			}
		}
	}
}

void MainWindow::slot_btnOneClickLoad()
{
	m_OneClickLoadDialog = new OneClickLoadDialog(this);
	connect(m_OneClickLoadDialog, &OneClickLoadDialog::one_load_tools, this, &MainWindow::slot_one_load_tools);

	QPushButton* pButton = (QPushButton*)sender();

	common::index = getBtnLoadIndex(pButton);

	m_OneClickLoadDialog->initTableView();

	m_OneClickLoadDialog->exec();
	//QPushButton* pButton = (QPushButton*)sender();
	int module = pButton->property("module").toInt();
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
	// 创建消息框
	QMessageBox msgBox;
	// 设置消息框的内容
	msgBox.setText(QString::fromLocal8Bit("请确认保存工程之后再关闭Tab页:"));
	// 创建自定义按钮
	QPushButton* button1 = msgBox.addButton(QString::fromLocal8Bit("坚持关闭"), QMessageBox::ActionRole);
	QPushButton* button3 = msgBox.addButton(QString::fromLocal8Bit("取消关闭"), QMessageBox::RejectRole);
	// 设置消息框的图标
	msgBox.setIcon(QMessageBox::Information);
	// 显示消息框
	msgBox.exec();
	// 判断按下的是哪个按钮
	if (msgBox.clickedButton() != button1) {
		//qDebug() << "用户选择了 选项 1";
		return;
	}

	// 通过 axTabWidget 获取 rdp 的指针
	CWidget* axTabWidget = (CWidget*)ui->tabWidgetModulel1->widget(index);
	if (!axTabWidget)
	{
		return;
	}

	if (axTabWidget->m_pAxWidget)
	{
		axTabWidget->m_pAxWidget->dynamicCall("Disconnect()");
		axTabWidget->m_pAxWidget->dynamicCall("RequestClose()");//关闭插件
	}
	QString strAcc = axTabWidget->m_account;
	QString strIp = axTabWidget->m_ip;
	addAccaunt(axTabWidget->m_ip, axTabWidget->m_softwareName, axTabWidget->m_account);

	ui->tabWidgetModulel1->removeTab(index); // 移除标签
}

void MainWindow::slot_tabModule2closeTab(int index)
{
	if (index <= 0)
	{
		return;
	}
	// 创建消息框
	QMessageBox msgBox;
	// 设置消息框的内容
	msgBox.setText(QString::fromLocal8Bit("请确认保存工程之后再关闭Tab页:"));
	// 创建自定义按钮
	QPushButton* button1 = msgBox.addButton(QString::fromLocal8Bit("坚持关闭"), QMessageBox::ActionRole);
	QPushButton* button3 = msgBox.addButton(QString::fromLocal8Bit("取消关闭"), QMessageBox::RejectRole);
	// 设置消息框的图标
	msgBox.setIcon(QMessageBox::Information);
	// 显示消息框
	msgBox.exec();
	// 判断按下的是哪个按钮
	if (msgBox.clickedButton() != button1) {
		//qDebug() << "用户选择了 选项 1";
		return;
	}

	// 通过 axTabWidget 获取 rdp 的指针
	CWidget* axTabWidget = (CWidget*)ui->tabWidgetModulel2->widget(index);
	if (!axTabWidget)
	{
		return;
	}
	if (axTabWidget->m_pAxWidget)
	{
		axTabWidget->m_pAxWidget->dynamicCall("Disconnect()");
		axTabWidget->m_pAxWidget->dynamicCall("RequestClose()");//关闭插件
	}
	QString strAcc = axTabWidget->m_account;
	QString strIp = axTabWidget->m_ip;
	addAccaunt(axTabWidget->m_ip, axTabWidget->m_softwareName, axTabWidget->m_account);
	ui->tabWidgetModulel2->removeTab(index); // 移除标签
}

void MainWindow::slot_tabModule3closeTab(int index)
{
	if (index <= 0)
	{
		return;
	}
	// 创建消息框
	QMessageBox msgBox;
	// 设置消息框的内容
	msgBox.setText(QString::fromLocal8Bit("请确认保存工程之后再关闭Tab页:"));
	// 创建自定义按钮
	QPushButton* button1 = msgBox.addButton(QString::fromLocal8Bit("坚持关闭"), QMessageBox::ActionRole);
	QPushButton* button3 = msgBox.addButton(QString::fromLocal8Bit("取消关闭"), QMessageBox::RejectRole);
	// 设置消息框的图标
	msgBox.setIcon(QMessageBox::Information);
	// 显示消息框
	msgBox.exec();
	// 判断按下的是哪个按钮
	if (msgBox.clickedButton() != button1) {

		return;
	}

	// 通过 axTabWidget 获取 rdp 的指针
	CWidget* axTabWidget = (CWidget*)ui->tabWidgetModulel3->widget(index);
	if (!axTabWidget)
	{
		return;
	}
	if (axTabWidget->m_pAxWidget)
	{
		axTabWidget->m_pAxWidget->dynamicCall("Disconnect()");
		axTabWidget->m_pAxWidget->dynamicCall("RequestClose()");//关闭插件
	}
	QString strAcc = axTabWidget->m_account;
	QString strIp = axTabWidget->m_ip;
	addAccaunt(axTabWidget->m_ip, axTabWidget->m_softwareName, axTabWidget->m_account);
	ui->tabWidgetModulel3->removeTab(index); // 移除标签   
}

void MainWindow::slot_tabModule4closeTab(int index)
{
	if (index <= 0)
	{
		return;
	}
	// 创建消息框
	QMessageBox msgBox;
	// 设置消息框的内容
	msgBox.setText(QString::fromLocal8Bit("请确认保存工程之后再关闭Tab页:"));
	// 创建自定义按钮
	QPushButton* button1 = msgBox.addButton(QString::fromLocal8Bit("坚持关闭"), QMessageBox::ActionRole);
	QPushButton* button3 = msgBox.addButton(QString::fromLocal8Bit("取消关闭"), QMessageBox::RejectRole);
	// 设置消息框的图标
	msgBox.setIcon(QMessageBox::Information);
	// 显示消息框
	msgBox.exec();
	// 判断按下的是哪个按钮
	if (msgBox.clickedButton() != button1) {
		//qDebug() << "用户选择了 选项 1";
		return;
	}

	// 通过 axTabWidget 获取 rdp 的指针
	CWidget* axTabWidget = (CWidget*)ui->tabWidgetModulel4->widget(index);
	if (!axTabWidget)
	{
		return;
	}
	if (axTabWidget->m_pAxWidget)
	{
		axTabWidget->m_pAxWidget->dynamicCall("Disconnect()");
		axTabWidget->m_pAxWidget->dynamicCall("RequestClose()");//关闭插件
	}
	QString strAcc = axTabWidget->m_account;
	QString strIp = axTabWidget->m_ip;
	addAccaunt(axTabWidget->m_ip, axTabWidget->m_softwareName, axTabWidget->m_account);
	ui->tabWidgetModulel4->removeTab(index); // 移除标签    
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

	//创建竖线
	QFrame *line = new QFrame();
	line->setFrameShape(QFrame::VLine);  // 设置为竖线
	line->setFrameShadow(QFrame::Sunken);  // 设置阴影为凹陷
	line->setLineWidth(2);  // 设置线宽
	line->setMidLineWidth(1);  // 设置中间线宽
	line->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::MinimumExpanding);  // 设置大小策略

	if (db::databaseDI::Instance().get_ip_data(ipMap, module, common::iLoginNum))
	{
		for (const auto& stTool : ipMap)
		{
			const std::string& software = stTool.first;
			const table_ip& data = stTool.second;
			if (data.used == 1)
			{
				QToolButton* pBtn = new QToolButton();
				//QPushButton* pBtn = new QPushButton(QString::fromLocal8Bit("测试"));
				//pBtn->setIcon(QIcon(QString::fromStdString(data.icoPath)));

				QImage img;
				img.loadFromData(reinterpret_cast<const uchar*>(data.imageData.data()), data.imageData.size());
				// 将 QImage 转换为 QIcon
				QIcon icon(QPixmap::fromImage(img));
				// 设置 QToolButton 的图标
				pBtn->setIcon(icon);
				pBtn->setIconSize(QSize(50, 46));
				pBtn->setText(QString::fromStdString(software));
				pBtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
				pBtn->setStyleSheet("background-color:rgba(0,0,0,0);font-size: 12px;");
				pBtn->setFocusPolicy(Qt::NoFocus);
				pBtn->setFixedSize(55, 64);
				//pBtn->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);  // 设置按钮的大小策略
				pBtn->setEnabled(true);

				pLayout->addWidget(pBtn);

				//鼠标右击事件
				//RightClickEvent *rightclick = new RightClickEvent;
				//pBtn->installEventFilter(rightclick);
				//connect(rightclick, &RightClickEvent::rightClicked, this, &MainWindow::onRightClicked);
				//鼠标双击事件
				DoubleClickInterceptor *interceptor = new DoubleClickInterceptor;
				pBtn->installEventFilter(interceptor);
				connect(interceptor, &DoubleClickInterceptor::doubleClicked, this, &MainWindow::onDoubleClicked);
			}
		}
	}
	if(module == 1)
	pLayout->addWidget(line);

	db::databaseDI::Instance().get_ip_data(ipMap, module, common::iLoginNum);
	for (const auto& stTool : ipMap)
	{
		const std::string& software = stTool.first;
		const table_ip& data = stTool.second;
		if (data.used == 0)
		{
			QToolButton* pBtn = new QToolButton();
			QImage img;
			img.loadFromData(reinterpret_cast<const uchar*>(data.imageData.data()), data.imageData.size());
			// 将 QImage 转换为 QIcon
			QIcon icon(QPixmap::fromImage(img));
			// 设置 QToolButton 的图标
			pBtn->setIcon(icon);
			pBtn->setIconSize(QSize(50, 46));
			pBtn->setText(QString::fromStdString(software));
			pBtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
			pBtn->setStyleSheet("background-color:rgba(0,0,0,0);font-size: 12px;");
			pBtn->setFocusPolicy(Qt::NoFocus);
			pBtn->setFixedSize(55, 64);
			//pBtn->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);  // 设置按钮的大小策略
			pBtn->setEnabled(true);

			pLayout->addWidget(pBtn);

			//鼠标双击事件
			DoubleClickInterceptor *interceptor = new DoubleClickInterceptor;
			pBtn->installEventFilter(interceptor);
			connect(interceptor, &DoubleClickInterceptor::doubleClicked, this, &MainWindow::onDoubleClicked);
		}
	}
}

void MainWindow::startUdpRdp(const QString ip)
{
	QAxWidget* rdp = new QAxWidget;
	//rdp->setControl(QString::fromUtf8("{1DF7C823-B2D4-4B54-975A-F2AC5D7CF8B8}")); // 对应于RDP的CLSID
	rdp->setControl(QString::fromUtf8(common::strAxCLSID.toUtf8())); // 对应于RDP的CLSID
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
	connect(widget, &CWidget::signal_softwareClose, this, &MainWindow::slot_widgetAboutToQuit);



	// 嵌入远端界面;
  //  QAxWidget* rdp = new QAxWidget;
	CAxWidget* rdp = new CAxWidget;
	//rdp->setControl(QString::fromUtf8("{1DF7C823-B2D4-4B54-975A-F2AC5D7CF8B8}")); // 对应于RDP的CLSID
	rdp->setControl(QString::fromUtf8(common::strAxCLSID.toUtf8())); // 对应于RDP的CLSID

	bool b = rdp->setProperty("Server", strIp.c_str()); // 远程桌面的IP地址
	b = rdp->setProperty("UserName", strAccaunt.c_str()); // 用户名
	b = rdp->setProperty("Password", pwd.c_str()); // 密码
	//b = rdp->setProperty("FullScreen", true); // 是否全屏
	//b = rdp->setProperty("DesktopWidth", this->width()-29);         //指定宽度
	//b = rdp->setProperty("DesktopHeight", this->height()-29);        //指定高度
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
		b = rdp->setProperty("DesktopWidth", width);         //指定宽度
		b = rdp->setProperty("DesktopHeight", height);        //指定高度
		qDebug() << "1111" << "width :" << width << "height : " << height;
	}
	else
	{
		b = rdp->setProperty("DesktopWidth", this->width() - 29);         //指定宽度
		b = rdp->setProperty("DesktopHeight", this->height() - 29);        //指定高度
	}

	//b = rdp->setProperty("ConnectingText", QString::fromUtf8("Visual Studio 2017"));
	b = rdp->setProperty("DisconnectedText", QString::fromLocal8Bit("远程连接已断开，请关闭标签页"));
	//b = rdp->setProperty("Domain", QString::fromUtf8("AD.jhapp.com"));
	b = rdp->setProperty("LoadBalanceInfo", QString::fromUtf8("tsv://MS Terminal Services Plugin.1.RDAPP"));
	//b = rdp->setProperty("LaunchedViaClientShellInterface", true);

	//普通参数,可选项
	rdp->setFocusPolicy(Qt::StrongFocus);        //设置控件接收键盘焦点的方式：鼠标单击、Tab键
	b = rdp->setProperty("ColorDepth", 32);          //画质/位深,32/24/16/15/8

	//高级参数
	QAxObject* pAdvancedObject = rdp->querySubObject("AdvancedSettings2");
	if (pAdvancedObject)
	{
		b = pAdvancedObject->setProperty("ClearTextPassword", pwd.c_str());     //用户密码(这种方式每次都不需要手动输入密码)
		b = pAdvancedObject->setProperty("EnableCredSspSupport", true); //必须设置,否则远程连接失败

		//高级参数,可选项
		b = pAdvancedObject->setProperty("BitmapPeristence", 1);         //位图缓存
		b = pAdvancedObject->setProperty("Compress", 1);                 //启用压缩,减小带宽
		b = pAdvancedObject->setProperty("singleConnectionTimeout", 10); //超时时间,s
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
	// QString strArguments1 = QString::fromUtf8("C:\\StartApp\\StartApp.exe \"C:\\Program Files (x86)\\Microsoft Visual Studio\\2017\\Enterprise\\Common7\\IDE\\devenv.exe\"");
	QString strArguments1 = QString::fromUtf8("C:\\QStartApp\\release\\StartApp.exe ");
	//   stipToolData.toolPath="\"C:\\Program Files (x86)\\Microsoft Visual Studio\\2017\\Enterprise\\Common7\\IDE\\devenv.exe\"";
	//QString path2 = QString::fromUtf8("C:\\Program Files (x86)\\Microsoft Visual Studio\\2017\\Enterprise\\Common7\\IDE\\devenv.exe");

	//QString strArguments = strArguments1 + " \"" + QString::fromStdString(path) + "\"" +"|" +common::strLoginUserName;
	QString strArguments = strArguments1 + " \"" + QString::fromStdString(path) + "|" + common::strLoginUserName + "\"";
	if (pSecuredmObject)
	{
		b = pSecuredmObject->setProperty("Fullscreen", true);
		//b = pSecuredmObject->setProperty("StartProgram", QString::fromUtf8("C:\\StartApp\\StartApp.exe \"C:\\Program Files\\Polyspace\\R2021a\\bin\\win64\\MATLAB.exe\""));
		//b = pSecuredmObject->setProperty("StartProgram", QString::fromUtf8("C:\\StartApp\\StartApp.exe \"C:\\Program Files (x86)\\National Instruments\\Circuit Design Suite 14.0\\multisim.exe\""));
		b = pSecuredmObject->setProperty("StartProgram", strArguments);
		//b = pSecuredmObject->setProperty("StartProgram", QString::fromUtf8("C:\\StartApp\\StartApp.exe \"C:\\MentorGraphics\\EEVX.2.8\\SDD_HOME\\common\\win64\\bin\\viewdraw.exe\""));
		//b = pSecuredmObject->setProperty("StartProgram", QString::fromUtf8("C:\\StartApp\\StartApp.exe \"C:\\MentorGraphics\\EEVX.2.8\\SDD_HOME\\common\\win64\\bin\\systemvision.bat\""));
		//b = pSecuredmObject->setProperty("StartProgram", QString::fromUtf8("C:\\StartApp\\StartApp.exe"));
		b = pSecuredmObject->setProperty("AudioRedirectionMode", true);
		b = pSecuredmObject->setProperty("KeyboardHookMode", true);
		//b = pSecuredmObject->setProperty("PCB", "2013");
	}
	QVariant v2 = rdp->dynamicCall("Connect()"); //连接

	QVBoxLayout* layout = new QVBoxLayout(widget);
	layout->addWidget(rdp);
	layout->setMargin(0);
	widget->setLayout(layout);
	widget->m_pAxWidget = rdp;
	if (tabWidget != nullptr)
	{
		//tabWidget->addTab(widget, tabName);
		int intdex = tabWidget->addTab(widget, tabName);
		tabWidget->setCurrentIndex(intdex);
	}
	else
	{
		widget->setWindowTitle(tabName);
		widget->showMaximized();
		widget->show();
	}
}


void MainWindow::startLongDistanceHost(const QString tabName, const int& module, const std::string strIp, const std::string strAccaunt, const std::string pwd, CWidget* widget, QTabWidget* tabWidget)
{
	connect(widget, &CWidget::signal_softwareClose, this, &MainWindow::slot_widgetAboutToQuit);



	// 嵌入远端界面;
  //  QAxWidget* rdp = new QAxWidget;
	CAxWidget* rdp = new CAxWidget;
	//rdp->setControl(QString::fromUtf8("{1DF7C823-B2D4-4B54-975A-F2AC5D7CF8B8}")); // 对应于RDP的CLSID
	rdp->setControl(QString::fromUtf8(common::strAxCLSID.toUtf8())); // 对应于RDP的CLSID

	bool b = rdp->setProperty("Server", strIp.c_str()); // 远程桌面的IP地址
	b = rdp->setProperty("UserName", strAccaunt.c_str()); // 用户名
	b = rdp->setProperty("Password", pwd.c_str()); // 密码
	//b = rdp->setProperty("FullScreen", true); // 是否全屏
	//b = rdp->setProperty("DesktopWidth", this->width()-29);         //指定宽度
	//b = rdp->setProperty("DesktopHeight", this->height()-29);        //指定高度
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
		b = rdp->setProperty("DesktopWidth", width);         //指定宽度
		b = rdp->setProperty("DesktopHeight", height);        //指定高度
		qDebug() << "1111" << "width :" << width << "height : " << height;
	}
	else
	{
		b = rdp->setProperty("DesktopWidth", this->width() - 29);         //指定宽度
		b = rdp->setProperty("DesktopHeight", this->height() - 29);        //指定高度
	}

	//b = rdp->setProperty("ConnectingText", QString::fromUtf8("Visual Studio 2017"));
	b = rdp->setProperty("DisconnectedText", QString::fromLocal8Bit("远程连接已断开，请关闭标签页"));
	//b = rdp->setProperty("Domain", QString::fromUtf8("AD.jhapp.com"));
	b = rdp->setProperty("LoadBalanceInfo", QString::fromUtf8("tsv://MS Terminal Services Plugin.1.RDAPP"));
	//b = rdp->setProperty("LaunchedViaClientShellInterface", true);

	//普通参数,可选项
	rdp->setFocusPolicy(Qt::StrongFocus);        //设置控件接收键盘焦点的方式：鼠标单击、Tab键
	b = rdp->setProperty("ColorDepth", 32);          //画质/位深,32/24/16/15/8

	//高级参数
	QAxObject* pAdvancedObject = rdp->querySubObject("AdvancedSettings2");
	if (pAdvancedObject)
	{
		b = pAdvancedObject->setProperty("ClearTextPassword", pwd.c_str());     //用户密码(这种方式每次都不需要手动输入密码)
		b = pAdvancedObject->setProperty("EnableCredSspSupport", true); //必须设置,否则远程连接失败

		//高级参数,可选项
		b = pAdvancedObject->setProperty("BitmapPeristence", 1);         //位图缓存
		b = pAdvancedObject->setProperty("Compress", 1);                 //启用压缩,减小带宽
		b = pAdvancedObject->setProperty("singleConnectionTimeout", 10); //超时时间,s
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
	// QString strArguments1 = QString::fromUtf8("C:\\StartApp\\StartApp.exe \"C:\\Program Files (x86)\\Microsoft Visual Studio\\2017\\Enterprise\\Common7\\IDE\\devenv.exe\"");
   // QString strArguments1 = QString::fromUtf8("C:\\StartApp\\StartApp.exe ");
	//   stipToolData.toolPath="\"C:\\Program Files (x86)\\Microsoft Visual Studio\\2017\\Enterprise\\Common7\\IDE\\devenv.exe\"";
	//QString path2 = QString::fromUtf8("C:\\Program Files (x86)\\Microsoft Visual Studio\\2017\\Enterprise\\Common7\\IDE\\devenv.exe");

   // QString strArguments = strArguments1 + " \"" + QString::fromStdString(path) + "\"";

	//if (pSecuredmObject)
	//{
	//    b = pSecuredmObject->setProperty("Fullscreen", true);
	//    //b = pSecuredmObject->setProperty("StartProgram", QString::fromUtf8("C:\\QStartApp\\release\\StartApp.exe \"C:\\Program Files\\Polyspace\\R2021a\\bin\\win64\\MATLAB.exe\""));
	//    //b = pSecuredmObject->setProperty("StartProgram", QString::fromUtf8("C:\\StartApp\\StartApp.exe \"C:\\Program Files (x86)\\National Instruments\\Circuit Design Suite 14.0\\multisim.exe\""));
	//    b = pSecuredmObject->setProperty("StartProgram", strArguments);
	//    //b = pSecuredmObject->setProperty("StartProgram", QString::fromUtf8("C:\\QStartApp\\StartApp.exe \"C:\\MentorGraphics\\EEVX.2.8\\SDD_HOME\\common\\win64\\bin\\viewdraw.exe\""));
	//    //b = pSecuredmObject->setProperty("StartProgram", QString::fromUtf8("C:\\QStartApp\\release\\StartApp.exe \"C:\\MentorGraphics\\EEVX.2.8\\SDD_HOME\\common\\win64\\bin\\systemvision.bat\""));
	//    //b = pSecuredmObject->setProperty("StartProgram", QString::fromUtf8("C:\\QStartApp\\release\\StartApp.exe"));
	//    b = pSecuredmObject->setProperty("AudioRedirectionMode", true);
	//    b = pSecuredmObject->setProperty("KeyboardHookMode", true);
	//    //b = pSecuredmObject->setProperty("PCB", "2013");
	//}
	QVariant v2 = rdp->dynamicCall("Connect()"); //连接

	QVBoxLayout* layout = new QVBoxLayout(widget);
	layout->addWidget(rdp);
	layout->setMargin(0);
	widget->setLayout(layout);
	widget->m_pAxWidget = rdp;
	if (tabWidget != nullptr)
	{
		int intdex=tabWidget->addTab(widget, tabName);
		tabWidget->setCurrentIndex(intdex);

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
	else if (btn->objectName() == "btnM2Load")
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

bool MainWindow::isHardwareAccelerator(const std::string str)
{
	std::string  prefix = "加速机";
	QString strprefix = QString::fromLocal8Bit("加速机");
	QString  value = QString::fromStdString(str);
	if (value.contains(strprefix))
	{
		return true;
	}
	/* if (value.compare(0, prefix.size(), prefix) == 0) {
		 return true;
	 }*/

	return false;
}

// 获取所有刀片机信息;
void MainWindow::getBladeComputerData(std::vector<table_ip_configure>& vecHostData)
{
	vecHostData.clear();
	std::list<table_ip_configure> listHostData;
	db::databaseDI::Instance().get_all_ip(listHostData);

	QString strprefix = QString::fromLocal8Bit("加速机");

	for (const auto& st : listHostData)
	{
		QString  value = QString::fromStdString(st.hostname);
		if (!value.contains(strprefix))
		{
			vecHostData.push_back(st);
		}
	}
}

void MainWindow::slot_reconnnectTimerOut()
{
	if (db::databaseDI::Instance().IsConnectLost())
	{
		if (!db::databaseDI::Instance().open())
		{
			//QMessageBox::warning(nullptr, QString::fromLocal8Bit("警告"), QString::fromLocal8Bit("数据库连接失败"));
			//return;
		}
	}
	if (m_FtpDialog)
	{
		int a = 0;
		m_FtpDialog->reConnectFtp();
	}

}

void MainWindow::slot_one_load_tools(int moduleNum, const QString &toolsName)
{
	table_ip stipToolData;
	//if (!db::databaseDI::Instance().get_one_ip_data(stipToolData, toolsName.toStdString(), common::iLoginNum))
	if (!db::databaseDI::Instance().get_ip_by_software(stipToolData, toolsName.toStdString(), common::iLoginNum, moduleNum))
	{
		return;
	}
	//QString strAccount = getAccaunt(QString::fromStdString(stipToolData.ip), toolsName);
	QString str = "app\\";
	QString strAccount = str + common::strLoginUserName;
	if (strAccount.isEmpty())
	{
		QMessageBox::warning(this, QString::fromLocal8Bit("警告"), QString::fromLocal8Bit("远程软件用户数量不足！"));
		return;
	}

	QString strPwd = "Atexcel@123";

	CWidget* axTabWidget = new CWidget();

	table_ip_configure st;
	common::findIpWithGpuMinValue(st);
	std::string strIP = st.ip;
	if (strIP.empty())
	{
		QMessageBox::warning(this, QString::fromLocal8Bit("警告"), QString::fromLocal8Bit("ip错误 请检查代码！"));
		return;
	}

	if (moduleNum == 1)
	{
		axTabWidget->m_account = strAccount;
		axTabWidget->m_ip = QString::fromStdString(stipToolData.ip);
		axTabWidget->m_softwareName = toolsName;
		if (isHardwareAccelerator(stipToolData.host))
		{
			startLongDistanceHost(toolsName + " " + QString::fromStdString(stipToolData.host), common::index, stipToolData.ip, strAccount.toStdString(), strPwd.toStdString(), axTabWidget, ui->tabWidgetModulel1);
		}
		else
		{
			startLongDistanceSoftware(toolsName + " " + QString::fromStdString(stipToolData.host), common::index, stipToolData.ip, strAccount.toStdString(), strPwd.toStdString(), stipToolData.toolPath, axTabWidget, ui->tabWidgetModulel1);

		}
	}
	else if (moduleNum == 2)
	{
		QString exeDir = QCoreApplication::applicationDirPath();
		axTabWidget->m_account = strAccount;
		axTabWidget->m_ip = QString::fromStdString(strIP);
		axTabWidget->m_softwareName = toolsName;

		if (isHardwareAccelerator(st.hostname))
		{
			startLongDistanceHost(toolsName + " " + QString::fromStdString(st.hostname), common::index, strIP, strAccount.toStdString(), strPwd.toStdString(), axTabWidget, ui->tabWidgetModulel2);
		}
		else
		{
			startLongDistanceSoftware(toolsName + " " + QString::fromStdString(st.hostname), common::index, strIP, strAccount.toStdString(), strPwd.toStdString(), stipToolData.toolPath, axTabWidget, ui->tabWidgetModulel2);
		}

	}
	else if (moduleNum == 3)
	{
		axTabWidget->m_account = strAccount;
		axTabWidget->m_ip = QString::fromStdString(strIP);
		axTabWidget->m_softwareName = toolsName;

		if (isHardwareAccelerator(st.hostname))
		{
			startLongDistanceHost(toolsName + " " + QString::fromStdString(st.hostname), common::index, strIP, strAccount.toStdString(), strPwd.toStdString(), axTabWidget, ui->tabWidgetModulel3);

		}
		else
		{
			startLongDistanceSoftware(toolsName + " " + QString::fromStdString(st.hostname), common::index, strIP, strAccount.toStdString(), strPwd.toStdString(), stipToolData.toolPath, axTabWidget, ui->tabWidgetModulel3);
		}

	}
	else if (moduleNum == 4)
	{
		axTabWidget->m_account = strAccount;
		axTabWidget->m_ip = QString::fromStdString(strIP);
		axTabWidget->m_softwareName = toolsName;
		if (isHardwareAccelerator(st.hostname))
		{
			startLongDistanceHost(toolsName + " " + QString::fromStdString(st.hostname), common::index, strIP, strAccount.toStdString(), strPwd.toStdString(), axTabWidget, ui->tabWidgetModulel4);
		}
		else
		{
			startLongDistanceSoftware(toolsName + " " + QString::fromStdString(st.hostname), common::index, strIP, strAccount.toStdString(), strPwd.toStdString(), stipToolData.toolPath, axTabWidget, ui->tabWidgetModulel4);
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

void MainWindow::onDoubleClicked(const QString &buttonText)
{
	table_ip stipToolData;
	if (!db::databaseDI::Instance().get_ip_by_software(stipToolData, buttonText.toStdString(), common::iLoginNum, common::indexNum))
	{
		return;
	}
	QString str = "app\\";
	QString strAccount = str + common::strLoginUserName;
	if (strAccount.isEmpty())
	{
		QMessageBox::warning(this, QString::fromLocal8Bit("警告"), QString::fromLocal8Bit("远程软件用户数量不足！"));
		return;
	}

	QString strPwd = "Atexcel@123";

	CWidget* axTabWidget = new CWidget();

	table_ip_configure st;
	common::findIpWithGpuMinValue(st);
	std::string strIP = st.ip;
	if (strIP.empty())
	{
		QMessageBox::warning(this, QString::fromLocal8Bit("警告"), QString::fromLocal8Bit("ip错误 请检查代码！"));
		return;
	}

	if (common::indexNum == 1)
	{
		if (stipToolData.used == 1)//模块1下固定ip启动
		{
			axTabWidget->m_account = strAccount;
			axTabWidget->m_ip = QString::fromStdString(stipToolData.ip);
			axTabWidget->m_softwareName = buttonText;
			if (isHardwareAccelerator(stipToolData.host))
			{
				startLongDistanceHost(buttonText + " " + QString::fromStdString(stipToolData.host), common::indexNum, stipToolData.ip, strAccount.toStdString(), strPwd.toStdString(), axTabWidget, ui->tabWidgetModulel1);
			}
			else
			{
				startLongDistanceSoftware(buttonText + " " + QString::fromStdString(stipToolData.host), common::indexNum, stipToolData.ip, strAccount.toStdString(), strPwd.toStdString(), stipToolData.toolPath, axTabWidget, ui->tabWidgetModulel1);

			}
		}
		else if (stipToolData.used == 0) //模块1下指定ip启动
		{
			QString strAssignIP = "";// 指定ip 主机;
			QString strAssignHostName = "";

			AddToolDialog addToooDialog(common::indexNum);
			QComboBox *toolComboBox = addToooDialog.getComboBox();
			toolComboBox->setEnabled(false);
			toolComboBox->setCurrentText(buttonText);
			if (addToooDialog.exec() == QDialog::Accepted)
			{
				QString toolName;
				QString tabName;
				int mode = -1;
				int displayMode = 0;
				QString  toolPath = -1;

				addToooDialog.getToolData(tabName, toolName, toolPath, mode, displayMode, strAssignIP, strAssignHostName);
				table_ip stipToolData;
				if (!db::databaseDI::Instance().get_ip_by_software(stipToolData, buttonText.toStdString(), common::iLoginNum, common::indexNum))
				{
					return;
				}
				if (strAssignIP == "") // 模块234 下是指定还是CPu随机
				{
					table_ip_configure st;
					common::findIpWithGpuMinValue(st);

					strAssignIP = QString::fromStdString(st.ip);
					strAssignHostName = QString::fromStdString(st.hostname);
				}
				tabName = tabName + " " + strAssignHostName;

				std::string strIP = strAssignIP.toStdString();
				if (strIP.empty())
				{
					QMessageBox::warning(this, QString::fromLocal8Bit("警告"), QString::fromLocal8Bit("ip错误 请检查代码！"));
					return;
				}

				QString strPwd;
				if (common::bAdministrator)
				{
					strPwd = common::strFtpAdminPwd;
				}
				else
				{
					strPwd = common::strFtpPwd;
				}
				CWidget* axTabWidget = new CWidget();
				QString str = "app\\";
				QString strAccount = str + common::strLoginUserName;
				if (displayMode == 0)
				{

					axTabWidget->m_account = strAccount;
					axTabWidget->m_ip = QString::fromStdString(strIP);
					axTabWidget->m_softwareName = buttonText;

					if (isHardwareAccelerator(strAssignHostName.toStdString()))
					{
						startLongDistanceHost(tabName, common::indexNum, strIP, strAccount.toStdString(), strPwd.toStdString(), axTabWidget, ui->tabWidgetModulel1);
					}
					else
					{
						startLongDistanceSoftware(tabName, common::indexNum, strIP, strAccount.toStdString(), strPwd.toStdString(), stipToolData.toolPath, axTabWidget, ui->tabWidgetModulel1);
					}

				}
				else
				{
					axTabWidget->m_account = strAccount;
					axTabWidget->m_ip = QString::fromStdString(strIP);
					axTabWidget->m_softwareName = buttonText;
					if (isHardwareAccelerator(strAssignHostName.toStdString()))
					{
						startLongDistanceHost(tabName, common::indexNum, strIP, strAccount.toStdString(), strPwd.toStdString(), axTabWidget);
					}
					else
					{
						startLongDistanceSoftware(tabName, common::indexNum, strIP, strAccount.toStdString(), strPwd.toStdString(), stipToolData.toolPath, axTabWidget);
					}

				}
			}
		}
	}
	else
	{
		QString strAssignIP = "";// 指定ip 主机;
		QString strAssignHostName = "";

		AddToolDialog addToooDialog(common::indexNum);
		QComboBox *toolComboBox = addToooDialog.getComboBox();
		toolComboBox->setEnabled(false);
		toolComboBox->setCurrentText(buttonText);
		if (addToooDialog.exec() == QDialog::Accepted)
		{
			QString toolName;
			QString tabName;
			int mode = -1;
			int displayMode = 0;
			QString  toolPath = -1;



			addToooDialog.getToolData(tabName, toolName, toolPath, mode, displayMode, strAssignIP, strAssignHostName);

			table_ip stipToolData;
			if (!db::databaseDI::Instance().get_ip_by_software(stipToolData, buttonText.toStdString(), common::iLoginNum, common::indexNum))
			{
				return;
			}
			/*if (common::indexNum == 1)
			{

				strAssignIP = QString::fromStdString(stipToolData.ip);
				strAssignHostName = QString::fromStdString(stipToolData.host);


				QString hostname = QString::fromStdString(stipToolData.host);
				tabName = tabName + " " + hostname;
			}*/
			//else
			//{
			if (strAssignIP == "") // 模块234 下是指定还是CPu随机
			{
				table_ip_configure st;
				common::findIpWithGpuMinValue(st);

				strAssignIP = QString::fromStdString(st.ip);
				strAssignHostName = QString::fromStdString(st.hostname);
			}
			tabName = tabName + " " + strAssignHostName;
			//}

			std::string strIP = strAssignIP.toStdString();
			if (strIP.empty())
			{
				QMessageBox::warning(this, QString::fromLocal8Bit("警告"), QString::fromLocal8Bit("ip错误 请检查代码！"));
				return;
			}

			QString strPwd;
			if (common::bAdministrator)
			{
				strPwd = common::strFtpAdminPwd;
			}
			else
			{
				strPwd = common::strFtpPwd;
			}
			CWidget* axTabWidget = new CWidget();
			QString str = "app\\";
			QString strAccount = str + common::strLoginUserName;
			if (strAccount.isEmpty())
			{
				QMessageBox::warning(this, QString::fromLocal8Bit("警告"), QString::fromLocal8Bit("远程软件用户数量不足！"));
				return;
			}

			if (common::indexNum == 2)
			{
				if (displayMode == 0)
				{

					axTabWidget->m_account = strAccount;
					axTabWidget->m_ip = QString::fromStdString(strIP);
					axTabWidget->m_softwareName = buttonText;

					if (isHardwareAccelerator(strAssignHostName.toStdString()))
					{
						startLongDistanceHost(tabName, common::indexNum, strIP, strAccount.toStdString(), strPwd.toStdString(), axTabWidget, ui->tabWidgetModulel2);
					}
					else
					{
						startLongDistanceSoftware(tabName, common::indexNum, strIP, strAccount.toStdString(), strPwd.toStdString(), stipToolData.toolPath, axTabWidget, ui->tabWidgetModulel2);
					}

				}
				else
				{
					axTabWidget->m_account = strAccount;
					axTabWidget->m_ip = QString::fromStdString(strIP);
					axTabWidget->m_softwareName = buttonText;
					if (isHardwareAccelerator(strAssignHostName.toStdString()))
					{
						startLongDistanceHost(tabName, common::indexNum, strIP, strAccount.toStdString(), strPwd.toStdString(), axTabWidget);
					}
					else
					{
						startLongDistanceSoftware(tabName, common::indexNum, strIP, strAccount.toStdString(), strPwd.toStdString(), stipToolData.toolPath, axTabWidget);
					}

				}

			}
			else if (common::indexNum == 3)
			{

				if (displayMode == 0)
				{

					axTabWidget->m_account = strAccount;
					axTabWidget->m_ip = QString::fromStdString(strIP);
					axTabWidget->m_softwareName = buttonText;
					if (isHardwareAccelerator(strAssignHostName.toStdString()))
					{
						startLongDistanceHost(tabName, common::indexNum, strIP, strAccount.toStdString(), strPwd.toStdString(), axTabWidget, ui->tabWidgetModulel3);
					}
					else
					{
						startLongDistanceSoftware(tabName, common::indexNum, strIP, strAccount.toStdString(), strPwd.toStdString(), stipToolData.toolPath, axTabWidget, ui->tabWidgetModulel3);

					}
				}
				else
				{
					axTabWidget->m_account = strAccount;
					axTabWidget->m_ip = QString::fromStdString(strIP);
					axTabWidget->m_softwareName = buttonText;
					if (isHardwareAccelerator(strAssignHostName.toStdString()))
					{
						startLongDistanceHost(tabName, common::indexNum, strIP, strAccount.toStdString(), strPwd.toStdString(), axTabWidget);
					}
					else
					{
						startLongDistanceSoftware(tabName, common::indexNum, strIP, strAccount.toStdString(), strPwd.toStdString(), stipToolData.toolPath, axTabWidget);
					}

				}
			}
			else if (common::indexNum == 4)
			{

				if (displayMode == 0)
				{

					axTabWidget->m_account = strAccount;
					axTabWidget->m_ip = QString::fromStdString(strIP);
					axTabWidget->m_softwareName = buttonText;
					if (isHardwareAccelerator(strAssignHostName.toStdString()))
					{
						startLongDistanceHost(tabName, common::indexNum, strIP, strAccount.toStdString(), strPwd.toStdString(), axTabWidget, ui->tabWidgetModulel4);
					}
					else
					{
						startLongDistanceSoftware(tabName, common::indexNum, strIP, strAccount.toStdString(), strPwd.toStdString(), stipToolData.toolPath, axTabWidget, ui->tabWidgetModulel4);
					}

				}
				else
				{
					axTabWidget->m_account = strAccount;
					axTabWidget->m_ip = QString::fromStdString(strIP);
					axTabWidget->m_softwareName = buttonText;
					if (isHardwareAccelerator(strAssignHostName.toStdString()))
					{
						startLongDistanceHost(tabName, common::indexNum, strIP, strAccount.toStdString(), strPwd.toStdString(), axTabWidget);
					}
					else
					{
						startLongDistanceSoftware(tabName, common::indexNum, strIP, strAccount.toStdString(), strPwd.toStdString(), stipToolData.toolPath, axTabWidget);
					}

				}

			}
		}
	}
}
void MainWindow::onRightClicked(QString &buttonText)
{
	QString strAssignIP = "";// 指定ip 主机;
	QString strAssignHostName = "";

	AddToolDialog addToooDialog(common::indexNum);
	QComboBox *toolComboBox = addToooDialog.getComboBox();
	toolComboBox->setEnabled(false);
	toolComboBox->setCurrentText(buttonText);
	if (addToooDialog.exec() == QDialog::Accepted)
	{
		QString toolName;
		QString tabName;
		int mode = -1;
		int displayMode = 0;
		QString  toolPath = -1;



		addToooDialog.getToolData(tabName, toolName, toolPath, mode, displayMode, strAssignIP, strAssignHostName);

		table_ip stipToolData;
		if (!db::databaseDI::Instance().get_ip_by_software(stipToolData, buttonText.toStdString(), common::iLoginNum, common::indexNum))
		{
			return;
		}
		if (common::indexNum == 1)
		{

			strAssignIP = QString::fromStdString(stipToolData.ip);
			strAssignHostName = QString::fromStdString(stipToolData.host);


			QString hostname = QString::fromStdString(stipToolData.host);
			tabName = tabName + " " + hostname;
		}
		else
		{
			//QString hostname = QString::fromStdString(strAssignHostName);


			if (strAssignIP == "") // 模块234 下是指定还是CPu随机
			{
				table_ip_configure st;
				common::findIpWithGpuMinValue(st);

				strAssignIP = QString::fromStdString(st.ip);
				strAssignHostName = QString::fromStdString(st.hostname);
			}
			tabName = tabName + " " + strAssignHostName;
			//else
			//{
			//	//st.ip = strAssignIP.toStdString();
			//	//st.hostname = strAssignHostName.toStdString();
			//}
		}


		std::string strIP = strAssignIP.toStdString();
		if (strIP.empty())
		{
			QMessageBox::warning(this, QString::fromLocal8Bit("警告"), QString::fromLocal8Bit("ip错误 请检查代码！"));
			return;
		}

		QString strPwd;
		if (common::bAdministrator)
		{
			strPwd = common::strFtpAdminPwd;
		}
		else
		{
			strPwd = common::strFtpPwd;
		}
		CWidget* axTabWidget = new CWidget();



		//if (!db::databaseDI::Instance().get_one_ip_data(stipToolData, toolName.toStdString(), common::iLoginNum))

		//QString strAccount = getAccaunt(QString::fromStdString(strIP), toolName);
		QString str = "app\\";
		QString strAccount = str + common::strLoginUserName;
		if (strAccount.isEmpty())
		{
			QMessageBox::warning(this, QString::fromLocal8Bit("警告"), QString::fromLocal8Bit("远程软件用户数量不足！"));
			return;
		}
		if (common::indexNum == 1)
		{

			if (displayMode == 0)
			{

				axTabWidget->m_account = strAccount;
				axTabWidget->m_ip = strAssignIP;
				axTabWidget->m_softwareName = buttonText;

				if (isHardwareAccelerator(strAssignHostName.toStdString()))
				{
					startLongDistanceHost(tabName, common::indexNum, strIP, strAccount.toStdString(), strPwd.toStdString(), axTabWidget, ui->tabWidgetModulel1);
				}
				else
				{
					startLongDistanceSoftware(tabName, common::indexNum, strIP, strAccount.toStdString(), strPwd.toStdString(), stipToolData.toolPath, axTabWidget, ui->tabWidgetModulel1);
				}

			}
			else
			{
				axTabWidget->m_account = strAccount;
				axTabWidget->m_ip = QString::fromStdString(strIP);
				axTabWidget->m_softwareName = buttonText;

				if (isHardwareAccelerator(strAssignHostName.toStdString()))
				{
					startLongDistanceHost(tabName, common::indexNum, strIP, strAccount.toStdString(), strPwd.toStdString(), axTabWidget);
				}
				else
				{
					startLongDistanceSoftware(tabName, common::indexNum, strIP, strAccount.toStdString(), strPwd.toStdString(), stipToolData.toolPath, axTabWidget);
				}

			}


		}
		else if (common::indexNum == 2)
		{
			if (displayMode == 0)
			{

				axTabWidget->m_account = strAccount;
				axTabWidget->m_ip = QString::fromStdString(strIP);
				axTabWidget->m_softwareName = buttonText;

				if (isHardwareAccelerator(strAssignHostName.toStdString()))
				{
					startLongDistanceHost(tabName, common::indexNum, strIP, strAccount.toStdString(), strPwd.toStdString(), axTabWidget, ui->tabWidgetModulel2);
				}
				else
				{
					startLongDistanceSoftware(tabName, common::indexNum, strIP, strAccount.toStdString(), strPwd.toStdString(), stipToolData.toolPath, axTabWidget, ui->tabWidgetModulel2);
				}

			}
			else
			{
				axTabWidget->m_account = strAccount;
				axTabWidget->m_ip = QString::fromStdString(strIP);
				axTabWidget->m_softwareName = buttonText;
				if (isHardwareAccelerator(strAssignHostName.toStdString()))
				{
					startLongDistanceHost(tabName, common::indexNum, strIP, strAccount.toStdString(), strPwd.toStdString(), axTabWidget);
				}
				else
				{
					startLongDistanceSoftware(tabName, common::indexNum, strIP, strAccount.toStdString(), strPwd.toStdString(), stipToolData.toolPath, axTabWidget);
				}

			}

		}
		else if (common::indexNum == 3)
		{

			if (displayMode == 0)
			{

				axTabWidget->m_account = strAccount;
				axTabWidget->m_ip = QString::fromStdString(strIP);
				axTabWidget->m_softwareName = buttonText;
				if (isHardwareAccelerator(strAssignHostName.toStdString()))
				{
					startLongDistanceHost(tabName, common::indexNum, strIP, strAccount.toStdString(), strPwd.toStdString(), axTabWidget, ui->tabWidgetModulel3);
				}
				else
				{
					startLongDistanceSoftware(tabName, common::indexNum, strIP, strAccount.toStdString(), strPwd.toStdString(), stipToolData.toolPath, axTabWidget, ui->tabWidgetModulel3);

				}
			}
			else
			{
				axTabWidget->m_account = strAccount;
				axTabWidget->m_ip = QString::fromStdString(strIP);
				axTabWidget->m_softwareName = buttonText;
				if (isHardwareAccelerator(strAssignHostName.toStdString()))
				{
					startLongDistanceHost(tabName, common::indexNum, strIP, strAccount.toStdString(), strPwd.toStdString(), axTabWidget);
				}
				else
				{
					startLongDistanceSoftware(tabName, common::indexNum, strIP, strAccount.toStdString(), strPwd.toStdString(), stipToolData.toolPath, axTabWidget);
				}

			}
		}
		else if (common::indexNum == 4)
		{

			if (displayMode == 0)
			{

				axTabWidget->m_account = strAccount;
				axTabWidget->m_ip = QString::fromStdString(strIP);
				axTabWidget->m_softwareName = buttonText;
				if (isHardwareAccelerator(strAssignHostName.toStdString()))
				{
					startLongDistanceHost(tabName, common::indexNum, strIP, strAccount.toStdString(), strPwd.toStdString(), axTabWidget, ui->tabWidgetModulel4);
				}
				else
				{
					startLongDistanceSoftware(tabName, common::indexNum, strIP, strAccount.toStdString(), strPwd.toStdString(), stipToolData.toolPath, axTabWidget, ui->tabWidgetModulel4);
				}

			}
			else
			{
				axTabWidget->m_account = strAccount;
				axTabWidget->m_ip = QString::fromStdString(strIP);
				axTabWidget->m_softwareName = buttonText;
				if (isHardwareAccelerator(strAssignHostName.toStdString()))
				{
					startLongDistanceHost(tabName, common::indexNum, strIP, strAccount.toStdString(), strPwd.toStdString(), axTabWidget);
				}
				else
				{
					startLongDistanceSoftware(tabName, common::indexNum, strIP, strAccount.toStdString(), strPwd.toStdString(), stipToolData.toolPath, axTabWidget);
				}

			}

		}
	}
}




