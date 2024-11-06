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
    ui->tabWidget->setCurrentIndex(0);
    m_model = new QStandardItemModel();
    m_model->setColumnCount(5);
    m_model->setHeaderData(0, Qt::Horizontal, QString::fromLocal8Bit("��������"));
    m_model->setHeaderData(1, Qt::Horizontal, QString::fromLocal8Bit("CPU"));//�б��е���ʾ
    m_model->setHeaderData(2, Qt::Horizontal, QString::fromLocal8Bit("�ڴ�"));
    m_model->setHeaderData(3, Qt::Horizontal, QString::fromLocal8Bit("����"));
    m_model->setHeaderData(4, Qt::Horizontal, QString::fromLocal8Bit("����"));

    ui->tableView->setModel(m_model);
    common::setTableViewBasicConfiguration(ui->tableView);


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
   //ui->comboBox->addItem(QString::fromLocal8Bit("����1"));
   //ui->comboBox->addItem(QString::fromLocal8Bit("����2"));
   //this->message = new Message_t();
   getUdpData(&message);
   //���������б������ĳ����������ؼ��Ŀ��
   ui->comboBox->setSizeAdjustPolicy(QComboBox::AdjustToContents);
   // �����źźͲ�
   connect(m_model, &QStandardItemModel::itemChanged, this, &ResourceManageDialog::slot_modelItemChanged);
   connect(ui->comboBox, &QComboBox::currentTextChanged, this, &ResourceManageDialog::slot_hostComboxChanged);

   m_timer = new QTimer(this);
   QObject::connect(m_timer, &QTimer::timeout, this, &ResourceManageDialog::slot_timerTimeout);
   //m_timer->start(1000); // ÿ�봥��һ��

}

ResourceManageDialog::~ResourceManageDialog()
{
    this->UdpSocket->close();
    delete this->UdpSocket;
    delete ui;
}

void ResourceManageDialog::initTableWidgetCurve()
{
    ui->tabWidgetCurve->setTabPosition(QTabWidget::West);
    ui->tabWidgetCurve->removeTab(1);
    ui->tabWidgetCurve->removeTab(0);

    // ����һЩʾ����ǩҳ
    QWidget* tab1Widget = new QWidget;
    QWidget* tab2Widget = new QWidget;
    QWidget* tab3Widget = new QWidget;
    QWidget* tab4Widget = new QWidget;
    // ���һЩ���ݵ�ÿ����ǩҳ
    tab1Widget->setLayout(new QVBoxLayout);
    tab2Widget->setLayout(new QVBoxLayout);
    tab3Widget->setLayout(new QVBoxLayout);
    tab4Widget->setLayout(new QVBoxLayout);

    // ���Զ����ǩ��ӵ� QTabWidget
    ui->tabWidgetCurve->addTab(tab1Widget, "");
    ui->tabWidgetCurve->addTab(tab2Widget, "");
    ui->tabWidgetCurve->addTab(tab3Widget, "");
    ui->tabWidgetCurve->addTab(tab4Widget, "");

    ui->tabWidgetCurve->setTabEnabled(0, true);
    ui->tabWidgetCurve->setTabEnabled(1, true);
    ui->tabWidgetCurve->setTabEnabled(2, true);

    //tabWidget->setTabIcon(0, QIcon()); // �������Ҫͼ�꣬�����Ƴ�����

    // �����Զ����ǩ
    ui->tabWidgetCurve->tabBar()->setTabButton(0, QTabBar::RightSide, createCustomTab("CPU"));//�����е���ʾ
    ui->tabWidgetCurve->tabBar()->setTabButton(1, QTabBar::RightSide, createCustomTab(QString::fromLocal8Bit("�ڴ�")));
    ui->tabWidgetCurve->tabBar()->setTabButton(2, QTabBar::RightSide, createCustomTab(QString::fromLocal8Bit("����")));
    ui->tabWidgetCurve->tabBar()->setTabButton(3, QTabBar::RightSide, createCustomTab(QString::fromLocal8Bit("����")));
    connect(ui->tabWidgetCurve->tabBar(), &QTabBar::tabBarClicked, this, &ResourceManageDialog::slot_get_data);

    initWebViewCpu(tab1Widget);
    initWebViewMemory(tab2Widget);
    initWebViewDisk(tab3Widget);
    initWebViewNet(tab4Widget);
   
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
    ValueVec  __values = { 0};


    QJsonArray  _data;
    for (size_t i = 0; i < __values.size(); i++)
    {
        QJsonObject itemData;
       // itemData.insert("itemName", QString::fromLocal8Bit(_names[i].c_str()));
      //  itemData.insert("itemValue", __values[i]);
        _data.append(itemData);
    }
    m_jsonDataNet.insert("titleName", QString::fromLocal8Bit("����"));
    m_jsonDataNet.insert("data", _data);
    // ����ͼ��line��
    // ��״ͼ��Bar��
    // ��ͼ��pie��
    // ɢ��ͼ��scatter��
    // ��ͼ��map��
    // �״�ͼ��radar�� 
    // ����ͼ��wordCloud��
    // ͼƬ��ͼ��imageMap��
    // ���ͼ��compose��
    // ©��ͼ��funnel��
    // �Ǳ��̣�gauge��
    // �б�ͼ��list��
    m_jsonDataNet.insert("type", "line");

    QObject::connect(m_webEngineViewNet, &QWebEngineView::loadFinished, [&]() {
        QString optionStr = QJsonDocument(m_jsonDataNet).toJson();
        //�õ�js��init() ����
        QString js = QString("setData(%1)").arg(optionStr);
        qDebug() << js;
        m_webEngineViewNet->page()->runJavaScript(js);
        });
}
void ResourceManageDialog::initWebViewCpu(QWidget* widget)
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
    m_jsonDataCpu.insert("titleName", QString::fromLocal8Bit("CPU"));
    m_jsonDataCpu.insert("data", _data);
 
    m_jsonDataCpu.insert("type", "line");

   QObject::connect(m_webEngineViewCpu, &QWebEngineView::loadFinished, [=]() {
        QString optionStr = QJsonDocument(m_jsonDataCpu).toJson();
        //�õ�js��init() ����
        QString js = QString("setData(%1)").arg(optionStr);
        qDebug() << js;
        m_webEngineViewCpu->page()->runJavaScript(js);
        });
    

}

void ResourceManageDialog::initWebViewMemory(QWidget* widget)
{
    m_webEngineViewMemory= new QWebEngineView(); 
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
    m_jsonDataMemory.insert("titleName", QString::fromLocal8Bit("�ڴ�"));
    m_jsonDataMemory.insert("data", _data);

    m_jsonDataMemory.insert("type", "line");

    QObject::connect(m_webEngineViewMemory, &QWebEngineView::loadFinished, [&]() {
        QString optionStr = QJsonDocument(m_jsonDataMemory).toJson();
        //�õ�js��init() ����
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
    m_jsonDataDisk.insert("titleName", QString::fromLocal8Bit("����"));
    m_jsonDataDisk.insert("data", _data);

    m_jsonDataDisk.insert("type", "line");

    QObject::connect(m_webEngineViewDisk, &QWebEngineView::loadFinished, [&]() {
        QString optionStr = QJsonDocument(m_jsonDataDisk).toJson();
        //�õ�js��init() ����
        QString js = QString("setData(%1)").arg(optionStr);
        qDebug() << js;
        m_webEngineViewDisk->page()->runJavaScript(js);
        });
}

void ResourceManageDialog::startWebFlushTimer()
{
    m_timer->start(1000);
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

void ResourceManageDialog::updateHostTableShow(const QString& host, const double& dCpu, const double& dMemory, const double& dDisk, const double& dNet)
{
    for (int row = 0; row < m_model->rowCount();row++)
    {
        QModelIndex index = m_model->index(row, 0, QModelIndex()); // ��ȡ��һ�е�����
        //QStandardItem* item = m_model->itemFromIndex(index); // ��ȡ��������Ӧ�� QStandardItem
        QStandardItem* item = m_model->item(row, 0);
        if (item->text()== host)
        { // ����������Ҫ������ "Row" ��ͷ����
            item= m_model->item(row, 1);
            item->setText(QString::number(dCpu)+QString(" %"));
            item = m_model->item(row, 2);
            item->setText(QString::number(dMemory) + QString(" %"));
            item = m_model->item(row, 3);
            item->setText(QString::number(dDisk) + QString(" %"));
          
            item = m_model->item(row, 4);
            item->setText(QString::number(dNet) + QString(" Kbps"));
            return;
        }
    }
  
    int newRowIndex = m_model->rowCount(); // ��ȡ��ǰ����
    m_model->insertRow(newRowIndex); // ��������
    m_model->setItem(newRowIndex, 0, new QStandardItem(host));
    m_model->setItem(newRowIndex, 1, new QStandardItem(QString::number(dCpu)));
    m_model->setItem(newRowIndex, 2, new QStandardItem(QString::number(dMemory)));
    m_model->setItem(newRowIndex, 3, new QStandardItem(QString::number(dDisk)));
    m_model->setItem(newRowIndex, 4, new QStandardItem(QString::number(dNet)));
    
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
    m_jsonDataCpu.insert("titleName", QString::fromLocal8Bit("CPUʹ����"));

    QString optionStr = QJsonDocument(m_jsonDataCpu).toJson();
    //�õ�js��init() ����
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
    jsonData.insert("titleName", QString::fromLocal8Bit("�ڴ�ʹ����"));

    QString optionStr = QJsonDocument(jsonData).toJson();
    //�õ�js��init() ����
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
    jsonData.insert("titleName", QString::fromLocal8Bit("����ʹ����"));

    QString optionStr = QJsonDocument(jsonData).toJson();
    //�õ�js��init() ����
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
    jsonData.insert("titleName", QString::fromLocal8Bit("����������"));

    QString optionStr = QJsonDocument(jsonData).toJson();
    //�õ�js��init() ����
    QString js = QString("setData(%1)").arg(optionStr);
    //qDebug() << js;
    m_webEngineViewNet->page()->runJavaScript(js);
}

void ResourceManageDialog::slot_modelItemChanged(QStandardItem* item)
{
    // ��ӡ�޸ĺ��ֵ
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
//   //�õ�js��init() ����
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
        //�����б�ҳ����ĸ�����
       // updateHostTableShow("1", dCpuUse, dMemUseRate, dDiskUseRate, netThroughput);
    if (message.host_name != 0) {
        updateHostTableShow(message.host_name, message.CPU_Message, message.Memory_Message, message.Disk_Message, message.Net_Message);
    }
    // ���comboBox���Ƿ��Ѿ����ڸ���
    int index = ui->comboBox->findText(message.host_name);
    if (index == -1 && !message.host_name.isEmpty())
    { // ��������ڣ������
        ui->comboBox->addItem(message.host_name);
    }
    if (CPU_init == true && message.host_name == ui->comboBox->currentText()) {
        //addHostCpuElemnet(message.host_name, message.CPU_Message);
		updateCpuWebViewShow(message.host_name);
    }
    else if (memory_init == true && message.host_name == ui->comboBox->currentText()) {
        //addHostMemoryElemnet(message.host_name, message.Memory_Message);
		updateMemoryWebViewShow(message.host_name);
    }
    else if (disk_init == true && message.host_name == ui->comboBox->currentText()) {
		updateDiskWebViewShow(message.host_name);
        //addHostDiskElemnet(message.host_name, message.Disk_Message);
    }
    else if (net_init == true && message.host_name == ui->comboBox->currentText()) {
        //addHostNetElemnet(message.host_name, message.Net_Message);
		updateNetWebViewShow(message.host_name);
    }
    /*if (message.host_name == ui->comboBox->currentText())
    {
        updateCpuWebViewShow(message.host_name);
        updateMemoryWebViewShow(message.host_name);
        updateDiskWebViewShow(message.host_name);
        updateNetWebViewShow(message.host_name);
    }*/

}

void ResourceManageDialog::slot_get_data(int index)
{
    if (index == 0)
    {
        CPU_init = true;
        memory_init = false;
        disk_init = false;
        net_init = false;

    }
    else if (index == 1)
    {
        CPU_init = false;
        memory_init = true;
        disk_init = false;
        net_init = false;

    }
    else if (index == 2)
    {
        CPU_init = false;
        memory_init = false;
        disk_init = true;
        net_init = false;

    }
    else if (index == 3)
    {
        CPU_init = false;
        memory_init = false;
        disk_init = false;
        net_init = true;

    }
}

void  ResourceManageDialog::getUdpData(Message_t * infor)
{
	
    // UDP������
    this->UdpSocket = new QUdpSocket();
    
    //this->UdpSocket->bind(QHostAddress::Any, 54321);
	this->UdpSocket->bind(QHostAddress::AnyIPv4,54321,QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint);


    connect(this->UdpSocket, &QUdpSocket::readyRead, [=]() {
        while (this->UdpSocket->hasPendingDatagrams())
        {
            QByteArray datagram;
            datagram.resize(this->UdpSocket->pendingDatagramSize());
			qint64 bytesRead = this->UdpSocket->readDatagram(datagram.data(), datagram.size(),&addr,&port);
			//qDebug() << addr.toString();
			if (bytesRead <= 0)
			{
				//Ӧ�������б���ɾ����һ�е���Ϣ
			}

            QDataStream stream(&datagram, QIODevice::ReadOnly);

            stream >> infor->host_name;
            stream >> infor->host_ip;
            stream >> infor->CPU_Message;
            stream >> infor->Memory_Message;
            stream >> infor->Disk_Message;
            quint32 temp;
            stream >> temp;
            infor->Net_Message = static_cast<unsigned long>(temp);
			//if (CPU_init == true)
			{
				addHostCpuElemnet(infor->host_name, infor->CPU_Message);
			}
			//else if (memory_init == true)
			{
				addHostMemoryElemnet(infor->host_name, infor->Memory_Message);
			}
			//else if (disk_init == true)
			{
				addHostDiskElemnet(infor->host_name, infor->Disk_Message);
			}
			//else if (net_init == true)
			{
				addHostNetElemnet(infor->host_name, infor->Net_Message);
			}

			//this->UdpSocket->writeDatagram("send to daili information", addr, port);
            // �������ݿ�;
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
