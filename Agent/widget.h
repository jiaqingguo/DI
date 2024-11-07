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

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

//用于UDP之间通信
typedef struct _Message
{
    QString host_name;
    QString host_ip;
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
    //获取主机信息
    void get_file_information();


	QList<QPair<QHostAddress, quint16>> m_serverList;

private:
    Ui::Widget *ui;

    QTimer *my_timer = nullptr;
    QUdpSocket *UDPSocket = nullptr;
  
private slots:
    void slot_useUdp();

};
#endif // WIDGET_H
