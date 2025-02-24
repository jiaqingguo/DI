#ifndef INFORMATIONCONFIHURATIONDIALOG_H
#define INFORMATIONCONFIHURATIONDIALOG_H

#include <QDialog>

class QStandardItemModel;
class AddToolInfoDialog;
class AddIpInfoDialog;
class QModelIndex;

namespace Ui {
class InformationConfihurationDialog;
}

class InformationConfihurationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit InformationConfihurationDialog(QWidget *parent = nullptr);
    ~InformationConfihurationDialog();

    void init();
    void initFaceData();

    void flushToolModelData(QStandardItemModel* model,const int &module);
    void flushIpModelData(QStandardItemModel* model);
    //void flushIpModelData(QStandardItemModel* model, const int& module);
    
    void clearModelData(QStandardItemModel* model);
    void delAllModelRow(QStandardItemModel* model);

	/*QPushButton *getbtnToolAdd1();
	QPushButton *getbtnToolAdd2();
	QPushButton *getbtnToolAdd3();
	QPushButton *getbtnToolAdd4();
	QPushButton *getbtnToolDel1();
	QPushButton *getbtnToolDel2();
	QPushButton *getbtnToolDel3();
	QPushButton *getbtnToolDel4();*/

private slots:
    void slot_btnToolAdd();

    void slot_btnIpAdd();


    void slot_btnToolDel();
    void slot_btnIpDel();

	void slot_btnShowModule1();
	void slot_btnShowModule2();
	void slot_btnShowModule3();
	void slot_btnShowModule4();

signals:
    void signal_updateToolIcon(int module);
    //void slot_tooltip(QModelIndex index);
private:
    Ui::InformationConfihurationDialog *ui;
    QStandardItemModel* m_modelTool1 = nullptr;
    QStandardItemModel* m_modelTool2 = nullptr;
    QStandardItemModel* m_modelTool3 = nullptr;
    QStandardItemModel* m_modelTool4 = nullptr;
    QStandardItemModel* m_modelIP1 = nullptr;
    //QStandardItemModel* m_modelIP2 = nullptr;
    //QStandardItemModel* m_modelIP3 = nullptr;
    //QStandardItemModel* m_modelIP4 = nullptr;

    AddToolInfoDialog* m_AddToolInfoDialog = nullptr;
    AddIpInfoDialog* m_AddIpInfoDialog = nullptr;

	int module = 1;

  
};

#endif // INFORMATIONCONFIHURATIONDIALOG_H
