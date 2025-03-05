

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
#include "InformationConfihurationDialog.h"

OneClickLoadDialog::OneClickLoadDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::OneClickLoadDialog)
{
	ui->setupUi(this);
	setWindowFlags(Qt::FramelessWindowHint);
	setWindowIcon(QIcon(":/image/OneLoadIcon.png"));
	m_model = new QStandardItemModel();
	m_model->setColumnCount(2);
	m_model->setHeaderData(0, Qt::Horizontal, QString::fromLocal8Bit("序号"));
	m_model->setHeaderData(1, Qt::Horizontal, QString::fromLocal8Bit("软件"));

	
	//m_model->setHeaderData(2, Qt::Horizontal, QString::fromLocal8Bit("模块"));
	//m_model->setHeaderData(3, Qt::Horizontal, QString::fromLocal8Bit("选择"));

	/* QStringList labels = QObject::trUtf8("ID,名字,value,时间,类别").simplified().split(",");
	 model->setHorizontalHeaderLabels(labels);*/
	ui->tableViewOneLoad->setModel(m_model);
	ui->tableViewOneLoad->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	ui->tableViewOneLoad->setSelectionBehavior(QAbstractItemView::SelectRows);   // 选择整行
	ui->tableViewOneLoad->verticalHeader()->setDefaultSectionSize(28);
	ui->tableViewOneLoad->verticalHeader()->setVisible(false);

	// 隐藏第二列
	//ui->tableView->setColumnHidden(0, true);
	//common::setTableViewBasicConfiguration(ui->tableView);


	//for (int i = 0; i < 7; i++)
	//{
	//    m_model->setItem(i, 0, new QStandardItem(QString::number(i + 1)));
	//    m_model->setItem(i, 1, new QStandardItem(QString("hello qt tablview %1").arg(i)));
	//    m_model->setItem(i, 2, new QStandardItem("normal"));
	// 
	//    QWidget* widget = new QWidget(); // 创建一个容器Widget来存放CheckBox
	//    QCheckBox* checkBox = new QCheckBox(); // 创建CheckBox
	//    checkBox->setProperty("row", i); // set custom property
	//    checkBox->setProperty("column", 3);
	//    QHBoxLayout* layout = new QHBoxLayout(widget); // 为容器Widget设置水平布局
	//    layout->addWidget(checkBox); // 将CheckBox添加到布局中
	//    layout->setAlignment(Qt::AlignCenter); // 设置布局中的控件居中对齐
	//    layout->setContentsMargins(0, 0, 0, 0); // 移除布局边距
	//   
	//    ui->tableView->setIndexWidget(m_model->index(i, 3), widget);
	//}

	connect(ui->btnDel, &QPushButton::clicked, this, &OneClickLoadDialog::slot_btnDel);
	connect(ui->btnAdd, &QPushButton::clicked, this, &OneClickLoadDialog::slot_btnAdd);
	connect(ui->btnOk, &QPushButton::clicked, this, &OneClickLoadDialog::slot_btnOK);
	ui->tableViewOneLoad->setShowGrid(false);
	ui->tableViewOneLoad->setStyleSheet("QTableView{font-size: 14px;color: #191a25;}");
	ui->tableViewOneLoad->horizontalHeader()->setStyleSheet("QHeaderView::section{font-size: 17px;color: #7482a6;}");
	ui->tableViewOneLoad->horizontalHeader()->setFixedHeight(40);  // 设置表头高度为40像素
	ui->tableViewOneLoad->verticalHeader()->setDefaultSectionSize(40);//设置每一行的高度为40
	

	// 创建自定义委托并设置到 QTableView
	BackgroundDelegate *delegate1 = new BackgroundDelegate(ui->tableViewOneLoad);
	ui->tableViewOneLoad->setItemDelegate(delegate1);

	connect(ui->btnOneLoadClose, &QPushButton::clicked, this, &OneClickLoadDialog::close);
}

OneClickLoadDialog::~OneClickLoadDialog()
{
	delete ui;
}

void OneClickLoadDialog::slot_btnAdd()
{
	// 创建QComboBox并设置模型数据
	this->comboBox = new QComboBox();
	//comboBox->setEditable(false);
	comboBox->setStyleSheet("QComboBox{font-size: 14px;color: #606580;}");
	comboBox->setStyleSheet("QComboBox QAbstractItemView {selection-background-color: #c3d2f0;}");
	std::map<std::string, table_ip> ipMap;
	std::string software;
	table_ip data;
	if (db::databaseDI::Instance().get_ip_data(ipMap, common::index))
	{
		for (const auto& stTool : ipMap)
		{
			software = stTool.first;
			data = stTool.second;
			comboBox->addItem(QString::fromStdString(software));
		}
	}
	// 设置占位符项为选中
	comboBox->setCurrentIndex(0);
	table_one_load_software stData;
	text = comboBox->itemText(0);
	stData.projectPath = text.toStdString();

	stData.module = common::index;
	stData.userID = common::iUserID;
	if (!db::databaseDI::Instance().add_load_software(stData))
	{
		return;
	}
	int newRowIndex = m_model->rowCount();
	QStandardItem *item2 = new QStandardItem(QString::number(newRowIndex + 1));
	item2->setTextAlignment(Qt::AlignCenter);
	m_model->setItem(newRowIndex, 0, item2);
	QModelIndex index = m_model->index(newRowIndex, 0);
	m_model->setData(index, stData.id, Qt::UserRole);
	item2->setEditable(false); // 使项不可编辑，以便在编辑模式下显示QComboBox
	item2->setTextAlignment(Qt::AlignCenter);
	m_model->setItem(newRowIndex, 1, item2);
	comboBox->setProperty("row",newRowIndex);
	ui->tableViewOneLoad->setIndexWidget(ui->tableViewOneLoad->model()->index(newRowIndex, 1), comboBox);

	connect(comboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &OneClickLoadDialog::slot_keep_soft);

	
}
void OneClickLoadDialog::slot_btnDel()
{
	QModelIndex index = ui->tableViewOneLoad->currentIndex();
	if (index.isValid())
	{
		// 获取当前选中单元格同一行的第2列的单元格
		//QModelIndex indexSecond = index.sibling(index.row(), 1); // 第2列的索引为1
		//获取要删除的单元格
		//QVariant name_data = m_model->data(indexSecond, Qt::DisplayRole);
		// 获取第二列的QComboBox控件
		int row = index.row();
		QWidget *comboBoxWidget = ui->tableViewOneLoad->indexWidget(ui->tableViewOneLoad->model()->index(row, 1));
		QComboBox *comboBox = qobject_cast<QComboBox*>(comboBoxWidget);
		// 获取QComboBox中的文本
		QString comboBoxText = comboBox->currentText();

		if (!db::databaseDI::Instance().del_load_software(comboBoxText.toStdString(), common::iUserID, common::index))
			return;

		m_model->removeRow(index.row()); // 删除第2行（索引从0开始）
	}

	for (int row = 0; row < m_model->rowCount(); ++row)
	{
		QStandardItem* item = m_model->item(row, 0); // 获取当前行的第一列项
		if (item)
		{
			item->setText(QString::number(row + 1)); // 更新序号
		}
	}
}
void OneClickLoadDialog::slot_btnOK()
{
	//std::vector<std::string> vecStrSoftware;
	//QString exeDir = QCoreApplication::applicationDirPath();
	for (int row = 0; row < m_model->rowCount(); ++row)
	{
		//QStandardItem* item_software = m_model->item(row, 1); // 获取当前行的第2列项
		//QStandardItem* item_module = m_model->item(row, 2);

		//if (item_module->data(Qt::DisplayRole).toInt() == 1)
		// 获取单元格的小部件
		QWidget *widget = ui->tableViewOneLoad->indexWidget(m_model->index(row, 1));
		if (widget)
		{
			// 将小部件转换为QComboBox
			QComboBox *comboBox = qobject_cast<QComboBox *>(widget);

			// 获取当前选中的文本
			QString currentText = comboBox->currentText();

			if (common::index == 1)
			{
				//if (item_software)
				{
					//emit one_load_tools(item_module->data(Qt::DisplayRole).toInt(), item_software->text());
					emit one_load_tools(common::index, currentText);
				}
			}
			else if (common::index == 2)
			{
				//if (item_software)
				{
					emit one_load_tools(common::index, currentText);
				}
			}
			else if (common::index == 3)
			{
				//if (item_software)
				{
					emit one_load_tools(common::index, currentText);
				}
			}
			else
			{
				//if (item_software)
				{
					emit one_load_tools(common::index, currentText);
				}
			}
		}
	}
	this->close();
}

void OneClickLoadDialog::slot_keep_soft(int index)
{
	//更新数据库
	QComboBox *pcomboBox = (QComboBox*)sender();
	int row = pcomboBox->property("row").toInt();
	QModelIndex ModelIndex = m_model->index(row,0);
	int id = m_model->data(ModelIndex, Qt::UserRole).toInt();
	text = pcomboBox->itemText(index);
	if (!db::databaseDI::Instance().update_software(text.toStdString(), id))
	{
		return;
	}
}
void OneClickLoadDialog::initTableView()
{
	common::delAllModelRow(m_model);
	//if (!m_OneClickLoadDialog->m_model->rowCount())
	{
		std::list<table_one_load_software> listData;
		if (db::databaseDI::Instance().get_load_software(listData))
		{
			for (auto &stData : listData)
			{
				if (stData.userID == common::iUserID && stData.module == common::index)
				{
					int newRowIndex = m_model->rowCount(); // 获取当前行数
					m_model->insertRow(newRowIndex); // 插入新行

					QStandardItem* item = new QStandardItem(QString::number(newRowIndex + 1));
					item->setTextAlignment(Qt::AlignCenter);
					m_model->setItem(newRowIndex, 0, item);
					QModelIndex index = m_model->index(newRowIndex, 0);
					m_model->setData(index,stData.id,Qt::UserRole);

					item->setEditable(false); // 使项不可编辑，以便在编辑模式下显示QComboBox

					// 创建QComboBox并设置模型数据
					QComboBox *comboBox = new QComboBox();
					item->setTextAlignment(Qt::AlignCenter);
					m_model->setItem(newRowIndex, 1, item);
					comboBox->setStyleSheet("QComboBox{font-size: 14px;color: #606580;}");
					comboBox->setStyleSheet("QComboBox QAbstractItemView {selection-background-color: #c3d2f0;}");
					std::map<std::string, table_ip> ipMap;
					if (db::databaseDI::Instance().get_ip_data(ipMap, common::index))
					{
						for (const auto& stTool : ipMap)
						{
							const std::string& software = stTool.first;
							const table_ip& data = stTool.second;
							comboBox->addItem(QString::fromStdString(software));
						}
					}
					comboBox->setCurrentText(QString::fromStdString(stData.projectPath));
					comboBox->setProperty("row",newRowIndex);
					
					connect(comboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &OneClickLoadDialog::slot_keep_soft);

					ui->tableViewOneLoad->setIndexWidget(m_model->index(newRowIndex, 1), comboBox);
				}
			}
		}
	}
}

void OneClickLoadDialog::init_ui()
{
	ui->btnAdd->setStyleSheet("QPushButton { border: 0.5px solid gray;border-radius: 5px;background-color: rgb(240, 240, 240)}");
	ui->btnDel->setStyleSheet("QPushButton { border: 0.5px solid gray;border-radius: 5px;background-color: rgb(240, 240, 240)}");
	ui->btnOk->setStyleSheet("QPushButton { color: white; border: 0.5px solid gray;border-radius: 10px;background-color: rgb(10, 135, 250)}");
}
