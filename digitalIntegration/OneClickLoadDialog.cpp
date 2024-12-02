

#include <QStandardItemModel>
#include <QComboBox>
#include <QDebug>
#include <QtWidgets/QApplication>
#include <QApplication>

#include "OneClickLoadDialog.h"
#include "ui_OneClickLoadDialog.h"
#include "common.h"
#include "globel.h"
#include "databaseDI.h"
#include "database.h"
#include "mainwindow.h"

OneClickLoadDialog::OneClickLoadDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::OneClickLoadDialog)
{
	ui->setupUi(this);

	m_model = new QStandardItemModel();
	m_model->setColumnCount(2);
	m_model->setHeaderData(0, Qt::Horizontal, QString::fromLocal8Bit("���"));
	m_model->setHeaderData(1, Qt::Horizontal, QString::fromLocal8Bit("���"));
	//m_model->setHeaderData(2, Qt::Horizontal, QString::fromLocal8Bit("ģ��"));
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
	//int newRowIndex = m_model->rowCount(); // ��ȡ��ǰ����
	//m_model->insertRow(newRowIndex); // ��������

	//QStandardItem* item = new QStandardItem(QString::number(newRowIndex + 1));
	//m_model->setItem(newRowIndex, 0, item);
	//QModelIndex index = m_model->index(newRowIndex, 0);
	//// item->setTextAlignment(Qt::AlignCenter);  // �����ı����ж���
	////m_model->setData(index, stIp.id, Qt::UserRole);  // ����id;

	//m_model->setItem(newRowIndex, 1, new QStandardItem(QString::fromStdString("")));
	//m_model->setItem(newRowIndex, 2, new QStandardItem(QString::fromStdString("")));

	// ����QComboBox������ģ������
	QComboBox *comboBox = new QComboBox();
	comboBox->setEditable(false);
	std::map<std::string, table_ip> ipMap;
	std::string software;
	table_ip data;
	if (db::databaseDI::Instance().get_ip_data(ipMap, common::index))
	{
		for (const auto& stTool : ipMap)
		{
			software = stTool.first;
			data = stTool.second;
			comboBox->addItems(QString::fromStdString(software).split(' '));
		}
	}
	// ����ռλ����Ϊѡ��
	comboBox->setCurrentIndex(-1);

	int newRowIndex = m_model->rowCount();
	QStandardItem *item2 = new QStandardItem(QString::number(newRowIndex + 1));
	m_model->setItem(newRowIndex, 0, item2);
	item2->setEditable(false); // ʹ��ɱ༭���Ա��ڱ༭ģʽ����ʾQComboBox
	m_model->setItem(newRowIndex, 1, item2);
	ui->tableView->setIndexWidget(ui->tableView->model()->index(newRowIndex, 1), comboBox);
	//ui->tableView->show();
	
	connect(comboBox, &QComboBox::currentTextChanged, this, &OneClickLoadDialog::slot_keep_soft);
}
void OneClickLoadDialog::slot_btnDel()
{
	QModelIndex index = ui->tableView->currentIndex();
	if (index.isValid())
	{
		// ��ȡ��ǰѡ�е�Ԫ��ͬһ�еĵ�2�еĵ�Ԫ��
		//QModelIndex indexSecond = index.sibling(index.row(), 1); // ��2�е�����Ϊ1
		//��ȡҪɾ���ĵ�Ԫ��
		//QVariant name_data = m_model->data(indexSecond, Qt::DisplayRole);
		// ��ȡ�ڶ��е�QComboBox�ؼ�
		int row = index.row();
		QWidget *comboBoxWidget = ui->tableView->indexWidget(ui->tableView->model()->index(row, 1));
		QComboBox *comboBox = qobject_cast<QComboBox*>(comboBoxWidget);
		// ��ȡQComboBox�е��ı�
		QString comboBoxText = comboBox->currentText();

		if (!db::databaseDI::Instance().del_load_software(comboBoxText.toStdString(), common::iUserID, common::index))
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
	//QString exeDir = QCoreApplication::applicationDirPath();
	for (int row = 0; row < m_model->rowCount(); ++row)
	{
		//QStandardItem* item_software = m_model->item(row, 1); // ��ȡ��ǰ�еĵ�2����
		//QStandardItem* item_module = m_model->item(row, 2);

		//if (item_module->data(Qt::DisplayRole).toInt() == 1)
		// ��ȡ��Ԫ���С����
		QWidget *widget = ui->tableView->indexWidget(m_model->index(row, 1));
		if (widget)
		{
			// ��С����ת��ΪQComboBox
			QComboBox *comboBox = qobject_cast<QComboBox *>(widget);

			// ��ȡ��ǰѡ�е��ı�
			QString currentText = comboBox->currentText();

			if (common::index == 1)
			{
				//if (item_software)
				{
					//emit one_load_tools(item_module->data(Qt::DisplayRole).toInt(), item_software->text());
					emit one_load_tools(common::index, currentText);
					////�������ݿ�
					//table_one_load_software stData;
					//stData.projectPath = currentText.toStdString();
					////stData.module = item_module->data(Qt::DisplayRole).toInt();
					//stData.module = common::index;
					//stData.userID = common::iUserID;
					//if (!db::databaseDI::Instance().get_software(stData.projectPath, common::iUserID, stData.module))
					//{
					//	if (!db::databaseDI::Instance().add_load_software(stData))
					//	{
					//		return;
					//	}
					//}
				}
			}
			else if (common::index == 2)
			{
				//if (item_software)
				{
					emit one_load_tools(common::index, currentText);

					////�������ݿ�
					//table_one_load_software stData;
					//stData.projectPath = currentText.toStdString();
					//stData.userID = common::iUserID;
					//stData.module = common::index;
					//if (!db::databaseDI::Instance().get_software(stData.projectPath, common::iUserID, stData.module))
					//{
					//	if (!db::databaseDI::Instance().add_load_software(stData))
					//	{
					//		return;
					//	}
					//}
				}
			}
			else if (common::index == 3)
			{
				//if (item_software)
				{
					emit one_load_tools(common::index, currentText);

					////�������ݿ�
					//table_one_load_software stData;
					//stData.projectPath = currentText.toStdString();
					//stData.userID = common::iUserID;
					//stData.module = common::index;
					//if (!db::databaseDI::Instance().get_software(stData.projectPath, common::iUserID, stData.module))
					//{
					//	if (!db::databaseDI::Instance().add_load_software(stData))
					//	{
					//		return;
					//	}
					//}
				}
			}
			else
			{
				//if (item_software)
				{
					emit one_load_tools(common::index, currentText);

					////�������ݿ�
					//table_one_load_software stData;
					//stData.projectPath = currentText.toStdString();
					//stData.userID = common::iUserID;
					//stData.module = common::index;
					//if (!db::databaseDI::Instance().get_software(stData.projectPath, common::iUserID, stData.module))
					//{
					//	if (!db::databaseDI::Instance().add_load_software(stData))
					//	{
					//		return;
					//	}
					//}
				}
			}
		}
	}
	this->close();
}

void OneClickLoadDialog::slot_keep_soft(QString text)
{
	//�������ݿ�
	table_one_load_software stData;
	stData.projectPath = text.toStdString();
	//stData.module = item_module->data(Qt::DisplayRole).toInt();
	stData.module = common::index;
	stData.userID = common::iUserID;
	if (!db::databaseDI::Instance().add_load_software(stData))
	{
		return;
	}
}
