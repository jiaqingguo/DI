#ifndef FILEMANGAGEDIALOG_H
#define FILEMANGAGEDIALOG_H

#include <QDialog>

class QTreeWidgetItem;
class FtpClientClass;
class QStandardItemModel;

namespace Ui {
class FilemangageDialog;
}

class FilemangageDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FilemangageDialog(QWidget *parent = nullptr);
    ~FilemangageDialog();
private:
    bool getFtpFolderShow();

    void createTreeChildNode( QTreeWidgetItem* pParentItem,const std::string strFolder);

private slots:

    void slot_treeWidgetItemDoubleClicked(QTreeWidgetItem* item, int column);
    void slot_treeWidgetItemClicked(QTreeWidgetItem* item, int column);
    void slot_itemBtnDownload();
    void slot_itemBtnDel();

    void slot_btnUploading();

    // Ê÷ÓÒ¼ü²Ëµ¥;
    void slot_treeWidgteCustomContextMenuRequested(const QPoint& pos);
private:
    Ui::FilemangageDialog *ui;

    FtpClientClass* m_FtpClientClass = nullptr;
    QStandardItemModel *m_modelFiles = nullptr;
};

#endif // FILEMANGAGEDIALOG_H
