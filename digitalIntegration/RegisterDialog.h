#ifndef REGISTERDIALOG_H
#define REGISTERDIALOG_H

#include <QDialog>
#include <QTimer>
#include <QMouseEvent>
//#include "fingerDlg.h"


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

	void init_ui();

	//table_user stUser;
	
private slots:
    void slot_btnRegister();
    //void slot_btnFingerprintInput();
	//void slot_updateLabelText();


private:
    Ui::RegisterDialog *ui;
	//QTimer* timer = new QTimer(this); // 'this' 是指向当前对象的指针

//protected:
//	void mousePressEvent(QMouseEvent *event) override
//	{
//		// 检查事件是否发生在子控件上
//		if (childAt(event->pos()) != nullptr)
//		{
//			return; // 如果是子控件，则不处理事件
//		}
//		if (event->button() == Qt::LeftButton)
//		{
//			dragPosition = event->globalPos() - frameGeometry().topLeft();
//			event->accept();
//		}
//	}
//
//	void mouseMoveEvent(QMouseEvent *event) override
//	{
//		// 检查事件是否发生在子控件上
//		if (childAt(event->pos()) != nullptr)
//		{
//			return; // 如果是子控件，则不处理事件
//		}
//		if (event->buttons() & Qt::LeftButton)
//		{
//			move(event->globalPos() - dragPosition);
//			event->accept();
//		}
//	}
//private:
//	QPoint dragPosition;
};

#endif // REGISTERDIALOG_H
