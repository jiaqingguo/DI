
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
    m_model->setHeaderData(0, Qt::Horizontal, QString::fromLocal8Bit("���"));
    m_model->setHeaderData(1, Qt::Horizontal, QString::fromLocal8Bit("�ļ�·��"));
    m_model->setHeaderData(2, Qt::Horizontal, QString::fromLocal8Bit("����"));

    /* QStringList labels = QObject::trUtf8("ID,����,value,ʱ��,���").simplified().split(",");
     model->setHorizontalHeaderLabels(labels);*/
    ui->tableView->setModel(m_model);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);   // ѡ������
    ui->tableView->verticalHeader()->setDefaultSectionSize(28);
    ui->tableView->verticalHeader()->setVisible(false);

    // ���صڶ���
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
    int newRowIndex = m_model->rowCount(); // ��ȡ��ǰ����
    m_model->insertRow(newRowIndex); // ��������

   // pModel->setItem(newRowIndex, 0, new QStandardItem(QString::fromStdString(stTools.host)));

    QStandardItem* item = new QStandardItem(QString::number(newRowIndex+1));
    // item->setTextAlignment(Qt::AlignCenter);  // �����ı����ж���
    m_model->setItem(newRowIndex, 0, item);
    QModelIndex index = m_model->index(newRowIndex, 0);
    //m_model->setData(index, stIp.id, Qt::UserRole);  // ����id;

    m_model->setItem(newRowIndex, 1, new QStandardItem(QString::fromStdString("")));

    QPushButton* buttonCopy = new QPushButton(QString::fromLocal8Bit("ճ��·��"));
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
        m_model->removeRow(index.row()); // ɾ����2�У�������0��ʼ��
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
        QStandardItem* item = m_model->item(row, 1); // ��ȡ�ڶ��У�����Ϊ1������
        if (item) 
        {
          //  qDebug() << item->text(); // ��ӡ�ı�
            vecStrPath.push_back(item->text().toLocal8Bit().toStdString());
        }
    }
    
    if (ui->lineEditDirPath->text().isEmpty())
    {
        QMessageBox::warning(this, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("·������Ϊ�գ�"));
        ui->lineEditDirPath->setFocus();
        return;
    }
    if (ui->lineEditZipName->text().isEmpty())
    {
        QMessageBox::warning(this, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("���Ʋ���Ϊ�գ�"));
        return;
    }
    QString zipPath = ui->lineEditDirPath->text() + "\\" + ui->lineEditZipName->text()+".zip";
    emit signals_zipMultPath(vecStrPath, zipPath.toLocal8Bit().toStdString());
}
