#ifndef CHANGEPWDDIALOG_H
#define CHANGEPWDDIALOG_H

#include <QDialog>
#include <QMouseEvent>
namespace Ui {
class ChangePwdDialog;
}

class ChangePwdDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChangePwdDialog(QWidget *parent = nullptr);
    ~ChangePwdDialog();

private slots:
    void  slot_btnModify();
private:
    Ui::ChangePwdDialog *ui;
protected:
	void mousePressEvent(QMouseEvent *event) override
	{
		// 检查事件是否发生在子控件上
		if (childAt(event->pos()) != nullptr)
		{
			return; // 如果是子控件，则不处理事件
		}
		if (event->button() == Qt::LeftButton)
		{
			dragPosition = event->globalPos() - frameGeometry().topLeft();
			event->accept();
		}
	}

	void mouseMoveEvent(QMouseEvent *event) override
	{
		// 检查事件是否发生在子控件上
		if (childAt(event->pos()) != nullptr)
		{
			return; // 如果是子控件，则不处理事件
		}
		if (event->buttons() & Qt::LeftButton)
		{
			move(event->globalPos() - dragPosition);
			event->accept();
		}
	}
private:
	QPoint dragPosition;
};

#endif // CHANGEPWDDIALOG_H
