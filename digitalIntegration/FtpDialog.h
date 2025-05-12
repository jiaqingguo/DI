#ifndef FTPDIALOG_H
#define FTPDIALOG_H

#include <QDialog>
#include <QMap>

class FtpClientClass;
class QFtp;
class CCtrlNetwork;
class QStandardItemModel;
class GifDialog;
struct st_udp;

namespace Ui {
class FtpDialog;
}

class FtpDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FtpDialog(QWidget *parent = nullptr);
    ~FtpDialog();

    void initConnectFtp();
    void reConnectFtp();
    void flushTableViewDownload();

    // 序列化函数
    QByteArray serializeFtpUdpData(const st_udp& data);
public slots:
    void slot_createUserDir(const QString strDirName);
    void slot_orderFinsh(int iFlag);


    void slot_signalFtpDownlaod(const QString strPath, const QString strFtpIP);
private slots:
    void slot_comboBoxChanged(int index);
    void slot_ableUI(bool b, QString str);
    void slot_compress(bool bLinuxServer, QString strIp, QString strArg1,QString strArg2);
    void slot_unCompress(bool bLinuxServer, QString strIp, QString order);
    void slot_del(bool bLinuxServer, QString strIp, QString order);

   
    void slot_btnFlush();
    void slot_btnFile();
    void slot_btnDowload();

    void slot_ItemDownloadBtnClicked();
	void slot_ItemDeleteBtnClicked();
    void slot_tableViewDownloadContextMenu(const QPoint& pos);

private:
    Ui::FtpDialog *ui;

    CCtrlNetwork* m_pUDP = nullptr;
    QStandardItemModel* m_modelDownload = nullptr;
    //QMap<QString, QFtp*> m_mapAdminFtp;
    GifDialog* m_pGifDialog = nullptr;
};

#endif // FTPDIALOG_H
