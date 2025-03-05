#ifndef ADDTOOLDIALOG_H
#define ADDTOOLDIALOG_H

#include <QDialog>
#include <QCheckBox> 
#include <QComboBox>
#include <QMouseEvent>
class QStandardItemModel;
namespace Ui {
class AddToolDialog;
}

class AddToolDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddToolDialog(int module,QWidget *parent = nullptr);
    ~AddToolDialog();
    
    void init();
    void initToolData(const QVector<QString> vecNames);
    void getToolData(QString &tabName,QString& toolName,QString  &toolPath, int& model, int& iDisplayMode, QString& strIp, QString& strHostName);
	void init_ui();
	QComboBox* getComboBox();
private slots:

    void slot_ipCheckBoxClicked();
    void slot_btnAddClicked();
	void slot_display_lineEditIP(QString text);
private:
    Ui::AddToolDialog *ui;
    QStandardItemModel* m_model;
    int m_iModule = 0;
    int m_iDisplayMode = 0;
    int m_lastCheckBoxCol = -1;
    int m_lastCheckBoxRow = -1;

    QList<QCheckBox*> checkBoxList;
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

#endif // ADDTOOLDIALOG_H
