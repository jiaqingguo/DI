#ifndef DATAMANAGEDIALOG_H
#define DATAMANAGEDIALOG_H

#include <QDialog>

namespace Ui {
class DataManageDialog;
}

class CPagedTableModel;

class DataManageDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DataManageDialog(QWidget *parent = nullptr);
    ~DataManageDialog();

    void init();

   
private slots:
    void slot_ItemBtnClicked();
private:
    Ui::DataManageDialog *ui;

    CPagedTableModel* m_CPagedTableModel;
};

#endif // DATAMANAGEDIALOG_H
