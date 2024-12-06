#ifndef FTPDIALOG_H
#define FTPDIALOG_H

#include <QDialog>

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
private slots:
    void slot_comboBoxChanged(int index);
private:
    Ui::FtpDialog *ui;
};

#endif // FTPDIALOG_H
