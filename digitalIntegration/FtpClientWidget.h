#ifndef FTPCLIENTWIDGET_H
#define FTPCLIENTWIDGET_H

#include <QWidget>
#include <QFile>
#include <QLabel>
#include <QMainWindow>
#include <QProgressBar>
#include <QStyledItemDelegate>
#include <QVector>


#include "qftp.h"

class QLabel;
class QTableWidgetItem;
class QUrlInfo;

class CCtrlNetwork;
class QMenu;

QT_BEGIN_NAMESPACE
namespace Ui { class FtpClientWidget; }
QT_END_NAMESPACE

class FtpClientWidget : public QWidget
{
    Q_OBJECT

public:
    FtpClientWidget(QWidget *parent = nullptr);
    ~FtpClientWidget();
public:
//    explicit MainWnd(QWidget *parent = 0);
//    ~MainWnd();

    void initVar();
    void saveToIni();
    void loadFmIni();
    void clear();
    QString createFolderName();

    void connectToFtpServer(const QString& strHostName, const QString& strAddr, const QString& strAcc, const QString& strPwd, const int& port = 21); 

    void Flush();
    void reconnectFtp();
    void createUserDir(const QString& strDirName);
    void setIsLinuxFtpServer(const bool &b);
    QString toFtpCodec(const QString& strLocal);
    QString  fromFtpCodec(const QString& str);


    void ApprovalDownload(const QString &strName,const QString& strPath ,const bool &bDir);
    void ConnectSlot();
    void DisConnectSlot();
private:
    void createDir(const QString& strDirPath);
    void uploadDirectory(const QString& localDirPath, const QString& remoteDirPath);
   // void downloadDirectory(const QUrlInfo& urlInfo, const QString& localDirPath, const QString& remoteDirPath);
    void downloadDirectory( QVector<QUrlInfo>& urlInfo, const QString& localDirPath, const QString& remoteDirPath);
    void setDisableUI(const QString& str);
    void setAbleUI();
    void downloadFile(const QString& name,const QString& strFtpPath);
    void downloadDir(const QString& name, const QString& strFtpPath);
public slots:
    void on_tbConnent_clicked();
    void on_tbDisconnent_clicked();

    void slot_tableWidget_doubleClicked(const QModelIndex &index);
    void slot_tableWidget_itemClicked(QTableWidgetItem *item);

    void slot_customContextMenuRequested(const QPoint& pos);
    void onUpload();
    void slot_UploadDir();
    
    void onDownload();
    void slot_downloadDirectory();
    void onCreateFolder();
    void slot_newDir();
    void onRename();
    void slot_rename();
    void onRemove();
    void onRefresh();
    void onInsertRow();
    void closePersistentEditor();

    void slot_actionCompress(); // 压缩
    void slot_actionUnCompress(); // 解压

    void listInfo(QUrlInfo url);
    void commandFinished(int id, bool err);
    void slot_ftpAdminCommandFinished(int id, bool err);
    void dataTransferProgress(qint64 readBytes, qint64 totalBytes);
    void slot_stateChanged(int state);
signals:
    void signal_ableUI(bool b,QString strMsg);
    void signal_compress(bool bLinuxServer, QString strIp, QString strArg1, QString strArg2);
    void signal_unCompress(bool bLinuxServer, QString strIp, QString strArg1);
    void signal_del(bool bLinuxServer, QString strIp, QString strArg1);
private:
    bool m_bLinuxFtpServer = false;
    QString m_strHostName;
    QString m_strAccount;
    QString m_strPwd;
    QString m_strAddr;
    int   m_iPort;
    QProgressBar progress;

   
    int renameRow;
    int removeRow;
    bool createFolder;

    int editRow;
    QString oldName;
    QString uploadPath;

    QFtp * m_pFtp = nullptr;
    QFtp* m_pFtpAdmin = nullptr;;
   // QFile file;
    QString currentPath;
    QHash<QString, bool> listPath;
    QHash<QString, QString> listType;

    // 重命名;
    int m_iRenameRow = -1;
    QString m_strRename;
    int m_curEditRow = -1;;
    QString m_oldName;

    //上传文件
    int m_iPutFileCommandID = -1;

    //下载文件
    int m_iGetFileCommandID = -1;
   

    //  上传目录相关数据;
    QMap<int, QFile*>  m_mapFileUpload;
    bool m_bUploadDir = false;
    int m_iUploadDirCommandTotal = 0;

    //  下载目录相关数据;
    bool m_bDownloadDir = false;
  //  QString m_loaclDownloadDirPath;
   // QString m_remoteDownloadDirPath;
    int m_downloadDirCommandID = -1;

    QVector<QUrlInfo>  m_vecListInfo;
    QMap<int,QString>  m_mapLoaclDownloadDirPath;
    QMap<int, QString>  m_mapRemoteDownloadDirPath;
    QMap<int, QFile*>  m_mapFileDownload;
    int m_iDoloadDirCommandTotal = 0;

    QString m_strDolwnloadText = "申请下载";
    CCtrlNetwork* m_pUdp = nullptr;
   // GifDialog* m_pGifDialog = nullptr;
    QMenu   * m_pMenu = nullptr;
    QAction* m_actionPutFile = nullptr;
    QAction* m_actionGetFile = nullptr;
    QAction* m_actionPutDir = nullptr;
    QAction* m_actionGetDir = nullptr;
    QAction* m_actionMkdir = nullptr;
    QAction* m_actionDel = nullptr;
    QAction* m_actionDownload = nullptr;
    QAction* m_actionRename = nullptr;
    QAction* m_actionCompress = nullptr;
    QAction* m_actionUnCompress = nullptr;
    QAction* m_actionCopyPath = nullptr;
    QAction* m_actionFlush = nullptr;
private:
    Ui::FtpClientWidget *ui;
};
#endif // FTPCLIENTWIDGET_H

//class MyStyledItemDelegate : QStyledItemDelegate
//{
//    Q_OBJECT
//public:
//    MyStyledItemDelegate(QObject *parent = 0) : QStyledItemDelegate(parent) {}
//    ~MyStyledItemDelegate() {}
//
//private:
//    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
//    {
//        QStyleOptionViewItem viewOption(option);
////        initStyleOption(&viewOption, index);
//        if (option.state.testFlag((QStyle::State_HasFocus)))
//        {
//            viewOption.state = viewOption.state ^ QStyle::State_HasFocus;
//        }
//
//        QStyledItemDelegate::paint(painter, viewOption, index);
//    }
//};
