#include "widget.h"
#include "ui_widget.h"
#include <cmath>

#include <qdebug.h>
#include <QFileInfo>

#include "Win32Utils/CDeviceHelper.h"
#include "Win32Utils/CWmiQueryHelper.h"
#include "Win32Utils/CDeviceHelper.h"
#include "Win32Utils/CStrUtils.h"
#include "CPerformHelper.h"
#include "ZipFunction.h"


#pragma warning(disable : 4996) 
#include "Winsock.h"
#undef  UNICODE
#include "windows.h"
#include <iostream>
#include <string>

#include <io.h>
#include <direct.h>
#include <string>
#include <tchar.h>
#include <WinNetWk.h>
#include <stdio.h>
#include "C7Zip.h"


using namespace std;
namespace fs = std::filesystem;

Widget::Widget(QWidget *parent)
	: QWidget(parent)
	, ui(new Ui::Widget)
{
	ui->setupUi(this);
	setWindowTitle(QString::fromLocal8Bit("代理"));

	//用于获取主机的信息
	this->my_timer = new QTimer();
	this->UDPSocket = new QUdpSocket();
	message = new Message_t();

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
	this->my_timer->start(3000);

	//QString localHostName=QHostInfo::localHostName();   //获取主机名
	//QHostInfo hostInfo=QHostInfo::fromName(localHostName);//本机的IP地址
	//QList<QHostAddress> listAdress=hostInfo.addresses();  //IP地址列表
	//         for(int i = 0;i<listAdress.size();i++)
	//         {
	//       // qDebug()<<listAdress.at(i).toString();  //如果主机的IP列表不为空，则使用其第一个IP地址
			 //	qDebug() << listAdress.at(1).toString();
			 //	qDebug() << listAdress.at(2).toString();
			 //}
	 //如果主机的IP列表不为空，则显示其第8个IP地址
	 //ui->textEdit->append(listAdress.at(7).toString());


//	Widget  myWidget;
//	auto boundFunction = std::bind(&Widget::receive_mess, myWidget);
//	std::thread t(boundFunction);
//	t.detach();//分离线程，主线程不阻塞
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

void Widget::sendOrderResult(const bool& b, const QHostAddress& host, const quint16& port)
{
	if (!b)
	{
		int ret = 0;
		ret = UDPSocket->writeDatagram("false", host, port);
		if (ret == -1)
		{
			qDebug() << "wirte  false:" << UDPSocket->errorString() << "  " << UDPSocket->error();
		}
		//	cout << "删除文件夹：" << buff << "失败" << endl;

	}
	else
	{
		int ret = 0;
		ret = UDPSocket->writeDatagram("success", host, port);
		if (ret == -1)
		{
			qDebug() << "wirte  false:" << UDPSocket->errorString() << "  " << UDPSocket->error();
		}
		//	cout << "删除文件夹：" << buff << "成功" << endl;
	}
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
		message->host_ip1 = listAdress[0].toString();
		message->host_ip2 = listAdress[1].toString();
		/*message->host_ip1 = listAdress[2].toString();
		message->host_ip2 = listAdress[3].toString();*/

		//ui->textEdit->append(listAdress[2].toString());
		//ui->textEdit->append(listAdress[3].toString());
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
	for (const auto &server : m_serverList)
	{
		ret = UDPSocket->writeDatagram(dataGram, server.first, 54321);
		if (ret == -1) {
			// 发送失败
			qDebug() << "Error sending datagram:" << UDPSocket->errorString() << "  " << UDPSocket->error();

			ui->textEdit->append(UDPSocket->errorString());
		}
		else {
			// 发送成功
			//qDebug() << "Bytes sent:" << ret;
			ui->textEdit->append(QString::number(ret));
		}

		//const QHostAddress &ip = server.first;
		//quint16 port = server.second;
		//qDebug() << "IP:" << ip.toString() << "Port:" << port;

		//确保数据报被发送
		//UDPSocket->waitForBytesWritten();

	}
	//delete message;
	//message = nullptr;

	//接收
	receive_mess();
}

void Widget::receive_mess()
{
	m_pC7Zip = new C7Zip();

	connect(UDPSocket, &QUdpSocket::readyRead, [this]() {
		while (UDPSocket->hasPendingDatagrams())
		{
			QByteArray receivedDatagram;
			receivedDatagram.resize(UDPSocket->pendingDatagramSize());
			//serverReplyAddress.setAddress("192.168.0.129");
			//bool result = UDPSocket->bind(, serverReplyPort,QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint);
			/*if(!result)
			{
				qDebug() << "Failed to bind port" << UDPSocket->errorString();
			}*/

			//char *buffer = nullptr;
			qint64 bytesReceived = UDPSocket->readDatagram(receivedDatagram.data(), receivedDatagram.size(), &serverReplyAddress, &serverReplyPort);
			if (bytesReceived > 0)
			{
				QDataStream stream(&receivedDatagram, QIODevice::ReadOnly);
				Command_t command;
				stream >> command.str1;
				stream >> command.str2;
				stream >> command.str3;
				//qDebug() << "000" << receivedDatagram.size();
				//qDebug() << "111111111111111 :" << command.str1;
				//qDebug() << "22222 :" << command.str2;
				//qDebug() << "333333 :" << command.str3;
				//QString message = QString::fromLocal8Bit(receivedDatagram);
				QByteArray byteArray = command.str1.toLocal8Bit();
				char cstrCopy[1024];
				strcpy(cstrCopy, byteArray.data());
				if (strcmp(cstrCopy, "Lcompress") == 0)
				{
					QString str1 = "Y:" + command.str2;
					QString str2 = "Y:" + command.str3;
					QByteArray byte1 = str1.toLocal8Bit();
					QByteArray byte2 = str2.toLocal8Bit();
					char cstr1[1024];
					char cstr2[1024];
					strcpy(cstr1, byte1.data());
					strcpy(cstr2, byte2.data());
					compress_file(cstr1, cstr2);
				}
				else if (strcmp(cstrCopy, "Wcompress") == 0)
				{
					QString str1 = "E:/share" + command.str2;
					QString str2 = "E:/share" + command.str3;
					QByteArray byte1 = str1.toLocal8Bit();
					QByteArray byte2 = str2.toLocal8Bit();
					char cstr1[1024];
					char cstr2[1024];
					strcpy(cstr1, byte1.data());
					strcpy(cstr2, byte2.data());
					compress_file(cstr1, cstr2);

				}
				else if (strcmp(cstrCopy, "Luncompress") == 0)
				{
					QString str1 = "Y:" + command.str2;
					QString str2 = "Y:" + command.str3;
					QByteArray byte1 = str1.toLocal8Bit();
					QByteArray byte2 = str2.toLocal8Bit();
					char cstr1[1024];
					char cstr2[1024];
					strcpy(cstr1, byte1.data());
					strcpy(cstr2, byte2.data());
					//uncompress_file(cstr1,cstr2);
					/*int dotIndex = str1.lastIndexOf('.');
					if (dotIndex != -1)
					{
						QString dataPath = str1.mid(dotIndex);
						if (dataPath == ".zip" || dataPath == ".rar" || dataPath == ".7z" || dataPath == ".tar"
							|| dataPath == ".gz" || dataPath == ".bz2" || dataPath == ".xz" || dataPath == "jar"
							|| dataPath == ".war" || dataPath == "ear")
						{*/
					std::vector<fs::path> paths;
					paths.push_back(cstr1);
					int ret = 0;
					for (auto& path : paths)
					{
						// 检查文件路径是否以 .zip 结尾
						if (path.extension() == ".zip" || path.extension() == ".rar" || path.extension() == ".7z" || path.extension() == ".tar"
							|| path.extension() == ".gz" || path.extension() == ".bz2" || path.extension() == ".xz" || path.extension() == "jar"
							|| path.extension() == ".war" || path.extension() == "ear")
						{
							// 返回不带 .zip 后缀的新路径
							fs::path newDir = path.parent_path() / path.stem();
							std::string strDir = newDir.string();
							std::cout << "解压 " << path << "   " << strDir << std::endl;
							ret = m_pC7Zip->ExtractFile(QString::fromStdWString(path.wstring()), QString::fromStdString(strDir));
						}
					}
					if (ret == 0)
					{
						QString data = "success";
						QByteArray dataGram;
						QDataStream stream(&dataGram, QIODevice::WriteOnly);
						stream << data;
						int ret = 0;
						ret = UDPSocket->writeDatagram(dataGram, serverReplyAddress, 54321);
						if (ret == -1)
						{
							qDebug() << "wirte  false:" << UDPSocket->errorString() << "  " << UDPSocket->error();
						}
					}
					else
					{
						QString data = "false";
						QByteArray dataGram;
						QDataStream stream(&dataGram, QIODevice::WriteOnly);
						stream << data;
						int ret = 0;
						ret = UDPSocket->writeDatagram(dataGram, serverReplyAddress, 54321);
						if (ret == -1)
						{
							qDebug() << "wirte  false:" << UDPSocket->errorString() << "  " << UDPSocket->error();
						}
					}
				}
				else if (strcmp(cstrCopy, "Wuncompress") == 0)
				{
					QString str1 = "E:/share" + command.str2;
					QString str2 = "E:/share" + command.str3;
					QByteArray byte1 = str1.toLocal8Bit();
					QByteArray byte2 = str2.toLocal8Bit();
					char cstr1[1024];
					char cstr2[1024];
					strcpy(cstr1, byte1.data());
					strcpy(cstr2, byte2.data());
					std::vector<fs::path> paths;
					paths.push_back(cstr1);
					int ret = 0;
					for (auto& path : paths)
					{
						// 检查文件路径是否以 .zip 结尾
						if (path.extension() == ".zip" || path.extension() == ".rar" || path.extension() == ".7z" || path.extension() == ".tar"
							|| path.extension() == ".gz" || path.extension() == ".bz2" || path.extension() == ".xz" || path.extension() == "jar"
							|| path.extension() == ".war" || path.extension() == "ear")
						{
							// 返回不带 .zip 后缀的新路径
							fs::path newDir = path.parent_path() / path.stem();
							std::string strDir = newDir.string();
							std::cout << "解压 " << path << "   " << strDir << std::endl;
							ret = m_pC7Zip->ExtractFile(QString::fromStdWString(path.wstring()), QString::fromStdString(strDir));
						}
					}
					if (ret == 0)
					{
						QString data = "success";
						QByteArray dataGram;
						QDataStream stream(&dataGram, QIODevice::WriteOnly);
						stream << data;
						int ret = 0;
						ret = UDPSocket->writeDatagram(dataGram, serverReplyAddress, 54321);
						if (ret == -1)
						{
							qDebug() << "wirte  false:" << UDPSocket->errorString() << "  " << UDPSocket->error();
						}
					}
					else
					{
						QString data = "false";
						QByteArray dataGram;
						QDataStream stream(&dataGram, QIODevice::WriteOnly);
						stream << data;
						int ret = 0;
						ret = UDPSocket->writeDatagram(dataGram, serverReplyAddress, 54321);
						if (ret == -1)
						{
							qDebug() << "wirte  false:" << UDPSocket->errorString() << "  " << UDPSocket->error();
						}
					}
				}
				else if (strcmp(cstrCopy, "Ldel") == 0)
				{
					QString str1 = "Y:" + command.str2;
					QFileInfo fileInfo(str1);

					if (fileInfo.isDir())
					{
						char buff[260];
						strcpy(buff, str1.toLocal8Bit().toStdString().c_str());
						delete_listFiles(buff);
						bool flag = RemoveDirectoryA(buff); // 删除文件夹本身;
						if (!flag)
						{
							QString data = "false";
							QByteArray dataGram;
							QDataStream stream(&dataGram, QIODevice::WriteOnly);
							stream << data;
							int ret = 0;
							ret = UDPSocket->writeDatagram(dataGram, serverReplyAddress, 54321);
							if (ret == -1)
							{
								qDebug() << "wirte  false:" << UDPSocket->errorString() << "  " << UDPSocket->error();
							}
							cout << "删除文件夹：" << buff << "失败" << endl;

						}
						else
						{
							QString data = "success";
							QByteArray dataGram;
							QDataStream stream(&dataGram, QIODevice::WriteOnly);
							stream << data;
							int ret = 0;
							ret = UDPSocket->writeDatagram(dataGram, serverReplyAddress, 54321);
							if (ret == -1)
							{
								qDebug() << "wirte  false:" << UDPSocket->errorString() << "  " << UDPSocket->error();
							}
							cout << "删除文件夹：" << buff << "成功" << endl;
						}
					}
					else
					{
						char buff[260];
						strcpy(buff, str1.toStdString().c_str());
						delete_file(buff);
					}

				}
				else if (strcmp(cstrCopy, "Wdel") == 0)
				{
					QString str1 = "E:/share" + command.str2;
					//cout << "删除的文件的路径：" << str1.toStdString();
					QFileInfo fileInfo(str1);

					if (fileInfo.isDir())
					{
						char buff[260];
						strcpy(buff, str1.toLocal8Bit().toStdString().c_str());
						delete_listFiles(buff);
						bool flag = RemoveDirectoryA(buff); // 删除文件夹本身;
						if (!flag)
						{
							QString data = "false";
							QByteArray dataGram;
							QDataStream stream(&dataGram, QIODevice::WriteOnly);
							stream << data;
							int ret = 0;
							ret = UDPSocket->writeDatagram(dataGram, serverReplyAddress, 54321);
							if (ret == -1)
							{
								qDebug() << "wirte  false:" << UDPSocket->errorString() << "  " << UDPSocket->error();
							}
							cout << "删除文件夹：" << buff << "失败" << endl;

						}
						else
						{
							QString data = "success";
							QByteArray dataGram;
							QDataStream stream(&dataGram, QIODevice::WriteOnly);
							stream << data;
							int ret = 0;
							ret = UDPSocket->writeDatagram(dataGram, serverReplyAddress, 54321);
							if (ret == -1)
							{
								qDebug() << "wirte  false:" << UDPSocket->errorString() << "  " << UDPSocket->error();
							}
							cout << "删除文件夹：" << buff << "成功" << endl;
						}
					}
					else
					{
						char buff[260];
						strcpy(buff, str1.toStdString().c_str());
						delete_file(buff);
					}

				}

			}
			else
			{
				ui->lineEdit->setText(UDPSocket->errorString());
			}

		}
	});
}

void Widget::compress_file(char buffer[1024], char buffer2[1024])
{
	std::vector<fs::path> paths;
	std::string strZipPath;
	//char* ptr = buffer;
	// 创建一个空的字符串来存储结果
	//std::string result;
	//while (*ptr != ' ')
	//{
		//result += *ptr; // 将字符添加到结果字符串
		//++ptr; // 移动指针到下一个字符	
	//}
	paths.push_back(buffer);
	//ptr++;
	//if (strncmp(ptr, "compress-zipname", 16) == 0)
	{
		char zipPath[1024] = { 0 };

		strcpy(zipPath, buffer2);
		strZipPath = zipPath;
	}



	//memset(sbuff, '\0', sizeof(sbuff));
	if (CompressMult2Zip(paths, strZipPath))
	{

		cout << "compress 成功" << endl;
		QString data = "success";
		QByteArray dataGram;
		QDataStream stream(&dataGram, QIODevice::WriteOnly);
		stream << data;
		int ret = 0;
		ret = UDPSocket->writeDatagram(dataGram, serverReplyAddress, 54321);
		if (ret == -1)
		{
			std::cout << "write  false:" << UDPSocket->error();
		}
		else
		{
			cout << "write  成功";
		}
	}
	else
	{
		cout << "compress 失败" << endl;
		QString data = "false";
		QByteArray dataGram;
		QDataStream stream(&dataGram, QIODevice::WriteOnly);
		stream << data;
		int ret = 0;
		ret = UDPSocket->writeDatagram(dataGram, serverReplyAddress, 54321);
		if (ret == -1)
		{
			qDebug() << "wirte  false:" << UDPSocket->errorString() << "  " << UDPSocket->error();
		}
	}
	cout << "compress 执行结束" << endl;
}

void Widget::uncompress_file(char buffer[1024], char buffer2[1024])
{
	std::vector<fs::path> paths;
	//std::string strZipPath;
	//char buffer[1024];
	//while (buffer != '\0')
	{
		//memset(buffer, '\0', sizeof(buffer));
		//int recvSize = recv(sockServer, buffer, sizeof(buffer), 0);
		//if (recvSize == -1)
		//{
			//std::cout << "客户端已退出 ！！！！！！！！！\n";
			//return;
		//}
		//if (strcmp(buffer2, "over") == 0)
		//{
			/*char zipPath[1024] = { 0 };

			strcpy(zipPath, buffer + 17);
			strZipPath = zipPath;*/
			//break;
		//}
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

	//memset(sbuff, '\0', sizeof(sbuff));
	//sprintf(sbuff, "uncompress-ok");
	//send(sockServer, sbuff, strlen(sbuff), 0);
	cout << "uncompress 成功" << endl;
	QString data = "success";
	QByteArray dataGram;
	QDataStream stream(&dataGram, QIODevice::WriteOnly);
	stream << data;
	int ret = 0;
	ret = UDPSocket->writeDatagram(dataGram, serverReplyAddress, 54321);
	if (ret == -1)
	{
		qDebug() << "wirte  false:" << UDPSocket->errorString() << "  " << UDPSocket->error();
	}
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
	net_Resource.lpRemoteName = const_cast<TCHAR*>(TEXT("\\\\192.168.1.253\\share")); // 共享资源的路径
	WNetCancelConnection2(net_Resource.lpLocalName, CONNECT_UPDATE_PROFILE, TRUE);
}

void Widget::delete_listFiles(std::string dir)
{
	//在目录后面加上"\\*.*"进行第一次搜索
	string newDir = dir + "\\*.*";
	//用于查找的句柄
	intptr_t handle;
	struct _finddata_t fileinfo;
	//第一次查找
	handle = _findfirst(newDir.c_str(), &fileinfo);

	if (handle == -1) {
		cout << "无文件" << endl;
		//	system("pause");
		return;
	}

	do
	{
		if (fileinfo.attrib & _A_SUBDIR) {//如果为文件夹，加上文件夹路径，再次遍历
			if (strcmp(fileinfo.name, ".") == 0 || strcmp(fileinfo.name, "..") == 0)
				continue;

			// 在目录后面加上"\\"和搜索到的目录名进行下一次搜索
			newDir = dir + "\\" + fileinfo.name;
			delete_listFiles(newDir.c_str());//先遍历删除文件夹下的文件，再删除空的文件夹
			cout << newDir.c_str() << endl;
			if (_rmdir(newDir.c_str()) == 0) {//删除空文件夹
				/*QString data = "success";
				QByteArray dataGram;
				QDataStream stream(&dataGram, QIODevice::WriteOnly);
				stream << data;
				int ret = 0;
				ret = UDPSocket->writeDatagram(dataGram, serverReplyAddress, 54321);*/
				cout << "delete empty dir success" << endl;
			}
			else {
				QString data = "false";
				QByteArray dataGram;
				QDataStream stream(&dataGram, QIODevice::WriteOnly);
				stream << data;
				int ret = 0;
				ret = UDPSocket->writeDatagram(dataGram, serverReplyAddress, 54321);
				cout << "delete empty dir error" << endl;
			}
		}
		else {
			string file_path = dir + "\\" + fileinfo.name;
			cout << file_path.c_str() << endl;
			if (remove(file_path.c_str()) == 0) //删除文件
			{
				cout << "delete file success" << endl;
			}
			else
			{
				QString data = "false";
				QByteArray dataGram;
				QDataStream stream(&dataGram, QIODevice::WriteOnly);
				stream << data;
				int ret = 0;
				ret = UDPSocket->writeDatagram(dataGram, serverReplyAddress, 54321);
				cout << "delete file error" << endl;
			}
		}
	} while (!_findnext(handle, &fileinfo));

	_findclose(handle);
	return;
}
DWORD Widget::delete_file(char fileName[])
{
	if (remove(fileName) == 0)
	{
		cout << "delete 成功" << endl;
		QString data = "success";
		QByteArray dataGram;
		QDataStream stream(&dataGram, QIODevice::WriteOnly);
		stream << data;
		int ret = 0;
		ret = UDPSocket->writeDatagram(dataGram, serverReplyAddress, 54321);
		if (ret == -1)
		{
			qDebug() << "wirte  false:" << UDPSocket->errorString() << "  " << UDPSocket->error();
		}
		cout << "删除成功" << endl;
		return 1;
	}
	else
	{
		QString data = "false";
		QByteArray dataGram;
		QDataStream stream(&dataGram, QIODevice::WriteOnly);
		stream << data;
		int ret = 0;
		ret = UDPSocket->writeDatagram(dataGram, serverReplyAddress, 54321);
		if (ret == -1)
		{
			qDebug() << "wirte  false:" << UDPSocket->errorString() << "  " << UDPSocket->error();
		}
		cout << "删除失败" << endl;
		return 0;
	}
}
