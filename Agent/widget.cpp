#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowTitle("客户端");

    //用于获取主机的信息
    my_timer=new QTimer(this);

    connect(my_timer,&QTimer::timeout,this,&Widget::slot_useUdp);

    //QString localHostName=QHostInfo::localHostName();   //获取主机名
    //QHostInfo hostInfo=QHostInfo::fromName(localHostName);//本机的IP地址
    //QList<QHostAddress> listAdress=hostInfo.addresses();  //IP地址列表
    //        for(int i=0;i<listAdress.size();i++)
    //        {
    //            qDebug()<<listAdress.at(i).toString();  //如果主机的IP列表不为空，则使用其第一个IP地址
    //        }
    //如果主机的IP列表不为空，则显示其第8个IP地址
    //ui->textEdit->append(listAdress.at(7).toString());

    my_timer->start(100);

    //    connect(this->UDPSocket,&QUdpSocket::readyRead,[=](){
    //        while(this->UDPSocket->hasPendingDatagrams())
    //        {
    //            QByteArray receivedDatagram;
    //            receivedDatagram.resize(this->UDPSocket->pendingDatagramSize());
    //            QHostAddress serverReplyAddress;
    //            quint16 serverReplyPort;

    //            qint64 bytesReceived = this->UDPSocket->readDatagram(receivedDatagram.data(), receivedDatagram.size(),&serverReplyAddress, &serverReplyPort);
    //            ui->textEdit->append(receivedDatagram.data());
    //        }
    //    });
}

Widget::~Widget()
{
    my_timer->stop();
    delete my_timer;
    delete ui;
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
    Message_t *message=new Message_t();
    QUdpSocket *UDPSocket=new QUdpSocket();

    QString localHostName=QHostInfo::localHostName();   //获取主机名
    message->host_name=localHostName;
    message->CPU_Message=common::getCpuUsage();

    long allPhysicsMem;
    long freePhysicsMem;
    common::getPhysicsMem(allPhysicsMem, freePhysicsMem);
    message->Memory_Message=(allPhysicsMem - freePhysicsMem) * 100.0 / allPhysicsMem;

    double lFreeAll;
    double lToalAll;
    common::getAllDisSpace(lFreeAll, lToalAll);
    message->Disk_Message=(lToalAll - lFreeAll) * 100.0 / lToalAll;
    //        common::getNetworkInterfaceStatistics();
    //        common::PrintAdapterInfo();
    message->Net_Message=common::GetNetworkInterfacesThroughput();

    QByteArray dataGram;
    QDataStream stream(&dataGram,QIODevice::WriteOnly);
    stream<<message->host_name;
    stream<<message->CPU_Message;
    stream<<message->Memory_Message;
    stream<<message->Disk_Message;
    stream<<static_cast<quint32>(message->Net_Message);


    //用于获取发送者的 IP 和端口
    //    QHostAddress &IP,quint16 &Port
    //    QHostAddress IP;
    //    quint16 Port=0;
    get_file_information();
    //    qint64 bytesWritten;
    for (const auto &server : m_serverList) {
        UDPSocket->writeDatagram(dataGram,server.first,server.second);
        //const QHostAddress &ip = server.first;
        //quint16 port = server.second;
        //qDebug() << "IP:" << ip.toString() << "Port:" << port;

        //确保数据报被发送
        UDPSocket->waitForBytesWritten();
    }



}

