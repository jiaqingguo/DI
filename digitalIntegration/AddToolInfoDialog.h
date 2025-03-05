#ifndef ADDTOOLINFODIALOG_H
#define ADDTOOLINFODIALOG_H



#include <QDialog>
#include <QLineEdit>
#include <QLabel>
#include <QRadioButton>
#include <QComboBox>
#include <QMouseEvent>
struct table_ip;

namespace Ui {
class AddToolInfoDialog;
}

class AddToolInfoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddToolInfoDialog(int module,QWidget *parent = nullptr);
    ~AddToolInfoDialog();

    //void getToolsData(table_ip& toolData);
	//void getToolsData(table_ip& toolsData);
	void getToolsData(table_ip& toolsData);
	void init_ui();
	QComboBox* getipComboBox1();
	QComboBox* getipComboBox2();
	QComboBox* getipComboBox3();
	QLabel* getlabel4();
	QLabel* getlabel5();
	QLabel* getlabel6();
	QRadioButton *getAccelerateRadio();
	QRadioButton *getnodeRadio();
	QWidget *getwidget();
private slots:
    void slot_btnOk();
	void slot_btnChooseImage();
	void slot_btnhideWidget();
	void slot_btnhideWidget2();
private:
    Ui::AddToolInfoDialog *ui;
	int m_iModule = 0;
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

#endif // ADDTOOLINFODIALOG_H
