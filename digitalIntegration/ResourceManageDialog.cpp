#include <QStandardItemModel>
#include <QLabel>
#include <QVBoxLayout>
#include <qwidget.h>
#include <QtWebEngineWidgets>
#include <iostream>

#include "ResourceManageDialog.h"
#include "ui_ResourceManageDialog.h"
#include "common.h"
#include "databaseDI.h"


//#include <QJsonObject>

ResourceManageDialog::ResourceManageDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::ResourceManageDialog)
{
	ui->setupUi(this);
	setWindowIcon(QIcon(":/image/ResourceManage.png"));
	
	/*ui->label->hide();
	ui->label_3->hide();
	ui->label_5->hide();
	ui->label_7->hide();
	ui->label_9->hide();*/

	ui->tableViewList->setShowGrid(false);
	ui->tableViewList->setStyleSheet("QTableView{font-size: 14px;color: #191a25;}");
	ui->tableViewList->horizontalHeader()->setStyleSheet("QHeaderView::section{font-size: 17px;color: #7482a6;}");
	ui->tableViewList->horizontalHeader()->setFixedHeight(45);  // 设置表头高度为50像素
	ui->tableViewList->verticalHeader()->setDefaultSectionSize(45);//设置每一行的高度为50

	//根据下拉列表中最长项的长度来调整控件的宽度
	ui->comboBox1->setSizeAdjustPolicy(QComboBox::AdjustToContents);
	ui->comboBox2->setSizeAdjustPolicy(QComboBox::AdjustToContents);
	ui->comboBox3->setSizeAdjustPolicy(QComboBox::AdjustToContents);
	ui->comboBox4->setSizeAdjustPolicy(QComboBox::AdjustToContents);
	ui->comboBox5->setSizeAdjustPolicy(QComboBox::AdjustToContents);
	/*ui->comboBox1->setFixedWidth(150);
	ui->comboBox2->setFixedWidth(150);
	ui->comboBox3->setFixedWidth(150);
	ui->comboBox4->setFixedWidth(150);
	ui->comboBox5->setFixedWidth(150);*/

	// 创建自定义委托并设置到 QTableView
	BackgroundDelegate *delegate = new BackgroundDelegate(ui->tableViewList);
	ui->tableViewList->setItemDelegate(delegate);
	connect(ui->btnList, &QPushButton::clicked, this, &ResourceManageDialog::slot_showList);
	ui->btnList->click();
	connect(ui->btnCurve, &QPushButton::clicked, this, &ResourceManageDialog::slot_showCurve);
	//ui->tabWidget->setCurrentIndex(0);
	//  int newRow3 = m_model->rowCount();
	  //m_model->setItem(0, 0, new QStandardItem("SetItem 1"));

	initTableWidgetCurve();
	/*m_model->appendRow(QList<QStandardItem*>()
		<< new QStandardItem("1")
		<< new QStandardItem("CPU")
		<< new QStandardItem(" 3")
		<< new QStandardItem(" 2")
		<< new QStandardItem("net 2"));
	m_model->appendRow(QList<QStandardItem*>()
		<< new QStandardItem("2")
		<< new QStandardItem("CPU")
		<< new QStandardItem(" 3")
		<< new QStandardItem(" 2")
		<< new QStandardItem("net 2"));
	m_model->appendRow(QList<QStandardItem*>()
		<< new QStandardItem("3")
		<< new QStandardItem("CPU")
		<< new QStandardItem(" 3")
		<< new QStandardItem(" 2")
		<< new QStandardItem("net 2"));*/
		//ui->comboBox->addItem(QString::fromLocal8Bit("主机1"));
		//ui->comboBox->addItem(QString::fromLocal8Bit("主机2"));
		//this->message = new Message_t();
	getUdpData();
	
	m_timer = new QTimer(this);
	QObject::connect(m_timer, &QTimer::timeout, this, &ResourceManageDialog::slot_timerTimeout);
	//m_timer->start(1000); // 每秒触发一次

}

ResourceManageDialog::~ResourceManageDialog()
{
	/*this->UdpSocket->close();
	delete this->UdpSocket;*/
	delete ui;
}

void ResourceManageDialog::initTableWidgetCurve()
{
	//ui->tabWidgetCurve->setTabPosition(QTabWidget::West);
	//ui->tabWidgetCurve->removeTab(1);
	//ui->tabWidgetCurve->removeTab(0);

	//// 创建一些示例标签页
	//QWidget* tab1Widget = new QWidget;
	//QWidget* tab2Widget = new QWidget;
	//QWidget* tab3Widget = new QWidget;
	//QWidget* tab4Widget = new QWidget;
	//QWidget* tab5Widget = new QWidget;
	//// 添加一些内容到每个标签页
	//tab1Widget->setLayout(new QVBoxLayout);
	//tab2Widget->setLayout(new QVBoxLayout);
	//tab3Widget->setLayout(new QVBoxLayout);
	//tab4Widget->setLayout(new QVBoxLayout);
	//tab5Widget->setLayout(new QVBoxLayout);

	//// 将自定义标签添加到 QTabWidget
	//ui->tabWidgetGpu->addTab(tab1Widget, "");
	//ui->tabWidgetMemory->addTab(tab2Widget, "");
	//ui->tabWidgetDisk->addTab(tab3Widget, "");
	//ui->tabWidgetNet->addTab(tab4Widget, "");
	//ui->tabWidgetGpu->addTab(tab5Widget, "");

	//ui->tabWidgetGpu->setTabEnabled(0, true);
	//ui->tabWidgetMemory->setTabEnabled(1, true);
	//ui->tabWidgetDisk->setTabEnabled(2, true);
	//ui->tabWidgetNet->setTabEnabled(3, true);
	//ui->tabWidgetGpu->setTabEnabled(4, true);

	//ui->tabWidgetCpu->setTabIcon(0, QIcon()); // 如果不需要图标，可以移除此行
	//ui->tabWidgetMemory->setTabIcon(0, QIcon());
	//ui->tabWidgetDisk->setTabIcon(0, QIcon());
	//ui->tabWidgetNet->setTabIcon(0, QIcon());
	//ui->tabWidgetGpu->setTabIcon(0, QIcon());
	// 创建自定义标签
	//ui->tabWidgetCurve->tabBar()->setTabButton(0, QTabBar::RightSide, createCustomTab("CPU"));//曲线中的显示
	//ui->tabWidgetCurve->tabBar()->setTabButton(1, QTabBar::RightSide, createCustomTab(QString::fromLocal8Bit("内存")));
	//ui->tabWidgetCurve->tabBar()->setTabButton(2, QTabBar::RightSide, createCustomTab(QString::fromLocal8Bit("磁盘")));
	//ui->tabWidgetCurve->tabBar()->setTabButton(3, QTabBar::RightSide, createCustomTab(QString::fromLocal8Bit("网络")));
	//ui->tabWidgetCurve->tabBar()->setTabButton(4, QTabBar::RightSide, createCustomTab("GPU"));
	//connect(ui->tabWidgetCurve->tabBar(), &QTabBar::tabBarClicked, this, &ResourceManageDialog::slot_get_data);

	
	initWebViewCpu(ui->widgetCpu);
	initWebViewMemory(ui->widgetMemory);
	initWebViewDisk(ui->widgetDisk);
	initWebViewNet(ui->widgetNet);
	initWebViewGpu(ui->widgetGpu);
	
}

void ResourceManageDialog::initWebViewNet(QWidget* widget)
{
	m_webEngineViewNet = new QWebEngineView();
	QString pathNet = qApp->applicationDirPath() + "/eChartFileNet.html";
	m_webEngineViewNet->load(QUrl(pathNet));

	widget->layout()->addWidget(m_webEngineViewNet);

	using NameVec = std::vector<std::string>;
	//NameVec _names = { "10", "20", "30", "40", "50", "60" ,"70" };

	using ValueVec = std::vector<int>;
	ValueVec  __values = { 0 };


	QJsonArray  _data;
	for (size_t i = 0; i < __values.size(); i++)
	{
		QJsonObject itemData;
		// itemData.insert("itemName", QString::fromLocal8Bit(_names[i].c_str()));
	   //  itemData.insert("itemValue", __values[i]);
		_data.append(itemData);
	}
	//m_jsonDataNet.insert("titleName", QString::fromLocal8Bit("网络吞吐量"));
	m_jsonDataNet.insert("data", _data);
	// 折线图（line）
	// 柱状图（Bar）
	// 饼图（pie）
	// 散点图（scatter）
	// 地图（map）
	// 雷达图（radar） 
	// 词云图（wordCloud）
	// 图片地图（imageMap）
	// 组合图（compose）
	// 漏斗图（funnel）
	// 仪表盘（gauge）
	// 列表图（list）
	m_jsonDataNet.insert("type", "line");

	QObject::connect(m_webEngineViewNet, &QWebEngineView::loadFinished, [&]() {
		QString optionStr = QJsonDocument(m_jsonDataNet).toJson();
		//用到js中init() 函数
		QString js = QString("setData(%1)").arg(optionStr);
		qDebug() << js;
		m_webEngineViewNet->page()->runJavaScript(js);
	});
}
void ResourceManageDialog::initWebViewCpu(QWidget *widget)
{
	m_webEngineViewCpu = new QWebEngineView();
	QString pathNet = qApp->applicationDirPath() + "/eChartFileCpu.html";
	//qDebug() << qApp->applicationDirPath()<<"11111111111"<<pathNet;
	m_webEngineViewCpu->load(QUrl(pathNet));

	widget->layout()->addWidget(m_webEngineViewCpu);

	using NameVec = std::vector<std::string>;
	NameVec _names = { "10", "20", "30", "40", "45", "46" ,"50" };

	using ValueVec = std::vector<int>;
	ValueVec  __values = { 0 };


	QJsonArray  _data;
	QJsonObject itemData;
	for (size_t i = 0; i < _names.size(); i++)
	{

		itemData.insert("itemName", QString::fromLocal8Bit(_names[i].c_str()));
		//  itemData.insert("itemValue", __values[i]);
		_data.append(itemData);
	}
	//m_jsonDataCpu.insert("titleName", QString::fromLocal8Bit("CPU使用率"));
	m_jsonDataCpu.insert("data", _data);

	m_jsonDataCpu.insert("type", "line");

	QObject::connect(m_webEngineViewCpu, &QWebEngineView::loadFinished, [=]() {
		QString optionStr = QJsonDocument(m_jsonDataCpu).toJson();
		//用到js中init() 函数
		QString js = QString("setData(%1)").arg(optionStr);
		qDebug() << js;
		m_webEngineViewCpu->page()->runJavaScript(js);
	});
}

void ResourceManageDialog::initWebViewMemory(QWidget* widget)
{
	m_webEngineViewMemory = new QWebEngineView();
	QString path = qApp->applicationDirPath() + "/eChartFileMemory.html";
	m_webEngineViewMemory->load(QUrl(path));

	widget->layout()->addWidget(m_webEngineViewMemory);

	using NameVec = std::vector<std::string>;
	NameVec _names = { "10", "20", "30", "40", "45", "46" ,"50" };

	using ValueVec = std::vector<int>;
	ValueVec  __values = { 0 };


	QJsonArray  _data;
	for (size_t i = 0; i < _names.size(); i++)
	{
		QJsonObject itemData;
		itemData.insert("itemName", QString::fromLocal8Bit(_names[i].c_str()));
		//    itemData.insert("itemValue", __values[i]);
		_data.append(itemData);
	}
	//m_jsonDataMemory.insert("titleName", QString::fromLocal8Bit("内存使用率"));
	m_jsonDataMemory.insert("data", _data);

	m_jsonDataMemory.insert("type", "line");

	QObject::connect(m_webEngineViewMemory, &QWebEngineView::loadFinished, [&]() {
		QString optionStr = QJsonDocument(m_jsonDataMemory).toJson();
		//用到js中init() 函数
		QString js = QString("setData(%1)").arg(optionStr);
		qDebug() << js;
		m_webEngineViewMemory->page()->runJavaScript(js);
	});
}

void ResourceManageDialog::initWebViewDisk(QWidget* widget)
{
	m_webEngineViewDisk = new QWebEngineView();
	QString path = qApp->applicationDirPath() + "/eChartFileDisk.html";
	m_webEngineViewDisk->load(QUrl(path));

	widget->layout()->addWidget(m_webEngineViewDisk);

	using NameVec = std::vector<std::string>;
	NameVec _names = { "10", "20", "30", "40", "45", "46" ,"50" };

	using ValueVec = std::vector<int>;
	ValueVec  __values = { 0 };


	QJsonArray  _data;
	for (size_t i = 0; i < _names.size(); i++)
	{
		QJsonObject itemData;
		itemData.insert("itemName", QString::fromLocal8Bit(_names[i].c_str()));
		//   itemData.insert("itemValue", __values[i]);
		_data.append(itemData);
	}
	//m_jsonDataDisk.insert("titleName", QString::fromLocal8Bit("磁盘使用率"));
	m_jsonDataDisk.insert("data", _data);

	m_jsonDataDisk.insert("type", "line");

	QObject::connect(m_webEngineViewDisk, &QWebEngineView::loadFinished, [&]() {
		QString optionStr = QJsonDocument(m_jsonDataDisk).toJson();
		//用到js中init() 函数
		QString js = QString("setData(%1)").arg(optionStr);
		qDebug() << js;
		m_webEngineViewDisk->page()->runJavaScript(js);
	});
}

void ResourceManageDialog::initWebViewGpu(QWidget* widget)
{
	m_webEngineViewGpu = new QWebEngineView();
	QString pathGpu = qApp->applicationDirPath() + "/eChartFileGpu.html";
	//qDebug() << qApp->applicationDirPath()<<"11111111111"<<pathNet;
	m_webEngineViewGpu->load(QUrl(pathGpu));

	widget->layout()->addWidget(m_webEngineViewGpu);

	using NameVec = std::vector<std::string>;
	NameVec _names = { "10", "20", "30", "40", "45", "46" ,"50" };

	using ValueVec = std::vector<int>;
	ValueVec  __values = { 0 };


	QJsonArray  _data;
	QJsonObject itemData;
	for (size_t i = 0; i < _names.size(); i++)
	{

		itemData.insert("itemName", QString::fromLocal8Bit(_names[i].c_str()));
		//  itemData.insert("itemValue", __values[i]);
		_data.append(itemData);
	}
	//m_jsonDataGpu.insert("titleName", QString::fromLocal8Bit("GPU使用率"));
	m_jsonDataGpu.insert("data", _data);

	m_jsonDataGpu.insert("type", "line");

	QObject::connect(m_webEngineViewGpu, &QWebEngineView::loadFinished, [=]() {
		QString optionStr = QJsonDocument(m_jsonDataGpu).toJson();
		//用到js中init() 函数
		QString js = QString("setData(%1)").arg(optionStr);
		qDebug() << js;
		m_webEngineViewGpu->page()->runJavaScript(js);
	});
}

void ResourceManageDialog::startWebFlushTimer()
{
	m_timer->start(2000);
}

void ResourceManageDialog::stopWebFlushTimer()
{
	m_timer->stop();
}

QWidget* ResourceManageDialog::createCustomTab(const QString& tabName)
{
	QWidget* widget = new QWidget;
	QHBoxLayout* layout = new QHBoxLayout(widget);
	QLabel* label = new QLabel(tabName, widget);
	layout->addWidget(label);
	layout->setContentsMargins(0, 0, 0, 0);
	layout->setAlignment(Qt::AlignCenter);
	widget->setLayout(layout);
	return widget;
}

void ResourceManageDialog::addHostCpuElemnet(const QString& host, const double& value)
{

	if (m_mapCpuData[host].size() >= m_vectorMaxSize)
	{
		m_mapCpuData[host].remove(0);
	}
	m_mapCpuData[host].push_back(value);

	//updateCpuWebViewShow(host);

}

void ResourceManageDialog::addHostNetElemnet(const QString& host, const unsigned long& value)
{
	if (m_mapNetData[host].size() >= m_vectorMaxSize)
	{
		m_mapNetData[host].remove(0);
	}
	m_mapNetData[host].push_back(value);

	//  updateNetWebViewShow(host);
}

void ResourceManageDialog::addHostMemoryElemnet(const QString& host, const double& value)
{
	if (m_mapMemoryData[host].size() >= m_vectorMaxSize)
	{
		m_mapMemoryData[host].remove(0);
	}
	m_mapMemoryData[host].push_back(value);

	//  updateMemoryWebViewShow(host);
}

void ResourceManageDialog::addHostDiskElemnet(const QString& host, const double& value)
{
	if (m_mapDiskData[host].size() >= m_vectorMaxSize)
	{
		m_mapDiskData[host].remove(0);
	}
	m_mapDiskData[host].push_back(value);

	//updateDiskWebViewShow(host);
}

void ResourceManageDialog::addHostGpuElemnet(const QString& host, const double& value)
{

	if (m_mapGpuData[host].size() >= m_vectorMaxSize)
	{
		m_mapGpuData[host].remove(0);
	}
	m_mapGpuData[host].push_back(value);
}

void ResourceManageDialog::updateHostTableShow(const QString& host, const double& dCpu, const double& dMemory, const double& dDisk, const double& dNet, const double& dGpu)
{
	for (int row = 0; row < m_model->rowCount(); row++)
	{
		QModelIndex index = m_model->index(row, 0, QModelIndex()); // 获取第一列的索引
		//QStandardItem* item = m_model->itemFromIndex(index); // 获取该索引对应的 QStandardItem
		QStandardItem* item = m_model->item(row, 0);
		item->setTextAlignment(Qt::AlignCenter);
		if (item->text() == host)
		{ // 假设我们想要更新以 "Row" 开头的项
			item = m_model->item(row, 1);
			item->setTextAlignment(Qt::AlignCenter);
			item->setText(QString::number(dCpu) + QString(" %"));
			item = m_model->item(row, 2);
			item->setTextAlignment(Qt::AlignCenter);
			item->setText(QString::number(dMemory) + QString(" %"));
			item = m_model->item(row, 3);
			item->setTextAlignment(Qt::AlignCenter);
			item->setText(QString::number(dDisk) + QString(" %"));
			item = m_model->item(row, 4);
			item->setTextAlignment(Qt::AlignCenter);
			QString netData = "Kbps";
			if (dNet > 1024)
			{
				double temp = dNet / 1000;
				netData = "Mbps";
				item->setText(QString::number(temp) + netData);
			}
			else
			{
				item->setText(QString::number(dNet) + netData);
			}
			item = m_model->item(row, 5);
			item->setTextAlignment(Qt::AlignCenter);
			item->setText(QString::number(dGpu) + QString(" %"));
			return;
		}
	}

	int newRowIndex = m_model->rowCount(); // 获取当前行数
	m_model->insertRow(newRowIndex); // 插入新行
	m_model->setItem(newRowIndex, 0, new QStandardItem(host));
	m_model->setItem(newRowIndex, 1, new QStandardItem(QString::number(dCpu)));
	m_model->setItem(newRowIndex, 2, new QStandardItem(QString::number(dMemory)));
	m_model->setItem(newRowIndex, 3, new QStandardItem(QString::number(dDisk)));
	m_model->setItem(newRowIndex, 4, new QStandardItem(QString::number(dNet)));
	m_model->setItem(newRowIndex, 5, new QStandardItem(QString::number(dGpu)));

}

void ResourceManageDialog::updateCpuWebViewShow(const QString& host)
{
	QVector<double>& vectorData = m_mapCpuData[host];
	using NameVec = std::vector<std::string>;

	QJsonArray  _data;
	for (size_t i = 0; i < vectorData.size(); i++)
	{
		QJsonObject itemData;

		itemData.insert("itemValue", vectorData[i]);
		_data.append(itemData);
	}
	m_jsonDataCpu.insert("data", _data);
	//m_jsonDataCpu.insert("titleName", QString::fromLocal8Bit("CPU使用率"));

	QString optionStr = QJsonDocument(m_jsonDataCpu).toJson();
	//用到js中init() 函数
	QString js = QString("setData(%1)").arg(optionStr);
	//qDebug() << js;
	m_webEngineViewCpu->page()->runJavaScript(js);

}

void ResourceManageDialog::updateMemoryWebViewShow(const QString& host)
{
	QVector<double>& vectorData = m_mapMemoryData[host];
	using NameVec = std::vector<std::string>;

	QJsonArray  _data;
	for (size_t i = 0; i < vectorData.size(); i++)
	{
		QJsonObject itemData;

		itemData.insert("itemValue", vectorData[i]);
		_data.append(itemData);
	}
	QJsonObject jsonData;
	jsonData.insert("data", _data);
	//jsonData.insert("titleName", QString::fromLocal8Bit("内存使用率"));

	QString optionStr = QJsonDocument(jsonData).toJson();
	//用到js中init() 函数
	QString js = QString("setData(%1)").arg(optionStr);
	//qDebug() << js;
	m_webEngineViewMemory->page()->runJavaScript(js);
}

void ResourceManageDialog::updateDiskWebViewShow(const QString& host)
{
	QVector<double>& vectorData = m_mapDiskData[host];
	using NameVec = std::vector<std::string>;

	QJsonArray  _data;
	for (size_t i = 0; i < vectorData.size(); i++)
	{
		QJsonObject itemData;

		itemData.insert("itemValue", vectorData[i]);
		_data.append(itemData);
	}
	QJsonObject jsonData;
	jsonData.insert("data", _data);
	//jsonData.insert("titleName", QString::fromLocal8Bit("磁盘使用率"));

	QString optionStr = QJsonDocument(jsonData).toJson();
	//用到js中init() 函数
	QString js = QString("setData(%1)").arg(optionStr);
	//qDebug() << js;
	m_webEngineViewDisk->page()->runJavaScript(js);
}

void ResourceManageDialog::updateNetWebViewShow(const QString& host)
{
	QVector<double>& vectorData = m_mapNetData[host];
	using NameVec = std::vector<std::string>;

	QJsonArray  _data;
	for (size_t i = 0; i < vectorData.size(); i++)
	{
		QJsonObject itemData;

		itemData.insert("itemValue", vectorData[i]);
		_data.append(itemData);
	}
	QJsonObject jsonData;
	jsonData.insert("data", _data);
	//jsonData.insert("titleName", QString::fromLocal8Bit("网络吞吐量"));

	QString optionStr = QJsonDocument(jsonData).toJson();
	//用到js中init() 函数
	QString js = QString("setData(%1)").arg(optionStr);
	//qDebug() << js;
	m_webEngineViewNet->page()->runJavaScript(js);
}

void ResourceManageDialog::updateGpuWebViewShow(const QString& host)
{
	QVector<double>& vectorData = m_mapGpuData[host];
	using NameVec = std::vector<std::string>;

	QJsonArray  _data;
	for (size_t i = 0; i < vectorData.size(); i++)
	{
		QJsonObject itemData;

		itemData.insert("itemValue", vectorData[i]);
		_data.append(itemData);
	}
	QJsonObject jsonData;
	jsonData.insert("data", _data);
	//jsonData.insert("titleName", QString::fromLocal8Bit("GPU使用率"));

	QString optionStr = QJsonDocument(jsonData).toJson();
	//用到js中init() 函数
	QString js = QString("setData(%1)").arg(optionStr);
	//qDebug() << js;
	m_webEngineViewGpu->page()->runJavaScript(js);
}

void ResourceManageDialog::slot_modelItemChanged(QStandardItem* item)
{
	// 打印修改后的值
	qDebug() << "Item changed:" << item->text();
}

void ResourceManageDialog::slot_hostComboxChanged(const QString& text)
{
	//    using NameVec = std::vector<std::string>;
	//    //NameVec _names = { "10", "20", "30", "40", "45", "46" ,"50" };
	//
	//    using ValueVec = std::vector<int>;
	//    ValueVec  __values = { 200, 20, 36, 10, 10, 20 ,222 ,333};
	//
	//    QJsonArray  _data;
	//    for (size_t i = 0; i < __values.size(); i++)
	//  {
	//        QJsonObject itemData;
	//      //itemData.insert("itemName", QString::fromLocal8Bit(_names[i].c_str()));
	//        itemData.insert("itemValue", __values[i]);
	//        _data.append(itemData);
	//    }
	//  //  m_jsonDataNet.insert("titleName", QString::fromLocal8Bit("CPU"));
	//    m_jsonDataNet.insert("data", _data);
	//   
	//    m_jsonDataNet.insert("type", "line");
	//
	//    QString optionStr = QJsonDocument(m_jsonDataNet).toJson();
	//   //用到js中init() 函数
	//    QString js = QString("setData(%1)").arg(optionStr);
	//    qDebug() << js;
	//    m_webEngineViewNet->page()->runJavaScript(js);
}

void ResourceManageDialog::slot_timerTimeout()
{

	/* double dCpuUse = common::getCpuUsage();
	 double lFreeAll;
	 double lToalAll;
	 common::getAllDisSpace(lFreeAll, lToalAll);
	 double dDiskUseRate = (lToalAll - lFreeAll) * 100.0 / lToalAll;
	 long allPhysicsMem;
	 long freePhysicsMem;
	 common::getPhysicsMem(allPhysicsMem, freePhysicsMem);
	 double dMemUseRate = (allPhysicsMem - freePhysicsMem) * 100.0 / allPhysicsMem;
	 common::getNetworkInterfaceStatistics();
	 common::PrintAdapterInfo();
	 unsigned long netThroughput = common::GetNetworkInterfacesThroughput();*/
	 //加载列表页面的四个数据
	// updateHostTableShow("1", dCpuUse, dMemUseRate, dDiskUseRate, netThroughput);
	//if (message.host_name != 0) 
	QString hostName;
	Message_t hostInformation;
	for (const auto& pair : myMap)
	{
		hostName = pair.first;
		hostInformation = pair.second;

		updateHostTableShow(hostInformation.host_name, hostInformation.Cpu_Message, hostInformation.Memory_Message, hostInformation.Disk_Message, hostInformation.Net_Message, hostInformation.Gpu_Message);

		// 检查comboBox中是否已经存在该项
		int index1 = ui->comboBox1->findText(hostInformation.host_name);
		int index2 = ui->comboBox2->findText(hostInformation.host_name);
		int index3 = ui->comboBox3->findText(hostInformation.host_name);
		int index4 = ui->comboBox4->findText(hostInformation.host_name);
		int index5 = ui->comboBox5->findText(hostInformation.host_name);
		if ((index1 == -1 || index2 == -1 ||index3 == -1 || index4 == -1 || index5 == -1) && !hostInformation.host_name.isEmpty())
		{
			// 如果不存在，才添加
			ui->comboBox1->addItem(hostInformation.host_name);
			ui->comboBox2->addItem(hostInformation.host_name);
			ui->comboBox3->addItem(hostInformation.host_name);
			ui->comboBox4->addItem(hostInformation.host_name);
			ui->comboBox5->addItem(hostInformation.host_name);
		}
		//if (CPU_init == true && hostInformation.host_name == ui->comboBox->currentText())
		//if (ui->comboBox1->currentText() == hostInformation.host_name)
		{
			updateCpuWebViewShow(ui->comboBox1->currentText());
		}
		//else if (ui->comboBox2->currentText()== hostInformation.host_name)
		{
			updateMemoryWebViewShow(ui->comboBox2->currentText());
		}
		//else if (ui->comboBox3->currentText() == hostInformation.host_name)
		{
			updateDiskWebViewShow(ui->comboBox3->currentText());
		}
		//else if (ui->comboBox4->currentText() == hostInformation.host_name)
		{
			updateNetWebViewShow(ui->comboBox4->currentText());
		}
		//else if (ui->comboBox5->currentText() == hostInformation.host_name)
		{
			updateGpuWebViewShow(ui->comboBox5->currentText());
		}
	}
	
}

void ResourceManageDialog::slot_get_data(int index)
{
	if (index == 0)
	{
		CPU_init = true;
		memory_init = false;
		disk_init = false;
		net_init = false;
		Gpu_init = false;
	}
	else if (index == 1)
	{
		CPU_init = false;
		memory_init = true;
		disk_init = false;
		net_init = false;
		Gpu_init = false;
	}
	else if (index == 2)
	{
		CPU_init = false;
		memory_init = false;
		disk_init = true;
		net_init = false;
		Gpu_init = false;
	}
	else if (index == 3)
	{
		CPU_init = false;
		memory_init = false;
		disk_init = false;
		net_init = true;
		Gpu_init = false;
	}
	else if (index == 4)
	{
		CPU_init = false;
		memory_init = false;
		disk_init = false;
		net_init = false;
		Gpu_init = true;
	}
}

void  ResourceManageDialog::getUdpData()
{
	// UDP的连接
	this->UdpSocket = new QUdpSocket();
	//this->UdpSocket->bind(QHostAddress::Any, 54321);
	bool ret;
	ret = this->UdpSocket->bind(QHostAddress::AnyIPv4, 54321, QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint);
	if (!ret)
	{
		qDebug() << ret;
	}
	//this->UdpSocket->joinMulticastGroup(QHostAddress("224.0.0.100"));
	connect(this->UdpSocket, &QUdpSocket::readyRead, [=]() {
		while (this->UdpSocket->hasPendingDatagrams())
		{
			QByteArray datagram;
			datagram.resize(this->UdpSocket->pendingDatagramSize());
			qint64 bytesRead = this->UdpSocket->readDatagram(datagram.data(), datagram.size(), &addr, &port);
			//qDebug() << addr.toString();
			if (bytesRead <= 0)
			{
				//应该是在列表中删除那一行的信息
			}

			QDataStream stream(&datagram, QIODevice::ReadOnly);

			stream >> message.host_name;

			if (message.host_name == "success" || message.host_name == "false")
			{
				if (message.host_name == "success")
				{
					emit  signal_udpOrderFinsh(1);
				}
				else
				{
					emit  signal_udpOrderFinsh(0);
				}
			}
			else
			{
				stream >> message.host_ip1;
				stream >> message.host_ip2;
				stream >> message.Cpu_Message;
				stream >> message.Memory_Message;
				stream >> message.Disk_Message;
				quint32 temp;
				stream >> temp;
				message.Net_Message = static_cast<unsigned long>(temp);
				stream >> message.Gpu_Message;

				//将消息存入map容器中
				myMap[message.host_name] = message;

				//输出收到的消息
				qDebug() <<"send host name:"<< message.host_name;
				qDebug() << "send host disk:" << message.Disk_Message;
				qDebug() << "send host ip:" << addr.toString();
				addHostCpuElemnet(message.host_name, message.Cpu_Message);
				addHostMemoryElemnet(message.host_name, message.Memory_Message);
				addHostDiskElemnet(message.host_name, message.Disk_Message);
				addHostNetElemnet(message.host_name, message.Net_Message);
				addHostGpuElemnet(message.host_name, message.Gpu_Message);

				for (auto& myset : common::setHostData)
				{
					if (message.host_ip1.toStdString() == myset.ip)
					{
						myset.dGpuUsage = message.Gpu_Message;
						myset.dCpuUsage = message.Cpu_Message;
					}
					else if (message.host_ip2.toStdString() == myset.ip)
					{
						myset.dGpuUsage = message.Gpu_Message;
						myset.dCpuUsage = message.Cpu_Message;
					}
				}
			}
			/*Command_t command;
			command.str1 = "Wuncompress";
			command.str2 = "user1//back.zip";
			command.str3 = "over";
			QByteArray dataGram;
			QDataStream stream2(&dataGram, QIODevice::WriteOnly);
			stream2 << command.str1;
			stream2 << command.str2;
			stream2 << command.str3;
			int ret = 0;
			ret = this->UdpSocket->writeDatagram(dataGram, addr, port);*/
			// 插入数据库;
		   /* table_ip stIp;
			stIp.ip = infor->host_ip.toStdString();
			stIp.host = infor->host_name.toStdString();
			int count = 0;
			if (db::databaseDI::Instance().get_ip_count(stIp.ip, count))
			{
				if (count <= 0)
				{
					if (!db::databaseDI::Instance().add_ip(stIp))
					{
						qDebug() << "db::databaseDI::Instance().add_ip   error!";
					}
				}

			}*/
		}
	});
}

void ResourceManageDialog::slot_showList()
{
	ui->btnList->setStyleSheet("QPushButton { font-size: 22px;color: #ffffff;border-image: url(:/image/btn_blue.png) 0 0 0 0 stretch;}");
	ui->btnCurve->setStyleSheet("QPushButton { font-size: 22px;color: #7482a6;}");
	ui->stackedWidget->setCurrentIndex(0);
	m_model = new QStandardItemModel();
	m_model->setColumnCount(6);
	m_model->setHeaderData(0, Qt::Horizontal, QString::fromLocal8Bit("主机名称"));
	m_model->setHeaderData(1, Qt::Horizontal, QString::fromLocal8Bit("CPU"));//列表中的显示
	m_model->setHeaderData(2, Qt::Horizontal, QString::fromLocal8Bit("内存"));
	m_model->setHeaderData(3, Qt::Horizontal, QString::fromLocal8Bit("磁盘"));
	m_model->setHeaderData(4, Qt::Horizontal, QString::fromLocal8Bit("网络"));
	m_model->setHeaderData(5, Qt::Horizontal, QString::fromLocal8Bit("GPU"));

	ui->tableViewList->setModel(m_model);
	common::setTableViewBasicConfiguration(ui->tableViewList);
}
void ResourceManageDialog::slot_showCurve()
{
	ui->btnCurve->setStyleSheet("QPushButton { font-size: 22px;color: #ffffff;border-image: url(:/image/btn_blue.png) 0 0 0 0 stretch;}");
	ui->btnList->setStyleSheet("QPushButton { font-size: 22px;color: #7482a6;}");
	//initTableWidgetCurve();
	ui->stackedWidget->setCurrentIndex(1);
	// 连接信号和槽
	//connect(ui->comboBox, &QComboBox::currentTextChanged, this, &ResourceManageDialog::slot_hostComboxChanged);
}
