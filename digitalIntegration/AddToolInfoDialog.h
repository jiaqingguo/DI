#ifndef ADDTOOLINFODIALOG_H
#define ADDTOOLINFODIALOG_H



#include <QDialog>
#include <QLineEdit>
#include <QLabel>

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
	void getToolsData(table_ip& toolsData, std::string ipdata[6]);

	QLineEdit* getlineEditIP1();
	QLineEdit* getlineEditIP2();
	QLineEdit* getlineEditIP3();
	QLineEdit* getlineEditIP4();
	QLineEdit* getlineEditIP5();
	QLineEdit* getlineEditIP6();
	QLabel* getlabelIP1();
	QLabel* getlabelIP2();
	QLabel* getlabelIP3();
	QLabel* getlabelIP4();
	QLabel* getlabelIP5();
	QLabel* getlabelIP6();
private slots:
    void slot_btnOk();
private:
    Ui::AddToolInfoDialog *ui;
	int m_iModule = 0;

};

#endif // ADDTOOLINFODIALOG_H
