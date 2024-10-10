#ifndef REGISTERDIALOG_H
#define REGISTERDIALOG_H

#include <QDialog>
#include <QTimer>


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
	void slot_updateLabelText();


private:
    Ui::RegisterDialog *ui;
	QTimer* timer = new QTimer(this); // 'this' ��ָ��ǰ�����ָ��

};

#endif // REGISTERDIALOG_H
