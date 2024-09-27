#ifndef FILEMANGAGEDIALOG_H
#define FILEMANGAGEDIALOG_H

#include <QDialog>
#include <QSet>

class QTreeWidgetItem;
class FtpClientClass;
class QStandardItemModel;
class GifDialog;
class QMessageBox;
class QMenu;
class QStandardItem;

namespace Ui {
class FilemangageDialog;
}

class FilemangageDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FilemangageDialog(QWidget *parent = nullptr);
    ~FilemangageDialog();

    void initTableViewDownload();
    void flushFtpDirShow();
    void flushFtpDirShow(QTreeWidgetItem* pParentItem);
    
    void flushTableViewDownload();
    void flushTableViewFtpFile();


private:
   
    bool getFtpFolderShow();

    void createTreeChildNode( QTreeWidgetItem* pParentItem,const std::string strFolder);

    int downloadFtpDir(const QString &strDirPath,const QString &newDirPath);
    void traverseUploadDir(const QString& strUploadDir,const QString& strDstDir);
    bool IsAdministratorDir(const QTreeWidgetItem* pItem);
    void getAdministratorDirs();
    void traverseAdministratorChildDir( QTreeWidgetItem* pItem);
    
signals:
    void  signal_downloadFinsh();
private slots:

    void slot_treeWidgetItemDoubleClicked(QTreeWidgetItem* item, int column);
    void slot_treeWidgetItemClicked(QTreeWidgetItem* item, int column);
    //  viewItem ���ذ�ť;
    void slot_itemBtnDownload();
    //  viewItem ɾ����ť;
    void slot_itemBtnDel();

    // �ϴ��ļ���ť;
    void slot_btnUploading();
    // �ϴ��ļ��а�ť;
    void slot_btnUploadingDir();
    // ���Ҽ��˵�;
    void slot_treeWidgteCustomContextMenuRequested(const QPoint& pos);
    //  ����ҳ��  viewItem ���ذ�ť;
    void slot_ItemDownloadBtnClicked();
    void slot_actionMkdir();
    void slot_actionDelDir();
    void slot_actionDownload();
    void slot_actioxnRename();
    void slot_actionCompressDir();
    void slot_actionCopyPath();

    void slot_tableViewFilesItemChanged(QStandardItem* item);

    void slot_btnCompress();   // ѹ��
    void slot_btnUnCompress(); // ��ѹ��

    void slot_btnCopyPath();  // ����·��

public slots:
    void slot_compressMultPath(std::vector<std::string> vecStrPath, std::string strZipPath);
private:
    Ui::FilemangageDialog *ui;

    FtpClientClass* m_FtpClientClass = nullptr;
    QStandardItemModel *m_modelFiles = nullptr;

    GifDialog *m_GifDialog = nullptr;

    QMessageBox *m_msgBox = nullptr;
    QStandardItemModel* m_modelDownload = nullptr;

    QString m_strDolwnloadText = QString::fromLocal8Bit("��������");

    QTreeWidgetItem* m_pRootItem = nullptr;

    QString m_AdministratorDir = "D:\\FileData\\vip";

    //QVector<QString> m_vecAdministratorDir;
    QSet<QString> m_vecAdministratorDir;
    QMenu  *m_pMenu = nullptr;
    QAction * m_actionMkdir = nullptr;
    QAction * m_actionDel = nullptr;
    QAction * m_actionDownload= nullptr;
    QAction * m_actionRename = nullptr;
    QAction* m_actionCompressDir = nullptr;
    QAction* m_actionCopyPath = nullptr;
};

#endif // FILEMANGAGEDIALOG_H
