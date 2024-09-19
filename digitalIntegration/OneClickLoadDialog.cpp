

#include <QStandardItemModel>
#include <QCheckBox>
#include <QDebug>
#include <QtWidgets/QApplication>
#include <QApplication>

#include "OneClickLoadDialog.h"
#include "ui_OneClickLoadDialog.h"
#include "common.h"
#include "globel.h"
#include "databaseDI.h"
#include "database.h"

OneClickLoadDialog::OneClickLoadDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::OneClickLoadDialog)
{
	ui->setupUi(this);

	m_model = new QStandardItemModel();
	m_model->setColumnCount(2);
	m_model->setHeaderData(0, Qt::Horizontal, QString::fromLocal8Bit("���"));
	m_model->setHeaderData(1, Qt::Horizontal, QString::fromLocal8Bit("���"));
	//m_model->setHeaderData(2, Qt::Horizontal, QString::fromLocal8Bit("�ļ�·��"));
	//m_model->setHeaderData(3, Qt::Horizontal, QString::fromLocal8Bit("ѡ��"));

	/* QStringList labels = QObject::trUtf8("ID,����,value,ʱ��,���").simplified().split(",");
	 model->setHorizontalHeaderLabels(labels);*/
	ui->tableView->setModel(m_model);
	ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);   // ѡ������
	ui->tableView->verticalHeader()->setDefaultSectionSize(28);
	ui->tableView->verticalHeader()->setVisible(false);

	// ���صڶ���
	//ui->tableView->setColumnHidden(0, true);
	//common::setTableViewBasicConfiguration(ui->tableView);


	//for (int i = 0; i < 7; i++)
	//{
	//    m_model->setItem(i, 0, new QStandardItem(QString::number(i + 1)));
	//    m_model->setItem(i, 1, new QStandardItem(QString("hello qt tablview %1").arg(i)));
	//    m_model->setItem(i, 2, new QStandardItem("normal"));
	// 
	//    QWidget* widget = new QWidget(); // ����һ������Widget�����CheckBox
	//    QCheckBox* checkBox = new QCheckBox(); // ����CheckBox
	//    checkBox->setProperty("row", i); // set custom property
	//    checkBox->setProperty("column", 3);
	//    QHBoxLayout* layout = new QHBoxLayout(widget); // Ϊ����Widget����ˮƽ����
	//    layout->addWidget(checkBox); // ��CheckBox��ӵ�������
	//    layout->setAlignment(Qt::AlignCenter); // ���ò����еĿؼ����ж���
	//    layout->setContentsMargins(0, 0, 0, 0); // �Ƴ����ֱ߾�
	//   
	//    ui->tableView->setIndexWidget(m_model->index(i, 3), widget);
	//}

	connect(ui->btnDel, &QPushButton::clicked, this, &OneClickLoadDialog::slot_btnDel);
	connect(ui->btnAdd, &QPushButton::clicked, this, &OneClickLoadDialog::slot_btnAdd);
	connect(ui->btnOk, &QPushButton::clicked, this, &OneClickLoadDialog::slot_btnOK);
}

OneClickLoadDialog::~OneClickLoadDialog()
{
	delete ui;
}

void OneClickLoadDialog::slot_btnAdd()
{
	int newRowIndex = m_model->rowCount(); // ��ȡ��ǰ����
	m_model->insertRow(newRowIndex); // ��������

	QStandardItem* item = new QStandardItem(QString::number(newRowIndex + 1));
	m_model->setItem(newRowIndex, 0, item);
	QModelIndex index = m_model->index(newRowIndex, 0);
	// item->setTextAlignment(Qt::AlignCenter);  // �����ı����ж���
	//m_model->setData(index, stIp.id, Qt::UserRole);  // ����id;

	m_model->setItem(newRowIndex, 1, new QStandardItem(QString::fromStdString("")));
}
void OneClickLoadDialog::slot_btnDel()
{
	QModelIndex index = ui->tableView->currentIndex();
	if (index.isValid())
	{
		//��ȡҪɾ���ĵ�Ԫ��
		QVariant data = m_model->data(index, Qt::DisplayRole);
		// ��ӡ���ߴ�������
		//qDebug() << "Ҫɾ���������ǣ�" << data.toString();
		if (!db::databaseDI::Instance().del_load_software(data.toString().toStdString(), common::iUserID))
			return;

		m_model->removeRow(index.row()); // ɾ����2�У�������0��ʼ��
	}

	for (int row = 0; row < m_model->rowCount(); ++row)
	{
		QStandardItem* item = m_model->item(row, 0); // ��ȡ��ǰ�еĵ�һ����
		if (item)
		{
			item->setText(QString::number(row + 1)); // �������
		}
	}
}
void OneClickLoadDialog::slot_btnOK()
{
	//std::vector<std::string> vecStrSoftware;
	QString exeDir = QCoreApplication::applicationDirPath();
	for (int row = 0; row < m_model->rowCount(); ++row)
	{
		QStandardItem* item = m_model->item(row, 1); // ��ȡ��ǰ�еĵ�2����
		if (item)
		{
			QString strDspPath = exeDir + "/dsp/" + QString::number(common::iLoginNum) + "/" + item->text() + ".bsp";

			//����bsp��Ƕ��
			int a = 1;

			//�������ݿ�
			table_load_project stData;
			stData.projectPath = item->text().toStdString();
			stData.userID = common::iUserID;
			if (!db::databaseDI::Instance().get_software(stData.projectPath, common::iUserID))
			{
				if (!db::databaseDI::Instance().add_load_software(stData))
				{
					return;
				}
			}
		}

	}
	this->close();
}
