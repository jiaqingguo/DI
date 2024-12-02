#ifndef ONECLICKLOADDIALOG_H
#define ONECLICKLOADDIALOG_H

#include <QDialog>

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
	QStandardItemModel* m_model = nullptr;
//private:
    Ui::OneClickLoadDialog *ui;
	
private slots:
	void slot_btnAdd();
	void slot_btnDel();
	void slot_btnOK();
	void slot_keep_soft(QString text);

signals:
	void one_load_tools(int module,const QString &toolsName);
};

#endif // ONECLICKLOADDIALOG_H
