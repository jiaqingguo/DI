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
	void compress_file(char buffer[1024]);
	//解压
	void uncompress_file(char buffer[1024]);

    void initGpu();
    double getGpuUsage();
	QList<QPair<QHostAddress, quint16>> m_serverList;

private:
    Ui::Widget *ui;

    QTimer *my_timer = nullptr;
    QUdpSocket *UDPSocket = nullptr;
    CPerformHelper *perfmon= nullptr;
    PDH_FMT_COUNTERVALUE m_SystemValue = { 0 };

	char rbuff[1024];	//接收缓冲区
	char sbuff[1024];	//发送缓冲区
private slots:
    void slot_useUdp();

};
#endif // WIDGET_H
