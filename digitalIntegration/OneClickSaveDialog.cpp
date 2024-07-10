#include "OneClickSaveDialog.h"
#include "ui_OneClickSaveDialog.h"

#include <QStandardItemModel>
#include <QCheckBox>

OneClickSaveDialog::OneClickSaveDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OneClickSaveDialog)
{
    ui->setupUi(this);

    QStandardItemModel* m_model = new QStandardItemModel();
    m_model->setColumnCount(4);
    m_model->setHeaderData(0, Qt::Horizontal, QString::fromLocal8Bit("序号"));
    m_model->setHeaderData(1, Qt::Horizontal, QString::fromLocal8Bit("已启动工具"));
    m_model->setHeaderData(2, Qt::Horizontal, QString::fromLocal8Bit("文件保存路径"));
    m_model->setHeaderData(3, Qt::Horizontal, QString::fromLocal8Bit("选择"));

    /* QStringList labels = QObject::trUtf8("ID,名字,value,时间,类别").simplified().split(",");
     model->setHorizontalHeaderLabels(labels);*/
    ui->tableView->setModel(m_model);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);   // 选择整行
    ui->tableView->verticalHeader()->setDefaultSectionSize(28);
    ui->tableView->verticalHeader()->setVisible(false);

    for (int i = 0; i < 7; i++)
    {
        m_model->setItem(i, 0, new QStandardItem(QString::number(i + 1)));
        m_model->setItem(i, 1, new QStandardItem(QString("hello qt tablview %1").arg(i)));
        m_model->setItem(i, 2, new QStandardItem("normal"));


        QWidget* widget = new QWidget(); // 创建一个容器Widget来存放CheckBox
        QCheckBox* checkBox = new QCheckBox(); // 创建CheckBox
        checkBox->setProperty("row", i); // set custom property
        checkBox->setProperty("column", 3);
        QHBoxLayout* layout = new QHBoxLayout(widget); // 为容器Widget设置水平布局
        layout->addWidget(checkBox); // 将CheckBox添加到布局中
        layout->setAlignment(Qt::AlignCenter); // 设置布局中的控件居中对齐
        layout->setContentsMargins(0, 0, 0, 0); // 移除布局边距
        // add button to the last column
       // QCheckBox* checkBox = new QCheckBox();


        ui->tableView->setIndexWidget(m_model->index(i, 3), widget);

    }
}

OneClickSaveDialog::~OneClickSaveDialog()
{
    delete ui;
}
