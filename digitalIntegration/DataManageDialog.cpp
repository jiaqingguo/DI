#include <QDebug>
#include <QMovie>
#include <QLabel>
#include <QDialog>
#include <QVBoxLayout>

#include "DataManageDialog.h"
#include "ui_DataManageDialog.h"

#include "CPagedTableModel.h"
#include "CButtonItemDelegate.h"
#include "globel.h"
#include "databaseDI.h"



DataManageDialog::DataManageDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DataManageDialog)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/image/DataManage.png"));
    ui->stackedWidget->setCurrentIndex(0);

    ui->btn1->setStyleSheet(strQssBlue);
    ui->btn2->setStyleSheet(strQssGray);
    ui->btn3->setStyleSheet(strQssGray);
    ui->btn4->setStyleSheet(strQssGray);
   
    init();
}

DataManageDialog::~DataManageDialog()
{
    delete ui;
}

void DataManageDialog::init()
{
 
    m_CPagedTableModel = new CPagedTableModel(this);

    QStandardItemModel* m_model = new QStandardItemModel();
    m_model->setColumnCount(10);
    m_model->setHeaderData(0, Qt::Horizontal, QString::fromLocal8Bit("序号"));
    m_model->setHeaderData(1, Qt::Horizontal, QString::fromLocal8Bit("主机"));
    m_model->setHeaderData(2, Qt::Horizontal, QString::fromLocal8Bit("生成时间"));
    m_model->setHeaderData(3, Qt::Horizontal, QString::fromLocal8Bit("工具名"));
    m_model->setHeaderData(4, Qt::Horizontal, QString::fromLocal8Bit("文件名"));
    m_model->setHeaderData(5, Qt::Horizontal, QString::fromLocal8Bit("文件类型"));
    m_model->setHeaderData(6, Qt::Horizontal, QString::fromLocal8Bit("位置"));
    m_model->setHeaderData(7, Qt::Horizontal, QString::fromLocal8Bit("操作"));
    m_model->setHeaderData(8, Qt::Horizontal, QString::fromLocal8Bit("操作"));
    m_model->setHeaderData(9, Qt::Horizontal, QString::fromLocal8Bit("操作"));

   /* QStringList labels = QObject::trUtf8("ID,名字,value,时间,类别").simplified().split(",");
    model->setHorizontalHeaderLabels(labels);*/
    ui->tableView1->setModel(m_model);
    ui->tableView1->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView1->setSelectionBehavior(QAbstractItemView::SelectRows);   // 选择整行
    ui->tableView1->verticalHeader()->setDefaultSectionSize(28);
    ui->tableView1->verticalHeader()->setVisible(false);
   
    for (int i = 0; i < 7; i++)
    {
        m_model->setItem(i, 0, new QStandardItem(QString::number(i + 1)));
        m_model->setItem(i, 1, new QStandardItem(QString::fromLocal8Bit("刀片机/* %1*/")/*.arg(i)*/));
        m_model->setItem(i, 2, new QStandardItem(QString::fromLocal8Bit("2024 / 06 / 15 18:01 : 25")));
        m_model->setItem(i, 3, new QStandardItem("Mentor"));
        m_model->setItem(i, 4, new QStandardItem("111"));
        m_model->setItem(i, 5, new QStandardItem("txt"));
        m_model->setItem(i, 6, new QStandardItem("D:\\Project"));
       
        QPushButton* button = new QPushButton(QString::fromLocal8Bit("预览"));
        button->setObjectName("itemBtn"); // 设置相同的对象名称
        button->setProperty("row", i); // set custom property
        button->setProperty("column", 7);
        button->setProperty("name", QString::fromLocal8Bit("刀片机 %1").arg(i));
        connect(button, SIGNAL(clicked()), this, SLOT(slot_ItemBtnClicked()));
        ui->tableView1->setIndexWidget(m_model->index(i, 7), button);

        button = new QPushButton(QString::fromLocal8Bit("下载"));
        button->setObjectName("itemBtn"); // 设置相同的对象名称
        button->setProperty("row", i); // set custom property
        button->setProperty("column", 8);
        button->setProperty("name", QString("hello qt tablview %1").arg(i));
        connect(button, SIGNAL(clicked()), this, SLOT(slot_ItemBtnClicked()));
        ui->tableView1->setIndexWidget(m_model->index(i, 8), button);

        button = new QPushButton(QString::fromLocal8Bit("删除"));
        button->setObjectName("itemBtn"); // 设置相同的对象名称
        button->setProperty("row", i); // set custom property
        button->setProperty("column", 9);
        button->setProperty("name", QString("hello qt tablview %1").arg(i));
        connect(button, SIGNAL(clicked()), this, SLOT(slot_ItemBtnClicked()));
        ui->tableView1->setIndexWidget(m_model->index(i, 9), button);
    }
    ui->tableView1->hideColumn(7);
}

void DataManageDialog::slot_ItemBtnClicked()
{
    QPushButton* pButton = (QPushButton*)sender();
    int row= pButton->property("row").toInt();
    pButton->property("name").toString() ;
    int col= pButton->property("column").toInt();

    table_dataApproval stDataApproval;

    stDataApproval.proposer = "1";
   // QModelIndex index = m_model->index(row, col, QModelIndex());
    stDataApproval.department = "1";
    stDataApproval.createTime =std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    stDataApproval.applicationTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    stDataApproval.fileName = "Mentor";
    stDataApproval.fileType = "txt";
    stDataApproval.host = QString::fromLocal8Bit("刀片机1").toStdString();
    stDataApproval.tool = "Mentor";
    if (!db::databaseDI::Instance().add_data_approval_info(stDataApproval))
    {
        qDebug() << "db::databaseDI::Instance().add_data_approval_info error !";
            return;
    }
}