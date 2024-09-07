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
    m_model->setHeaderData(0, Qt::Horizontal, QString::fromLocal8Bit("序号"));
    m_model->setHeaderData(1, Qt::Horizontal, QString::fromLocal8Bit("ip列表"));
    m_model->setHeaderData(2, Qt::Horizontal, QString::fromLocal8Bit("占用状态"));
    //m_model->setHeaderData(3, Qt::Horizontal, QString::fromLocal8Bit("操作"));
    m_model->setHeaderData(3, Qt::Horizontal, QString::fromLocal8Bit("主机名"));
    m_model->setHeaderData(4, Qt::Horizontal, QString::fromLocal8Bit("用户名"));
    ui->tableViewIpSet->setModel(m_model);
    common::setTableViewBasicConfiguration(ui->tableViewIpSet);
    

   
    connect(ui->btnAdd, SIGNAL(clicked()), this, SLOT(slot_btnAddClicked()));


    // 2.初始化界面数据;
 
    //2.1 combox 软件数据;
   
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
            int newRowIndex = m_model->rowCount(); // 获取当前行数
            m_model->insertRow(newRowIndex); // 插入新行

            QStandardItem* item = new QStandardItem(QString::number(i));
            item->setTextAlignment(Qt::AlignCenter);   // 设置文本居中对齐
            //item->setData(QString::fromStdString(stData.name), Qt::ToolTipRole);
            m_model->setItem(newRowIndex, 0, item);

            QModelIndex index = m_model->index(newRowIndex, 0);
            m_model->setData(index, stData.id, Qt::UserRole);  // 设置id;


            item = new QStandardItem(QString::fromStdString(stData.ip));
            item->setTextAlignment(Qt::AlignCenter);  // 设置文本居中对齐
            m_model->setItem(newRowIndex, 1, item);

            item = new QStandardItem(QString::fromStdString(stData.host));
            item->setTextAlignment(Qt::AlignCenter);  // 设置文本居中对齐
            m_model->setItem(newRowIndex, 3, item);

            item = new QStandardItem(QString::fromStdString(stData.username));
            item->setTextAlignment(Qt::AlignCenter);  // 设置文本居中对齐
            m_model->setItem(newRowIndex, 4, item);


            QWidget* widget = new QWidget(); // 创建一个容器Widget来存放CheckBox
            QCheckBox* checkBox = new QCheckBox(); // 创建CheckBox
            checkBox->setProperty("row", newRowIndex); // set custom property
            //checkBox->setProperty("column", 3);

          //checkBoxList.append(checkBox); // 将checkBox添加到列表中

            QHBoxLayout* layout = new QHBoxLayout(widget); // 为容器Widget设置水平布局
            layout->addWidget(checkBox); // 将CheckBox添加到布局中
            layout->setAlignment(Qt::AlignCenter); // 设置布局中的控件居中对齐
            layout->setContentsMargins(0, 0, 0, 0); // 移除布局边距
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
                item = new QStandardItem(QString::fromLocal8Bit("未占用"));
                item->setTextAlignment(Qt::AlignCenter);  // 设置文本居中对齐
                m_model->setItem(newRowIndex, 2, item);
                connect(checkBox, &QCheckBox::clicked, this, &AddToolDialog::slot_ipCheckBoxClicked);
            }
            else 
            {
                checkBox->setChecked(true);
                checkBox->setDisabled(true);
                item = new QStandardItem(QString::fromLocal8Bit("已占用"));
                item->setTextAlignment(Qt::AlignCenter);  // 设置文本居中对齐
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

