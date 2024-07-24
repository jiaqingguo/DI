#ifndef ADDTOOLDIALOG_H
#define ADDTOOLDIALOG_H

#include <QDialog>
#include <QCheckBox> 

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
    void getToolData(QString &tabName,QString& toolName, int& model, int& iDisplayMode);
private slots:

    void slot_ipCheckBoxClicked();
    void slot_btnAddClicked();
private:
    Ui::AddToolDialog *ui;
    QStandardItemModel* m_model;
    int m_iModule = 0;
    int m_iDisplayMode = 0;
    int m_lastCheckBoxCol = -1;
    int m_lastCheckBoxRow = -1;

    QList<QCheckBox*> checkBoxList;

};

#endif // ADDTOOLDIALOG_H
