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
	ui->groupBox->hide();
	//ui->allocationAllocation->setChecked(true);

	ui->lineEditTabName->setPlaceholderText(GBK_STRING("默认值"));
	ui->lineEditTabName->setReadOnly(false);


	m_model = new QStandardItemModel();
	m_model->setColumnCount(3);
	m_model->setHeaderData(0, Qt::Horizontal, QString::fromLocal8Bit("序号"));
	m_model->setHeaderData(1, Qt::Horizontal, QString::fromLocal8Bit("ip列表"));
	m_model->setHeaderData(2, Qt::Horizontal, QString::fromLocal8Bit("占用状态"));
	//m_model->setHeaderData(3, Qt::Horizontal, QString::fromLocal8Bit("操作"));
	//m_model->setHeaderData(3, Qt::Horizontal, QString::fromLocal8Bit("主机名"));
	//m_model->setHeaderData(4, Qt::Horizontal, QString::fromLocal8Bit("用户名"));
	ui->tableViewIpSet->setModel(m_model);
	common::setTableViewBasicConfiguration(ui->tableViewIpSet);



	connect(ui->btnAdd, SIGNAL(clicked()), this, SLOT(slot_btnAddClicked()));


	// 2.初始化界面数据;

	//2.1 combox 软件数据;

	ui->comboBoxToolNames->clear();
	std::map<std::string, table_ip> ipMap;
	if (db::databaseDI::Instance().get_ip_data(ipMap, m_iModule, common::iLoginNum))
	{
		//ui->comboBoxToolNames->addItem("");
		ui->comboBoxToolNames->clear();
		for (const auto& stTool : ipMap)
		{
			const std::string& software = stTool.first;
			const table_ip& data = stTool.second;
			//ui->comboBoxToolNames->addItem(QString::fromStdString(software));

			ui->comboBoxToolNames->addItem(QString::fromStdString(software), QVariant(QString::fromStdString(data.toolPath))); // 添加 "Item 3"，设置数据为 3
		}
	}
	if (m_iModule != 1)
	{
		ui->label_4->setHidden(true);
		ui->lineEditIP->setHidden(true);
	}
	connect(ui->comboBoxToolNames, &QComboBox::currentTextChanged, this,&AddToolDialog::slot_display_lineEditIP);
	// 手动触发槽函数以显示初始 IP 地址
	if (ui->comboBoxToolNames->count() > 0) 
	{
		slot_display_lineEditIP(ui->comboBoxToolNames->itemText(0));
	}

	common::delAllModelRow(m_model);
	std::list<table_ip_configure> listData;

	if (db::databaseDI::Instance().get_all_ip(listData))
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

			//item = new QStandardItem(QString::fromStdString(stData.host));
			//item->setTextAlignment(Qt::AlignCenter);  // 设置文本居中对齐
			//m_model->setItem(newRowIndex, 3, item);

			//item = new QStandardItem(QString::fromStdString(stData.username));
			//item->setTextAlignment(Qt::AlignCenter);  // 设置文本居中对齐
			//m_model->setItem(newRowIndex, 4, item);


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
			//if (stData.used == 0)
			{
				item = new QStandardItem(QString::fromLocal8Bit("未占用"));
				item->setTextAlignment(Qt::AlignCenter);  // 设置文本居中对齐
				m_model->setItem(newRowIndex, 2, item);
				connect(checkBox, &QCheckBox::clicked, this, &AddToolDialog::slot_ipCheckBoxClicked);
			}
			//else
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

void AddToolDialog::getToolData(QString& tabName, QString& toolName, QString& toolPath , int& model, int& iDisplayMode)
{
	tabName = ui->lineEditTabName->text();
	if (tabName.isEmpty())
	{
		tabName = ui->lineEditTabName->placeholderText();
	}
	toolName = ui->comboBoxToolNames->currentText();
	toolPath = ui->comboBoxToolNames->currentData(Qt::UserRole).toString();
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

void AddToolDialog::slot_display_lineEditIP(QString text)
{
	if (m_iModule == 1)
	{
		table_ip stipToolData;
		if (db::databaseDI::Instance().get_ip_by_software(stipToolData, text.toStdString(), common::iLoginNum, m_iModule))
		{
			ui->lineEditIP->setText(stipToolData.ip.c_str());
		}
		else
		{
			ui->lineEditIP->clear(); // 如果没有找到 IP，清除 QLineEdit
		}
	}
	//else
	//{
	//	int i = common::iSoftStartHostNum % 3;
	//	if (common::setHostData.size() >= i)
	//	{
	//		auto it = std::next(common::setHostData.begin(), i); // 移动到第i个元素
	//		std::string strValue = it->ip;
	//		ui->lineEditIP->setText(QString::fromStdString(strValue));
	//		common::iSoftStartHostNum++;
	//	}
	//}
}

