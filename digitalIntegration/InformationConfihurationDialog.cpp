#include "InformationConfihurationDialog.h"
#include "ui_InformationConfihurationDialog.h"
#include "databaseDI.h"
//#include "globel.h"
#include "AddToolInfoDialog.h"
#include "AddIpInfoDialog.h"
#include "common.h"

#include <QStandardItemModel>
#include <QToolTip>
#include <QModelIndex>
#include <QDebug>


InformationConfihurationDialog::InformationConfihurationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InformationConfihurationDialog)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/image/InformationConfihuration.png"));
    init();
    initFaceData();
  
}

InformationConfihurationDialog::~InformationConfihurationDialog()
{
    delete ui;
}

void InformationConfihurationDialog::init()
{

    m_AddToolInfoDialog = new AddToolInfoDialog(this);
    m_AddIpInfoDialog = new AddIpInfoDialog(this);

    m_modelTool1 = new QStandardItemModel();
    m_modelTool1->setColumnCount(4);
    m_modelTool1->setHeaderData(0, Qt::Horizontal, QString::fromLocal8Bit("主机"));
    m_modelTool1->setHeaderData(1, Qt::Horizontal, QString::fromLocal8Bit("工具名称"));
    m_modelTool1->setHeaderData(2, Qt::Horizontal, QString::fromLocal8Bit("工具路径"));
    m_modelTool1->setHeaderData(3, Qt::Horizontal, QString::fromLocal8Bit("工具图标"));
    ui->tableViewTool1->setModel(m_modelTool1);
    common::setTableViewBasicConfiguration(ui->tableViewTool1);

    //m_modelTool1->appendRow(QList<QStandardItem*>()
    //    << new QStandardItem("computer1")
    //    << new QStandardItem("VS")
    //    << new QStandardItem("D:\1_project\jqg\demo\qt\digitalIntegration")
    //    << new QStandardItem("D:\1_project\jqg\demo\qt\digitalIntegration"));
    //m_modelTool1->appendRow(QList<QStandardItem*>()
    //    << new QStandardItem("computer2")
    //    << new QStandardItem("PS")
    //    << new QStandardItem("D:\1_project\jqg\demo\qt\digitalIntegration")
    //    << new QStandardItem("D:\1_project\jqg\demo\qt\digitalIntegration"));
    //  
    //m_modelTool1->appendRow(QList<QStandardItem*>()
    //    << new QStandardItem("computer3")
    //    << new QStandardItem("XD")
    //    << new QStandardItem("D:\1_project\jqg\demo\qt\digitalIntegration")
    //    << new QStandardItem("D:\1_project\jqg\demo\qt\digitalIntegration"));


    m_modelTool2 = new QStandardItemModel();
    m_modelTool2->setColumnCount(4);
    m_modelTool2->setHeaderData(0, Qt::Horizontal, QString::fromLocal8Bit("主机"));
    m_modelTool2->setHeaderData(1, Qt::Horizontal, QString::fromLocal8Bit("工具名称"));
    m_modelTool2->setHeaderData(2, Qt::Horizontal, QString::fromLocal8Bit("工具路径"));
    m_modelTool2->setHeaderData(3, Qt::Horizontal, QString::fromLocal8Bit("工具图标"));
    ui->tableViewTool2->setModel(m_modelTool2);
    common::setTableViewBasicConfiguration(ui->tableViewTool2);

    m_modelTool3 = new QStandardItemModel();
    m_modelTool3->setColumnCount(4);
    m_modelTool3->setHeaderData(0, Qt::Horizontal, QString::fromLocal8Bit("主机"));
    m_modelTool3->setHeaderData(1, Qt::Horizontal, QString::fromLocal8Bit("工具名称"));
    m_modelTool3->setHeaderData(2, Qt::Horizontal, QString::fromLocal8Bit("工具路径"));
    m_modelTool3->setHeaderData(3, Qt::Horizontal, QString::fromLocal8Bit("工具图标"));
    ui->tableViewTool3->setModel(m_modelTool3);
    common::setTableViewBasicConfiguration(ui->tableViewTool3);

    m_modelTool4 = new QStandardItemModel();
    m_modelTool4->setColumnCount(4);
    m_modelTool4->setHeaderData(0, Qt::Horizontal, QString::fromLocal8Bit("主机"));
    m_modelTool4->setHeaderData(1, Qt::Horizontal, QString::fromLocal8Bit("工具名称"));
    m_modelTool4->setHeaderData(2, Qt::Horizontal, QString::fromLocal8Bit("工具路径"));
    m_modelTool4->setHeaderData(3, Qt::Horizontal, QString::fromLocal8Bit("工具图标"));
    ui->tableViewTool4->setModel(m_modelTool4);
    common::setTableViewBasicConfiguration(ui->tableViewTool4);

    m_modelIP1 = new QStandardItemModel();
    m_modelIP1->setColumnCount(3);
    m_modelIP1->setHeaderData(0, Qt::Horizontal, QString::fromLocal8Bit("ip"));
    m_modelIP1->setHeaderData(1, Qt::Horizontal, QString::fromLocal8Bit("主机"));
    m_modelIP1->setHeaderData(2, Qt::Horizontal, QString::fromLocal8Bit("软件"));
    ui->tableViewIP1->setModel(m_modelIP1);
    common::setTableViewBasicConfiguration(ui->tableViewIP1);

    m_modelIP2 = new QStandardItemModel();
    m_modelIP2->setColumnCount(2);
    m_modelIP2->setHeaderData(0, Qt::Horizontal, QString::fromLocal8Bit("主机"));
    m_modelIP2->setHeaderData(1, Qt::Horizontal, QString::fromLocal8Bit("ip"));
    ui->tableViewIP2->setModel(m_modelIP2);
    common::setTableViewBasicConfiguration(ui->tableViewIP2);

    m_modelIP3 = new QStandardItemModel();
    m_modelIP3->setColumnCount(2);
    m_modelIP3->setHeaderData(0, Qt::Horizontal, QString::fromLocal8Bit("主机"));
    m_modelIP3->setHeaderData(1, Qt::Horizontal, QString::fromLocal8Bit("ip"));
    ui->tableViewIP3->setModel(m_modelIP3);
    common::setTableViewBasicConfiguration(ui->tableViewIP3);

    m_modelIP4 = new QStandardItemModel();
    m_modelIP4->setColumnCount(2);
    m_modelIP4->setHeaderData(0, Qt::Horizontal, QString::fromLocal8Bit("主机"));
    m_modelIP4->setHeaderData(1, Qt::Horizontal, QString::fromLocal8Bit("ip"));
    ui->tableViewIP4->setModel(m_modelIP4);
    common::setTableViewBasicConfiguration(ui->tableViewIP4);

    //m_modelIP1->appendRow(QList<QStandardItem*>()
    //    << new QStandardItem("computer1")
    //    << new QStandardItem("192.168.1.1"));
    //m_modelIP1->appendRow(QList<QStandardItem*>()
    //    << new QStandardItem("computer2")
    //    << new QStandardItem("192.168.1.100"));
    //m_modelIP1->appendRow(QList<QStandardItem*>()
    //    << new QStandardItem("computer3")
    //    << new QStandardItem("192.168.1.21"));

    ui->btnToolAdd1->setProperty("module", 1);
    ui->btnToolAdd2->setProperty("module", 2);
    ui->btnToolAdd3->setProperty("module", 3);
    ui->btnToolAdd4->setProperty("module", 4);
    ui->btnIpAdd1->setProperty("module", 1);
    ui->btnIpAdd2->setProperty("module", 2);
    ui->btnIpAdd3->setProperty("module", 3);
    ui->btnIpAdd4->setProperty("module", 4);
    ui->btnToolDel1->setProperty("module", 1);
    ui->btnToolDel2->setProperty("module", 2);
    ui->btnToolDel3->setProperty("module", 3);
    ui->btnToolDel4->setProperty("module", 4);
    ui->btnIpDel1->setProperty("module", 1);
    ui->btnIpDel2->setProperty("module", 2);
    ui->btnIpDel3->setProperty("module", 3);
    ui->btnIpDel4->setProperty("module", 4);
    connect(ui->btnToolAdd1, &QPushButton::clicked, this, &InformationConfihurationDialog::slot_btnToolAdd);
    connect(ui->btnToolAdd2, &QPushButton::clicked, this, &InformationConfihurationDialog::slot_btnToolAdd);
    connect(ui->btnToolAdd3, &QPushButton::clicked, this, &InformationConfihurationDialog::slot_btnToolAdd);
    connect(ui->btnToolAdd4, &QPushButton::clicked, this, &InformationConfihurationDialog::slot_btnToolAdd);
    connect(ui->btnIpAdd1, &QPushButton::clicked, this, &InformationConfihurationDialog::slot_btnIpAdd);
    connect(ui->btnIpAdd2, &QPushButton::clicked, this, &InformationConfihurationDialog::slot_btnIpAdd);
    connect(ui->btnIpAdd3, &QPushButton::clicked, this, &InformationConfihurationDialog::slot_btnIpAdd);
    connect(ui->btnIpAdd4, &QPushButton::clicked, this, &InformationConfihurationDialog::slot_btnIpAdd);

    connect(ui->btnToolDel1, &QPushButton::clicked, this, &InformationConfihurationDialog::slot_btnToolDel);
    connect(ui->btnToolDel2, &QPushButton::clicked, this, &InformationConfihurationDialog::slot_btnToolDel);
    connect(ui->btnToolDel3, &QPushButton::clicked, this, &InformationConfihurationDialog::slot_btnToolDel);
    connect(ui->btnToolDel4, &QPushButton::clicked, this, &InformationConfihurationDialog::slot_btnToolDel);

    connect(ui->btnIpDel1, &QPushButton::clicked, this, &InformationConfihurationDialog::slot_btnIpDel);
    connect(ui->btnIpDel2, &QPushButton::clicked, this, &InformationConfihurationDialog::slot_btnIpDel);
    connect(ui->btnIpDel3, &QPushButton::clicked, this, &InformationConfihurationDialog::slot_btnIpDel);
    connect(ui->btnIpDel4, &QPushButton::clicked, this, &InformationConfihurationDialog::slot_btnIpDel);

    ui->tableViewTool1->setMouseTracking(true);

    connect(ui->tableViewTool1, SIGNAL(entered(QModelIndex)), this, SLOT(slot_tooltip(QModelIndex)));

      
}

void InformationConfihurationDialog::initFaceData()
{
    flushToolModelData(m_modelTool1,1);
    flushToolModelData(m_modelTool2,2);
    flushToolModelData(m_modelTool3,3);
    flushToolModelData(m_modelTool4,4);

    flushIpModelData(m_modelIP1);
    flushIpModelData(m_modelIP2, 2);
    flushIpModelData(m_modelIP3, 3);
    flushIpModelData(m_modelIP4, 4);
}

void InformationConfihurationDialog::flushToolModelData(QStandardItemModel* model, const int& module)
{
    delAllModelRow(model);
    std::list<table_tools> listTools;
    if (db::databaseDI::Instance().get_tools(listTools, module))
    {
        for (const auto& stTool : listTools)
        {
         /*   model->appendRow(QList<QStandardItem*>()
                << new QStandardItem(QString::fromStdString(stTool.host))
                << new QStandardItem(QString::fromStdString(stTool.name))
                << new QStandardItem(QString::fromStdString(stTool.path))
                << new QStandardItem(QString::fromStdString(stTool.icoPath)));
*/

            int newRowIndex = model->rowCount(); // 获取当前行数
            model->insertRow(newRowIndex); // 插入新行

            QStandardItem* item = new QStandardItem(QString::fromStdString(stTool.host));
            // item->setTextAlignment(Qt::AlignCenter);  // 设置文本居中对齐
            model->setItem(newRowIndex, 0, item);
            QModelIndex index = model->index(newRowIndex, 0);
            model->setData(index, stTool.id, Qt::UserRole);  // 设置id;

            model->setItem(newRowIndex, 1, new QStandardItem(QString::fromStdString(stTool.name)));
            model->setItem(newRowIndex, 2, new QStandardItem(QString::fromStdString(stTool.path)));
            model->setItem(newRowIndex, 3, new QStandardItem(QString::fromStdString(stTool.icoPath)));

        }

    }
}

void InformationConfihurationDialog::flushIpModelData(QStandardItemModel* pModel)
{
    delAllModelRow(pModel);
    std::list<table_ip> listData;
    if (db::databaseDI::Instance().get_ip_data(listData))
    {
        for (const auto& stIp : listData)
        {
            int newRowIndex = pModel->rowCount(); // 获取当前行数
            pModel->insertRow(newRowIndex); // 插入新行

            QStandardItem* item = new QStandardItem(QString::fromStdString(stIp.ip));
            // item->setTextAlignment(Qt::AlignCenter);  // 设置文本居中对齐
            pModel->setItem(newRowIndex, 0, item);
            QModelIndex index = pModel->index(newRowIndex, 0);
            pModel->setData(index, stIp.id, Qt::UserRole);  // 设置id;

            pModel->setItem(newRowIndex, 0, item);
            pModel->setItem(newRowIndex, 1, new QStandardItem(QString::fromStdString(stIp.host)));

        
            pModel->setItem(newRowIndex, 2, new QStandardItem(QString::fromStdString(stIp.software)));
        }
    }

}

void InformationConfihurationDialog::flushIpModelData(QStandardItemModel* pModel, const int& module)
{
    delAllModelRow(pModel);
    std::list<table_ip> listData;
    if (db::databaseDI::Instance().get_ip_data(listData, module))
    {
        for (const auto& stIp : listData)
        {
            //pModel->appendRow(QList<QStandardItem*>()
            //    << new QStandardItem(QString::fromStdString(stData.host))
            //    << new QStandardItem(QString::fromStdString(stData.ip)));

            int newRowIndex = pModel->rowCount(); // 获取当前行数
            pModel->insertRow(newRowIndex); // 插入新行

            QStandardItem* item = new QStandardItem(QString::fromStdString(stIp.host));
            // item->setTextAlignment(Qt::AlignCenter);  // 设置文本居中对齐
            pModel->setItem(newRowIndex, 0, item);
            QModelIndex index = pModel->index(newRowIndex, 0);
            pModel->setData(index, stIp.id, Qt::UserRole);  // 设置id;

            pModel->setItem(newRowIndex, 0, item);
            pModel->setItem(newRowIndex, 1, new QStandardItem(QString::fromStdString(stIp.ip)));
        }
    }
}



void InformationConfihurationDialog::clearModelData(QStandardItemModel* model)
{
    // 清理所有数据项，但保留列标题
    for (int row = 0; row < model->rowCount(); ++row)
    {
        for (int column = 0; column < model->columnCount(); ++column) 
        {
            model->setItem(row, column, nullptr);
        }
    }
}

void InformationConfihurationDialog::delAllModelRow(QStandardItemModel* model)
{
    // 删除所有行
    int rowCount = model->rowCount();
    for (int row = rowCount - 1; row >= 0; --row)
    {
        model->removeRow(row);
    }
}

void InformationConfihurationDialog::slot_btnToolAdd()
{

    QPushButton* pButton = (QPushButton*)sender();
    int moduleNumber = pButton->property("module").toInt();

    AddToolInfoDialog addToolInfoDialog;
    if (addToolInfoDialog.exec() == QDialog::Accepted)
    {
        table_tools stTools;
        addToolInfoDialog.getToolsData(stTools);
        stTools.module = moduleNumber;
        QStandardItemModel* pModel = nullptr;
        if (moduleNumber == 1)
        {
            pModel = m_modelTool1;
        }
        else if (moduleNumber == 2)
        {
            pModel = m_modelTool2;
        }
        else if (moduleNumber == 3)
        {
            pModel = m_modelTool3;
        }
        else if (moduleNumber == 4)
        {
            pModel = m_modelTool4;
        }
        if (pModel == nullptr)
            return;
        int newRowIndex = pModel->rowCount(); // 获取当前行数
        pModel->insertRow(newRowIndex); // 插入新行
        
       // pModel->setItem(newRowIndex, 0, new QStandardItem(QString::fromStdString(stTools.host)));

        QStandardItem* item = new QStandardItem(QString::fromStdString(stTools.host));
       // item->setTextAlignment(Qt::AlignCenter);  // 设置文本居中对齐
        pModel->setItem(newRowIndex, 0, item);
        QModelIndex index = pModel->index(newRowIndex, 0);
        pModel->setData(index, stTools.id, Qt::UserRole);  // 设置id;

        pModel->setItem(newRowIndex, 1, new QStandardItem(QString::fromStdString(stTools.name)));
        pModel->setItem(newRowIndex, 2, new QStandardItem(QString::fromStdString(stTools.path)));
        pModel->setItem(newRowIndex, 3, new QStandardItem(QString::fromStdString(stTools.icoPath)));

        // 插入数据库;
        if (!db::databaseDI::Instance().add_tools(stTools))
        {
            qDebug() << "db::databaseDI::Instance().add_tools   error!";
        }

      emit  signal_updateToolIcon(moduleNumber);
    }
   
    // 使用 setData 设置特定单元格的数据
  
    // 滚动到最下方
    ui->tableViewTool1->scrollToBottom();
}


void InformationConfihurationDialog::slot_btnIpAdd()
{
    QPushButton* pButton = (QPushButton*)sender();
    int moduleNumber = pButton->property("module").toInt();
    AddIpInfoDialog addIpInfoDialog;
    if (addIpInfoDialog.exec() == QDialog::Accepted)
    {
        table_ip stIp;
        addIpInfoDialog.getIpData(stIp);
        stIp.module = moduleNumber;
     
        QStandardItemModel* pModel = nullptr;
        if (moduleNumber == 1)
        {
            pModel = m_modelIP1;
        }
        else if (moduleNumber == 2)
        {
            pModel = m_modelIP2;
        }
        else if (moduleNumber == 3)
        {
            pModel = m_modelIP3;
        }
        else if (moduleNumber == 4)
        {
            pModel = m_modelIP4;
        }
        if (pModel == nullptr)
            return;

        int newRowIndex = pModel->rowCount(); // 获取当前行数
        pModel->insertRow(newRowIndex); // 插入新行

        QStandardItem* item = new QStandardItem(QString::fromStdString(stIp.host));
        // item->setTextAlignment(Qt::AlignCenter);  // 设置文本居中对齐
        pModel->setItem(newRowIndex, 0, item);
        QModelIndex index = pModel->index(newRowIndex, 0);
        pModel->setData(index, stIp.id, Qt::UserRole);  // 设置id;

        pModel->setItem(newRowIndex, 1, new QStandardItem(QString::fromStdString(stIp.ip)));
        
        // 插入数据库;
       if (!db::databaseDI::Instance().add_ip(stIp))
       {
            qDebug() << "db::databaseDI::Instance().add_ip   error!";   
       }

    }

    // 使用 setData 设置特定单元格的数据

    // 滚动到最下方
    ui->tableViewTool1->scrollToBottom();
}



void InformationConfihurationDialog::slot_btnToolDel()
{
    
    QPushButton* pButton = (QPushButton*)sender();
    int moduleNumber = pButton->property("module").toInt();
    QModelIndex currentIndex;
    QStandardItemModel* pModelTool = nullptr;
    if (moduleNumber == 1)                                                                                     
    {
        currentIndex = ui->tableViewTool1->currentIndex();
       
       pModelTool = m_modelTool1;
    }
    else if (moduleNumber == 2)
    {
        currentIndex = ui->tableViewTool2->currentIndex();
        pModelTool = m_modelTool2;
    }
    else if (moduleNumber == 3)
    {
        currentIndex = ui->tableViewTool3->currentIndex();
        pModelTool = m_modelTool3;
    }
    else if (moduleNumber == 4)
    {
        currentIndex = ui->tableViewTool4->currentIndex();
        pModelTool = m_modelTool4;
    }

    if (pModelTool == nullptr)
        return;
    if (!currentIndex.isValid())
        return;
    QModelIndex firstColumnIndex = pModelTool->index(currentIndex.row(), 0, QModelIndex());

    int id = pModelTool->data(firstColumnIndex, Qt::UserRole).toInt();
    qDebug() << "First column data of current row   id: " << id;

    if (db::databaseDI::Instance().del_tools(id))
    {
        pModelTool->removeRow(currentIndex.row());
        emit  signal_updateToolIcon(moduleNumber);
    }
}

void InformationConfihurationDialog::slot_btnIpDel()
{
    QPushButton* pButton = (QPushButton*)sender();
    int moduleNumber = pButton->property("module").toInt();
    QModelIndex currentIndex;
    QStandardItemModel* pModel = nullptr;
    if (moduleNumber == 1)
    {
        currentIndex = ui->tableViewIP1->currentIndex();

        pModel= m_modelIP1;
    }
    else if (moduleNumber == 2)
    {
        currentIndex = ui->tableViewIP2->currentIndex();
        pModel = m_modelIP2;
    }
    else if (moduleNumber == 3)
    {
        currentIndex = ui->tableViewIP3->currentIndex();
        pModel = m_modelIP3;
    }
    else if (moduleNumber == 4)
    {
        currentIndex = ui->tableViewIP4->currentIndex();
        pModel = m_modelIP4;
    }

    if (pModel == nullptr)
        return;
    if (!currentIndex.isValid())
        return;
    QModelIndex firstColumnIndex = pModel->index(currentIndex.row(), 0, QModelIndex());

    int id = pModel->data(firstColumnIndex, Qt::UserRole).toInt();
    qDebug() << "First column data of current row   id: " << id;

    if (db::databaseDI::Instance().del_ip(id))
    {
        pModel->removeRow(currentIndex.row());
    }
}



//void InformationConfihurationDialog::slot_tooltip(QModelIndex index)
//{
//   // QToolTip::showText(QCursor::pos(), index.data().toString());
//   // QToolTip::showText(QCursor::pos(), index.data().toString());
//}
