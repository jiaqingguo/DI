#ifndef ONECLICKSAVEDIALOG_H
#define ONECLICKSAVEDIALOG_H

#include <QDialog>

class QStandardItemModel;

namespace Ui {
class OneClickSaveDialog;
}

class OneClickSaveDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OneClickSaveDialog(QWidget *parent = nullptr);
    ~OneClickSaveDialog();


private slots:

    void slot_btnAdd();

    void slot_btnDel();
    void slot_btnPaste();

    void slot_itmeBtnCopy();
    void slot_btnOK();
signals:
    void signals_zipMultPath(std::vector<std::string> vecStrPath, std::string strZipPath);
private:
    Ui::OneClickSaveDialog *ui;
    QStandardItemModel* m_model = nullptr;
};

#endif // ONECLICKSAVEDIALOG_H
