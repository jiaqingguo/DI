#ifndef ONECLICKLOADDIALOG_H
#define ONECLICKLOADDIALOG_H

#include <QDialog>
#include <QComboBox>

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
};

#endif // ONECLICKLOADDIALOG_H
