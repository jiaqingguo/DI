

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
	m_model->setHeaderData(0, Qt::Horizontal, QString::fromLocal8Bit("序号"));
	m_model->setHeaderData(1, Qt::Horizontal, QString::fromLocal8Bit("软件"));
	//m_model->setHeaderData(2, Qt::Horizontal, QString::fromLocal8Bit("文件路径"));
	//m_model->setHeaderData(3, Qt::Horizontal, QString::fromLocal8Bit("选择"));

	/* QStringList labels = QObject::trUtf8("ID,名字,value,时间,类别").simplified().split(",");
	 model->setHorizontalHeaderLabels(labels);*/
	ui->tableView->setModel(m_model);
	ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);   // 选择整行
	ui->tableView->verticalHeader()->setDefaultSectionSize(28);
	ui->tableView->verticalHeader()->setVisible(false);

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
}

OneClickLoadDialog::~OneClickLoadDialog()
{
	delete ui;
}

void OneClickLoadDialog::slot_btnAdd()
{
	int newRowIndex = m_model->rowCount(); // 获取当前行数
	m_model->insertRow(newRowIndex); // 插入新行

	QStandardItem* item = new QStandardItem(QString::number(newRowIndex + 1));
	m_model->setItem(newRowIndex, 0, item);
	QModelIndex index = m_model->index(newRowIndex, 0);
	// item->setTextAlignment(Qt::AlignCenter);  // 设置文本居中对齐
	//m_model->setData(index, stIp.id, Qt::UserRole);  // 设置id;

	m_model->setItem(newRowIndex, 1, new QStandardItem(QString::fromStdString("")));
}
void OneClickLoadDialog::slot_btnDel()
{
	QModelIndex index = ui->tableView->currentIndex();
	if (index.isValid())
	{
		//获取要删除的单元格
		QVariant data = m_model->data(index, Qt::DisplayRole);
		// 打印或者处理数据
		//qDebug() << "要删除的数据是：" << data.toString();
		if (!db::databaseDI::Instance().del_load_software(data.toString().toStdString(), common::iUserID))
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
	QString exeDir = QCoreApplication::applicationDirPath();
	for (int row = 0; row < m_model->rowCount(); ++row)
	{
		QStandardItem* item = m_model->item(row, 1); // 获取当前行的第2列项
		if (item)
		{
			QString strDspPath = exeDir + "/dsp/" + QString::number(common::iLoginNum) + "/" + item->text() + ".bsp";

			//启动bsp的嵌入
			int a = 1;

			//插入数据库
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
