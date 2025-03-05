#ifndef ONECLICKLOADDIALOG_H
#define ONECLICKLOADDIALOG_H

#include <QDialog>
#include <QComboBox>
#include <QMouseEvent>
class QStandardItemModel;

namespace Ui {
class OneClickLoadDialog;
}

class OneClickLoadDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OneClickLoadDialog(QWidget *parent = nullptr);
    ~OneClickLoadDialog();

	void initTableView();
	void init_ui();
    Ui::OneClickLoadDialog *ui;
private:
	QStandardItemModel* m_model = nullptr;
	QComboBox *comboBox = nullptr;
	//用于存储最后一次选择的文本
	QString text = nullptr;
private slots:
	void slot_btnAdd();
	void slot_btnDel();
	void slot_btnOK();
	void slot_keep_soft(int index);

signals:
	void one_load_tools(int module,const QString &toolsName);
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

#endif // ONECLICKLOADDIALOG_H
