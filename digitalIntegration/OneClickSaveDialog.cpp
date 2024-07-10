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
    m_model->setHeaderData(0, Qt::Horizontal, QString::fromLocal8Bit("���"));
    m_model->setHeaderData(1, Qt::Horizontal, QString::fromLocal8Bit("����������"));
    m_model->setHeaderData(2, Qt::Horizontal, QString::fromLocal8Bit("�ļ�����·��"));
    m_model->setHeaderData(3, Qt::Horizontal, QString::fromLocal8Bit("ѡ��"));

    /* QStringList labels = QObject::trUtf8("ID,����,value,ʱ��,���").simplified().split(",");
     model->setHorizontalHeaderLabels(labels);*/
    ui->tableView->setModel(m_model);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);   // ѡ������
    ui->tableView->verticalHeader()->setDefaultSectionSize(28);
    ui->tableView->verticalHeader()->setVisible(false);

    for (int i = 0; i < 7; i++)
    {
        m_model->setItem(i, 0, new QStandardItem(QString::number(i + 1)));
        m_model->setItem(i, 1, new QStandardItem(QString("hello qt tablview %1").arg(i)));
        m_model->setItem(i, 2, new QStandardItem("normal"));


        QWidget* widget = new QWidget(); // ����һ������Widget�����CheckBox
        QCheckBox* checkBox = new QCheckBox(); // ����CheckBox
        checkBox->setProperty("row", i); // set custom property
        checkBox->setProperty("column", 3);
        QHBoxLayout* layout = new QHBoxLayout(widget); // Ϊ����Widget����ˮƽ����
        layout->addWidget(checkBox); // ��CheckBox��ӵ�������
        layout->setAlignment(Qt::AlignCenter); // ���ò����еĿؼ����ж���
        layout->setContentsMargins(0, 0, 0, 0); // �Ƴ����ֱ߾�
        // add button to the last column
       // QCheckBox* checkBox = new QCheckBox();


        ui->tableView->setIndexWidget(m_model->index(i, 3), widget);

    }
}

OneClickSaveDialog::~OneClickSaveDialog()
{
    delete ui;
}
