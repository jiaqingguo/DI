#ifndef FTPDIALOG_H
#define FTPDIALOG_H

#include <QDialog>
#include <QMap>

class FtpClientClass;
class QFtp;
class CCtrlNetwork;
class QStandardItemModel;

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
    void flushTableViewDownload();
public slots:
    void slot_createUserDir(const QString strDirName);
private slots:
    void slot_comboBoxChanged(int index);
    void slot_ableUI(bool b);
    void slot_compress(bool bLinuxServer, QString strIp, QString order);
    void slot_unCompress(bool bLinuxServer, QString strIp, QString order);

    void slot_btnFlush();

    void slot_ItemDownloadBtnClicked();

private:
    Ui::FtpDialog *ui;

    CCtrlNetwork* m_pUDP = nullptr;
    QStandardItemModel* m_modelDownload = nullptr;
    //QMap<QString, QFtp*> m_mapAdminFtp;
};

#endif // FTPDIALOG_H
