#include "InformationConfihurationDialog.h"
#include "ui_InformationConfihurationDialog.h"
#include "databaseDI.h"
//#include "globel.h"
#include "AddToolInfoDialog.h"
#include "AddIpInfoDialog.h"
#include "common.h"

#include <QStandardItemModel>
#include <QToolTip>
#include <QModelIndex>
#include <QDebug>
#include <QMessageBox>
#include <QComboBox>
#include <fstream> // 用于 std::ifstream



InformationConfihurationDialog::InformationConfihurationDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::InformationConfihurationDialog)
{
	ui->setupUi(this);
	setWindowIcon(QIcon(":/image/InformationConfihuration.png"));
	// 移除帮助按钮
	setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
	init();
	initFaceData();

}

InformationConfihurationDialog::~InformationConfihurationDialog()
{
	delete ui;
}

void InformationConfihurationDialog::init()
{

	m_AddToolInfoDialog = new AddToolInfoDialog(module);
	//m_AddIpInfoDialog = new AddIpInfoDialog(this);

	m_modelTool1 = new QStandardItemModel();
	m_modelTool1->setColumnCount(2);
	//m_modelTool1->setHeaderData(0, Qt::Horizontal, QString::fromLocal8Bit("主机"));
	m_modelTool1->setHeaderData(0, Qt::Horizontal, QString::fromLocal8Bit("工具名称"));
	m_modelTool1->setHeaderData(1, Qt::Horizontal, QString::fromLocal8Bit("工具路径"));
	//m_modelTool1->setHeaderData(2, Qt::Horizontal, QString::fromLocal8Bit("工具图标"));

	ui->tableViewTool1->setModel(m_modelTool1);
	common::setTableViewBasicConfiguration(ui->tableViewTool1);

	//m_modelTool1->appendRow(QList<QStandardItem*>()
	//    << new QStandardItem("computer1")
	//    << new QStandardItem("VS")
	//    << new QStandardItem("D:\1_project\jqg\demo\qt\digitalIntegration")
	//    << new QStandardItem("D:\1_project\jqg\demo\qt\digitalIntegration"));
	//m_modelTool1->appendRow(QList<QStandardItem*>()
	//    << new QStandardItem("computer2")
	//    << new QStandardItem("PS")
	//    << new QStandardItem("D:\1_project\jqg\demo\qt\digitalIntegration")
	//    << new QStandardItem("D:\1_project\jqg\demo\qt\digitalIntegration"));
	//  
	//m_modelTool1->appendRow(QList<QStandardItem*>()
	//    << new QStandardItem("computer3")
	//    << new QStandardItem("XD")
	//    << new QStandardItem("D:\1_project\jqg\demo\qt\digitalIntegration")
	//    << new QStandardItem("D:\1_project\jqg\demo\qt\digitalIntegration"));


	m_modelTool2 = new QStandardItemModel();
	m_modelTool2->setColumnCount(2);
	//m_modelTool2->setHeaderData(0, Qt::Horizontal, QString::fromLocal8Bit("主机"));
	m_modelTool2->setHeaderData(0, Qt::Horizontal, QString::fromLocal8Bit("工具名称"));
	m_modelTool2->setHeaderData(1, Qt::Horizontal, QString::fromLocal8Bit("工具路径"));
	//m_modelTool2->setHeaderData(2, Qt::Horizontal, QString::fromLocal8Bit("工具图标"));
	ui->tableViewTool2->setModel(m_modelTool2);
	common::setTableViewBasicConfiguration(ui->tableViewTool2);

	m_modelTool3 = new QStandardItemModel();
	m_modelTool3->setColumnCount(2);
	//m_modelTool3->setHeaderData(0, Qt::Horizontal, QString::fromLocal8Bit("主机"));
	m_modelTool3->setHeaderData(0, Qt::Horizontal, QString::fromLocal8Bit("工具名称"));
	m_modelTool3->setHeaderData(1, Qt::Horizontal, QString::fromLocal8Bit("工具路径"));
	//m_modelTool3->setHeaderData(2, Qt::Horizontal, QString::fromLocal8Bit("工具图标"));
	ui->tableViewTool3->setModel(m_modelTool3);
	common::setTableViewBasicConfiguration(ui->tableViewTool3);

	m_modelTool4 = new QStandardItemModel();
	m_modelTool4->setColumnCount(2);
	//m_modelTool4->setHeaderData(0, Qt::Horizontal, QString::fromLocal8Bit("主机"));
	m_modelTool4->setHeaderData(0, Qt::Horizontal, QString::fromLocal8Bit("工具名称"));
	m_modelTool4->setHeaderData(1, Qt::Horizontal, QString::fromLocal8Bit("工具路径"));
	//m_modelTool4->setHeaderData(2, Qt::Horizontal, QString::fromLocal8Bit("工具图标"));
	ui->tableViewTool4->setModel(m_modelTool4);
	common::setTableViewBasicConfiguration(ui->tableViewTool4);

	m_modelIP1 = new QStandardItemModel();
	m_modelIP1->setColumnCount(2);
	m_modelIP1->setHeaderData(0, Qt::Horizontal, QString::fromLocal8Bit("ip"));
	m_modelIP1->setHeaderData(1, Qt::Horizontal, QString::fromLocal8Bit("主机"));
	//m_modelIP1->setHeaderData(2, Qt::Horizontal, QString::fromLocal8Bit("软件"));
	ui->tableViewIP1->setModel(m_modelIP1);
	common::setTableViewBasicConfiguration(ui->tableViewIP1);

	ui->tableViewTool1->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive); // 允许用户交互式调整列宽
	ui->tableViewTool1->horizontalHeader()->setStretchLastSection(true); // 让最后一列填满剩余空间
	ui->tableViewTool2->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
	ui->tableViewTool2->horizontalHeader()->setStretchLastSection(true); // 让最后一列填满剩余空间
	ui->tableViewTool3->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
	ui->tableViewTool3->horizontalHeader()->setStretchLastSection(true); // 让最后一列填满剩余空间
	ui->tableViewTool4->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
	ui->tableViewTool4->horizontalHeader()->setStretchLastSection(true); // 让最后一列填满剩余空间

	ui->tableViewIP1->setShowGrid(false);
	ui->tableViewTool1->setShowGrid(false);
	ui->tableViewTool2->setShowGrid(false);
	ui->tableViewTool3->setShowGrid(false);
	ui->tableViewTool4->setShowGrid(false);
	ui->tableViewTool1->setStyleSheet("QTableView{font-size: 18px;color: #191a25;}");
	ui->tableViewTool2->setStyleSheet("QTableView{font-size: 18px;color: #191a25;}");
	ui->tableViewTool3->setStyleSheet("QTableView{font-size: 18px;color: #191a25;}");
	ui->tableViewTool4->setStyleSheet("QTableView{font-size: 18px;color: #191a25;}");
	ui->tableViewIP1->setStyleSheet("QTableView{font-size: 18px;color: #191a25;}");

	ui->tableViewTool1->horizontalHeader()->setStyleSheet("QHeaderView::section{font-size: 22px;color: #7482a6;}");
	ui->tableViewTool1->horizontalHeader()->setFixedHeight(60);  // 设置表头高度为60像素
	ui->tableViewTool1->verticalHeader()->setDefaultSectionSize(60);//设置每一行的高度为60
	ui->tableViewTool2->horizontalHeader()->setStyleSheet("QHeaderView::section{font-size: 22px;color: #7482a6;}");
	ui->tableViewTool2->horizontalHeader()->setFixedHeight(60);
	ui->tableViewTool2->verticalHeader()->setDefaultSectionSize(60);
	ui->tableViewTool3->horizontalHeader()->setStyleSheet("QHeaderView::section{font-size: 22px;color: #7482a6;}");
	ui->tableViewTool3->horizontalHeader()->setFixedHeight(60);  
	ui->tableViewTool3->verticalHeader()->setDefaultSectionSize(60);
	ui->tableViewTool4->horizontalHeader()->setStyleSheet("QHeaderView::section{font-size: 22px;color: #7482a6;}");
	ui->tableViewTool4->horizontalHeader()->setFixedHeight(60); 
	ui->tableViewTool4->verticalHeader()->setDefaultSectionSize(60);
	ui->tableViewIP1->horizontalHeader()->setStyleSheet("QHeaderView::section{font-size: 22px;color: #7482a6;}");
	ui->tableViewIP1->horizontalHeader()->setFixedHeight(60); 
	ui->tableViewIP1->verticalHeader()->setDefaultSectionSize(60);

	/*   m_modelIP2 = new QStandardItemModel();
	   m_modelIP2->setColumnCount(2);
	   m_modelIP2->setHeaderData(0, Qt::Horizontal, QString::fromLocal8Bit("主机"));
	   m_modelIP2->setHeaderData(1, Qt::Horizontal, QString::fromLocal8Bit("ip"));
	   ui->tableViewIP2->setModel(m_modelIP2);
	   common::setTableViewBasicConfiguration(ui->tableViewIP2);

	   m_modelIP3 = new QStandardItemModel();
	   m_modelIP3->setColumnCount(2);
	   m_modelIP3->setHeaderData(0, Qt::Horizontal, QString::fromLocal8Bit("主机"));
	   m_modelIP3->setHeaderData(1, Qt::Horizontal, QString::fromLocal8Bit("ip"));
	   ui->tableViewIP3->setModel(m_modelIP3);
	   common::setTableViewBasicConfiguration(ui->tableViewIP3);

	   m_modelIP4 = new QStandardItemModel();
	   m_modelIP4->setColumnCount(2);
	   m_modelIP4->setHeaderData(0, Qt::Horizontal, QString::fromLocal8Bit("主机"));
	   m_modelIP4->setHeaderData(1, Qt::Horizontal, QString::fromLocal8Bit("ip"));
	   ui->tableViewIP4->setModel(m_modelIP4);
	   common::setTableViewBasicConfiguration(ui->tableViewIP4);*/

	   //m_modelIP1->appendRow(QList<QStandardItem*>()
	   //    << new QStandardItem("computer1")
	   //    << new QStandardItem("192.168.1.1"));
	   //m_modelIP1->appendRow(QList<QStandardItem*>()
	   //    << new QStandardItem("computer2")
	   //    << new QStandardItem("192.168.1.100"));
	   //m_modelIP1->appendRow(QList<QStandardItem*>()
	   //    << new QStandardItem("computer3")
	   //    << new QStandardItem("192.168.1.21"));

	ui->btnToolAdd1->setProperty("module", 1);
	ui->btnToolAdd2->setProperty("module", 2);
	ui->btnToolAdd3->setProperty("module", 3);
	ui->btnToolAdd4->setProperty("module", 4);
	//ui->btnIpAdd1->setProperty("module", 1);
	//ui->btnIpAdd1->setHidden(true);

	/*   ui->btnIpAdd2->setProperty("module", 2);
	   ui->btnIpAdd3->setProperty("module", 3);
	   ui->btnIpAdd4->setProperty("module", 4);*/
	ui->btnToolDel1->setProperty("module", 1);
	ui->btnToolDel2->setProperty("module", 2);
	ui->btnToolDel3->setProperty("module", 3);
	ui->btnToolDel4->setProperty("module", 4);
	//ui->btnIpDel1->setProperty("module", 1);
	//ui->btnIpDel1->setHidden(true);
	//ui->btnIpDel2->setProperty("module", 2);
	//ui->btnIpDel3->setProperty("module", 3);
	//ui->btnIpDel4->setProperty("module", 4);
	connect(ui->btnToolAdd1, &QPushButton::clicked, this, &InformationConfihurationDialog::slot_btnToolAdd);
	connect(ui->btnToolAdd2, &QPushButton::clicked, this, &InformationConfihurationDialog::slot_btnToolAdd);
	connect(ui->btnToolAdd3, &QPushButton::clicked, this, &InformationConfihurationDialog::slot_btnToolAdd);
	connect(ui->btnToolAdd4, &QPushButton::clicked, this, &InformationConfihurationDialog::slot_btnToolAdd);
	//connect(ui->btnIpAdd1, &QPushButton::clicked, this, &InformationConfihurationDialog::slot_btnIpAdd);
	/*  connect(ui->btnIpAdd2, &QPushButton::clicked, this, &InformationConfihurationDialog::slot_btnIpAdd);
	  connect(ui->btnIpAdd3, &QPushButton::clicked, this, &InformationConfihurationDialog::slot_btnIpAdd);
	  connect(ui->btnIpAdd4, &QPushButton::clicked, this, &InformationConfihurationDialog::slot_btnIpAdd);*/

	connect(ui->btnToolDel1, &QPushButton::clicked, this, &InformationConfihurationDialog::slot_btnToolDel);
	connect(ui->btnToolDel2, &QPushButton::clicked, this, &InformationConfihurationDialog::slot_btnToolDel);
	connect(ui->btnToolDel3, &QPushButton::clicked, this, &InformationConfihurationDialog::slot_btnToolDel);
	connect(ui->btnToolDel4, &QPushButton::clicked, this, &InformationConfihurationDialog::slot_btnToolDel);

	//connect(ui->btnIpDel1, &QPushButton::clicked, this, &InformationConfihurationDialog::slot_btnIpDel);
	/*   connect(ui->btnIpDel2, &QPushButton::clicked, this, &InformationConfihurationDialog::slot_btnIpDel);
	   connect(ui->btnIpDel3, &QPushButton::clicked, this, &InformationConfihurationDialog::slot_btnIpDel);
	   connect(ui->btnIpDel4, &QPushButton::clicked, this, &InformationConfihurationDialog::slot_btnIpDel);*/

	ui->tableViewTool1->setMouseTracking(true);
	connect(ui->tableViewTool1, SIGNAL(entered(QModelIndex)), this, SLOT(slot_tooltip(QModelIndex)));
	connect(ui->btnModule1, &QPushButton::clicked, this, &InformationConfihurationDialog::slot_btnShowModule1);
	connect(ui->btnModule2, &QPushButton::clicked, this, &InformationConfihurationDialog::slot_btnShowModule2);
	connect(ui->btnModule3, &QPushButton::clicked, this, &InformationConfihurationDialog::slot_btnShowModule3);
	connect(ui->btnModule4, &QPushButton::clicked, this, &InformationConfihurationDialog::slot_btnShowModule4);
}

void InformationConfihurationDialog::initFaceData()
{
	ui->btnModule1->click();
	flushToolModelData(m_modelTool1, 1);
	flushToolModelData(m_modelTool2, 2);
	flushToolModelData(m_modelTool3, 3);
	flushToolModelData(m_modelTool4, 4);
	flushIpModelData(m_modelIP1);
	//flushIpModelData(m_modelIP2, 2);
	//flushIpModelData(m_modelIP3, 3);
	//flushIpModelData(m_modelIP4, 4);
}

void InformationConfihurationDialog::flushToolModelData(QStandardItemModel* model, const int& module)
{
	delAllModelRow(model);
	std::map<std::string, table_ip> ipMap;
	if (db::databaseDI::Instance().get_ip_data(ipMap, module, common::iLoginNum))
	{
		for (const auto& stTool : ipMap)
		{
			const std::string& software = stTool.first;
			const table_ip& data = stTool.second;

			/*   model->appendRow(QList<QStandardItem*>()
				   << new QStandardItem(QString::fromStdString(stTool.host))
				   << new QStandardItem(QString::fromStdString(stTool.name))
				   << new QStandardItem(QString::fromStdString(stTool.path))
				   << new QStandardItem(QString::fromStdString(stTool.icoPath)));*/
				   //if (data.username == std::to_string(common::iUserID))
				   //if (data.number == common::iLoginNum)// &&不显示其他用户添加的软件
			{
				int newRowIndex = model->rowCount(); // 获取当前行数
				model->insertRow(newRowIndex); // 插入新行

				QStandardItem* item = new QStandardItem(QString::fromStdString(software));
				item->setTextAlignment(Qt::AlignCenter);  // 设置文本居中对齐
				model->setItem(newRowIndex, 0, item);
				QStandardItem* item2 = new QStandardItem(QString::fromStdString(data.toolPath));
				item2->setTextAlignment(Qt::AlignCenter);  // 设置文本居中对齐
				model->setItem(newRowIndex, 1, item2);
				//QModelIndex index = model->index(newRowIndex, 0);
				//model->setData(index, QString::fromStdString(stTool.first), Qt::UserRole);  // 设置id;
				//model->setItem(newRowIndex, 0, new QStandardItem(QString::fromStdString(software)));
				//model->setItem(newRowIndex, 1, new QStandardItem(QString::fromStdString(data.toolPath)));
			}
		}
	}
	// 创建自定义委托并设置到 QTableView
	BackgroundDelegate *delegate1 = new BackgroundDelegate(ui->tableViewTool1);
	ui->tableViewTool1->setItemDelegate(delegate1);
	BackgroundDelegate *delegate2 = new BackgroundDelegate(ui->tableViewTool2);
	ui->tableViewTool2->setItemDelegate(delegate2);
	BackgroundDelegate *delegate3 = new BackgroundDelegate(ui->tableViewTool3);
	ui->tableViewTool3->setItemDelegate(delegate3);
	BackgroundDelegate *delegate4 = new BackgroundDelegate(ui->tableViewTool4);
	ui->tableViewTool4->setItemDelegate(delegate4);
}

void InformationConfihurationDialog::flushIpModelData(QStandardItemModel* pModel)
{
	delAllModelRow(pModel);
	//std::list<table_ip> listData;
	//if (db::databaseDI::Instance().get_ip_data(listData))
	std::list<table_ip_configure> listData;
	if (db::databaseDI::Instance().get_all_ip(listData))
	{
		for (const auto& stIp : listData)
		{
			//if (stIp.number == common::iLoginNum && stIp.username == std::to_string(common::iUserID))
			//if (stIp.number == common::iLoginNum)
			{
				int newRowIndex = pModel->rowCount(); // 获取当前行数
				pModel->insertRow(newRowIndex); // 插入新行

				QStandardItem* item1 = new QStandardItem(QString::fromStdString(stIp.ip));
				item1->setTextAlignment(Qt::AlignCenter);  // 设置文本居中对齐
				pModel->setItem(newRowIndex, 0, item1);
				QStandardItem* item2 = new QStandardItem(QString::fromStdString(stIp.hostname));
				item2->setTextAlignment(Qt::AlignCenter);  // 设置文本居中对齐
				pModel->setItem(newRowIndex, 1, item2);
			}
		}
	}
	// 创建自定义委托并设置到 QTableView
	BackgroundDelegate *delegate = new BackgroundDelegate(ui->tableViewIP1);
	ui->tableViewIP1->setItemDelegate(delegate);
}

//void InformationConfihurationDialog::flushIpModelData(QStandardItemModel* pModel, const int& module)
//{
//	delAllModelRow(pModel);
//	std::list<table_ip> listData;
//	if (db::databaseDI::Instance().get_ip_data(listData, module))
//	{
//		for (const auto& stIp : listData)
//		{
//			//pModel->appendRow(QList<QStandardItem*>()
//			//    << new QStandardItem(QString::fromStdString(stData.host))
//			//    << new QStandardItem(QString::fromStdString(stData.ip)));
//
//			int newRowIndex = pModel->rowCount(); // 获取当前行数
//			pModel->insertRow(newRowIndex); // 插入新行
//
//			QStandardItem* item = new QStandardItem(QString::fromStdString(stIp.host));
//			// item->setTextAlignment(Qt::AlignCenter);  // 设置文本居中对齐
//			pModel->setItem(newRowIndex, 0, item);
//			QModelIndex index = pModel->index(newRowIndex, 0);
//			pModel->setData(index, stIp.id, Qt::UserRole);  // 设置id;
//
//			pModel->setItem(newRowIndex, 0, item);
//			pModel->setItem(newRowIndex, 1, new QStandardItem(QString::fromStdString(stIp.ip)));
//		}
//	}
//}



void InformationConfihurationDialog::clearModelData(QStandardItemModel* model)
{
	// 清理所有数据项，但保留列标题
	for (int row = 0; row < model->rowCount(); ++row)
	{
		for (int column = 0; column < model->columnCount(); ++column)
		{
			model->setItem(row, column, nullptr);
		}
	}
}

void InformationConfihurationDialog::delAllModelRow(QStandardItemModel* model)
{
	// 删除所有行
	int rowCount = model->rowCount();
	for (int row = rowCount - 1; row >= 0; --row)
	{
		model->removeRow(row);
	}
}

void InformationConfihurationDialog::slot_btnToolAdd()
{
	QPushButton* pButton = (QPushButton*)sender();
	int moduleNumber = pButton->property("module").toInt();

	AddToolInfoDialog addToolInfoDialog(moduleNumber);

	QRadioButton *accelerate = addToolInfoDialog.getAccelerateRadio();
	QRadioButton *node = addToolInfoDialog.getnodeRadio();
	QLabel *label4 = addToolInfoDialog.getlabel4();
	QLabel *label5 = addToolInfoDialog.getlabel5();
	QLabel *label6 = addToolInfoDialog.getlabel6();
	QComboBox *ipcomboBox1 = addToolInfoDialog.getipComboBox1();
	QComboBox *ipcomboBox2 = addToolInfoDialog.getipComboBox2();
	QComboBox *ipcomboBox3 = addToolInfoDialog.getipComboBox3();
	QWidget *widget = addToolInfoDialog.getwidget();
	if (moduleNumber != 1)
	{
		accelerate->setEnabled(false);
		accelerate->setVisible(false);
		node->setEnabled(false);
		node->setVisible(false);

		widget->setLayout(nullptr);             // 移除布局
		delete widget;
		addToolInfoDialog.resize(300,50);
	}
	table_ip stIp;
	std::list<table_ip_configure> listData;
	if (addToolInfoDialog.exec() == QDialog::Accepted)
	{
		addToolInfoDialog.getToolsData(stIp);

		// 读取图片文件
		std::ifstream file(stIp.icoPath, std::ios::binary);
		stIp.imageData.assign((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

		db::databaseDI::Instance().get_all_ip(listData);
		if (db::databaseDI::Instance().select_same_name_software(stIp.software, moduleNumber))
		{
			QMessageBox::information(this, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("该模块下已存在该软件,添加失败！"));
			return;
		}
		QStandardItemModel* pModel = nullptr;
		if (moduleNumber == 1)
		{
			//模块1中添加软件,选择指定节点
			if (accelerate->isChecked())
			{
				for (auto &soft_ip : listData)
				{
					pModel = m_modelTool1;

					stIp.ip = soft_ip.ip;
					stIp.host = soft_ip.hostname;
					stIp.module = moduleNumber;
					stIp.used = 0;
					stIp.username = std::to_string(common::iUserID);
					stIp.number = soft_ip.number;
					//stIp.number = common::iLoginNum;
					// 插入数据库;
					if (!db::databaseDI::Instance().add_ip_tool(stIp))
					{
						qDebug() << "db::databaseDI::Instance().add_ip_tools   error!";
					}
					else
					{
						flushToolModelData(m_modelTool1, 1);
					}
				}

			}
			else if (node->isChecked())//计算节点
			{
				std::list<table_ip_configure> list_data;
				std::string currentHostname1 = ipcomboBox1->currentText().toStdString();
				std::string currentHostname2 = ipcomboBox2->currentText().toStdString();
				std::string currentHostname3 = ipcomboBox3->currentText().toStdString();
				
				if (!db::databaseDI::Instance().get_ip_by_hostname(list_data, currentHostname1))
				{
					qDebug() << "db::databaseDI::Instance().get_ip_by_hostname   error!";
				}
				else
				{
					for (auto &soft_ip : list_data)
					{
						pModel = m_modelTool1;

						stIp.ip = soft_ip.ip;
						stIp.host = soft_ip.hostname;
						stIp.module = moduleNumber;
						stIp.used = 1;
						stIp.username = std::to_string(common::iUserID);
						stIp.number = soft_ip.number;
						//stIp.number = common::iLoginNum;
						// 插入数据库;
						if (!db::databaseDI::Instance().add_ip_tool(stIp))
						{
							qDebug() << "db::databaseDI::Instance().add_ip_tools   error!";
						}
						else
						{
							flushToolModelData(m_modelTool1, 1);
						}
					}
				}
				
				if (!db::databaseDI::Instance().get_ip_by_hostname(list_data, currentHostname2))
				{
					qDebug() << "db::databaseDI::Instance().get_ip_by_hostname   error!";
				}
				else
				{
					for (auto &soft_ip : list_data)
					{
						pModel = m_modelTool1;

						stIp.ip = soft_ip.ip;
						stIp.host = soft_ip.hostname;
						stIp.module = moduleNumber;
						stIp.used = 1;
						stIp.username = std::to_string(common::iUserID);
						stIp.number = soft_ip.number;
						//stIp.number = common::iLoginNum;
						// 插入数据库;
						if (!db::databaseDI::Instance().add_ip_tool(stIp))
						{
							qDebug() << "db::databaseDI::Instance().add_ip_tools   error!";
						}
						else
						{
							flushToolModelData(m_modelTool1, 1);
						}
					}
				}
				if (!db::databaseDI::Instance().get_ip_by_hostname(list_data, currentHostname3))
				{
					qDebug() << "db::databaseDI::Instance().get_ip_by_hostname   error!";
				}
				else
				{
					for (auto &soft_ip : list_data)
					{
						pModel = m_modelTool1;

						stIp.ip = soft_ip.ip;
						stIp.host = soft_ip.hostname;
						stIp.module = moduleNumber;
						stIp.used = 1;
						stIp.username = std::to_string(common::iUserID);
						stIp.number = soft_ip.number;
						//stIp.number = common::iLoginNum;
						// 插入数据库;
						if (!db::databaseDI::Instance().add_ip_tool(stIp))
						{
							qDebug() << "db::databaseDI::Instance().add_ip_tools   error!";
						}
						else
						{
							flushToolModelData(m_modelTool1, 1);
						}
					}
				}
			}
		}
		else if (moduleNumber == 2)
		{
			for (auto &soft_ip : listData)
			{
				pModel = m_modelTool2;

				stIp.ip = soft_ip.ip;
				stIp.host = soft_ip.hostname;
				stIp.module = moduleNumber;
				stIp.used = 0;
				stIp.username = std::to_string(common::iUserID);
				stIp.number = soft_ip.number;
				//stIp.number = common::iLoginNum;
				// 插入数据库;
				if (!db::databaseDI::Instance().add_ip_tool(stIp))
				{
					qDebug() << "db::databaseDI::Instance().add_ip_tools   error!";
				}
				else
				{
					flushToolModelData(m_modelTool2, 2);
				}
			}
		}
		else if (moduleNumber == 3)
		{
			for (auto &soft_ip : listData)
			{
				pModel = m_modelTool3;

				stIp.ip = soft_ip.ip;
				stIp.host = soft_ip.hostname;
				stIp.module = moduleNumber;
				stIp.used = 0;
				stIp.username = std::to_string(common::iUserID);
				stIp.number = soft_ip.number;
				// 插入数据库;
				if (!db::databaseDI::Instance().add_ip_tool(stIp))
				{
					qDebug() << "db::databaseDI::Instance().add_ip_tools   error!";
				}
				else
				{
					flushToolModelData(m_modelTool3, 3);
				}
			}
		}
		else if (moduleNumber == 4)
		{
			for (auto &soft_ip : listData)
			{
				pModel = m_modelTool4;

				stIp.ip = soft_ip.ip;
				stIp.host = soft_ip.hostname;
				stIp.module = moduleNumber;
				stIp.used = 0;
				stIp.username = std::to_string(common::iUserID);
				stIp.number = soft_ip.number;
				// 插入数据库;
				if (!db::databaseDI::Instance().add_ip_tool(stIp))
				{
					qDebug() << "db::databaseDI::Instance().add_ip_tools   error!";
				}
				else
				{
					flushToolModelData(m_modelTool4, 4);
				}
			}
		}
		if (pModel == nullptr)
			return;
		//int newRowIndex = pModel->rowCount(); // 获取当前行数
		//pModel->insertRow(newRowIndex); // 插入新行
		//QStandardItem* item = new QStandardItem(QString::fromStdString(stIp.host));
		//// item->setTextAlignment(Qt::AlignCenter);  // 设置文本居中对齐
		//pModel->setItem(newRowIndex, 0, item);

		//pModel->setItem(newRowIndex, 1, new QStandardItem(QString::fromStdString(stIp.software)));
		//pModel->setItem(newRowIndex, 2, new QStandardItem(QString::fromStdString(stIp.icoPath)));
		emit  signal_updateToolIcon(moduleNumber);
	}

	// 使用 setData 设置特定单元格的数据

	// 滚动到最下方
	ui->tableViewTool1->scrollToBottom();
}


void InformationConfihurationDialog::slot_btnIpAdd()
{
	QPushButton* pButton = (QPushButton*)sender();
	int moduleNumber = pButton->property("module").toInt();
	AddIpInfoDialog addIpInfoDialog;
	if (addIpInfoDialog.exec() == QDialog::Accepted)
	{
		table_ip stIp;
		addIpInfoDialog.getIpData(stIp);
		stIp.module = moduleNumber;

		QStandardItemModel* pModel = nullptr;
		if (moduleNumber == 1)
		{
			pModel = m_modelIP1;
		}
		/*    else if (moduleNumber == 2)
			{
				pModel = m_modelIP2;
			}
			else if (moduleNumber == 3)
			{
				pModel = m_modelIP3;
			}
			else if (moduleNumber == 4)
			{
				pModel = m_modelIP4;
			}*/
		if (pModel == nullptr)
			return;

		int newRowIndex = pModel->rowCount(); // 获取当前行数
		pModel->insertRow(newRowIndex); // 插入新行

		//QStandardItem* item = new QStandardItem(QString::fromStdString(stIp.host));
		// item->setTextAlignment(Qt::AlignCenter);  // 设置文本居中对齐
		//pModel->setItem(newRowIndex, 0, item);
		//QModelIndex index = pModel->index(newRowIndex, 0);
		//pModel->setData(index, stIp.id, Qt::UserRole);  // 设置id;

		pModel->setItem(newRowIndex, 0, new QStandardItem(QString::fromStdString(stIp.ip)));

		// 插入数据库;
		if (!db::databaseDI::Instance().add_ip(stIp))
		{
			qDebug() << "db::databaseDI::Instance().add_ip   error!";
		}

	}

	// 使用 setData 设置特定单元格的数据

	// 滚动到最下方
	ui->tableViewTool1->scrollToBottom();
}



void InformationConfihurationDialog::slot_btnToolDel()
{

	QPushButton* pButton = (QPushButton*)sender();
	int moduleNumber = pButton->property("module").toInt();
	QModelIndex currentIndex;
	QStandardItemModel* pModelTool = nullptr;
	if (moduleNumber == 1)
	{
		currentIndex = ui->tableViewTool1->currentIndex();
		pModelTool = m_modelTool1;
	}
	else if (moduleNumber == 2)
	{
		currentIndex = ui->tableViewTool2->currentIndex();
		pModelTool = m_modelTool2;
	}
	else if (moduleNumber == 3)
	{
		currentIndex = ui->tableViewTool3->currentIndex();
		pModelTool = m_modelTool3;
	}
	else if (moduleNumber == 4)
	{
		currentIndex = ui->tableViewTool4->currentIndex();
		pModelTool = m_modelTool4;
	}

	if (pModelTool == nullptr)
		return;
	if (!currentIndex.isValid())
		return;
	//QModelIndex firstColumnIndex = pModelTool->index(currentIndex.row(), 0, QModelIndex());

	//int id = pModelTool->data(firstColumnIndex, Qt::UserRole).toInt();
	//qDebug() << "First column data of current row   id: " << id;
	/*QVariant dataVariant = pModelTool->item(currentIndex.row(), currentIndex.column())->text();
	QString qstr = dataVariant.toString();*/
	// 获取当前选中单元格同一行的第1列的单元格
	QModelIndex indexFirst = pModelTool->index(currentIndex.row(), 0, currentIndex.parent());
	//获取要删除的单元格
	QVariant soft_name = pModelTool->data(indexFirst);
	QString qstr = soft_name.toString();
	std::string software = qstr.toStdString();
	qDebug() << "First column data of current row  software: " << software.c_str();

	if (db::databaseDI::Instance().del_tools(software, moduleNumber))
	{
		pModelTool->removeRow(currentIndex.row());
		emit  signal_updateToolIcon(moduleNumber);
	}
}

void InformationConfihurationDialog::slot_btnIpDel()
{
	QPushButton* pButton = (QPushButton*)sender();
	int moduleNumber = pButton->property("module").toInt();
	QModelIndex currentIndex;
	QStandardItemModel* pModel = nullptr;
	if (moduleNumber == 1)
	{
		currentIndex = ui->tableViewIP1->currentIndex();

		pModel = m_modelIP1;
	}
	//else if (moduleNumber == 2)
	//{
	//    currentIndex = ui->tableViewIP2->currentIndex();
	//    pModel = m_modelIP2;
	//}
	//else if (moduleNumber == 3)
	//{
	//    currentIndex = ui->tableViewIP3->currentIndex();
	//    pModel = m_modelIP3;
	//}
	//else if (moduleNumber == 4)
	//{
	//    currentIndex = ui->tableViewIP4->currentIndex();
	//    pModel = m_modelIP4;
	//}

	if (pModel == nullptr)
		return;
	if (!currentIndex.isValid())
		return;
	QModelIndex firstColumnIndex = pModel->index(currentIndex.row(), 0, QModelIndex());

	int id = pModel->data(firstColumnIndex, Qt::UserRole).toInt();
	qDebug() << "First column data of current row   id: " << id;

	if (db::databaseDI::Instance().del_ip(id))
	{
		pModel->removeRow(currentIndex.row());
	}
}

void InformationConfihurationDialog::slot_btnShowModule1()
{
	ui->btnModule1->setStyleSheet("QPushButton { font-size: 22px;color: #ffffff;border-image: url(:/image/btn_blue.png) 0 0 0 0 stretch;}");
	ui->btnModule2->setStyleSheet("QPushButton { font-size: 22px;color: #7482a6;}");
	ui->btnModule3->setStyleSheet("QPushButton { font-size: 22px;color: #7482a6;}");
	ui->btnModule4->setStyleSheet("QPushButton { font-size: 22px;color: #7482a6;}");
	flushToolModelData(m_modelTool1, 1);
	ui->stackedWidget->setCurrentIndex(0);
}
void InformationConfihurationDialog::slot_btnShowModule2()
{
	ui->btnModule1->setStyleSheet("QPushButton { font-size: 22px;color: #7482a6;}");
	ui->btnModule2->setStyleSheet("QPushButton { font-size: 22px;color: #ffffff;border-image: url(:/image/btn_blue.png) 0 0 0 0 stretch;}");
	ui->btnModule3->setStyleSheet("QPushButton { font-size: 22px;color: #7482a6;}");
	ui->btnModule4->setStyleSheet("QPushButton { font-size: 22px;color: #7482a6;}");
	flushToolModelData(m_modelTool2, 2);
	ui->stackedWidget->setCurrentIndex(1);
}
void InformationConfihurationDialog::slot_btnShowModule3()
{
	ui->btnModule1->setStyleSheet("QPushButton { font-size: 22px;color: #7482a6;}");
	ui->btnModule2->setStyleSheet("QPushButton { font-size: 22px;color: #7482a6;}");
	ui->btnModule3->setStyleSheet("QPushButton { font-size: 22px;color: #ffffff;border-image: url(:/image/btn_blue.png) 0 0 0 0 stretch;}");
	ui->btnModule4->setStyleSheet("QPushButton { font-size: 22px;color: #7482a6;}");
	flushToolModelData(m_modelTool3, 3);
	ui->stackedWidget->setCurrentIndex(2);
}
void InformationConfihurationDialog::slot_btnShowModule4()
{
	ui->btnModule1->setStyleSheet("QPushButton { font-size: 22px;color: #7482a6;}");
	ui->btnModule2->setStyleSheet("QPushButton { font-size: 22px;color: #7482a6;}");
	ui->btnModule3->setStyleSheet("QPushButton { font-size: 22px;color: #7482a6;}");
	ui->btnModule4->setStyleSheet("QPushButton { font-size: 22px;color: #ffffff;border-image: url(:/image/btn_blue.png) 0 0 0 0 stretch;}");
	flushToolModelData(m_modelTool4, 4);
	ui->stackedWidget->setCurrentIndex(3);
}

//QPushButton *InformationConfihurationDialog::getbtnToolAdd1()
//{
//	return ui->btnToolAdd1;
//}
//QPushButton *InformationConfihurationDialog::getbtnToolAdd2()
//{
//	return ui->btnToolAdd2;
//}
//QPushButton *InformationConfihurationDialog::getbtnToolAdd3()
//{
//	return ui->btnToolAdd3;
//}
//QPushButton *InformationConfihurationDialog::getbtnToolAdd4()
//{
//	return ui->btnToolAdd4;
//}
//QPushButton *InformationConfihurationDialog::getbtnToolDel1()
//{
//	return ui->btnToolDel1;
//}
//QPushButton *InformationConfihurationDialog::getbtnToolDel2()
//{
//	return ui->btnToolDel2;
//}
//QPushButton *InformationConfihurationDialog::getbtnToolDel3()
//{
//	return ui->btnToolDel3;
//}
//QPushButton *InformationConfihurationDialog::getbtnToolDel4()
//{
//	return ui->btnToolDel4;
//}



//void InformationConfihurationDialog::slot_tooltip(QModelIndex index)
//{
//   // QToolTip::showText(QCursor::pos(), index.data().toString());
//   // QToolTip::showText(QCursor::pos(), index.data().toString());
//}
