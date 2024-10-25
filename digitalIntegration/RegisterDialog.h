#ifndef REGISTERDIALOG_H
#define REGISTERDIALOG_H

#include <QDialog>
#include <QTimer>
#include "fingerDlg.h"


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
	void init();

	//table_user stUser;
	
private slots:
    void slot_btnRegister();
    void slot_btnFingerprintInput();
	void slot_updateLabelText();


private:
    Ui::RegisterDialog *ui;
	QTimer* timer = new QTimer(this); // 'this' 是指向当前对象的指针


};

#endif // REGISTERDIALOG_H
