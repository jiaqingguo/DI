#ifndef ADDTOOLINFODIALOG_H
#define ADDTOOLINFODIALOG_H



#include <QDialog>
#include <QLineEdit>
#include <QLabel>
#include <QRadioButton>
#include <QComboBox>

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

	/*QLineEdit* getlineEditIP1();
	QLineEdit* getlineEditIP2();
	QLineEdit* getlineEditIP3();
	QLineEdit* getlineEditIP4();
	QLineEdit* getlineEditIP5();
	QLineEdit* getlineEditIP6();*/
	QComboBox* getipComboBox1();
	QComboBox* getipComboBox2();
	QComboBox* getipComboBox3();
	QLabel* getlabel4();
	QLabel* getlabel5();
	QLabel* getlabel6();
	QRadioButton *getAccelerateRadio();
	QRadioButton *getnodeRadio();
private slots:
    void slot_btnOk();
	void slot_btnChooseImage();
	void slot_btnhideWidget();
	void slot_btnhideWidget2();
private:
    Ui::AddToolInfoDialog *ui;
	int m_iModule = 0;

};

#endif // ADDTOOLINFODIALOG_H
