
#include <QStandardItemModel>
#include <QCheckBox>
#include <QMessageBox>

#include "OneClickSaveDialog.h"
#include "ui_OneClickSaveDialog.h"
#include "common.h"


OneClickSaveDialog::OneClickSaveDialog(QWidget* parent) :
    QDialog(parent),
    ui(new Ui::OneClickSaveDialog)
{
    ui->setupUi(this);

    m_model = new QStandardItemModel();
    m_model->setColumnCount(3);
    m_model->setHeaderData(0, Qt::Horizontal, QString::fromLocal8Bit("序号"));
    m_model->setHeaderData(1, Qt::Horizontal, QString::fromLocal8Bit("文件路径"));
    m_model->setHeaderData(2, Qt::Horizontal, QString::fromLocal8Bit("操作"));

    /* QStringList labels = QObject::trUtf8("ID,名字,value,时间,类别").simplified().split(",");
     model->setHorizontalHeaderLabels(labels);*/
    ui->tableView->setModel(m_model);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);   // 选择整行
    ui->tableView->verticalHeader()->setDefaultSectionSize(28);
    ui->tableView->verticalHeader()->setVisible(false);

    // 隐藏第二列
    ui->tableView->setColumnHidden(0, true);

    connect(ui->btnDel, &QPushButton::clicked, this, &OneClickSaveDialog::slot_btnDel);
    connect(ui->btnAdd, &QPushButton::clicked, this, &OneClickSaveDialog::slot_btnAdd);
    connect(ui->btnOk, &QPushButton::clicked, this, &OneClickSaveDialog::slot_btnOK);
    connect(ui->btnPaste, &QPushButton::clicked, this, &OneClickSaveDialog::slot_btnPaste);
}

OneClickSaveDialog::~OneClickSaveDialog()
{
    delete ui;
}


void OneClickSaveDialog::slot_btnAdd()
{
    int newRowIndex = m_model->rowCount(); // 获取当前行数
    m_model->insertRow(newRowIndex); // 插入新行

   // pModel->setItem(newRowIndex, 0, new QStandardItem(QString::fromStdString(stTools.host)));

    QStandardItem* item = new QStandardItem(QString::number(newRowIndex+1));
    // item->setTextAlignment(Qt::AlignCenter);  // 设置文本居中对齐
    m_model->setItem(newRowIndex, 0, item);
    QModelIndex index = m_model->index(newRowIndex, 0);
    //m_model->setData(index, stIp.id, Qt::UserRole);  // 设置id;

    m_model->setItem(newRowIndex, 1, new QStandardItem(QString::fromStdString("")));

    QPushButton* buttonCopy = new QPushButton(QString::fromLocal8Bit("粘贴路径"));
    buttonCopy->setObjectName("buttonCopy");
    buttonCopy->setProperty("row", newRowIndex); // set custom property
    buttonCopy->setProperty("column", 2);

    connect(buttonCopy, SIGNAL(clicked()), this, SLOT(slot_itmeBtnCopy()));
    ui->tableView->setIndexWidget(m_model->index(newRowIndex, 2), buttonCopy);
   
}

void OneClickSaveDialog::slot_btnDel()
{
    QModelIndex index= ui->tableView->currentIndex();
    if (index.isValid())
    {
        m_model->removeRow(index.row()); // 删除第2行（索引从0开始）
    }
    
}

void OneClickSaveDialog::slot_btnPaste()
{
    ui->lineEditDirPath->setText(common::strCopyPath);
}

void OneClickSaveDialog::slot_itmeBtnCopy()
{
    QPushButton* pButton = (QPushButton*)sender();
    int row = pButton->property("row").toInt();
    int column = pButton->property("column").toInt();
   // QModelIndex index = m_model->index(row, 0);
   // int id = m_model->data(index, Qt::UserRole).toInt();

    QModelIndex index = ui->tableView->currentIndex();

    QStandardItem* pItem = m_model->item(index.row(),1);

    pItem->setText(common::strCopyPath);

}

void OneClickSaveDialog::slot_btnOK()
{
    std::vector<std::string> vecStrPath;
    for (int row = 0; row < m_model->rowCount(); ++row) 
    {
        QStandardItem* item = m_model->item(row, 1); // 获取第二列（索引为1）的项
        if (item) 
        {
          //  qDebug() << item->text(); // 打印文本
            vecStrPath.push_back(item->text().toLocal8Bit().toStdString());
        }
    }
    
    if (ui->lineEditDirPath->text().isEmpty())
    {
        QMessageBox::warning(this, QString::fromLocal8Bit("警告"), QString::fromLocal8Bit("路径不能为空！"));
        ui->lineEditDirPath->setFocus();
        return;
    }
    if (ui->lineEditZipName->text().isEmpty())
    {
        QMessageBox::warning(this, QString::fromLocal8Bit("警告"), QString::fromLocal8Bit("名称不能为空！"));
        return;
    }
    QString zipPath = ui->lineEditDirPath->text() + "\\" + ui->lineEditZipName->text()+".zip";
    emit signals_zipMultPath(vecStrPath, zipPath.toLocal8Bit().toStdString());
}
