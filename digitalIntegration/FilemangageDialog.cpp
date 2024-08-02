#include <QStandardItemModel>
#include <QFileDialog>
#include <QMenu>
#include <QInputDialog>

#include "FilemangageDialog.h"
#include "ui_FilemangageDialog.h"
#include "FtpClientClass.h"
#include "common.h"
#include "Util/UtilTool.h"

FilemangageDialog::FilemangageDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FilemangageDialog)
{
    ui->setupUi(this);
	setWindowTitle(QString::fromLocal8Bit("�ļ�����"));
	//// ��ȡĬ�����ɵĸ��ڵ�
	//QTreeWidgetItem* rootItem = ui->treeWidget->invisibleRootItem();

	//// ɾ�����ڵ�
	//ui->treeWidget->takeTopLevelItem(ui->treeWidget->indexOfTopLevelItem(rootItem));
	// ���ر�����
	ui->treeWidget->setHeaderHidden(true);
    m_FtpClientClass = new FtpClientClass;

	m_modelFiles = new QStandardItemModel();
	m_modelFiles->setColumnCount(4);
	m_modelFiles->setHeaderData(0, Qt::Horizontal, QString::fromLocal8Bit("���"));
	m_modelFiles->setHeaderData(1, Qt::Horizontal, QString::fromLocal8Bit("�ļ���"));
	m_modelFiles->setHeaderData(2, Qt::Horizontal, QString::fromLocal8Bit("����"));
	m_modelFiles->setHeaderData(3, Qt::Horizontal, QString::fromLocal8Bit("����"));

	ui->tableView->setModel(m_modelFiles);
	common::setTableViewBasicConfiguration(ui->tableView);
	ui->tableView->verticalHeader()->setVisible(false);
	ui->tableView->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Fixed);
	ui->tableView->setColumnWidth(0, 80); // �����еĹ̶����
	ui->tableView->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Fixed);
	ui->tableView->setColumnWidth(2, 80); // �����еĹ̶����
	ui->tableView->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Fixed);
	ui->tableView->setColumnWidth(3, 80); // �����еĹ̶����

	 // ����������ʾ
	//ui->tableView->setMouseTracking(true);
	
	getFtpFolderShow();

	// ����˫���¼��Ͳۺ���
	//connect(ui->treeWidget, &QTreeWidget::itemDoubleClicked, this, &FilemangageDialog::slot_treeWidgetItemDoubleClicked);
	connect(ui->treeWidget, &QTreeWidget::itemClicked, this, &FilemangageDialog::slot_treeWidgetItemClicked);
	connect(ui->pushButton, &QPushButton::clicked, this, &FilemangageDialog::slot_btnUploading);
	// ���������Ĳ˵�����ΪCustomContextMenu
	ui->treeWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->treeWidget, &QTreeWidget::customContextMenuRequested, this, &FilemangageDialog::slot_treeWidgteCustomContextMenuRequested);
	
}

FilemangageDialog::~FilemangageDialog()
{
    delete ui;
}

bool FilemangageDialog::getFtpFolderShow()
{
	
	if (m_FtpClientClass->newConnection() == false)
	{
		return false;
	}
	else
	{
		///***********************�ѵ�ǰ�ļ�·����ʾ�����νṹ��*****************************/
		string strRootPath;
		strRootPath = m_FtpClientClass->Gets_CurrentPath();
		// �����ڵ�
		QTreeWidgetItem* pRootItem = new QTreeWidgetItem();
		QString RootPath = QString::fromLocal8Bit(strRootPath.c_str());
		pRootItem->setText(0, RootPath);
		pRootItem->setData(0, Qt::UserRole, RootPath);
		pRootItem->setIcon(0, QIcon(":/image/Dir.png")); // ����ͼ�꣨��ȷ��·����ȷ��:/image/ftpDir.png
		pRootItem->setToolTip(0, RootPath);
		ui->treeWidget->addTopLevelItem(pRootItem);
		

		if (m_FtpClientClass->newConnection())
		{
			m_FtpClientClass->execute_ls();//ִ��ls 

		//������֧��ʾ��ǰ·���ļ�������

			auto vecFolderNames = m_FtpClientClass->Gets_FolderName();
			for (int i = 0; i < vecFolderNames.size(); i++)
			{

				QTreeWidgetItem* pItem = new QTreeWidgetItem();
				QString strText = QString::fromLocal8Bit(vecFolderNames[i].c_str());
				QString strPath = RootPath + "\\" + strText;
				pItem->setText(0, strText);
				pItem->setData(0, Qt::UserRole, strPath);
				pItem->setIcon(0, QIcon(":/image/Dir.png"));
				pItem->setToolTip(0, strText);
				createTreeChildNode(pItem, vecFolderNames[i]);
				pRootItem->addChild(pItem);
			}
		}
		
		

		return 1;
	}
}

void FilemangageDialog::createTreeChildNode( QTreeWidgetItem* pParentItem, const std::string strFolder)
{
	if (!m_FtpClientClass->newConnection())
		return;
	m_FtpClientClass->execute_cdFloder(strFolder);//�������ļ���

	if (!m_FtpClientClass->newConnection())
		return;
	m_FtpClientClass->execute_ls();//ִ��ls 
	
	vector<string> vecFolders = m_FtpClientClass->Gets_FolderName();
	for (int j = 0; j < vecFolders.size(); j++)
	{
		QTreeWidgetItem* pItem = new QTreeWidgetItem();
		QString strText = QString::fromLocal8Bit(vecFolders[j].c_str());
		QString strPath = pParentItem->data(0,Qt::UserRole).toString() + "\\" + strText;
		pItem->setText(0, QString::fromLocal8Bit(vecFolders[j].c_str()));
		pItem->setData(0, Qt::UserRole, strPath);
		pItem->setIcon(0, QIcon(":/image/Dir.png"));
		pItem->setToolTip(0, strText);
		createTreeChildNode(pItem, vecFolders[j]);
		pParentItem->addChild(pItem);
	}
	
	if (!m_FtpClientClass->newConnection())
		return;
	m_FtpClientClass->execute_cdGoback();//������һ��Ŀ¼
}

void FilemangageDialog::slot_treeWidgetItemClicked(QTreeWidgetItem* pTreeItem, int column)
{
	QString strDirPath = pTreeItem->data(column, Qt::UserRole).toString();

	if (!m_FtpClientClass->newConnection())
		return;
	m_FtpClientClass->execute_cdFloder(strDirPath.toLocal8Bit().toStdString());//�������ļ���

	if (!m_FtpClientClass->newConnection())
		return;
	m_FtpClientClass->execute_ls();//ִ��ls 

	auto vecFileData = m_FtpClientClass->Gets_FileName();

	common::delAllModelRow(m_modelFiles);
	for (int i = 0; i < vecFileData.size(); i++)
	{

		int newRowIndex = m_modelFiles->rowCount(); // ��ȡ��ǰ����
		m_modelFiles->insertRow(newRowIndex); // ��������

		QStandardItem* item = new QStandardItem(QString::number(i));
		item->setTextAlignment(Qt::AlignCenter);  // �����ı����ж���
		m_modelFiles->setItem(newRowIndex, 0, item);

	
		QModelIndex index = m_modelFiles->index(newRowIndex, 0);
		m_modelFiles->setData(index, strDirPath, Qt::UserRole);  // �����ļ�����Ŀ¼;


		item = new QStandardItem(QString::fromLocal8Bit(vecFileData[i][0].c_str()));
		item->setTextAlignment(Qt::AlignCenter);  // �����ı����ж���
		m_modelFiles->setItem(newRowIndex, 1, item);

		

		QPushButton* buttonYes = new QPushButton(QString::fromLocal8Bit("����"));
		buttonYes->setObjectName("itemBtnDownload");
		buttonYes->setProperty("row", newRowIndex); // set custom property
		buttonYes->setProperty("column", 2);

		connect(buttonYes, SIGNAL(clicked()), this, SLOT(slot_itemBtnDownload()));
		ui->tableView->setIndexWidget(m_modelFiles->index(newRowIndex, 2), buttonYes);

		QPushButton* buttonNo = new QPushButton(QString::fromLocal8Bit("ɾ��"));
		buttonNo->setObjectName("itemBtnDel");
		buttonNo->setProperty("row", newRowIndex); // set custom property
		buttonNo->setProperty("column", 3);

		connect(buttonNo, SIGNAL(clicked()), this, SLOT(slot_itemBtnDel()));
		ui->tableView->setIndexWidget(m_modelFiles->index(newRowIndex, 3), buttonNo);
	}
	// ע��Ҫ����Ҫ��Ҫ�лظ�Ŀ¼;
}

void FilemangageDialog::slot_itemBtnDownload()
{
	QPushButton* pButton = (QPushButton*)sender();
	int row = pButton->property("row").toInt();
	int column = pButton->property("column").toInt();

	//QModelIndex index = m_modelFiles->index(row, 0);
	auto strFileName = m_modelFiles->item(row,1)->text();

//	QString strDirPath=m_modelFiles->item(row, 0)->data(Qt::UserRole).toString();
	QString directory = QFileDialog::getExistingDirectory(nullptr, QString::fromLocal8Bit("ѡ������Ŀ¼"), QDir::currentPath());

	std::string str = directory.toLocal8Bit().toStdString();
	std::wstring wstr = directory.toStdWString();
	const wchar_t* lpcwstr = wstr.c_str();
	SetCurrentDirectory(lpcwstr);//���õ�ǰĿ¼

	if (!m_FtpClientClass->newConnection())
		return;
	m_FtpClientClass->execute_getFile(strFileName.toLocal8Bit().toStdString());

}

void FilemangageDialog::slot_itemBtnDel()
{

	QPushButton* pButton = (QPushButton*)sender();
	int row = pButton->property("row").toInt();
	int column = pButton->property("column").toInt();

	auto strFileName = m_modelFiles->item(row, 1)->text();
	if (!m_FtpClientClass->newConnection())
		return;
	m_FtpClientClass->execute_Filedelete(strFileName.toLocal8Bit().toStdString());

	m_modelFiles->removeRow(row);
}

void FilemangageDialog::slot_btnUploading()
{
	// �����ļ�ѡ��Ի���
	QString strFilePath = QFileDialog::getOpenFileName(nullptr, QString::fromLocal8Bit("ѡ���ļ�"));

	if (strFilePath.isEmpty())
		return;

	QFileInfo fileInfo(strFilePath);
	QString directoryPath = fileInfo.path();

	
	std::wstring wstr = directoryPath.toStdWString();
	const wchar_t* lpcwstr = wstr.c_str();
	SetCurrentDirectory(lpcwstr);//���õ�ǰĿ¼

	strFilePath.replace("/", "\\\\");
	if (!m_FtpClientClass->newConnection())
		return;
	m_FtpClientClass->execute_putFile(strFilePath.toLocal8Bit().toStdString());

}

void FilemangageDialog::slot_treeWidgteCustomContextMenuRequested(const QPoint& pos)
{
	QTreeWidgetItem* pItem = ui->treeWidget->itemAt(pos);
	if (pItem)
	{
		
		QMenu menu;
		QAction* add = menu.addAction(QString::fromLocal8Bit("�½��ļ���"));
		QAction* del = menu.addAction(QString::fromLocal8Bit("ɾ���ļ���"));
		
		connect(add, &QAction::triggered, [=]()
			{
				QString DirName = QInputDialog::getText(this, QString::fromLocal8Bit("�½�"), QString::fromLocal8Bit("�����½��ļ������ƣ�"));
				if (!DirName.isEmpty())	// �û��������ļ�����
				{
					QString dirPath = pItem->data(0, Qt::UserRole).toString();
					if (m_FtpClientClass->newConnection())
					{
						m_FtpClientClass->execute_cdFloder(dirPath.toLocal8Bit().toStdString());
						if (m_FtpClientClass->newConnection())
						{
							m_FtpClientClass->execute_mkdirFolder(DirName.toLocal8Bit().toStdString());

							QTreeWidgetItem* pNewItem = new QTreeWidgetItem();
							QString strPath = pItem->data(0, Qt::UserRole).toString() + "\\" + DirName;
							pNewItem->setText(0, DirName);
							pNewItem->setData(0, Qt::UserRole, strPath);
							pNewItem->setIcon(0, QIcon(":/image/Dir.png"));
							pNewItem->setToolTip(0, DirName);

							pItem->addChild(pNewItem);
						}
					}	
					//qDebug() << "�ļ����ƣ�" << DirName;
				}
			});

		connect(del, &QAction::triggered, [=]()
			{
				
				QTreeWidgetItem* pParentItem = pItem->parent();
				if (!pParentItem)
					return;
				QString parentDir = pParentItem->data(0, Qt::UserRole).toString();
				QString dirPath = pParentItem->data(0, Qt::UserRole).toString() + "\\" + pItem->text(0);
				dirPath.replace("/", "\\\\");
				parentDir.replace("/", "\\\\");
				/*if (m_FtpClientClass->newConnection())
				{
					m_FtpClientClass->execute_cdFloder(parentDir.toLocal8Bit().toStdString());*/

					/*m_FtpClientClass->newConnection();
					m_FtpClientClass->execute_cdFloder(parentDir.toLocal8Bit().toStdString());*/

					if (m_FtpClientClass->newConnection())
					{
						//m_FtpClientClass->execute_delFolder(pItem->text(0).toLocal8Bit().toStdString());
						m_FtpClientClass->execute_deleteFileList(dirPath.toLocal8Bit().toStdString());
						delete pItem;
					}
				//}
			
				
			
			
			});


		menu.exec(QCursor::pos());


	}

}

void FilemangageDialog::slot_treeWidgetItemDoubleClicked(QTreeWidgetItem* item, int column)
{
	//QString strDirPath = item->data(column, Qt::UserRole).toString();

	//m_FtpClientClass->newConnection();
	//m_FtpClientClass->execute_cdFloder(strDirPath.toLocal8Bit().toStdString());//�������ļ���

	//m_FtpClientClass->newConnection();
	//m_FtpClientClass->execute_ls();//ִ��ls 

	//auto vecFileData = m_FtpClientClass->Gets_FileName();

	//common::delAllModelRow(m_modelFiles);
	//for (int i = 0; i < vecFileData.size(); i++)
	//{
	//
 //       int newRowIndex = m_modelFiles->rowCount(); // ��ȡ��ǰ����
	//	m_modelFiles->insertRow(newRowIndex); // ��������

 //       QStandardItem* item = new QStandardItem(QString::number(i));
 //       item->setTextAlignment(Qt::AlignCenter);  // �����ı����ж���
	//	m_modelFiles->setItem(newRowIndex, 0, item);

 //       item = new QStandardItem(QString::fromLocal8Bit(vecFileData[i][0].c_str()));
 //       item->setTextAlignment(Qt::AlignCenter);  // �����ı����ж���
	//	m_modelFiles->setItem(newRowIndex, 1, item);
 //      
 // 
 //       // add button to the last column
 //       QPushButton* buttonYes = new QPushButton(QString::fromLocal8Bit("����"));
 //       buttonYes->setObjectName("itemBtnDownload");
 //       buttonYes->setProperty("row", newRowIndex); // set custom property
 //       buttonYes->setProperty("column", 2);

 //       connect(buttonYes, SIGNAL(clicked()), this, SLOT(slot_ItemBtnClicked()));
 //       ui->tableView->setIndexWidget(m_modelFiles->index(newRowIndex, 2), buttonYes);

 //       QPushButton* buttonNo = new QPushButton(QString::fromLocal8Bit("ɾ��"));
 //       buttonNo->setObjectName("itemBtnDel");
 //       buttonNo->setProperty("row", newRowIndex); // set custom property
 //       buttonNo->setProperty("column", 3);
	//
	//	connect(buttonNo, SIGNAL(clicked()), this, SLOT(slot_ItemBtnClicked()));
	//	ui->tableView->setIndexWidget(m_modelFiles->index(newRowIndex, 3), buttonNo);
 //   }
	//// ע��Ҫ����Ҫ��Ҫ�лظ�Ŀ¼;
}