#include "widget.h"
#include "ui_widget.h"
#include <cmath>

#include <qdebug.h>

#include "Win32Utils/CDeviceHelper.h"
#include "Win32Utils/CWmiQueryHelper.h"
#include "Win32Utils/CDeviceHelper.h"
#include "Win32Utils/CStrUtils.h"
#include "CPerformHelper.h"


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    setWindowTitle("代理");

    //用于获取主机的信息
    this->my_timer=new QTimer();

    // 设置定时器类型为Qt::VeryCoarseTimer
    this->my_timer->setTimerType(Qt::VeryCoarseTimer);

    initGpu();
    connect(my_timer,&QTimer::timeout,this,&Widget::slot_useUdp);
    this->my_timer->start(2000);

    //QString localHostName=QHostInfo::localHostName();   //获取主机名
    //QHostInfo hostInfo=QHostInfo::fromName(localHostName);//本机的IP地址
    //QList<QHostAddress> listAdress=hostInfo.addresses();  //IP地址列表
    //        for(int i=0;i<listAdress.size();i++)
    //        {
    //            qDebug()<<listAdress.at(i).toString();  //如果主机的IP列表不为空，则使用其第一个IP地址
    //        }
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
}

void Widget::initGpu()
{

    std::vector<VIDEO_ADAPTER_DESC_INFO> vResult = CDeviceHelper::GetAllVideoAdapterDesc();

    CDeviceHelper obj;

    clock_t tmBegin = ::clock();
    DEVICE_INFO info = obj.GetDeviceInfo();
    clock_t tmEnd = ::clock();

    

     perfmon = new CPerformHelper;

    int nTimeInterval = 1000;

    perfmon->Initialize();
    perfmon->SetCollectInterval(nTimeInterval);
    perfmon->AddCounter(_T(PERFM_PATH_CPU_UTILITY));
    perfmon->AddCounter(_T(PERFM_PATH_DISK_READ_RATE));
    perfmon->AddCounter(_T(PERFM_PATH_DISK_WRITE_RATE));
    perfmon->AddCounter(_T(PERFM_PATH_CPU_PERFORMANCE));
    perfmon->AddCounter(_T(PERFM_PATH_CPU_FREQUENCY));
    perfmon->AddCounter(_T(PERFM_PATH_NETWORK_RECV_RATE));
    perfmon->AddCounter(_T(PERFM_PATH_NETWORK_SENT_RATE));
    perfmon->AddCounter(_T(PERFM_PATH_GPU_UTILITY));
    perfmon->AddCounter(_T(PERFM_PATH_GPU_MEMORY_DEDICATED_USAGE_UTILITY));
    perfmon->AddCounter(_T(PERFM_PATH_GPU_MEMORY_SHARE_USAGE_UTILITY));
    perfmon->AddCounter(_T(PERFM_PATH_GPU_MEMORY_TOTAL_COMMITTED_USAGE_UTILITY));
    perfmon->StartCollect();

   // PDH_FMT_COUNTERVALUE value = { 0 };

    SIZE_T DedicatedVideoMemory = vResult[0].AdapterDesc.DedicatedVideoMemory;
    SIZE_T DedicatedSystemMemory = vResult[0].AdapterDesc.DedicatedSystemMemory;
    SIZE_T SharedSystemMemory = vResult[0].AdapterDesc.SharedSystemMemory;

    MEMORYSTATUSEX memStatus = { 0 };
    memStatus.dwLength = sizeof(MEMORYSTATUSEX);

    double lfFrequency = 0.0f;
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
        quint16 Port = settings.value("sendPort",0).toUInt();
        QHostAddress IP;
        IP.setAddress(settings.value("sendIp","").toString());

        if (!IP.isNull() && Port != 0) {
            m_serverList.append(QPair<QHostAddress, quint16>(IP, Port));
        }
        settings.endGroup();

        //        }
    }
}

void Widget::slot_useUdp()
{

    qDebug() << "GPU 利用率: " << getGpuUsage() << "%%";

    this->UDPSocket = new QUdpSocket();
    Message_t *message = new Message_t();

    //qDebug() << "111111111111111111111111111";

    QString localHostName = QHostInfo::localHostName();   //获取主机名
    message->host_name = localHostName;
    //获取本机的IP地址
    QList<QHostAddress> addresses = QNetworkInterface::allAddresses();
    for (const QHostAddress &address : addresses) {
        // 检查是否是IPv4地址
        if (address.protocol() == QAbstractSocket::IPv4Protocol && !address.isLoopback()) {
            // 打印IPv4地址
            message->host_ip = address.toString();
        }
    }
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
	//value = common::getGpuUsage(_T(PERFM_PATH_GPU_UTILITY), PDH_FMT_DOUBLE);
    //int roundedValue = static_cast<int>(value);
   // message->Gpu_Message = value;

    QByteArray dataGram;
    QDataStream stream(&dataGram, QIODevice::WriteOnly);
    stream << message->host_name;
    stream << message->host_ip;
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
    bool result = UDPSocket->bind(QHostAddress::AnyIPv4,12345,QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint);
    if(!result)
    {
        qDebug() << "Failed to bind port" << UDPSocket->errorString();
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
    //    connect(UDPSocket,&QUdpSocket::readyRead,[=](){
    //        while(UDPSocket->hasPendingDatagrams())
    //        {
    //            QByteArray receivedDatagram;
    //            receivedDatagram.resize(UDPSocket->pendingDatagramSize());
    //            QHostAddress serverReplyAddress;
    //            quint16 serverReplyPort;

    //            qint64 bytesReceived = UDPSocket->readDatagram(receivedDatagram.data(), receivedDatagram.size(),&serverReplyAddress, &serverReplyPort);
    //            if(bytesReceived > 0 )
    //            {
    //                ui->lineEdit->setText(receivedDatagram.data());
    //            }
    //            else
    //            {
    //                ui->lineEdit->setText(UDPSocket->errorString());
    //            }
    //        }
    //    });
    delete message;
    message = nullptr;
}

