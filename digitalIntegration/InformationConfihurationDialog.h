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
    void flushIpModelData(QStandardItemModel* model, const int& module);
    
    void clearModelData(QStandardItemModel* model);
    void delAllModelRow(QStandardItemModel* model);
private slots:
    void slot_btnToolAdd();

    void slot_btnIpAdd();


    void  slot_btnToolDel();
    void  slot_btnIpDel();
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
    QStandardItemModel* m_modelIP2 = nullptr;
    QStandardItemModel* m_modelIP3 = nullptr;
    QStandardItemModel* m_modelIP4 = nullptr;

    AddToolInfoDialog* m_AddToolInfoDialog = nullptr;
    AddIpInfoDialog* m_AddIpInfoDialog = nullptr;

  
};

#endif // INFORMATIONCONFIHURATIONDIALOG_H
