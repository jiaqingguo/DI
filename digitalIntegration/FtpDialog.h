#ifndef FTPDIALOG_H
#define FTPDIALOG_H

#include <QDialog>

class FtpClientClass;
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
    void slot_ableUI(bool b);
private:
    Ui::FtpDialog *ui;
   
};

#endif // FTPDIALOG_H
