#ifndef RESOURCEMANAGEDIALOG_H
#define RESOURCEMANAGEDIALOG_H

#include <QDialog>
#include <QJsonObject>
#include <QMap>
#include <QUdpSocket>
#include <QHostAddress>
class QStandardItemModel;
class QWebEngineView;
class QJsonObject;
class QStandardItem;

//用于UDP之间通信
typedef struct _Message
{
    QString host_name = 0;
    QString host_ip1 = 0;
	QString host_ip2 = 0;
    double Cpu_Message = 0;
    double Memory_Message = 0;
    double Disk_Message = 0;
    unsigned long Net_Message = 0;
	double Gpu_Message = 0;
}Message_t;
//接收解压缩命令
typedef struct _Com
{
	QString str1;
	QString str2;
	QString str3;
}Command_t;

namespace Ui {
class ResourceManageDialog;
}

class ResourceManageDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ResourceManageDialog(QWidget *parent = nullptr);
    ~ResourceManageDialog();
    void initTableWidgetCurve();

    void initWebViewNet(QWidget *widget);
    void initWebViewCpu(QWidget* widget);
    void initWebViewMemory(QWidget* widget);
    void initWebViewDisk(QWidget* widget);
	void initWebViewGpu(QWidget* widget);

    void startWebFlushTimer();
    void stopWebFlushTimer();
    QWidget* createCustomTab(const QString& tabName);

    void addHostCpuElemnet(const QString &host,const double &value);
    void addHostNetElemnet(const QString& host, const unsigned long& value);
    void addHostMemoryElemnet(const QString& host, const double& value);
    void addHostDiskElemnet(const QString& host, const double& value);
	void addHostGpuElemnet(const QString& host, const double& value);

    void updateHostTableShow(const QString& host, const double& dCpu, const double& dMemory, const double& dDisk, const double& dNet, const double& dGpu);

    void updateCpuWebViewShow(const QString & host);
    void updateMemoryWebViewShow(const QString& host);
    void updateDiskWebViewShow(const QString& host);
    void updateNetWebViewShow(const QString& host);
	void updateGpuWebViewShow(const QString& host);
    void getUdpData();
signals:
    void signal_udpOrderFinsh(int flag);
private slots:
    void slot_modelItemChanged(QStandardItem* item);
    void slot_hostComboxChanged(const QString &text);

    void slot_timerTimeout();

    void slot_get_data(int index);

	void slot_showList();
	void slot_showCurve();
private:
    Ui::ResourceManageDialog *ui;

    QStandardItemModel* m_model = nullptr;

    QWebEngineView* m_webEngineViewCpu = nullptr;
    QWebEngineView* m_webEngineViewNet = nullptr;
    QWebEngineView* m_webEngineViewMemory = nullptr;
    QWebEngineView* m_webEngineViewDisk = nullptr;
	QWebEngineView* m_webEngineViewGpu = nullptr;
    QJsonObject m_jsonDataNet;
    QJsonObject m_jsonDataCpu;
    QJsonObject m_jsonDataMemory;
    QJsonObject m_jsonDataDisk;
	QJsonObject m_jsonDataGpu;

    int m_vectorMaxSize = 60;
    QMap<QString, QVector<double>> m_mapCpuData;
    QMap<QString, QVector<double>> m_mapNetData;
    QMap<QString, QVector<double>> m_mapMemoryData;
    QMap<QString, QVector<double>> m_mapDiskData;
	QMap<QString, QVector<double>> m_mapGpuData;

    bool CPU_init = true;
    bool memory_init = false;
    bool disk_init = false;
    bool net_init = false;
	bool Gpu_init = false;

    QTimer* m_timer = nullptr;
    QUdpSocket* UdpSocket = nullptr;
    //QThread* thread = nullptr;
	std::map<QString, Message_t> myMap;
    Message_t message;
	//通信的ip和端口，用于获取发送者的 IP 和端口
	QHostAddress addr;
	quint16 port;

};

#endif // RESOURCEMANAGEDIALOG_H
