#ifndef FILEMANGAGEDIALOG_H
#define FILEMANGAGEDIALOG_H

#include <QDialog>

class QTreeWidgetItem;
class FtpClientClass;
class QStandardItemModel;
class GifDialog;
class QMessageBox;

namespace Ui {
class FilemangageDialog;
}

class FilemangageDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FilemangageDialog(QWidget *parent = nullptr);
    ~FilemangageDialog();


    void flushFtpDirShow();

    void initTableViewDownload();
    void flushTableViewDownload();
private:
   
    bool getFtpFolderShow();


    void createTreeChildNode( QTreeWidgetItem* pParentItem,const std::string strFolder);

    int downloadFtpDir(const QString &strDirPath,const QString &newDirPath);
    void traverseUploadDir(const QString& strUploadDir,const QString& strDstDir);
    bool IsAdministratorDir(const QTreeWidgetItem* pItem);
signals:
    void  signal_downloadFinsh();
private slots:

    void slot_treeWidgetItemDoubleClicked(QTreeWidgetItem* item, int column);
    void slot_treeWidgetItemClicked(QTreeWidgetItem* item, int column);
    void slot_itemBtnDownload();
    void slot_itemBtnDel();

    void slot_btnUploading();
    void slot_btnUploadingDir();

    // Ê÷ÓÒ¼ü²Ëµ¥;
    void slot_treeWidgteCustomContextMenuRequested(const QPoint& pos);

    void slot_ItemDownloadBtnClicked();
private:
    Ui::FilemangageDialog *ui;

    FtpClientClass* m_FtpClientClass = nullptr;
    QStandardItemModel *m_modelFiles = nullptr;

    GifDialog *m_GifDialog = nullptr;

    QMessageBox *m_msgBox = nullptr;
    QStandardItemModel* m_modelDownload = nullptr;

    QString m_strDolwnloadText = QString::fromLocal8Bit("ÉêÇëÏÂÔØ");

    QTreeWidgetItem* m_pRootItem = nullptr;

    QString m_AdministratorDir = "vip";
};

#endif // FILEMANGAGEDIALOG_H
