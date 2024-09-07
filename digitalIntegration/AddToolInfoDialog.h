#ifndef ADDTOOLINFODIALOG_H
#define ADDTOOLINFODIALOG_H



#include <QDialog>

struct table_ip;

namespace Ui {
class AddToolInfoDialog;
}

class AddToolInfoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddToolInfoDialog(QWidget *parent = nullptr);
    ~AddToolInfoDialog();

    //void getToolsData(table_ip& toolData);
	void getToolsData(table_ip& toolsData);
private slots:
    void slot_btnOk();
private:
    Ui::AddToolInfoDialog *ui;
};

#endif // ADDTOOLINFODIALOG_H
