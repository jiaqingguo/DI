#include <QStandardItemModel>

#include "AddToolDialog.h"
#include "ui_AddToolDialog.h"
#include "common.h"
#include "databaseDI.h"

AddToolDialog::AddToolDialog(int module, QWidget *parent) :m_iModule(module),
    QDialog(parent),
    ui(new Ui::AddToolDialog)
{
    ui->setupUi(this);
    //ui->btnAdd->setEnabled(false);
    init();

  


 
}

AddToolDialog::~AddToolDialog()
{
    delete ui;
}

void AddToolDialog::init()
{
    ui->allocationAllocation->setChecked(true);
   
    m_model = new QStandardItemModel();
    m_model->setColumnCount(5);
    m_model->setHeaderData(0, Qt::Horizontal, QString::fromLocal8Bit("���"));
    m_model->setHeaderData(1, Qt::Horizontal, QString::fromLocal8Bit("ip�б�"));
    m_model->setHeaderData(2, Qt::Horizontal, QString::fromLocal8Bit("ռ��״̬"));
    //m_model->setHeaderData(3, Qt::Horizontal, QString::fromLocal8Bit("����"));
    m_model->setHeaderData(3, Qt::Horizontal, QString::fromLocal8Bit("������"));
    m_model->setHeaderData(4, Qt::Horizontal, QString::fromLocal8Bit("�û���"));
    ui->tableViewIpSet->setModel(m_model);
    common::setTableViewBasicConfiguration(ui->tableViewIpSet);
    

   
    connect(ui->btnAdd, SIGNAL(clicked()), this, SLOT(slot_btnAddClicked()));


    // 2.��ʼ����������;
 
    //2.1 combox �������;
   
    ui->comboBoxToolNames->clear();
    std::list<table_tools> listTools;
    if (db::databaseDI::Instance().get_tools(listTools, m_iModule))
    {
        for (const auto& stTool : listTools)
        {
            ui->comboBoxToolNames->addItem(QString::fromStdString(stTool.name));
        }
    }


    common::delAllModelRow(m_model);
    std::list<table_ip> listData;
  
    //if (db::databaseDI::Instance().get_all_ip_data(listData))
    {
        int i = 1;
        for (auto& stData : listData)
        {
            int newRowIndex = m_model->rowCount(); // ��ȡ��ǰ����
            m_model->insertRow(newRowIndex); // ��������

            QStandardItem* item = new QStandardItem(QString::number(i));
            item->setTextAlignment(Qt::AlignCenter);   // �����ı����ж���
            //item->setData(QString::fromStdString(stData.name), Qt::ToolTipRole);
            m_model->setItem(newRowIndex, 0, item);

            QModelIndex index = m_model->index(newRowIndex, 0);
            m_model->setData(index, stData.id, Qt::UserRole);  // ����id;


            item = new QStandardItem(QString::fromStdString(stData.ip));
            item->setTextAlignment(Qt::AlignCenter);  // �����ı����ж���
            m_model->setItem(newRowIndex, 1, item);

            item = new QStandardItem(QString::fromStdString(stData.host));
            item->setTextAlignment(Qt::AlignCenter);  // �����ı����ж���
            m_model->setItem(newRowIndex, 3, item);

            item = new QStandardItem(QString::fromStdString(stData.username));
            item->setTextAlignment(Qt::AlignCenter);  // �����ı����ж���
            m_model->setItem(newRowIndex, 4, item);


            QWidget* widget = new QWidget(); // ����һ������Widget�����CheckBox
            QCheckBox* checkBox = new QCheckBox(); // ����CheckBox
            checkBox->setProperty("row", newRowIndex); // set custom property
            //checkBox->setProperty("column", 3);

          //checkBoxList.append(checkBox); // ��checkBox��ӵ��б���

            QHBoxLayout* layout = new QHBoxLayout(widget); // Ϊ����Widget����ˮƽ����
            layout->addWidget(checkBox); // ��CheckBox��ӵ�������
            layout->setAlignment(Qt::AlignCenter); // ���ò����еĿؼ����ж���
            layout->setContentsMargins(0, 0, 0, 0); // �Ƴ����ֱ߾�
            //ui->tableViewIpSet->setIndexWidget(m_model->index(newRowIndex, 3), widget);
   //         connect(checkBox, &QCheckBox::clicked, [=](bool checked) 
			//{
   //             if (checked) {
   //                 ui->btnAdd->setEnabled(true);
   //                 for (QCheckBox* otherCheckBox : checkBoxList) {
   //                     if (otherCheckBox != checkBox) {
   //                         //otherCheckBox->setChecked(false);
   //                         otherCheckBox->setDisabled(true);
   //                     }
   //                 }
   //                 if (!db::databaseDI::Instance().update_ip_status(stData.id, !stData.used))
   //                     return;
   //             }
   //             else {
   //                 ui->btnAdd->setEnabled(false);
   //                 for (QCheckBox* otherCheckBox : checkBoxList) {
   //                     if (otherCheckBox != checkBox) {
   //                         //otherCheckBox->setChecked(false);
   //                         otherCheckBox->setDisabled(false);
   //                     }
   //                 }
   //                 if (!db::databaseDI::Instance().update_ip_status(stData.id, stData.used))
   //                     return;
   //                 if (stData.used == 1)
   //                 {
   //                     //checkBox->setEnabled(false);
   //                     checkBox->setChecked(true);
   //                     checkBox->setDisabled(true);
   //                 }
   //             }
   //             });
            if (stData.used == 0)
            {
                item = new QStandardItem(QString::fromLocal8Bit("δռ��"));
                item->setTextAlignment(Qt::AlignCenter);  // �����ı����ж���
                m_model->setItem(newRowIndex, 2, item);
                connect(checkBox, &QCheckBox::clicked, this, &AddToolDialog::slot_ipCheckBoxClicked);
            }
            else 
            {
                checkBox->setChecked(true);
                checkBox->setDisabled(true);
                item = new QStandardItem(QString::fromLocal8Bit("��ռ��"));
                item->setTextAlignment(Qt::AlignCenter);  // �����ı����ж���
                m_model->setItem(newRowIndex, 2, item);
            }
         
            i++;
      
        }
     
    }
}

void AddToolDialog::initToolData(const QVector<QString> vecNames)
{
    ui->lineEditTabName->clear();
    ui->comboBoxToolNames->clear();
    for (const auto& name : vecNames)
    {
        ui->comboBoxToolNames->addItem(name);
    }
}

void AddToolDialog::getToolData(QString& tabName, QString& toolName, int& model, int& iDisplayMode)
{
    tabName = ui->lineEditTabName->text();
    toolName = ui->comboBoxToolNames->currentText();
    model = ui->comboBoxDisplayMode->currentIndex();
    iDisplayMode = ui->comboBoxDisplayMode->currentIndex();
}

void AddToolDialog::slot_ipCheckBoxClicked()
{
    //int CurRow=
}

void AddToolDialog::slot_btnAddClicked()
{
    this->accept();
}

