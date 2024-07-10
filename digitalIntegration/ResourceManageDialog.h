#ifndef RESOURCEMANAGEDIALOG_H
#define RESOURCEMANAGEDIALOG_H

#include <QDialog>
#include <QJsonObject>
#include <QMap>
class QStandardItemModel;
class QWebEngineView;
class QJsonObject;
class QStandardItem;



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
    QWidget* createCustomTab(const QString& tabName);

    void addHostCpuElemnet(const QString &host,const double &value);
    void addHostNetElemnet(const QString& host, const unsigned long& value);
    void addHostMemoryElemnet(const QString& host, const double& value);
    void addHostDiskElemnet(const QString& host, const double& value);

    void updateHostTableShow(const QString& host, const double& dCpu, const double& dMemory, const double& dDisk, const double& dNet);

    void updateCpuWebViewShow(const QString & host);
    void updateMemoryWebViewShow(const QString& host);
    void updateDiskWebViewShow(const QString& host);
    void updateNetWebViewShow(const QString& host);
private slots:
    void slot_modelItemChanged(QStandardItem* item);
    void slot_hostComboxChanged(const QString& text);

    void slot_timerTimeout();
private:
    Ui::ResourceManageDialog *ui;

    QStandardItemModel* m_model = nullptr;

    QWebEngineView* m_webEngineViewCpu = nullptr;
    QWebEngineView* m_webEngineViewNet = nullptr;
    QWebEngineView* m_webEngineViewMemory = nullptr;
    QWebEngineView* m_webEngineViewDisk = nullptr;
    QJsonObject m_jsonDataNet;
    QJsonObject m_jsonDataCpu;
    QJsonObject m_jsonDataMemory;
    QJsonObject m_jsonDataDisk;

    int m_vectorMaxSize = 60;
    QMap<QString, QVector<double>> m_mapCpuData;
    QMap<QString, QVector<double>> m_mapNetData;
    QMap<QString, QVector<double>> m_mapMemoryData;
    QMap<QString, QVector<double>> m_mapDiskData;

};

#endif // RESOURCEMANAGEDIALOG_H
