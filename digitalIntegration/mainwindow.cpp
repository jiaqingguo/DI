﻿#pragma comment  (lib, "User32.lib")
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
#include <dwmapi.h>
#include "windows.h"
#include <thread>
#include <functional>

MainWindow* g_pMainWindow = NULL;

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	g_pMainWindow = this;

	setWindowTitle(GBK_STRING("数字样机一体化平台"));
	setWindowIcon(QIcon(":/image/CASC.png"));

	// 设置无边框窗口
	setWindowFlags(windowFlags() | Qt::FramelessWindowHint);
	this->setAttribute(Qt::WA_StyledBackground, true);
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
	//ui->labelUserIcon->hide();

	ui->statusbar->hide();
	initInitface();


	//common::addNetworkCredential(target, username, password);
	getBladeComputerData(common::setHostData);
	//initAccount();

	m_reconnectTimer = new QTimer(this);
	// 将定时器的超时信号连接到槽函数
	connect(m_reconnectTimer, &QTimer::timeout, this, &MainWindow::slot_reconnnectTimerOut);

	//connect(this, &MainWindow::signal_soft, this, &MainWindow::slot_SoftTreeItemDoubleClicked);
	connect(ui->widgetTital, &CustomTitleWidget::signal_Maximized, this, &MainWindow::slot_showMax);
	connect(ui->widgetTital, &CustomTitleWidget::signal_Minimized, this, &MainWindow::showMinimized);
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
	/*if (m_RegisterDialog != nullptr)
		delete m_RegisterDialog;*/

		/*if (m_ResourceManageDialog != nullptr)
			delete m_ResourceManageDialog;*/
	if (m_DataManageDialog != nullptr)
		delete m_DataManageDialog;

	delete ui;
}

void MainWindow::initInitface()
{
	//ui->btnTitleIcon->setBa(QIcon(":/image/CASC.png"));
	initTreeMenu();

	m_LoginDialog = new LoginDialog(this);

	m_GifDialog = new GifDialog;

	//m_RegisterDialog = new RegisterDialog(this);

	//m_ResourceManageDialog = new ResourceManageDialog(this);

//	m_InforConfihurationDialog = new InformationConfihurationDialog(this);
	connect(ui->m_InforConfihurationDialog, &InformationConfihurationDialog::signal_updateToolIcon, this, &MainWindow::slot_updateModuleToolIcon);

	m_DataManageDialog = new DataManageDialog(this);

	//m_FilemangageDialog = new FilemangageDialog(this);
	/*m_FtpDialog = new FtpDialog();
	ui->stackedWidget->insertWidget(2, m_FtpDialog);*/
	//m_ApprovalProgressDialog = new ApprovalProgressDialog(this);

	connect(ui->m_ApprovalProgressDialog, &ApprovalProgressDialog::signal_createFtpUserDir, ui->m_FtpDialog, &FtpDialog::slot_createUserDir);
	connect(ui->m_ResourceManageDialog, &ResourceManageDialog::signal_udpOrderFinsh, ui->m_FtpDialog, &FtpDialog::slot_orderFinsh);
	connect(ui->m_ApprovalProgressDialog, &ApprovalProgressDialog::signal_ftpDownlaod, ui->m_FtpDialog, &FtpDialog::slot_signalFtpDownlaod);
	//m_OneClickLoadDialog = new OneClickLoadDialog(this);
	//connect(m_OneClickLoadDialog, &OneClickLoadDialog::one_load_tools, this, &MainWindow::slot_one_load_tools);

	m_OneClickSaveDialog = new OneClickSaveDialog(this);


	/*connect(ui->btnMinimize, &QPushButton::clicked, this, &MainWindow::showMinimized);
	connect(ui->btnMaximize, &QPushButton::clicked, this, &MainWindow::slot_btnMaximize);
	connect(ui->btnClose, &QPushButton::clicked, this, &MainWindow::close);*/



	//ui->btnFunction->setCheckable(true);
	//ui->btnModule1->setCheckable(true);
	//ui->btnModule2->setCheckable(true);
	//ui->btnModule3->setCheckable(true);
	//ui->btnModule4->setCheckable(true);

	//ui->btnFunction->setChecked(true);
	ui->stackedWidget->setCurrentIndex(0);
	updateModuleToolTreeItem(1);
	updateModuleToolTreeItem(2);
	updateModuleToolTreeItem(3);
	updateModuleToolTreeItem(4);





	// 初始化模块1-4界面;
	/*ui->btnM2Load->hide();
	ui->btnM3Load->hide();
	ui->btnM4Load->hide();
	ui->btnM1Save->hide();
	ui->btnM2Save->hide();
	ui->btnM3Save->hide();
	ui->btnM4Save->hide();*/

	//ui->tabWidgetModulel1->setTabsClosable(true); // 允许关闭标签

	ui->tabWidgetModulel1->tabBar()->installEventFilter(this);
	ui->tabWidgetModulel2->tabBar()->installEventFilter(this);
	ui->tabWidgetModulel3->tabBar()->installEventFilter(this);
	ui->tabWidgetModulel4->tabBar()->installEventFilter(this);

	 // 获取 QTabBar
	QTabBar* tabBar = ui->tabWidgetModulel1->tabBar();

	// 为每个标签设置自定义属性
	tabBar->setTabData(0, "tab1"); // 第一个标签

	ui->tabWidgetModulel1->removeTab(1);
	ui->tabWidgetModulel2->removeTab(1);
	ui->tabWidgetModulel3->removeTab(1);
	ui->tabWidgetModulel4->removeTab(1);
	/*ui->tabWidgetModulel1->removeTab(0);
	ui->tabWidgetModulel2->removeTab(0);
	ui->tabWidgetModulel3->removeTab(0);
	ui->tabWidgetModulel4->removeTab(0);*/
	//ui->btnAddTab1->setProperty("module", 1);
	//ui->btnAddTab2->setProperty("module", 2);
	//ui->btnAddTab3->setProperty("module", 3);
	//ui->btnAddTab4->setProperty("module", 4);
	//connect(ui->btnAddTab1, &QPushButton::clicked, this, &MainWindow::slot_btnAddToolTab);
	//connect(ui->btnAddTab2, &QPushButton::clicked, this, &MainWindow::slot_btnAddToolTab);
	//connect(ui->btnAddTab3, &QPushButton::clicked, this, &MainWindow::slot_btnAddToolTab);
	//connect(ui->btnAddTab4, &QPushButton::clicked, this, &MainWindow::slot_btnAddToolTab);

	//ui->btnM1Load->setCheckable(true);
	//ui->btnM2Load->setCheckable(true);
	//ui->btnM3Load->setCheckable(true);
	//ui->btnM4Load->setCheckable(true);
	//ui->btnM1Load->setProperty("module", 1);
	//ui->btnM2Load->setProperty("module", 2);
	//ui->btnM3Load->setProperty("module", 3);
	//ui->btnM4Load->setProperty("module", 4);
	//ui->btnM1Save->setCheckable(true);
	//ui->btnM2Save->setCheckable(true);
	//ui->btnM3Save->setCheckable(true);
	//ui->btnM4Save->setCheckable(true);
	//ui->btnM1Save->setProperty("module", 1);
	//ui->btnM2Save->setProperty("module", 2);
	//ui->btnM3Save->setProperty("module", 3);
	//ui->btnM4Save->setProperty("module", 4);
	//connect(ui->btnM1Load, &QPushButton::clicked, this, &MainWindow::slot_btnOneClickLoad);
	//connect(ui->btnM2Load, &QPushButton::clicked, this, &MainWindow::slot_btnOneClickLoad);
	//connect(ui->btnM3Load, &QPushButton::clicked, this, &MainWindow::slot_btnOneClickLoad);
	//connect(ui->btnM4Load, &QPushButton::clicked, this, &MainWindow::slot_btnOneClickLoad);
	//connect(ui->btnM1Save, &QPushButton::clicked, this, &MainWindow::slot_btnOneClickSave);
	//connect(ui->btnM2Save, &QPushButton::clicked, this, &MainWindow::slot_btnOneClickSave);
	//connect(ui->btnM3Save, &QPushButton::clicked, this, &MainWindow::slot_btnOneClickSave);
	//connect(ui->btnM4Save, &QPushButton::clicked, this, &MainWindow::slot_btnOneClickSave);
	ui->tabWidgetModulel1->setMovable(true); // 允许用户拖拽调整 Tab 顺序
	ui->tabWidgetModulel2->setMovable(true); // 允许用户拖拽调整 Tab 顺序
	ui->tabWidgetModulel3->setMovable(true); // 允许用户拖拽调整 Tab 顺序
	ui->tabWidgetModulel4->setMovable(true); // 允许用户拖拽调整 Tab 顺序

	ui->tabWidgetModulel1->setTabsClosable(true);
	ui->tabWidgetModulel2->setTabsClosable(true);
	ui->tabWidgetModulel3->setTabsClosable(true);
	ui->tabWidgetModulel4->setTabsClosable(true);
	// 连接关闭请求信号到槽函数
	connect(ui->tabWidgetModulel1, &QTabWidget::tabCloseRequested, this, &MainWindow::slot_tabModule1closeTab);
	connect(ui->tabWidgetModulel2, &QTabWidget::tabCloseRequested, this, &MainWindow::slot_tabModule2closeTab);
	connect(ui->tabWidgetModulel3, &QTabWidget::tabCloseRequested, this, &MainWindow::slot_tabModule3closeTab);
	connect(ui->tabWidgetModulel4, &QTabWidget::tabCloseRequested, this, &MainWindow::slot_tabModule4closeTab);


	// 连接右键点击信号
	ui->tabWidgetModulel1->setContextMenuPolicy(Qt::CustomContextMenu);
	connect(ui->tabWidgetModulel1, &QTabWidget::customContextMenuRequested, this, &MainWindow::slot_tabWidgetCustomContextMenuRequested);

	QTabBar* pTabBar = ui->tabWidgetModulel1->tabBar();
	//connect(pTabBar, &QTabBar::tabBarClicked, this, &MainWindow::slot_tabWidgetModulel1TabChanged);
	pTabBar->setTabButton(0, QTabBar::RightSide, nullptr); // 隐藏右侧关闭按钮
	
	// 设置第一个选项卡的字体
	QFont font = tabBar->font(); // 获取默认字体
	font.setPointSize(16);       // 设置字体大小
	//pTabBar->setTabFont(0, font); // 为第一个选项卡设置字体
	// 设置最后一个标签页的字体变大
	//pTabBar->setStyleSheet(
	//	"QTabBar::tab:last-child { font-size: 29px; }"  // 最后一个标签页字体变大
	//);


	pTabBar = ui->tabWidgetModulel2->tabBar();
	pTabBar->setTabButton(0, QTabBar::RightSide, nullptr); // 隐藏右侧关闭按钮

//	connect(pTabBar, &QTabBar::tabBarClicked, this, &MainWindow::slot_tabWidgetModulel2TabChanged);

	pTabBar = ui->tabWidgetModulel3->tabBar();
	pTabBar->setTabButton(0, QTabBar::RightSide, nullptr); // 隐藏右侧关闭按钮
//	connect(pTabBar, &QTabBar::tabBarClicked, this, &MainWindow::slot_tabWidgetModulel3TabChanged);
	pTabBar = ui->tabWidgetModulel4->tabBar();
	pTabBar->setTabButton(0, QTabBar::RightSide, nullptr); // 隐藏右侧关闭按钮
//	connect(pTabBar, &QTabBar::tabBarClicked, this, &MainWindow::slot_tabWidgetModulel4TabChanged);

	connect(this, &MainWindow::signal_addSoftDialogShow, this, &MainWindow::slot_addToolTabDiaogShow);


	// 连接信号
	//connect(ui->tabWidgetModulel1, &QTabWidget::currentChanged, this, &MainWindow::slot_tabWidgetModulel1TabChanged);
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
void MainWindow::initTreeMenu()
{
	ui->treeWidget->setColumnCount(1); // 设置列数
	//ui->treeWidget->setHeaderLabel("样机类型"); // 设置表头
	ui->treeWidget->setHeaderHidden(true); // 隐藏列标题
	//ui->treeWidget->setIndentation(0); // 关键代码：禁用缩进

	ui->treeWidget->setFocusPolicy(Qt::NoFocus); // 禁用焦点框


	ui->treeWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // 隐藏垂直滚动条

	QFont font1;
	font1.setPointSize(15); // 设置字体大小为 12

	QFont font2;
	font2.setPointSize(13); // 设置字体大小为 12

	// 创建五个根节点
	m_pFunctionNode = new QTreeWidgetItem(ui->treeWidget, QStringList(QString::fromLocal8Bit("菜单")));
	m_pFunctionNode->setSizeHint(0, QSize(70, 75));
	m_pFunctionNode->setFont(0, font1);


	m_pFunctionPrototypeNode = new QTreeWidgetItem(ui->treeWidget, QStringList(QString::fromLocal8Bit("功能样机")));
	m_pFunctionPrototypeNode->setSizeHint(0, QSize(75, 75));
	m_pFunctionPrototypeNode->setData(0, Qt::UserRole + 2, 4);
	m_pFunctionPrototypeNode->setFont(0, font1);

	m_pGeometryPrototypeNode = new QTreeWidgetItem(ui->treeWidget, QStringList(QString::fromLocal8Bit("几何样机")));
	m_pGeometryPrototypeNode->setSizeHint(0, QSize(75, 75));
	m_pGeometryPrototypeNode->setData(0, Qt::UserRole + 2, 5);
	m_pGeometryPrototypeNode->setFont(0, font1);


	m_pPerformancePrototypeNode = new QTreeWidgetItem(ui->treeWidget, QStringList(QString::fromLocal8Bit("性能样机")));
	m_pPerformancePrototypeNode->setSizeHint(0, QSize(75, 75));
	m_pPerformancePrototypeNode->setData(0, Qt::UserRole + 2, 6);
	m_pPerformancePrototypeNode->setFont(0, font1);

	m_pProductionPrototypeNode = new QTreeWidgetItem(ui->treeWidget, QStringList(QString::fromLocal8Bit("生产样机")));
	m_pProductionPrototypeNode->setSizeHint(0, QSize(75, 75));
	m_pProductionPrototypeNode->setData(0, Qt::UserRole + 2, 7);
	m_pProductionPrototypeNode->setFont(0, font1);
	// 设置图标
	//; // 使用资源文件中的图标，或者替换为实际路径

	m_pFunctionNode->setIcon(0, QIcon(":/image/function.png"));
	m_pFunctionNode->setData(0, Qt::UserRole, "function_select");

	m_pFunctionPrototypeNode->setIcon(0, QIcon(":/image/FunctionPrototype.png"));
	m_pFunctionPrototypeNode->setData(0, Qt::UserRole, "FunctionPrototype_select");

	m_pGeometryPrototypeNode->setIcon(0, QIcon(":/image/GeometryPrototype.png"));
	m_pGeometryPrototypeNode->setData(0, Qt::UserRole, "GeometryPrototype_select");

	m_pPerformancePrototypeNode->setIcon(0, QIcon(":/image/PerformancePrototype.png"));
	m_pPerformancePrototypeNode->setData(0, Qt::UserRole, "PerformancePrototype_select");

	m_pProductionPrototypeNode->setIcon(0, QIcon(":/image/ProductionPrototype.png"));
	m_pProductionPrototypeNode->setData(0, Qt::UserRole, "ProductionPrototype_select");

	// 为每个根节点添加两个子节点
	m_functionChild1 = new QTreeWidgetItem(m_pFunctionNode, QStringList(QString::fromLocal8Bit("资源管理器")));
	m_functionChild1->setSizeHint(0, QSize(75, 75));
	m_functionChild1->setIcon(0, QIcon(":/image/treeItem.png"));
	m_functionChild1->setData(0, Qt::UserRole + 2, 0);
	m_functionChild1->setData(0, Qt::UserRole, "functionChild1");
	m_functionChild1->setFont(0, font2);

	// 设置目标项为选中状态
	m_functionChild1->setSelected(true);
	// 设定当前项为目标项
	ui->treeWidget->setCurrentItem(m_functionChild1);

	m_functionChild2 = new QTreeWidgetItem(m_pFunctionNode, QStringList(QString::fromLocal8Bit("信息配置")));
	m_functionChild2->setSizeHint(0, QSize(75, 75));
	m_functionChild2->setIcon(0, QIcon(":/image/treeItem.png"));
	m_functionChild2->setData(0, Qt::UserRole + 2, 1);
	m_functionChild2->setData(0, Qt::UserRole, "functionChild2");
	m_functionChild2->setFont(0, font2);


	m_functionChild3 = new QTreeWidgetItem(m_pFunctionNode, QStringList(QString::fromLocal8Bit("文件管理")));
	m_functionChild3->setSizeHint(0, QSize(75, 75));
	m_functionChild3->setIcon(0, QIcon(":/image/treeItem.png"));
	m_functionChild3->setData(0, Qt::UserRole + 2, 2);
	m_functionChild3->setData(0, Qt::UserRole, "functionChild3");
	m_functionChild3->setFont(0, font2);

	m_pApprovalProgressNode = new QTreeWidgetItem(m_pFunctionNode, QStringList(QString::fromLocal8Bit("审批进度")));
	m_pApprovalProgressNode->setSizeHint(0, QSize(75, 75));
	m_pApprovalProgressNode->setIcon(0, QIcon(":/image/treeItem.png"));
	m_pApprovalProgressNode->setData(0, Qt::UserRole + 2, 3);
	m_pApprovalProgressNode->setData(0, Qt::UserRole, "m_pApprovalProgressNode");
	m_pApprovalProgressNode->setFont(0, font2);




	// 展开所有节点
	//ui->treeWidget->expandAll();
	m_pFunctionNode->setExpanded(true);
	// 连接双击信号到槽函数
	connect(ui->treeWidget, &QTreeWidget::itemDoubleClicked, this, &MainWindow::slot_treeWidgetDoubleClicked);
	connect(ui->treeWidget, &QTreeWidget::itemClicked, this, &MainWindow::slot_treeWidgetClicked);


	// 创建上下文菜单
	//QMenu contextMenu;
	m_TreeWidgetMenu = new QMenu;
	// 添加操作
	//m_addAction = m_TreeWidgetMenu->addAction(QString::fromLocal8Bit("+"));
	m_oneClickLoadAction = m_TreeWidgetMenu->addAction(QString::fromLocal8Bit("一键加载"));
	connect(m_oneClickLoadAction, &QAction::triggered, this, &MainWindow::slot_btnOneClickLoad);

	//// 连接右键点击信号
	//ui->treeWidget->setContextMenuPolicy(Qt::CustomContextMenu);
	//connect(ui->treeWidget, &QTreeWidget::customContextMenuRequested, this, &MainWindow::slot_treeWidgetCustomContextMenuRequested);
	// 绑定操作
	//connect(addAction, &QAction::triggered, [=]() {
	//	if (item) 
	//	{
	//		QTreeWidgetItem* newItem = new QTreeWidgetItem(item, QStringList() << "New Item");
	//		item->addChild(newItem);
	//		ui->treeWidget->expandItem(item); // 展开父项
	//	}
	//	});
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

		return;
	}
}

void MainWindow::showRegisterDialog()
{
	//m_RegisterDialog->exec();
}
void MainWindow::setUserNameText(const QString& userName)
{
	//ui->labelUserName->setText(userName);
	ui->widgetTital->SetUserName(userName);
}
void MainWindow::showGif()
{
	m_GifDialog->show();
}
void MainWindow::closeGif()
{
	m_GifDialog->close();
	// m_FilemangageDialog->exec();
}
bool MainWindow::showLoginDialog()
{
	m_LoginDialog->setWindowFlags(windowFlags() | Qt::FramelessWindowHint);
	//m_LoginDialog->setWindowFlags(Qt::FramelessWindowHint);// 设置无边框窗口
	if (m_LoginDialog->exec() == QDialog::Accepted)
	{
		//ui->labelUserName->setText(m_LoginDialog->GetUser());
		//ui->widgetTital->SetUserName(common::strLoginUserName);
		ui->widgetTital->SetUserName(m_LoginDialog->GetUser());
		common::strLoginUserName = m_LoginDialog->GetUser();
		if (m_LoginDialog->GetPop())
		{
			//ui->btnApprovalProgress->hide();
			m_pApprovalProgressNode->setHidden(true);
		}
		slot_showMax();
		this->show();

		//ui->stackedWidget->setCurrentIndex(1);
		//ui->stackedWidget->setCurrentIndex(0);

		//m_FilemangageDialog->initTableViewDownload();
		//connect(m_OneClickSaveDialog, &OneClickSaveDialog::signals_zipMultPath, m_FilemangageDialog, &FilemangageDialog::slot_compressMultPath);
		common::getHostNameData();
		ui->m_FtpDialog->initConnectFtp();
		// 设置时间间隔并启动定时器
		m_reconnectTimer->start(2000); // 每隔 10 (10000)秒触发一次
		//ui->m_ResourceManageDialog->startWebFlushTimer();
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



void MainWindow::slot_btnResourceManageClicked()  //todo 需要由别出触发;
{
	ui->m_ResourceManageDialog->startWebFlushTimer();
	int  x = 0;
	int  y = 0;
	//common::getScreenCenterPos(x, y, ui->m_ResourceManageDialog->width(), ui->m_ResourceManageDialog->height());
	//ui->m_ResourceManageDialog->move(x, y);
	//ui->m_ResourceManageDialog->exec();
	//ui->m_ResourceManageDialog->stopWebFlushTimer();
	//ui->btnResourceManage->setChecked(false);
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
	//m_InforConfihurationDialog->initFaceData();
	int  x = 0;
	int  y = 0;
	/*common::getScreenCenterPos(x, y, m_InforConfihurationDialog->width(), m_InforConfihurationDialog->height());
	m_InforConfihurationDialog->move(x, y);
	m_InforConfihurationDialog->exec();*/
	//ui->btnInformationConfihuration->setChecked(false);
}

void MainWindow::slot_btnDataManageClicked()
{

	//m_DataManageDialog->exec();
	int  x = 0;
	int  y = 0;
	//common::getScreenCenterPos(x, y, m_FilemangageDialog->width(), m_FilemangageDialog->height());
	//m_FilemangageDialog->move(x, y);
	//m_FilemangageDialog->show();

	//ui->m_FtpDialog->exec();
	//ui->btnDataManage->setChecked(false);
}

void MainWindow::slot_btnApprovalProgressClicked()
{
	ui->m_ApprovalProgressDialog->init();
	/*int  x = 0;
	int  y = 0;
	common::getScreenCenterPos(x, y, ui->m_ApprovalProgressDialog->width(), ui->m_ApprovalProgressDialog->height());
	m_ApprovalProgressDialog->move(x, y);
	m_ApprovalProgressDialog->exec();*/
	//	ui->btnApprovalProgress->setChecked(false);
}

void MainWindow::slot_btnAddToolTab()
{
	QPushButton* pButton = (QPushButton*)sender();
	int moduleNumber = pButton->property("module").toInt();


	QString strAssignIP = "";// 指定ip 主机;
	QString strAssignHostName = "";
	AddToolDialog addToooDialog(moduleNumber, this);
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
			tabName = tabName + "  " + hostname;
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
			tabName = tabName + "  " + strAssignHostName;
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
	m_OneClickLoadDialog->initTableView();
	m_OneClickLoadDialog->exec();
	connect(m_OneClickLoadDialog, &OneClickLoadDialog::one_load_tools, this, &MainWindow::slot_one_load_tools);

	QPushButton* pButton = (QPushButton*)sender();

	common::index = getBtnLoadIndex(pButton);
	//QPushButton* pButton = (QPushButton*)sender();
	//int module = pButton->property("module").toInt();
	//if (module == 1)
	//{
	//	ui->btnM1Load->setChecked(false);
	//}
	//else if (module == 2)
	//{
	//	ui->btnM2Load->setChecked(false);
	//}
	//else if (module == 3)
	//{
	//	ui->btnM3Load->setChecked(false);
	//}
	//else if (module == 4)
	//{
	//	ui->btnM4Load->setChecked(false);
	//}

}

void MainWindow::slot_btnOneClickSave()
{
	m_OneClickSaveDialog->exec();
	QPushButton* pButton = (QPushButton*)sender();
	int module = pButton->property("module").toInt();
	/*if (module == 1)
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
	}*/
}

void MainWindow::slot_updateModuleToolIcon(int module)
{
	//updateModuleToolIcon(module);
	updateModuleToolTreeItem(module);
}

void MainWindow::slot_downlaodFinsh()
{
	closeGif();
}

void MainWindow::slot_tabModule1closeTab(int index)
{
	if (index == (ui->tabWidgetModulel1->count() - 1))
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

	// 移除标签页前，记录前一个标签页的索引
	int prevIndex = (index > 0) ? index - 1 : 0;

	// 移除标签页
	ui->tabWidgetModulel1->removeTab(index);

	// 切换到前一个标签页（如果存在）
	if (ui->tabWidgetModulel1->count() > 0) 
	{
		ui->tabWidgetModulel1->setCurrentIndex(prevIndex);
	}
}

void MainWindow::slot_tabModule2closeTab(int index)
{
	if (index == (ui->tabWidgetModulel2->count() - 1))
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

	// 移除标签页前，记录前一个标签页的索引
	int prevIndex = (index > 0) ? index - 1 : 0;

	// 移除标签页
	ui->tabWidgetModulel2->removeTab(index);

	// 切换到前一个标签页（如果存在）
	if (ui->tabWidgetModulel2->count() > 0)
	{
		ui->tabWidgetModulel2->setCurrentIndex(prevIndex);
	}
}

void MainWindow::slot_tabModule3closeTab(int index)
{
	if (index == (ui->tabWidgetModulel3->count() - 1))
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
	// 移除标签页前，记录前一个标签页的索引
	int prevIndex = (index > 0) ? index - 1 : 0;

	// 移除标签页
	ui->tabWidgetModulel3->removeTab(index);

	// 切换到前一个标签页（如果存在）
	if (ui->tabWidgetModulel3->count() > 0)
	{
		ui->tabWidgetModulel3->setCurrentIndex(prevIndex);
	}
}

void MainWindow::slot_tabModule4closeTab(int index)
{
	if (index == (ui->tabWidgetModulel4->count() - 1))
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
	// 移除标签页前，记录前一个标签页的索引
	int prevIndex = (index > 0) ? index - 1 : 0;

	// 移除标签页
	ui->tabWidgetModulel4->removeTab(index);

	// 切换到前一个标签页（如果存在）
	if (ui->tabWidgetModulel4->count() > 0)
	{
		ui->tabWidgetModulel4->setCurrentIndex(prevIndex);
	}
}

void MainWindow::updateModuleToolIcon(int module)
{
	//QLayout* pLayout = nullptr;
	//if (module == 1)
	//{
	//	pLayout = ui->layoutM1ToolIcon;
	//}
	//else if (module == 2)
	//{
	//	pLayout = ui->layoutM2ToolIcon;
	//}
	//else if (module == 3)
	//{
	//	pLayout = ui->layoutM3ToolIcon;
	//}
	//else if (module == 4)
	//{
	//	pLayout = ui->layoutM4ToolIcon;
	//}

	//common::clearLayout(pLayout);
	//std::map<std::string, table_ip> ipMap;

	////创建竖线
	//QFrame *line = new QFrame();
	//line->setFrameShape(QFrame::VLine);  // 设置为竖线
	//line->setFrameShadow(QFrame::Sunken);  // 设置阴影为凹陷
	//line->setLineWidth(2);  // 设置线宽
	//line->setMidLineWidth(1);  // 设置中间线宽
	//line->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::MinimumExpanding);  // 设置大小策略

	//if (db::databaseDI::Instance().get_ip_data(ipMap, module, common::iLoginNum))
	//{
	//	for (const auto& stTool : ipMap)
	//	{
	//		const std::string& software = stTool.first;
	//		const table_ip& data = stTool.second;
	//		if (data.used == 1)
	//		{
	//			QToolButton* pBtn = new QToolButton();
	//			//QPushButton* pBtn = new QPushButton(QString::fromLocal8Bit("测试"));
	//			//pBtn->setIcon(QIcon(QString::fromStdString(data.icoPath)));

	//			QImage img;
	//			img.loadFromData(reinterpret_cast<const uchar*>(data.imageData.data()), data.imageData.size());
	//			// 将 QImage 转换为 QIcon
	//			QIcon icon(QPixmap::fromImage(img));
	//			// 设置 QToolButton 的图标
	//			pBtn->setIcon(icon);
	//			pBtn->setIconSize(QSize(50, 46));
	//			pBtn->setText(QString::fromStdString(software));
	//			pBtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
	//			pBtn->setStyleSheet("background-color:rgba(0,0,0,0);font-size: 12px;");
	//			pBtn->setFocusPolicy(Qt::NoFocus);
	//			pBtn->setFixedSize(55, 64);
	//			//pBtn->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);  // 设置按钮的大小策略
	//			pBtn->setEnabled(true);

	//			pLayout->addWidget(pBtn);

	//			//鼠标右击事件
	//			//RightClickEvent *rightclick = new RightClickEvent;
	//			//pBtn->installEventFilter(rightclick);
	//			//connect(rightclick, &RightClickEvent::rightClicked, this, &MainWindow::onRightClicked);
	//			//鼠标双击事件
	//			DoubleClickInterceptor *interceptor = new DoubleClickInterceptor;
	//			pBtn->installEventFilter(interceptor);
	//			connect(interceptor, &DoubleClickInterceptor::doubleClicked, this, &MainWindow::onDoubleClicked);
	//		}
	//	}
	//}
	//if(module == 1)
	//pLayout->addWidget(line);

	//db::databaseDI::Instance().get_ip_data(ipMap, module, common::iLoginNum);
	//for (const auto& stTool : ipMap)
	//{
	//	const std::string& software = stTool.first;
	//	const table_ip& data = stTool.second;
	//	if (data.used == 0)
	//	{
	//		QToolButton* pBtn = new QToolButton();
	//		QImage img;
	//		img.loadFromData(reinterpret_cast<const uchar*>(data.imageData.data()), data.imageData.size());
	//		// 将 QImage 转换为 QIcon
	//		QIcon icon(QPixmap::fromImage(img));
	//		// 设置 QToolButton 的图标
	//		pBtn->setIcon(icon);
	//		pBtn->setIconSize(QSize(50, 46));
	//		pBtn->setText(QString::fromStdString(software));
	//		pBtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
	//		pBtn->setStyleSheet("background-color:rgba(0,0,0,0);font-size: 12px;");
	//		pBtn->setFocusPolicy(Qt::NoFocus);
	//		pBtn->setFixedSize(55, 64);
	//		//pBtn->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);  // 设置按钮的大小策略
	//		pBtn->setEnabled(true);

	//		pLayout->addWidget(pBtn);

	//		//鼠标双击事件
	//		DoubleClickInterceptor *interceptor = new DoubleClickInterceptor;
	//		pBtn->installEventFilter(interceptor);
	//		connect(interceptor, &DoubleClickInterceptor::doubleClicked, this, &MainWindow::onDoubleClicked);
	//	}
	//}
}

void MainWindow::updateModuleToolTreeItem(int module)
{

	QTreeWidgetItem* pModelTreeItem = nullptr;
	if (module == 1)
	{

		pModelTreeItem = m_pFunctionPrototypeNode;
	}
	else if (module == 2)
	{

		pModelTreeItem = m_pGeometryPrototypeNode;
	}
	else if (module == 3)
	{

		pModelTreeItem = m_pPerformancePrototypeNode;
	}
	else if (module == 4)
	{

		pModelTreeItem = m_pProductionPrototypeNode;
	}
	pModelTreeItem->takeChildren();
	//common::clearLayout(pLayout);
	std::map<std::string, table_ip> ipMap;


	if (db::databaseDI::Instance().get_ip_data(ipMap, module, common::iLoginNum))
	{
		for (const auto& stTool : ipMap)
		{
			const std::string& software = stTool.first;
			const table_ip& data = stTool.second;
			//if (data.used == 1)
			{
				QTreeWidgetItem* pToolsChildItem = new QTreeWidgetItem(pModelTreeItem, QStringList(QString::fromStdString(software)));
				pToolsChildItem->setSizeHint(0, QSize(75, 75));

				pToolsChildItem->setData(0, Qt::UserRole + 1, QString::fromStdString(software));
				QFont font2;
				font2.setPointSize(14); // 设置字体大小
				pToolsChildItem->setFont(0, font2);
				QToolButton* pBtn = new QToolButton();

				QImage img;
				img.loadFromData(reinterpret_cast<const uchar*>(data.imageData.data()), data.imageData.size());
				// 将 QImage 转换为 QIcon
				QIcon icon(QPixmap::fromImage(img));
				pToolsChildItem->treeWidget()->setIconSize(QSize(45, 45));
				pToolsChildItem->setIcon(0, icon);

			}
		}
	}
	/*if (module == 1)
		pLayout->addWidget(line);*/

		//db::databaseDI::Instance().get_ip_data(ipMap, module, common::iLoginNum);
		//for (const auto& stTool : ipMap)
		//{
		//	const std::string& software = stTool.first;
		//	const table_ip& data = stTool.second;
		//	if (data.used == 0)
		//	{
		//		QToolButton* pBtn = new QToolButton();
		//		QImage img;
		//		img.loadFromData(reinterpret_cast<const uchar*>(data.imageData.data()), data.imageData.size());
		//		// 将 QImage 转换为 QIcon
		//		QIcon icon(QPixmap::fromImage(img));
		//		// 设置 QToolButton 的图标
		//		pBtn->setIcon(icon);
		//		pBtn->setIconSize(QSize(50, 46));
		//		pBtn->setText(QString::fromStdString(software));
		//		pBtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
		//		pBtn->setStyleSheet("background-color:rgba(0,0,0,0);font-size: 12px;");
		//		pBtn->setFocusPolicy(Qt::NoFocus);
		//		pBtn->setFixedSize(55, 64);
		//		//pBtn->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);  // 设置按钮的大小策略
		//		pBtn->setEnabled(true);

		//		pLayout->addWidget(pBtn);

		//		//鼠标双击事件
		//		DoubleClickInterceptor* interceptor = new DoubleClickInterceptor;
		//		pBtn->installEventFilter(interceptor);
		//		connect(interceptor, &DoubleClickInterceptor::doubleClicked, this, &MainWindow::onDoubleClicked);
		//	}
		//}
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
	QFont font;
	font.setPointSize(30); // 设置字体大小为 20
	rdp->setFont(font);
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
	b = rdp->setProperty("ColorDepth", 8);          //画质/位深,32/24/16/15/8

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
	//widget->setStyleSheet("border:none;");
	widget->m_pAxWidget = rdp;
	if (tabWidget != nullptr)
	{
		//tabWidget->addTab(widget, tabName);

		int intdex = tabWidget->insertTab(tabWidget->count() - 1, widget, tabName);
		tabWidget->setCurrentIndex(intdex);
	}
	else
	{
		widget->setWindowTitle(tabName);
		widget->showMaximized();
		widget->show();
	}

	connect(ui->tabWidgetModulel1, &MyTabWidget::resized, [=]() {
		QWidget* TabWidget1 = ui->tabWidgetModulel1->widget(0);
		if (TabWidget1)
		{
			int height = TabWidget1->height();
			//int width = TabWidget->width();
		}
		QVariant result1 = rdp->dynamicCall("UpdateSessionDisplaySettings(int,int,int,int,int,int,int)", ui->tabWidgetModulel1->width(), height, 1920, 1080, 0, 100, 100);
	});
	connect(ui->tabWidgetModulel2, &MyTabWidget::resized, [=]() {
		QWidget* TabWidget2 = ui->tabWidgetModulel2->widget(0);
		if (TabWidget2)
		{
			int height = TabWidget2->height();
			//int width = TabWidget->width();
		}
		QVariant result2 = rdp->dynamicCall("UpdateSessionDisplaySettings(int,int,int,int,int,int,int)", ui->tabWidgetModulel2->width(), height, 1920, 1080, 0, 100, 100);
	});
	connect(ui->tabWidgetModulel3, &MyTabWidget::resized, [=]() {
		QWidget* TabWidget3 = ui->tabWidgetModulel3->widget(0);
		if (TabWidget3)
		{
			int height = TabWidget3->height();
			//int width = TabWidget->width();
		}
		QVariant result3 = rdp->dynamicCall("UpdateSessionDisplaySettings(int,int,int,int,int,int,int)", ui->tabWidgetModulel3->width(), height, 1920, 1080, 0, 100, 100);
	});
	connect(ui->tabWidgetModulel4, &MyTabWidget::resized, [=]() {
		QWidget* TabWidget4 = ui->tabWidgetModulel4->widget(0);
		if (TabWidget4)
		{
			int height = TabWidget4->height();
			//int width = TabWidget->width();
		}
		QVariant result4 = rdp->dynamicCall("UpdateSessionDisplaySettings(int,int,int,int,int,int,int)", ui->tabWidgetModulel4->width(), height, 1920, 1080, 0, 100, 100);
	});
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
		int intdex = tabWidget->insertTab(tabWidget->count() - 1, widget, tabName);
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
	if (ui->m_FtpDialog)
	{
		int a = 0;
		ui->m_FtpDialog->reConnectFtp();
	}

}

void MainWindow::ChangeTreeItemIcon(QTreeWidgetItem* pItem)
{
	if (m_strLastTreeItem == "function")
	{
		//functionNode->
	}
	else if (m_strLastTreeItem == "function")
	{
		m_pFunctionPrototypeNode->setIcon(0, QIcon(":/image/function_select.png"));
	}
	else if (m_strLastTreeItem == "FunctionPrototype")
	{
		m_pFunctionPrototypeNode->setIcon(0, QIcon(":/image/FunctionPrototype_select.png"));
	}
	else if (m_strLastTreeItem == "GeometryPrototype")
	{
		m_pGeometryPrototypeNode->setIcon(0, QIcon(":/image/GeometryPrototype_select.png"));
	}
	else if (m_strLastTreeItem == "PerformancePrototype")
	{
		m_pPerformancePrototypeNode->setIcon(0, QIcon(":/image/PerformancePrototype_select.png"));
	}
	else if (m_strLastTreeItem == "ProductionPrototype")
	{
		m_pProductionPrototypeNode->setIcon(0, QIcon(":/image/ProductionPrototype_select.png"));
	}
	else if (m_strLastTreeItem == "functionChild1")
	{
		m_functionChild1->setIcon(0, QIcon(":/image/treeItem.png"));
	}
	else if (m_strLastTreeItem == "functionChild2")
	{
		m_functionChild2->setIcon(0, QIcon(":/image/treeItem.png"));
	}
	else if (m_strLastTreeItem == "functionChild3")
	{
		m_functionChild3->setIcon(0, QIcon(":/image/treeItem.png"));
	}
	else if (m_strLastTreeItem == "m_pApprovalProgressNode")
	{
		m_pApprovalProgressNode->setIcon(0, QIcon(":/image/treeItem.png"));
	}

	m_strCurTrrItem = pItem->data(0, Qt::UserRole).toString();
	if (m_strCurTrrItem == "function")
	{
		//functionNode->
	}
	else if (m_strCurTrrItem == "function")
	{
		m_pFunctionPrototypeNode->setIcon(0, QIcon(":/image/FunctionPrototype.png"));
	}
	else if (m_strCurTrrItem == "FunctionPrototype")
	{
		m_pFunctionPrototypeNode->setIcon(0, QIcon(":/image/FunctionPrototype.png"));
	}
	else if (m_strCurTrrItem == "GeometryPrototype")
	{
		m_pGeometryPrototypeNode->setIcon(0, QIcon(":/image/GeometryPrototype.png"));
	}
	else if (m_strCurTrrItem == "PerformancePrototype")
	{
		m_pPerformancePrototypeNode->setIcon(0, QIcon(":/image/PerformancePrototype.png"));
	}
	else if (m_strCurTrrItem == "ProductionPrototype")
	{
		m_pProductionPrototypeNode->setIcon(0, QIcon(":/image/ProductionPrototype.png"));
	}
	else if (m_strCurTrrItem == "functionChild1")
	{
		m_functionChild1->setIcon(0, QIcon(":/image/treeItem_select.png"));
	}
	else if (m_strCurTrrItem == "functionChild2")
	{
		m_functionChild2->setIcon(0, QIcon(":/image/treeItem_select.png"));
	}
	else if (m_strCurTrrItem == "functionChild3")
	{
		m_functionChild3->setIcon(0, QIcon(":/image/treeItem_select.png"));
	}
	else if (m_strCurTrrItem == "m_pApprovalProgressNode")
	{
		m_pApprovalProgressNode->setIcon(0, QIcon(":/image/treeItem_select.png"));
	}
	m_strLastTreeItem = m_strCurTrrItem;
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

	//QString str = "app\\";
	//QString strAccount = str + common::strLoginUserName;
	QString strAccount = common::strLoginUserName;

	if (strAccount.isEmpty())
	{
		QMessageBox::warning(this, QString::fromLocal8Bit("警告"), QString::fromLocal8Bit("远程软件用户数量不足！"));
		return;
	}

	QString strPwd = "Atexcel@123";
	if (common::bAdministrator)
	{
		strPwd = "Atexcel_123";
	}

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
			startLongDistanceHost(toolsName + "  " + QString::fromStdString(stipToolData.host), common::index, stipToolData.ip, strAccount.toStdString(), strPwd.toStdString(), axTabWidget, ui->tabWidgetModulel1);
		}
		else
		{
			startLongDistanceSoftware(toolsName + "  " + QString::fromStdString(stipToolData.host), common::index, stipToolData.ip, strAccount.toStdString(), strPwd.toStdString(), stipToolData.toolPath, axTabWidget, ui->tabWidgetModulel1);

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
			startLongDistanceHost(toolsName + "  " + QString::fromStdString(st.hostname), common::index, strIP, strAccount.toStdString(), strPwd.toStdString(), axTabWidget, ui->tabWidgetModulel2);
		}
		else
		{
			startLongDistanceSoftware(toolsName + "  " + QString::fromStdString(st.hostname), common::index, strIP, strAccount.toStdString(), strPwd.toStdString(), stipToolData.toolPath, axTabWidget, ui->tabWidgetModulel2);
		}

	}
	else if (moduleNum == 3)
	{
		axTabWidget->m_account = strAccount;
		axTabWidget->m_ip = QString::fromStdString(strIP);
		axTabWidget->m_softwareName = toolsName;

		if (isHardwareAccelerator(st.hostname))
		{
			startLongDistanceHost(toolsName + "  " + QString::fromStdString(st.hostname), common::index, strIP, strAccount.toStdString(), strPwd.toStdString(), axTabWidget, ui->tabWidgetModulel3);

		}
		else
		{
			startLongDistanceSoftware(toolsName + "  " + QString::fromStdString(st.hostname), common::index, strIP, strAccount.toStdString(), strPwd.toStdString(), stipToolData.toolPath, axTabWidget, ui->tabWidgetModulel3);
		}

	}
	else if (moduleNum == 4)
	{
		axTabWidget->m_account = strAccount;
		axTabWidget->m_ip = QString::fromStdString(strIP);
		axTabWidget->m_softwareName = toolsName;
		if (isHardwareAccelerator(st.hostname))
		{
			startLongDistanceHost(toolsName + "  " + QString::fromStdString(st.hostname), common::index, strIP, strAccount.toStdString(), strPwd.toStdString(), axTabWidget, ui->tabWidgetModulel4);
		}
		else
		{
			startLongDistanceSoftware(toolsName + "  " + QString::fromStdString(st.hostname), common::index, strIP, strAccount.toStdString(), strPwd.toStdString(), stipToolData.toolPath, axTabWidget, ui->tabWidgetModulel4);
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
	//QString strAccount = common::strLoginUserName;
	if (strAccount.isEmpty())
	{
		QMessageBox::warning(this, QString::fromLocal8Bit("警告"), QString::fromLocal8Bit("远程软件用户数量不足！"));
		return;
	}

	QString strPwd = "Atexcel@123";
	if (common::bAdministrator)
	{
		strPwd = "Atexcel_123";
	}

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
				startLongDistanceHost(buttonText + "  " + QString::fromStdString(stipToolData.host), common::indexNum, stipToolData.ip, strAccount.toStdString(), strPwd.toStdString(), axTabWidget, ui->tabWidgetModulel1);
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

			AddToolDialog addToooDialog(common::indexNum, this);
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
				tabName = tabName + "  " + strAssignHostName;

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
				//QString strAccount = common::strLoginUserName;

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

		AddToolDialog addToooDialog(common::indexNum, this);
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
			tabName = tabName + "  " + strAssignHostName;
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
void MainWindow::onRightClicked()
{
	//QString strAssignIP = "";// 指定ip 主机;
	//QString strAssignHostName = "";

	//AddToolDialog addToooDialog(common::indexNum,this);
	//QComboBox *toolComboBox = addToooDialog.getComboBox();
	//toolComboBox->setEnabled(false);
	//toolComboBox->setCurrentText(buttonText);
	//if (addToooDialog.exec() == QDialog::Accepted)
	//{
	//	QString toolName;
	//	QString tabName;
	//	int mode = -1;
	//	int displayMode = 0;
	//	QString  toolPath = -1;



	//	addToooDialog.getToolData(tabName, toolName, toolPath, mode, displayMode, strAssignIP, strAssignHostName);

	//	table_ip stipToolData;
	//	if (!db::databaseDI::Instance().get_ip_by_software(stipToolData, buttonText.toStdString(), common::iLoginNum, common::indexNum))
	//	{
	//		return;
	//	}
	//	if (common::indexNum == 1)
	//	{

	//		strAssignIP = QString::fromStdString(stipToolData.ip);
	//		strAssignHostName = QString::fromStdString(stipToolData.host);


	//		QString hostname = QString::fromStdString(stipToolData.host);
	//		tabName = tabName + " " + hostname;
	//	}
	//	else
	//	{
	//		//QString hostname = QString::fromStdString(strAssignHostName);


	//		if (strAssignIP == "") // 模块234 下是指定还是CPu随机
	//		{
	//			table_ip_configure st;
	//			common::findIpWithGpuMinValue(st);

	//			strAssignIP = QString::fromStdString(st.ip);
	//			strAssignHostName = QString::fromStdString(st.hostname);
	//		}
	//		tabName = tabName + " " + strAssignHostName;
	//		//else
	//		//{
	//		//	//st.ip = strAssignIP.toStdString();
	//		//	//st.hostname = strAssignHostName.toStdString();
	//		//}
	//	}


	//	std::string strIP = strAssignIP.toStdString();
	//	if (strIP.empty())
	//	{
	//		QMessageBox::warning(this, QString::fromLocal8Bit("警告"), QString::fromLocal8Bit("ip错误 请检查代码！"));
	//		return;
	//	}

	//	QString strPwd;
	//	if (common::bAdministrator)
	//	{
	//		strPwd = common::strFtpAdminPwd;
	//	}
	//	else
	//	{
	//		strPwd = common::strFtpPwd;
	//	}
	//	CWidget* axTabWidget = new CWidget();



	//	//if (!db::databaseDI::Instance().get_one_ip_data(stipToolData, toolName.toStdString(), common::iLoginNum))

	//	//QString strAccount = getAccaunt(QString::fromStdString(strIP), toolName);
	//	QString str = "app\\";
	//	QString strAccount = str + common::strLoginUserName;
	//	if (strAccount.isEmpty())
	//	{
	//		QMessageBox::warning(this, QString::fromLocal8Bit("警告"), QString::fromLocal8Bit("远程软件用户数量不足！"));
	//		return;
	//	}
	//	if (common::indexNum == 1)
	//	{

	//		if (displayMode == 0)
	//		{

	//			axTabWidget->m_account = strAccount;
	//			axTabWidget->m_ip = strAssignIP;
	//			axTabWidget->m_softwareName = buttonText;

	//			if (isHardwareAccelerator(strAssignHostName.toStdString()))
	//			{
	//				startLongDistanceHost(tabName, common::indexNum, strIP, strAccount.toStdString(), strPwd.toStdString(), axTabWidget, ui->tabWidgetModulel1);
	//			}
	//			else
	//			{
	//				startLongDistanceSoftware(tabName, common::indexNum, strIP, strAccount.toStdString(), strPwd.toStdString(), stipToolData.toolPath, axTabWidget, ui->tabWidgetModulel1);
	//			}

	//		}
	//		else
	//		{
	//			axTabWidget->m_account = strAccount;
	//			axTabWidget->m_ip = QString::fromStdString(strIP);
	//			axTabWidget->m_softwareName = buttonText;

	//			if (isHardwareAccelerator(strAssignHostName.toStdString()))
	//			{
	//				startLongDistanceHost(tabName, common::indexNum, strIP, strAccount.toStdString(), strPwd.toStdString(), axTabWidget);
	//			}
	//			else
	//			{
	//				startLongDistanceSoftware(tabName, common::indexNum, strIP, strAccount.toStdString(), strPwd.toStdString(), stipToolData.toolPath, axTabWidget);
	//			}

	//		}


	//	}
	//	else if (common::indexNum == 2)
	//	{
	//		if (displayMode == 0)
	//		{

	//			axTabWidget->m_account = strAccount;
	//			axTabWidget->m_ip = QString::fromStdString(strIP);
	//			axTabWidget->m_softwareName = buttonText;

	//			if (isHardwareAccelerator(strAssignHostName.toStdString()))
	//			{
	//				startLongDistanceHost(tabName, common::indexNum, strIP, strAccount.toStdString(), strPwd.toStdString(), axTabWidget, ui->tabWidgetModulel2);
	//			}
	//			else
	//			{
	//				startLongDistanceSoftware(tabName, common::indexNum, strIP, strAccount.toStdString(), strPwd.toStdString(), stipToolData.toolPath, axTabWidget, ui->tabWidgetModulel2);
	//			}

	//		}
	//		else
	//		{
	//			axTabWidget->m_account = strAccount;
	//			axTabWidget->m_ip = QString::fromStdString(strIP);
	//			axTabWidget->m_softwareName = buttonText;
	//			if (isHardwareAccelerator(strAssignHostName.toStdString()))
	//			{
	//				startLongDistanceHost(tabName, common::indexNum, strIP, strAccount.toStdString(), strPwd.toStdString(), axTabWidget);
	//			}
	//			else
	//			{
	//				startLongDistanceSoftware(tabName, common::indexNum, strIP, strAccount.toStdString(), strPwd.toStdString(), stipToolData.toolPath, axTabWidget);
	//			}

	//		}

	//	}
	//	else if (common::indexNum == 3)
	//	{

	//		if (displayMode == 0)
	//		{

	//			axTabWidget->m_account = strAccount;
	//			axTabWidget->m_ip = QString::fromStdString(strIP);
	//			axTabWidget->m_softwareName = buttonText;
	//			if (isHardwareAccelerator(strAssignHostName.toStdString()))
	//			{
	//				startLongDistanceHost(tabName, common::indexNum, strIP, strAccount.toStdString(), strPwd.toStdString(), axTabWidget, ui->tabWidgetModulel3);
	//			}
	//			else
	//			{
	//				startLongDistanceSoftware(tabName, common::indexNum, strIP, strAccount.toStdString(), strPwd.toStdString(), stipToolData.toolPath, axTabWidget, ui->tabWidgetModulel3);

	//			}
	//		}
	//		else
	//		{
	//			axTabWidget->m_account = strAccount;
	//			axTabWidget->m_ip = QString::fromStdString(strIP);
	//			axTabWidget->m_softwareName = buttonText;
	//			if (isHardwareAccelerator(strAssignHostName.toStdString()))
	//			{
	//				startLongDistanceHost(tabName, common::indexNum, strIP, strAccount.toStdString(), strPwd.toStdString(), axTabWidget);
	//			}
	//			else
	//			{
	//				startLongDistanceSoftware(tabName, common::indexNum, strIP, strAccount.toStdString(), strPwd.toStdString(), stipToolData.toolPath, axTabWidget);
	//			}

	//		}
	//	}
	//	else if (common::indexNum == 4)
	//	{

	//		if (displayMode == 0)
	//		{

	//			axTabWidget->m_account = strAccount;
	//			axTabWidget->m_ip = QString::fromStdString(strIP);
	//			axTabWidget->m_softwareName = buttonText;
	//			if (isHardwareAccelerator(strAssignHostName.toStdString()))
	//			{
	//				startLongDistanceHost(tabName, common::indexNum, strIP, strAccount.toStdString(), strPwd.toStdString(), axTabWidget, ui->tabWidgetModulel4);
	//			}
	//			else
	//			{
	//				startLongDistanceSoftware(tabName, common::indexNum, strIP, strAccount.toStdString(), strPwd.toStdString(), stipToolData.toolPath, axTabWidget, ui->tabWidgetModulel4);
	//			}

	//		}
	//		else
	//		{
	//			axTabWidget->m_account = strAccount;
	//			axTabWidget->m_ip = QString::fromStdString(strIP);
	//			axTabWidget->m_softwareName = buttonText;
	//			if (isHardwareAccelerator(strAssignHostName.toStdString()))
	//			{
	//				startLongDistanceHost(tabName, common::indexNum, strIP, strAccount.toStdString(), strPwd.toStdString(), axTabWidget);
	//			}
	//			else
	//			{
	//				startLongDistanceSoftware(tabName, common::indexNum, strIP, strAccount.toStdString(), strPwd.toStdString(), stipToolData.toolPath, axTabWidget);
	//			}

	//		}

	//	}
	//}
}

void MainWindow::slot_treeWidgetDoubleClicked(QTreeWidgetItem* item, int column)
{
	// 获取存储在 QTreeWidgetItem 中的自定义数据
	QVariant data = item->data(0, Qt::UserRole + 1);

	// 根据数据类型打印输出
	if (data.isValid())
	{
		if (data.type() == QVariant::String)
		{
			QString  toolName = data.toString();
			QTreeWidgetItem* parentItem = item->parent();
			if (parentItem != nullptr)
			{
				int Index = parentItem->data(0, Qt::UserRole + 2).toInt();
				if (Index == 4)  // 模块1
				{
					//ui->tabWidgetModulel1
				//	emit signal_soft(toolName);
					slot_SoftTreeItemDoubleClicked(toolName); // 嵌入软件

				}
				else if (Index == 5) // 模块2
				{
					slot_SoftTreeItemDoubleClicked(toolName); // 嵌入软件
					//emit signal_soft(toolName);
				}
				else if (Index == 6)
				{
					slot_SoftTreeItemDoubleClicked(toolName); // 嵌入软件
					//emit signal_soft(toolName);
				}
				else if (Index == 7)
				{
					slot_SoftTreeItemDoubleClicked(toolName); // 嵌入软件
					//emit signal_soft(toolName);
				}
				qDebug() << "Double-clicked item data (string):" << data.toString();

			}



		}
		else if (data.type() == QVariant::Int)
		{
			qDebug() << "Double-clicked item data (int):" << data.toInt();
		}
		else {
			qDebug() << "Double-clicked item data (other):" << data;
		}
	}
	else
	{
		qDebug() << "No custom data found in double-clicked item.";
	}
}

void MainWindow::slot_treeWidgetClicked(QTreeWidgetItem* item, int column)
{
	ChangeTreeItemIcon(item);
	// 获取存储在 QTreeWidgetItem 中的自定义数据
	QVariant data = item->data(column, Qt::UserRole + 2);

	int stackIndex = -1;
	// 根据数据类型打印输出
	if (data.isValid())
	{
		if (data.type() == QVariant::String)
		{
			qDebug() << "-clicked item data (string):" << data.toString();
		}
		else if (data.type() == QVariant::Int)
		{
			qDebug() << "-clicked item data (int):" << data.toInt();
			stackIndex = data.toInt();


			//ui->stackedWidgetBtn->setCurrentIndex(index);
		}
		else {
			qDebug() << "-clicked item data (other):" << data;
		}
	}
	else
	{
		QTreeWidgetItem* parentItem = item->parent();
		if (parentItem != nullptr)
		{
			stackIndex = parentItem->data(0, Qt::UserRole + 2).toInt();
		}
	}
	if (stackIndex != -1)
	{
		if (ui->stackedWidget->currentIndex() != stackIndex)
		{
			ui->stackedWidget->setCurrentIndex(stackIndex);

		}
		QString str = item->text(0);
		//ui->btnChildTitle->setText(str);

		ui->m_ResourceManageDialog->stopWebFlushTimer();
		if (stackIndex == 0)
		{
			ui->m_ResourceManageDialog->startWebFlushTimer();
		}
		else if (stackIndex == 1)
		{

		}
		else if (stackIndex == 2)
		{

		}
		else if (stackIndex == 3)
		{
			ui->m_ApprovalProgressDialog->init();
		}
		else if (stackIndex == 4)
		{
			common::indexNum = 1; // 之前的模块下标 概念;
		}
		else if (stackIndex == 5)
		{
			common::indexNum = 2; // 之前的模块下标 概念;
		}
		else if (stackIndex == 6)
		{
			common::indexNum = 3; // 之前的模块下标 概念;
		}
		else if (stackIndex == 7)
		{
			common::indexNum = 4; // 之前的模块下标 概念;
		}


	}
}


void MainWindow::slot_btnMaximize()
{
	if (isMaximized())
	{
		//window()->showNormal();
		ui->splitter->setVisible(false);
		//ui->btnMaximize->setText(QString::fromLocal8Bit("□"));
	}
	else {
		ui->splitter->setVisible(true);
		//this->showMaximized();
	}



}
void MainWindow::slot_showMax()
{
	if (m_showMax)
	{
		// 获取屏幕几何信息
		QRect availableRect = QApplication::desktop()->availableGeometry(this);

		// 获取当前窗口的几何信息
	//	QRect windowGeometry = this->geometry();

		// 计算新的宽度和高度
		int newWidth = static_cast<int>(availableRect.width() * 0.8);
		int newHeight = static_cast<int>(availableRect.height() * 0.8);

		// 计算新的窗口位置
		int newX = availableRect.x() + (availableRect.width() - newWidth) / 2;
		int newY = availableRect.y() + (availableRect.height() - newHeight) / 2;


		// 设置新大小和位置
		this->setGeometry(newX, newY, newWidth, newHeight);
		m_showMax = false;
	}
	else
	{
		m_showMax = true;
		QRect availableRect = QApplication::desktop()->availableGeometry(this);
		this->setGeometry(availableRect);
	}

}
void MainWindow::slot_showMin()
{
	this->showMinimized();
}
void MainWindow::slot_actionStartSoft()
{

}
void MainWindow::slot_actionOneClickLoad()
{
	slot_btnOneClickLoad();
}
void MainWindow::onDisconnected()
{
	QMessageBox msgBox;
	msgBox.setWindowTitle(QString::fromLocal8Bit("提示"));

	// 设置字体大小
	QFont font;
	font.setPointSize(50); // 设置字体大小为 16 磅
	msgBox.setFont(font);

	msgBox.setText(QString::fromLocal8Bit("远程连接已断开，请关闭标签页"));
	msgBox.exec();
}

bool MainWindow::eventFilter(QObject* obj, QEvent* event)
{
	if (obj == ui->tabWidgetModulel1->tabBar() && event->type() == QEvent::MouseButtonPress)
	{
		//if (event->type() == QEvent::MouseButtonPress)
		{
			QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
			int tabIndex = ui->tabWidgetModulel1->tabBar()->tabAt(mouseEvent->pos());

			if (tabIndex == ui->tabWidgetModulel1->count() - 1) // 如果是最后一个 Tab
			{
				emit signal_addSoftDialogShow(1);
				return true; // 直接拦截点击事件，阻止后续处理
			}
		}
	}
	else if (obj == ui->tabWidgetModulel2->tabBar() && event->type() == QEvent::MouseButtonPress)
	{
		//if (event->type() == QEvent::MouseButtonPress)
		{
			QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
			int tabIndex = ui->tabWidgetModulel2->tabBar()->tabAt(mouseEvent->pos());

			if (tabIndex == ui->tabWidgetModulel2->count() - 1) // 如果是最后一个 Tab
			{
				emit signal_addSoftDialogShow(2);
				return true; // 直接拦截点击事件，阻止后续处理
			}
		}
	}
	else if (obj == ui->tabWidgetModulel3->tabBar() && event->type() == QEvent::MouseButtonPress)
	{
		//if (event->type() == QEvent::MouseButtonPress)
		{
			QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
			int tabIndex = ui->tabWidgetModulel3->tabBar()->tabAt(mouseEvent->pos());

			if (tabIndex == ui->tabWidgetModulel3->count() - 1) // 如果是最后一个 Tab
			{
				emit signal_addSoftDialogShow(3);
				return true; // 直接拦截点击事件，阻止后续处理
			}
		}
	}
	else if (obj == ui->tabWidgetModulel4->tabBar() && event->type() == QEvent::MouseButtonPress)
	{
		//if (event->type() == QEvent::MouseButtonPress)
		{
			QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
			int tabIndex = ui->tabWidgetModulel4->tabBar()->tabAt(mouseEvent->pos());

			if (tabIndex == ui->tabWidgetModulel4->count() - 1) // 如果是最后一个 Tab
			{
				emit signal_addSoftDialogShow(4);
				return true; // 直接拦截点击事件，阻止后续处理
			}
		}
	}
	return QObject::eventFilter(obj, event);
}
void MainWindow::changeEvent(QEvent *event)
{
	if (event->type() == QEvent::WindowStateChange)
	{
		QWindowStateChangeEvent *stateEvent = static_cast<QWindowStateChangeEvent*>(event);
		if (isMinimized())
		{
			this->setAttribute(Qt::WA_Mapped);
		}
		/*else if (stateEvent->oldState() & Qt::WindowMinimized)
		{
			this->setAttribute(Qt::WA_Mapped);
		}*/
	}
	QMainWindow::changeEvent(event); // 调用父类处理
}

void MainWindow::slot_addToolTabDiaogShow(const int& module)
{

	int moduleNumber = module;

	QString strAssignIP = "";// 指定ip 主机;
	QString strAssignHostName = "";
	AddToolDialog addToooDialog(moduleNumber, this);
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
			tabName = tabName + "  " + hostname;
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
			tabName = tabName + "  " + strAssignHostName;
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
	else 
	{
		/*if (moduleNumber == 1)
		{
			ui->tabWidgetModulel1->m_cancleAddTab = true;
		}*/
	}
}

void MainWindow::slot_tabWidgetCustomContextMenuRequested(const QPoint& pos)
{
	// 显示菜单
	m_TreeWidgetMenu->exec(ui->tabWidgetModulel1->mapToGlobal(pos));
}

void MainWindow::slot_treeWidgetCustomContextMenuRequested(const QPoint& pos)
{
	QTreeWidgetItem* item = ui->treeWidget->itemAt(pos);

	// 获取存储在 QTreeWidgetItem 中的自定义数据
	QVariant data = item->data(0, Qt::UserRole + 2);

	int stackIndex = -1;
	// 根据数据类型打印输出
	if (data.isValid())
	{
		if (data.type() == QVariant::String)
		{
			qDebug() << "-clicked item data (string):" << data.toString();
		}
		else if (data.type() == QVariant::Int)
		{
			qDebug() << "-clicked item data (int):" << data.toInt();
			stackIndex = data.toInt();


			//ui->stackedWidgetBtn->setCurrentIndex(index);
		}
		else {
			qDebug() << "-clicked item data (other):" << data;
		}
	}
	else
	{
		QTreeWidgetItem* parentItem = item->parent();
		if (parentItem != nullptr)
		{
			stackIndex = parentItem->data(0, Qt::UserRole + 2).toInt();
		}
	}
	if (stackIndex >= 4 && stackIndex <= 7)
	{
		if (stackIndex == 4)
		{
			m_oneClickLoadAction->setVisible(true);
		}
		else
		{
			m_oneClickLoadAction->setVisible(false);
		}
		// 显示菜单
		m_TreeWidgetMenu->exec(ui->treeWidget->mapToGlobal(pos));
	}
}

void MainWindow::slot_tabWidgetModulel1TabChanged(int index)
{
	if (index == (ui->tabWidgetModulel1->count() - 1))
	{
		ui->tabWidgetModulel1->m_cancleAddTab = true;
		emit signal_addSoftDialogShow(1);
		//addToolTabDiaogShow(1);
	}
	int a = 0;
}

void MainWindow::slot_tabWidgetModulel2TabChanged(int index)
{
	if (index == (ui->tabWidgetModulel2->count() - 1))
	{
		emit signal_addSoftDialogShow(2);
		//addToolTabDiaogShow(2);
	}
}

void MainWindow::slot_tabWidgetModulel3TabChanged(int index)
{
	if (index == (ui->tabWidgetModulel3->count() - 1))
	{
		emit signal_addSoftDialogShow(3);
		//addToolTabDiaogShow(3);
	}
}

void MainWindow::slot_tabWidgetModulel4TabChanged(int index)
{
	if (index == (ui->tabWidgetModulel4->count() - 1))
	{
		//addToolTabDiaogShow(4);
		emit signal_addSoftDialogShow(4);
	}
}

void MainWindow::slot_SoftTreeItemDoubleClicked(QString buttonText)
{
	table_ip stipToolData;
	if (!db::databaseDI::Instance().get_ip_by_software(stipToolData, buttonText.toStdString(), common::iLoginNum, common::indexNum))
	{
		return;
	}
	QString str = "app\\";
	QString strAccount = str + common::strLoginUserName;
	//QString strAccount = common::strLoginUserName;
	if (strAccount.isEmpty())
	{
		QMessageBox::warning(this, QString::fromLocal8Bit("警告"), QString::fromLocal8Bit("远程软件用户数量不足！"));
		return;
	}

	QString strPwd = "Atexcel@123";
	if (common::bAdministrator)
	{
		strPwd = "Atexcel_123";
	}

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
				startLongDistanceHost(buttonText + "  " + QString::fromStdString(stipToolData.host), common::indexNum, stipToolData.ip, strAccount.toStdString(), strPwd.toStdString(), axTabWidget, ui->tabWidgetModulel1);
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

			AddToolDialog addToooDialog(common::indexNum, this);
			QComboBox* toolComboBox = addToooDialog.getComboBox();
			toolComboBox->setEnabled(false);
			// 设置禁用状态下的样式表
			toolComboBox->setStyleSheet("QComboBox::down-arrow { width: 0px; height: 0px; }");
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
				tabName = tabName + "  " + strAssignHostName;

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
				//QString strAccount = common::strLoginUserName;
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

		AddToolDialog addToooDialog(common::indexNum, this);
		QComboBox* toolComboBox = addToooDialog.getComboBox();
		toolComboBox->setEnabled(false);
		// 设置禁用状态下的样式表
		toolComboBox->setStyleSheet("QComboBox::down-arrow { width: 0px; height: 0px; }");
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
			tabName = tabName + "  " + strAssignHostName;
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
void MainWindow::slot_ResizeEvent()
{

}

