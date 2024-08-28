#ifndef REGISTERDIALOG_H
#define REGISTERDIALOG_H

#include <QDialog>


namespace Ui {
class RegisterDialog;
}

class fingerDlg;

class RegisterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RegisterDialog(QWidget *parent = nullptr);
    ~RegisterDialog();
private slots:
    void slot_btnRegister();
    void slot_btnFingerprintInput();


private:
    Ui::RegisterDialog *ui;
};

#endif // REGISTERDIALOG_H
