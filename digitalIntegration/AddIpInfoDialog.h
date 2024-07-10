#ifndef ADDIPINFODIALOG_H
#define ADDIPINFODIALOG_H

#include <QDialog>

struct table_ip;

namespace Ui {
class AddIpInfoDialog;
}

class AddIpInfoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddIpInfoDialog(QWidget *parent = nullptr);
    ~AddIpInfoDialog();

    void getIpData(table_ip& stIp);
private slots:
    void slot_btnOk();
private:
    Ui::AddIpInfoDialog *ui;
};

#endif // ADDIPINFODIALOG_H
