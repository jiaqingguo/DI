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
class GifDialog;
class CCtrlNetwork;

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

    void connectToFtpServer(const QString& strAddr, const QString& strAcc, const QString& strPwd,const int &port =21);
    void createUserDir(const QString& strDirName);
    QString toFtpCodec(const QString& strLocal);
    QString  fromFtpCodec(const QString& str);
private:
    void createDir(const QString& strDirPath);
    void uploadDirectory(const QString& localDirPath, const QString& remoteDirPath);
   // void downloadDirectory(const QUrlInfo& urlInfo, const QString& localDirPath, const QString& remoteDirPath);
    void downloadDirectory( QVector<QUrlInfo>& urlInfo, const QString& localDirPath, const QString& remoteDirPath);
    void setDisableUI();
    void setAbleUI();
public slots:
    void on_tbConnent_clicked();
    void on_tbDisconnent_clicked();

    void slot_tableWidget_doubleClicked(const QModelIndex &index);
    void slot_tableWidget_itemClicked(QTableWidgetItem *item);
    //void contextMenuEvent(QContextMenuEvent *event);
   // void con(QContextMenuEvent* event);
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

    void listInfo(QUrlInfo url);
    void commandFinished(int id, bool err);
    void slot_ftpAdminCommandFinished(int id, bool err);
    void dataTransferProgress(qint64 readBytes, qint64 totalBytes);
    void slot_stateChanged(int state);
signals:
    void signal_ableUI(bool b);
private:
    QString m_strAccount;
    QString m_strPwd;
    QString m_strAddr;
    int   m_iPort;
    QProgressBar progress;

    int editRow;
    int renameRow;
    int removeRow;
    bool createFolder;

    QString oldName;
    QString uploadPath;

    QFtp ftp;
    QFtp m_ftpAdmin;
   // QFile file;
    QString currentPath;
    QHash<QString, bool> listPath;
    QHash<QString, QString> listType;

    // 重命名;
    int m_iRenameRow = -1;
    QString m_strRename;


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


    CCtrlNetwork* m_pUdp = nullptr;
    GifDialog* m_pGifDialog = nullptr;

private:
    Ui::FtpClientWidget *ui;
};
#endif // FTPCLIENTWIDGET_H

class MyStyledItemDelegate : QStyledItemDelegate
{
    Q_OBJECT
public:
    MyStyledItemDelegate(QObject *parent = 0) : QStyledItemDelegate(parent) {}
    ~MyStyledItemDelegate() {}

private:
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
    {
        QStyleOptionViewItem viewOption(option);
//        initStyleOption(&viewOption, index);
        if (option.state.testFlag((QStyle::State_HasFocus)))
        {
            viewOption.state = viewOption.state ^ QStyle::State_HasFocus;
        }

        QStyledItemDelegate::paint(painter, viewOption, index);
    }
};
