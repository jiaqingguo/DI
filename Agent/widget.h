#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTimer>
#include <windows.h>
#include <QSettings>
#include <QUdpSocket>
#include <QHostInfo>
#include "gethostinformation.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

//用于UDP之间通信
typedef struct _Message
{
    QString host_name;
    double CPU_Message;
    double Memory_Message;
    double Disk_Message;
    unsigned long Net_Message;
}Message_t;

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

    void get_file_information();

private:
    Ui::Widget *ui;

//    QUdpSocket *UDPSocket;


    //获取主机信息
    QTimer *my_timer=nullptr;
    QList<QPair<QHostAddress, quint16>> m_serverList;
private slots:
    void slot_useUdp();

};
#endif // WIDGET_H
