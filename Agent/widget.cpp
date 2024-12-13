#include "widget.h"
#include "ui_widget.h"
#include <cmath>

#include <qdebug.h>

#include "Win32Utils/CDeviceHelper.h"
#include "Win32Utils/CWmiQueryHelper.h"
#include "Win32Utils/CDeviceHelper.h"
#include "Win32Utils/CStrUtils.h"
#include "CPerformHelper.h"
#include "ZipFunction.h"

using namespace std;
namespace fs = std::filesystem;

Widget::Widget(QWidget *parent)
	: QWidget(parent)
	, ui(new Ui::Widget)
{
	ui->setupUi(this);
	setWindowTitle("代理");

	//用于获取主机的信息
	this->my_timer = new QTimer();
	this->UDPSocket = new QUdpSocket();

	qint64 ret;
	bool result = UDPSocket->bind(QHostAddress::AnyIPv4, 6667, QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint);
	if (!result)
	{
		qDebug() << "Failed to bind port" << UDPSocket->errorString();
	}


	// 设置定时器类型为Qt::VeryCoarseTimer
	this->my_timer->setTimerType(Qt::VeryCoarseTimer);

	initGpu();
	connect(my_timer, &QTimer::timeout, this, &Widget::slot_useUdp);
	this->my_timer->start(1000);

	//QString localHostName=QHostInfo::localHostName();   //获取主机名
	//QHostInfo hostInfo=QHostInfo::fromName(localHostName);//本机的IP地址
	//QList<QHostAddress> listAdress=hostInfo.addresses();  //IP地址列表
	//         for(int i = 0;i<listAdress.size();i++)
	//         {
	//             //qDebug()<<listAdress.at(i).toString();  //如果主机的IP列表不为空，则使用其第一个IP地址
			 //	qDebug() << listAdress.at(1).toString();
			 //	qDebug() << listAdress.at(2).toString();
			 //}
	 //如果主机的IP列表不为空，则显示其第8个IP地址
	 //ui->textEdit->append(listAdress.at(7).toString());

}

Widget::~Widget()
{
	UDPSocket->close();
	delete UDPSocket;
	UDPSocket = nullptr;

	my_timer->stop();
	delete my_timer;
	my_timer = nullptr;
	delete ui;
	//取消映射
	cancel_mapping();
}

void Widget::initGpu()
{

	std::vector<VIDEO_ADAPTER_DESC_INFO> vResult = CDeviceHelper::GetAllVideoAdapterDesc();

	CDeviceHelper obj;

	//clock_t tmBegin = ::clock();
	DEVICE_INFO info = obj.GetDeviceInfo();
	//clock_t tmEnd = ::clock();



	perfmon = new CPerformHelper;

	int nTimeInterval = 1000;

	perfmon->Initialize();
	perfmon->SetCollectInterval(nTimeInterval);
	//perfmon->AddCounter(_T(PERFM_PATH_CPU_UTILITY));
	//perfmon->AddCounter(_T(PERFM_PATH_DISK_READ_RATE));
	//perfmon->AddCounter(_T(PERFM_PATH_DISK_WRITE_RATE));
	//perfmon->AddCounter(_T(PERFM_PATH_CPU_PERFORMANCE));
	//perfmon->AddCounter(_T(PERFM_PATH_CPU_FREQUENCY));
	//perfmon->AddCounter(_T(PERFM_PATH_NETWORK_RECV_RATE));
	//perfmon->AddCounter(_T(PERFM_PATH_NETWORK_SENT_RATE));
	perfmon->AddCounter(_T(PERFM_PATH_GPU_UTILITY));
	//perfmon->AddCounter(_T(PERFM_PATH_GPU_MEMORY_DEDICATED_USAGE_UTILITY));
	//perfmon->AddCounter(_T(PERFM_PATH_GPU_MEMORY_SHARE_USAGE_UTILITY));
	//perfmon->AddCounter(_T(PERFM_PATH_GPU_MEMORY_TOTAL_COMMITTED_USAGE_UTILITY));
	perfmon->StartCollect();

	// PDH_FMT_COUNTERVALUE value = { 0 };

	 //SIZE_T DedicatedVideoMemory = vResult[0].AdapterDesc.DedicatedVideoMemory;
	 //SIZE_T DedicatedSystemMemory = vResult[0].AdapterDesc.DedicatedSystemMemory;
	 //SIZE_T SharedSystemMemory = vResult[0].AdapterDesc.SharedSystemMemory;

	MEMORYSTATUSEX memStatus = { 0 };
	memStatus.dwLength = sizeof(MEMORYSTATUSEX);

	//double lfFrequency = 0.0f;
	//while (1)
	//{
	//    //获取GPU占用率
	//    if (perfmon->GetFormattedCounterArray(_T(PERFM_PATH_GPU_UTILITY), PDH_FMT_DOUBLE, &m_SystemValue))
	//    {
	//      //  Console::Printf(_T("GPU 利用率: %.1lf%%"), value.doubleValue);
	//     
	//        qDebug() << "GPU 利用率: " << m_SystemValue.doubleValue << "%%";
	//    }
	//}
}

double Widget::getGpuUsage()
{
	if (perfmon->GetFormattedCounterArray(_T(PERFM_PATH_GPU_UTILITY), PDH_FMT_DOUBLE, &m_SystemValue))
	{
		return   m_SystemValue.doubleValue;
	}
	return 0.0;
}


void Widget::get_file_information()
{

	QString exeDir = QCoreApplication::applicationDirPath();
	//qDebug()<<exeDir;

	QString strIniPath = exeDir + "/soft.ini";

	// 创建QSettings对象并指定INI文件路径
	QSettings settings(strIniPath, QSettings::IniFormat);

	// 获取INI文件中的所有节
	QStringList sections = settings.childGroups();
	// 清空之前的列表
	m_serverList.clear();

	// 遍历节列表
	foreach(const QString & section, sections)
	{
		// 切换到指定的节
		settings.beginGroup(section);

		// 获取该节下的所有键
		//        QStringList keys = settings.allKeys();

		//        if (section == "UDP")
		//        {
		quint16 Port = settings.value("sendPort", 0).toUInt();
		QHostAddress IP;
		IP.setAddress(settings.value("sendIp", "").toString());

		if (!IP.isNull() && Port != 0) {
			m_serverList.append(QPair<QHostAddress, quint16>(IP, Port));
		}
		settings.endGroup();

		//        }
	}
}

void Widget::slot_useUdp()
{

	//qDebug() << "GPU 利用率: " << getGpuUsage() << "%%";

	Message_t *message = new Message_t();

	//qDebug() << "111111111111111111111111111";

	QString localHostName = QHostInfo::localHostName();   //获取主机名
	message->host_name = localHostName;
	//获取本机的IP地址
	QHostInfo hostInfo = QHostInfo::fromName(localHostName);//本机的IP地址
	QList<QHostAddress> listAdress = hostInfo.addresses();  //IP地址列表
	//for(int i = 1;i < 3;++i){
	/* QList<QHostAddress> addresses = QNetworkInterface::allAddresses();
	 for (const QHostAddress &address : addresses) {*/
	 // 检查是否是IPv4地址
	 //if (address.protocol() == QAbstractSocket::IPv4Protocol && !address.isLoopback()) 
	{
		//message->host_ip1 = listAdress[0].toString();
		//message->host_ip2 = listAdress[1].toString();
		message->host_ip1 = listAdress[2].toString();
		message->host_ip2 = listAdress[3].toString();

		ui->textEdit->append(listAdress[2].toString());
		ui->textEdit->append(listAdress[3].toString());
	}
	// }
	 //qDebug()<<message->host_ip;
	message->CPU_Message = common::getCpuUsage();

	long allPhysicsMem;
	long freePhysicsMem;
	common::getPhysicsMem(allPhysicsMem, freePhysicsMem);
	message->Memory_Message = (allPhysicsMem - freePhysicsMem) * 100.0 / allPhysicsMem;

	double lFreeAll;
	double lToalAll;
	common::getAllDisSpace(lFreeAll, lToalAll);
	message->Disk_Message = (lToalAll - lFreeAll) * 100.0 / lToalAll;
	//        common::getNetworkInterfaceStatistics();
	//        common::PrintAdapterInfo();
	message->Net_Message = common::GetNetworkInterfacesThroughput();
	double value;
	value = getGpuUsage();
	//int roundedValue = static_cast<int>(value);
	message->Gpu_Message = value;

	QByteArray dataGram;
	QDataStream stream(&dataGram, QIODevice::WriteOnly);
	stream << message->host_name;
	stream << message->host_ip1;
	stream << message->host_ip2;
	stream << message->CPU_Message;
	stream << message->Memory_Message;
	stream << message->Disk_Message;
	stream << static_cast<quint32>(message->Net_Message);
	stream << message->Gpu_Message;


	//用于获取发送者的 IP 和端口
	//    QHostAddress &IP,quint16 &Port
	//    QHostAddress IP;
	//    quint16 Port=0;
	get_file_information();


	qint64 ret;
	//bool result = UDPSocket->bind(QHostAddress::AnyIPv4,8888,QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint);
	//if(!result)
	{
		//qDebug() << "Failed to bind port" << UDPSocket->errorString();
	}
	for (const auto &server : m_serverList)
	{
		ret = UDPSocket->writeDatagram(dataGram, server.first, server.second);
		if (ret == -1) {
			// 发送失败
			qDebug() << "Error sending datagram:" << UDPSocket->errorString() << "  " << UDPSocket->error();

			ui->textEdit->append(UDPSocket->errorString());
		}
		else {
			// 发送成功
			qDebug() << "Bytes sent:" << ret;
			ui->textEdit->append(QString::number(ret));
		}

		//const QHostAddress &ip = server.first;
		//quint16 port = server.second;
		//qDebug() << "IP:" << ip.toString() << "Port:" << port;

		//确保数据报被发送
		//UDPSocket->waitForBytesWritten();

	}
	delete message;
	message = nullptr;

	//接收
	//QString command;
	receive_mess();
}

void Widget::receive_mess()
{

	connect(UDPSocket, &QUdpSocket::readyRead, [this]() {
		while (UDPSocket->hasPendingDatagrams())
		{
			QByteArray receivedDatagram;
			receivedDatagram.resize(UDPSocket->pendingDatagramSize());
			QHostAddress serverReplyAddress;
			quint16 serverReplyPort;

			qint64 bytesReceived = UDPSocket->readDatagram(receivedDatagram.data(), receivedDatagram.size(), &serverReplyAddress, &serverReplyPort);
			if (bytesReceived > 0)
			{
				qDebug() << receivedDatagram.data();

				QDataStream stream(&receivedDatagram, QIODevice::ReadOnly);
				//stream >>

				QString message = QString::fromLocal8Bit(receivedDatagram);
				QByteArray byteArray = message.toLocal8Bit();
				char cstrCopy[1024];
				strcpy(cstrCopy, byteArray.data());
				if (strncmp(cstrCopy, "compress", 8) == 0)
				{
					compress_file(cstrCopy + 9);
				}
				else if (strncmp(cstrCopy, "uncompress", 10) == 0)
				{
					uncompress_file(cstrCopy + 11);
				}
			}
			else
			{
				ui->lineEdit->setText(UDPSocket->errorString());
			}

		}
	});
}

void Widget::compress_file(char buffer[1024])
{
	std::vector<fs::path> paths;
	std::string strZipPath;
	char* ptr = buffer;
	// 创建一个空的字符串来存储结果
	std::string result;
	while (*ptr != ' ')
	{
		result += *ptr; // 将字符添加到结果字符串
		++ptr; // 移动指针到下一个字符	
	}
	paths.push_back(result);
	ptr++;
	if (strncmp(ptr, "compress-zipname", 16) == 0)
	{
		char zipPath[1024] = { 0 };

		strcpy(zipPath, ptr + 17);
		strZipPath = zipPath;
	}



	memset(sbuff, '\0', sizeof(sbuff));
	if (CompressMult2Zip(paths, strZipPath))
	{
		sprintf(sbuff, "compress-ok");
		//send(sockServer, sbuff, strlen(sbuff), 0);
	}
	else
	{
		sprintf(sbuff, "compress-false");
		//send(sockServer, sbuff, strlen(sbuff), 0);
	}
	cout << "compress 执行结束" << endl;
}

void Widget::uncompress_file(char buffer[1024])
{
	std::vector<fs::path> paths;
	//std::string strZipPath;
	//char buffer[1024];
	while (1)
	{
		memset(buffer, '\0', sizeof(buffer));
		//int recvSize = recv(sockServer, buffer, sizeof(buffer), 0);
		//if (recvSize == -1)
		{
			//std::cout << "客户端已退出 ！！！！！！！！！\n";
			//return;
		}
		if (strncmp(buffer, "uncompress-paths-end", 20) == 0)
		{
			/*char zipPath[1024] = { 0 };

			strcpy(zipPath, buffer + 17);
			strZipPath = zipPath;*/
			break;
		}
		//std::string  strPath(buffer);
		paths.push_back(buffer);
	}

	for (auto& path : paths)
	{
		// 检查文件路径是否以 .zip 结尾
		if (path.extension() == ".zip")
		{
			// 返回不带 .zip 后缀的新路径
			fs::path newDir = path.parent_path() / path.stem(); // 添加父目录并返回新的目录名
			std::string strDir = newDir.string();
			std::cout << "解压 " << path << "   " << strDir << std::endl;
			extractZip(path, strDir);
		}

	}

	memset(sbuff, '\0', sizeof(sbuff));
	sprintf(sbuff, "uncompress-ok");
	//send(sockServer, sbuff, strlen(sbuff), 0);
	cout << "uncompress 执行结束" << endl;
}

void Widget::cancel_mapping()
{
	NETRESOURCE net_Resource;

	net_Resource.dwDisplayType = RESOURCEDISPLAYTYPE_DIRECTORY;
	net_Resource.dwScope = RESOURCE_CONNECTED;
	net_Resource.dwType = RESOURCETYPE_DISK;
	net_Resource.dwUsage = 0;
	net_Resource.lpComment = NULL;
	net_Resource.lpLocalName = const_cast<TCHAR*>(TEXT("Y:")); // 映射到本地驱动器
	net_Resource.lpProvider = NULL;
	net_Resource.lpRemoteName = const_cast<TCHAR*>(TEXT("\\\\192.168.10.240\\share")); // 共享资源的路径
	WNetCancelConnection2(net_Resource.lpLocalName, CONNECT_UPDATE_PROFILE, TRUE);
}
