#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTimer>
#include <windows.h>
#include <QSettings>
#include <QUdpSocket>
#include <QHostInfo>
#include <QNetworkInterface>
#include <QLineEdit>
#include <tchar.h>
#include "gethostinformation.h"

class CPerformHelper;

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE


//发送刀片机信息
typedef struct _Message
{
    QString host_name;
    QString host_ip1;
	QString host_ip2;
    double CPU_Message;
    double Memory_Message;
    double Disk_Message;
    unsigned long Net_Message;
    double Gpu_Message;
}Message_t;

//接收解压缩命令
typedef struct _Com
{
	QString str1;//Lcompress\Wcompress\Luncompress\Wuncompress
	QString str2;//要压缩的文件的路径\解压时的压缩包的路径
	QString str3;//压缩包的路径
}Command_t;

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();
	//取消映射
	void cancel_mapping();
    //获取主机信息
    void get_file_information();
	//接收消息
	void receive_mess();
	//压缩
	void compress_file(char buffer[1024],char buffer2[1024]);
	//解压
	void uncompress_file(char buffer[1024], char buffer2[1024]);
	void delete_listFiles(std::string dir);
	DWORD delete_file(char fileName[]);
    void initGpu();
    double getGpuUsage();

    // 发送指令结果;
    void sendOrderResult(const bool &b, const QHostAddress& host,const quint16 & port);
	QList<QPair<QHostAddress, quint16>> m_serverList;

private:
    Ui::Widget *ui;

    QTimer *my_timer = nullptr;
    QUdpSocket *UDPSocket = nullptr;
	Message_t *message = nullptr;
    CPerformHelper *perfmon= nullptr;
    PDH_FMT_COUNTERVALUE m_SystemValue = { 0 };
	QHostAddress serverReplyAddress;
	quint16 serverReplyPort;

	char rbuff[1024];	//接收缓冲区
	char sbuff[1024];	//发送缓冲区
private slots:
    void slot_useUdp();

};
#endif // WIDGET_H
