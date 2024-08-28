#include <QStandardItemModel>
#include <QFileDialog>
#include <QMovie>
#include <QMenu>
#include <QInputDialog>
#include <QLabel>
#include <QToolButton>
#include <QMessageBox>
#include <QDateTime>
#include <QMenu>

#include <QDebug>

#include "FilemangageDialog.h"
#include "ui_FilemangageDialog.h"
#include "FtpClientClass.h"
#include "common.h"
#include "Util/UtilTool.h"
#include "GifDialog.h"
#include "mainwindow.h"
#include "databaseDI.h"
#include "globel.h"

FilemangageDialog::FilemangageDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FilemangageDialog)
{
    ui->setupUi(this);
	setWindowTitle(QString::fromLocal8Bit("�ļ�����"));
	m_GifDialog = new GifDialog;
	m_msgBox = new QMessageBox;
	// ������Ϣ��ı���
	m_msgBox->setWindowTitle("Custom Message Box");

	// ������Ϣ����ı�����
	m_msgBox->setText("This is a custom message box with a custom icon.");

	// �����Զ���ͼ��
	QPixmap customIcon(":/image/load.png"); // �滻Ϊ���ͼƬ·��
	m_msgBox->setIconPixmap(customIcon);

	// ������Ϣ��Ĵ�С
	m_msgBox->resize(300, 200);

	// ͨ������Qt::WindowFlagsȥ�����ϽǵĹرհ�ť
	m_msgBox->setWindowFlags(m_msgBox->windowFlags() & ~Qt::WindowCloseButtonHint & Qt::CustomizeWindowHint & Qt::WindowTitleHint & Qt::WindowStaysOnTopHint);
	//m_GifDialog->show();
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

	ui->tableViewFile->setModel(m_modelFiles);
	common::setTableViewBasicConfiguration(ui->tableViewFile);
	ui->tableViewFile->verticalHeader()->setVisible(false);
	ui->tableViewFile->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Fixed);
	ui->tableViewFile->setColumnWidth(0, 80); // �����еĹ̶����
	ui->tableViewFile->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Fixed);
	ui->tableViewFile->setColumnWidth(2, 80); // �����еĹ̶����
	ui->tableViewFile->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Fixed);
	ui->tableViewFile->setColumnWidth(3, 80); // �����еĹ̶����

	 // ����������ʾ
	//ui->tableViewFile->setMouseTracking(true);
	
	getFtpFolderShow();

	// ����˫���¼��Ͳۺ���
	//connect(ui->treeWidget, &QTreeWidget::itemDoubleClicked, this, &FilemangageDialog::slot_treeWidgetItemDoubleClicked);
	connect(ui->treeWidget, &QTreeWidget::itemClicked, this, &FilemangageDialog::slot_treeWidgetItemClicked);
	connect(ui->pushButton, &QPushButton::clicked, this, &FilemangageDialog::slot_btnUploading); 
	connect(ui->btnUploadDir, &QPushButton::clicked, this, &FilemangageDialog::slot_btnUploadingDir);
	// ���������Ĳ˵�����ΪCustomContextMenu
	ui->treeWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->treeWidget, &QTreeWidget::customContextMenuRequested, this, &FilemangageDialog::slot_treeWidgteCustomContextMenuRequested);
	
	// ���� itemChanged �źŵ��Զ����
	//connect(m_modelFiles, &QStandardItemModel::itemChanged, this, &FilemangageDialog::slot_tableViewFilesItemChanged);
	
}

FilemangageDialog::~FilemangageDialog()
{
    delete ui;
}

void FilemangageDialog::flushFtpDirShow()
{
	
	ui->treeWidget->clear();

	string strRootPath;
	
	if (!m_FtpClientClass->Gets_CurrentPath(strRootPath))
	{
		return;
	}
	// �����ڵ�
	m_pRootItem = new QTreeWidgetItem();
	QString RootPath = QString::fromLocal8Bit(strRootPath.c_str());
	m_pRootItem->setText(0, RootPath);
	m_pRootItem->setData(0, Qt::UserRole, RootPath);
	m_pRootItem->setIcon(0, QIcon(":/image/Dir.png")); // ����ͼ�꣨��ȷ��·����ȷ��:/image/ftpDir.png
	m_pRootItem->setToolTip(0, RootPath);
	ui->treeWidget->addTopLevelItem(m_pRootItem);


	//if (m_FtpClientClass->newConnection())
	{
		m_FtpClientClass->execute_ls(strRootPath);//ִ��ls 

	//������֧��ʾ��ǰ·���ļ�������

		auto vecFolderNames = m_FtpClientClass->Gets_FolderName();
		for (int i = 0; i < vecFolderNames.size(); i++)
		{
			QTreeWidgetItem* pItem = new QTreeWidgetItem();
			QString strText = QString::fromLocal8Bit(vecFolderNames[i][0].c_str());
			
			QString strPath = RootPath + "\\" + strText;
			pItem->setText(0, strText);
			pItem->setData(0, Qt::UserRole, strPath);
			
			pItem->setData(0, Qt::UserRole + 1, QString::fromLocal8Bit(vecFolderNames[i][1].c_str()));
			pItem->setIcon(0, QIcon(":/image/Dir.png"));
			pItem->setToolTip(0, strText);

			std::string strDirPath = strRootPath + "\\" + vecFolderNames[i][0];
			createTreeChildNode(pItem, strDirPath);
			//createTreeChildNode(pItem, vecFolderNames[i]);
			m_pRootItem->addChild(pItem);
		}
	}
	m_pRootItem->setExpanded(true);
	getAdministratorDirs();
}

void FilemangageDialog::initTableViewDownload()
{
	if (common::bAdministrator) // ����Ա;
	{
		// ���صڶ�����ǩҳ
		ui->tabWidget->removeTab(1); // �Ƴ� Tab 2
		m_strDolwnloadText = QString::fromLocal8Bit("����");
	}
	else
	{
		m_modelDownload = new QStandardItemModel();
		m_modelDownload->setColumnCount(9);
		m_modelDownload->setHeaderData(0, Qt::Horizontal, QString::fromLocal8Bit("���"));
		m_modelDownload->setHeaderData(1, Qt::Horizontal, QString::fromLocal8Bit("������"));
		m_modelDownload->setHeaderData(2, Qt::Horizontal, QString::fromLocal8Bit("���ڲ���"));
		m_modelDownload->setHeaderData(3, Qt::Horizontal, QString::fromLocal8Bit("����ʱ��"));
		m_modelDownload->setHeaderData(4, Qt::Horizontal, QString::fromLocal8Bit("�ļ���"));
		m_modelDownload->setHeaderData(5, Qt::Horizontal, QString::fromLocal8Bit("�ļ�����"));
		m_modelDownload->setHeaderData(6, Qt::Horizontal, QString::fromLocal8Bit("����ʱ��"));
		m_modelDownload->setHeaderData(7, Qt::Horizontal, QString::fromLocal8Bit("״̬"));
		m_modelDownload->setHeaderData(8, Qt::Horizontal, QString::fromLocal8Bit("����"));
		ui->tableViewDownload->setModel(m_modelDownload);
		common::setTableViewBasicConfiguration(ui->tableViewDownload);

		ui->tableViewDownload->verticalHeader()->setVisible(false);

		flushTableViewDownload();
	}

	m_pMenu = new QMenu;

	m_actionMkdir= m_pMenu->addAction(QString::fromLocal8Bit("�½��ļ���"));
	m_actionDel = m_pMenu->addAction(QString::fromLocal8Bit("ɾ���ļ���"));
	m_actionDownload = m_pMenu->addAction(m_strDolwnloadText);
	m_actionRename = m_pMenu->addAction(QString::fromLocal8Bit("������"));
	connect(m_actionMkdir, &QAction::triggered, this, &FilemangageDialog::slot_actionMkdir);
	connect(m_actionDel, &QAction::triggered, this, &FilemangageDialog::slot_actionDelDir);
	connect(m_actionDownload, &QAction::triggered, this, &FilemangageDialog::slot_actionDownload);
	connect(m_actionRename, &QAction::triggered, this, &FilemangageDialog::slot_actioxnRename);
	
}

void FilemangageDialog::flushTableViewDownload()
{
	common::delAllModelRow(m_modelDownload);

	std::list<table_DownloadApproval> listDataApproval;
	db::databaseDI::Instance().get_download_approval_list_by_userID(listDataApproval, common::iUserID);
	for (auto& stData : listDataApproval)
	{

		table_user stUserData;
		db::databaseDI::Instance().get_user_by_condition(stUserData, stData.userID);
		stData.userName = stUserData.name;
		stData.department = stUserData.department;
	}
	int i = 0;
	for (auto& stData : listDataApproval)
	{

		/* table_user stUserData;
		 db::databaseDI::Instance().get_user_by_condition(stUserData,stData.userID);
		 stData.userName = stUserData.name;
		 stData.department = stUserData.department;*/

		int newRowIndex = m_modelDownload->rowCount(); // ��ȡ��ǰ����
		m_modelDownload->insertRow(newRowIndex); // ��������

		QStandardItem* item = new QStandardItem(QString::number(i + 1));
		item->setTextAlignment(Qt::AlignCenter);  // �����ı����ж���
	
		//item->setData(QString::fromStdString(stData.name), Qt::ToolTipRole);
		m_modelDownload->setItem(newRowIndex, 0, item);

		QModelIndex index = m_modelDownload->index(newRowIndex, 0);
		m_modelDownload->setData(index, stData.id, Qt::UserRole);  // ����id;
		//m_modelDownload->setData(index,QString::fromLocal8Bit(stData.filePath.c_str(), Qt::UserRole));
		//  item->setText(QString::fromStdString(stData.name));

		item = new QStandardItem(QString::fromStdString(stData.userName));
		item->setTextAlignment(Qt::AlignCenter);  // �����ı����ж���
		m_modelDownload->setItem(newRowIndex, 1, item);

		item = new QStandardItem(QString::fromStdString(stData.department));
		item->setTextAlignment(Qt::AlignCenter);  // �����ı����ж���
		m_modelDownload->setItem(newRowIndex, 2, item);

		item = new QStandardItem(QDateTime::fromTime_t(stData.applicationTime).toString("yyyy/MM/dd HH:mm:ss"));
		item->setTextAlignment(Qt::AlignCenter);  // �����ı����ж���
		m_modelDownload->setItem(newRowIndex, 3, item);


		QString filePath = QString::fromLocal8Bit(stData.filePath.c_str());
		QFileInfo fileInfo1(filePath);

		item = new QStandardItem(fileInfo1.fileName());
		item->setTextAlignment(Qt::AlignCenter);  // �����ı����ж���

		m_modelDownload->setItem(newRowIndex, 4, item);
		QModelIndex indexFilePath = m_modelDownload->index(newRowIndex, 4);
		m_modelDownload->setData(indexFilePath, filePath, Qt::UserRole);


		item = new QStandardItem(QString::fromStdString(stData.fileType));
		item->setTextAlignment(Qt::AlignCenter);  // �����ı����ж���
		m_modelDownload->setItem(newRowIndex, 5, item);

		item = new QStandardItem(QDateTime::fromTime_t(stData.fileTime).toString("yyyy/MM/dd HH:mm:ss"));
		item->setTextAlignment(Qt::AlignCenter);  // �����ı����ж���
		m_modelDownload->setItem(newRowIndex, 6, item);




		// add button to the last column
		QPushButton* buttonD = new QPushButton(QString::fromLocal8Bit("����"));
		buttonD->setObjectName("itemBtnYes");
		buttonD->setProperty("row", newRowIndex); // set custom property
		buttonD->setProperty("column", 8);
		buttonD->setProperty("approval", 1);
		connect(buttonD, SIGNAL(clicked()), this, SLOT(slot_ItemDownloadBtnClicked()));
		ui->tableViewDownload->setIndexWidget(m_modelDownload->index(newRowIndex, 8), buttonD);
		//buttonD->setEnabled(false);


		if (stData.status == 1)
		{
			item = new QStandardItem(QString::fromLocal8Bit("��ͨ��"));
			item->setForeground(QBrush(QColor(Qt::green)));
			item->setTextAlignment(Qt::AlignCenter);  // �����ı����ж���
			m_modelDownload->setItem(newRowIndex, 7, item);
			buttonD->setEnabled(true);

		}
		else if (stData.status == 0)
		{
			item = new QStandardItem(QString::fromLocal8Bit("�����"));
			item->setForeground(QBrush(QColor("#33C1FF")));
			item->setTextAlignment(Qt::AlignCenter);  // �����ı����ж���
			m_modelDownload->setItem(newRowIndex, 7, item);
			buttonD->setEnabled(false);
		}
		else if (stData.status == 2)
		{
			item = new QStandardItem(QString::fromLocal8Bit("�Ѳ���"));
			item->setTextAlignment(Qt::AlignCenter);  // �����ı����ж���
			item->setForeground(QBrush(QColor(Qt::red)));
			m_modelDownload->setItem(newRowIndex, 7, item);
			buttonD->setEnabled(true);

		}
		i++;
	}
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

	
		bool ret = m_FtpClientClass->Gets_CurrentPath(strRootPath);
		if (!ret)
		{
			return false;
		}
			
		// �����ڵ�
		m_pRootItem = new QTreeWidgetItem();
		QString RootPath = QString::fromLocal8Bit(strRootPath.c_str());
		m_pRootItem->setText(0, RootPath);
		m_pRootItem->setData(0, Qt::UserRole, RootPath);
		m_pRootItem->setIcon(0, QIcon(":/image/Dir.png")); // ����ͼ�꣨��ȷ��·����ȷ��:/image/ftpDir.png
		m_pRootItem->setToolTip(0, RootPath);
		ui->treeWidget->addTopLevelItem(m_pRootItem);
		

		//if (m_FtpClientClass->newConnection())
		{
			m_FtpClientClass->execute_ls(strRootPath);//ִ��ls 

		//������֧��ʾ��ǰ·���ļ�������

			auto vecFolderNames = m_FtpClientClass->Gets_FolderName();
			for (int i = 0; i < vecFolderNames.size(); i++)
			{

				QTreeWidgetItem* pItem = new QTreeWidgetItem();
				QString strText = QString::fromLocal8Bit(vecFolderNames[i][0].c_str());
				QString strPath = RootPath + "\\" + strText;
				pItem->setText(0, strText);
				pItem->setData(0, Qt::UserRole, strPath);
				pItem->setData(0, Qt::UserRole+1, QString::fromLocal8Bit(vecFolderNames[i][1].c_str()));
				pItem->setIcon(0, QIcon(":/image/Dir.png"));
				pItem->setToolTip(0, strText);

				std::string strDirPath = strRootPath + "\\" + vecFolderNames[i][0];
				createTreeChildNode(pItem, strDirPath);
				//createTreeChildNode(pItem, vecFolderNames[i]);
				m_pRootItem->addChild(pItem);
			}
		}
		
	}
	getAdministratorDirs();
	return true;
}

void FilemangageDialog::createTreeChildNode( QTreeWidgetItem* pParentItem, const std::string strFolder)
{
	
	m_FtpClientClass->execute_ls(strFolder);//ִ��ls 
	
	auto vecFolders = m_FtpClientClass->Gets_FolderName();
	for (int j = 0; j < vecFolders.size(); j++)
	{
		QTreeWidgetItem* pItem = new QTreeWidgetItem();
		QString strText = QString::fromLocal8Bit(vecFolders[j][0].c_str());
		QString strPath = pParentItem->data(0,Qt::UserRole).toString() + "\\" + strText;
		pItem->setText(0, QString::fromLocal8Bit(vecFolders[j][0].c_str()));
		pItem->setData(0, Qt::UserRole, strPath);
		pItem->setData(0, Qt::UserRole+1, QString::fromLocal8Bit(vecFolders[j][1].c_str()));
		pItem->setIcon(0, QIcon(":/image/Dir.png"));
		pItem->setToolTip(0, strText);
		std::string strDirPath = strFolder + "\\" + vecFolders[j][0];
		createTreeChildNode(pItem, strDirPath);
		//createTreeChildNode(pItem, vecFolders[j]);
		pParentItem->addChild(pItem);
	}
	
	return;
}

int FilemangageDialog::downloadFtpDir(const QString& strDirPath, const QString& newDirPath)
{
	int ret=m_FtpClientClass->execute_ls(strDirPath.toLocal8Bit().toStdString());//ִ��ls 

	if (ret !=1)
	{
		return ret;
	}
	QDir dir(newDirPath);
	if (!dir.exists())
	{
		if (!dir.mkdir(newDirPath))
		{
			//qDebug() << "�ļ��д���ʧ�ܣ�";
			return -3;
		}
	}
	
	auto vecFileData = m_FtpClientClass->Gets_FileName();
	auto vecFtpDirData = m_FtpClientClass->Gets_FolderName();

	for (int i = 0; i < vecFileData.size(); i++)
	{
		QString ftpFilePath = strDirPath + "\\\\" + QString::fromLocal8Bit(vecFileData[i][0].c_str());
		QString newFilePath = newDirPath + "\\\\" + QString::fromLocal8Bit(vecFileData[i][0].c_str());
	/*	if (!m_FtpClientClass->newConnection())
			return;*/
		
		m_FtpClientClass->execute_getFile(ftpFilePath.toLocal8Bit().toStdString(), newFilePath.toLocal8Bit().toStdString());
	}

	
	for (int j = 0; j < vecFtpDirData.size(); j++)
	{
		QString ftpDirPath = strDirPath + "\\\\" + QString::fromLocal8Bit(vecFtpDirData[j][0].c_str());
		QString newChildDirPath = newDirPath + "\\\\" + QString::fromLocal8Bit(vecFtpDirData[j][0].c_str());
		downloadFtpDir(ftpDirPath, newChildDirPath);
	}
	
	//emit signal_downloadFinsh();
}

bool FilemangageDialog::IsAdministratorDir(const QTreeWidgetItem* pItem)
{
	if (pItem->text(0) == m_AdministratorDir)
	{
		return true;
	}
	if (pItem->parent() != nullptr)
	{
		IsAdministratorDir(pItem->parent());
	}
	return false;
}

void FilemangageDialog::getAdministratorDirs()
{
	int iAdminDir = 1;
//	m_vecAdministratorDir.clear();
	QTreeWidgetItem* pAdminItem = nullptr;
	// �ݹ���ڵ�������ӽڵ�;
	for (int i = 0; i < m_pRootItem->childCount(); ++i)
	{
		QString  strPath = m_pRootItem->child(i)->data(0, Qt::UserRole).toString();
		if (strPath == m_AdministratorDir)
		{
			pAdminItem = m_pRootItem->child(i);
			pAdminItem->setData(0, Qt::UserRole + 1, iAdminDir);
			//m_vecAdministratorDir.insert(strPath);
			break;
		}

	}
	if (pAdminItem == nullptr)
		return;
	//QString  strPath = pAdminItem->data(0, Qt::UserRole).toString();
	
	// �ݹ���������ӽڵ�
	for (int i = 0; i < pAdminItem->childCount(); ++i)
	{
		traverseAdministratorChildDir(pAdminItem->child(i));
	}
	
	
}

void FilemangageDialog::traverseAdministratorChildDir( QTreeWidgetItem* pItem)
{
	int iAdminDir = 1;
	//QString  strPath = pItem->data(0, Qt::UserRole).toString();
	//m_vecAdministratorDir.insert(strPath);
	pItem->setData(0, Qt::UserRole + 1, iAdminDir);
	for (int i = 0; i < pItem->childCount(); ++i)
	{
		traverseAdministratorChildDir(pItem->child(i));
	}
}

void FilemangageDialog::traverseUploadDir(const QString& strUploadDir, const QString& strDstDir)
{
	
	m_FtpClientClass->execute_mkdirFolder(strDstDir.toLocal8Bit().toStdString());
	QDir dir(strUploadDir);

	// �г������ļ���Ŀ¼
//	QStringList filters;
	//filters << "*"; // �ɸ�����Ҫ���ù����������� "*.txt" ֻ��ȡ�ı��ļ�
	//dir.setNameFilters(filters);
	dir.setFilter(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot); // �ų� . �� ..

	QFileInfoList entries = dir.entryInfoList();
	// �洢�ļ���Ŀ¼
	//QList<QFileInfo> files;
	//QList<QFileInfo> directories;

	// ������Ŀ������
	foreach(const QFileInfo & entry, entries) 
	{
		/*if (entry.isDir()) 
		{
			directories.append(entry);
		}
		else if (entry.isFile()) {
			files.append(entry);
		}*/

		if (entry.isDir()) 
		{
			QString strFtpNewPath = strDstDir + "\\" + entry.fileName();
			//m_FtpClientClass->execute_mkdirFolder(strFtpNewPath.toLocal8Bit().toStdString());

			QString strLocalDir = entry.absoluteFilePath();
			traverseUploadDir(strLocalDir, strFtpNewPath);
			//qDebug() << "Ŀ¼:" << entry.filePath() << "����ʱ��:" << creationTime;
		}
		else if (entry.isFile()) {

			QString strFtpNewPath = strDstDir + "\\" + entry.fileName();
			QString strLocalFilePath = entry.absoluteFilePath();
			m_FtpClientClass->execute_putFile(strLocalFilePath.toLocal8Bit().toStdString(), strFtpNewPath.toLocal8Bit().toStdString());
			//qDebug() << "�ļ�:" << entry.filePath() << "��С:" << entry.size() << "�ֽ�" << "����ʱ��:" << creationTime;
		}
	}

}

void FilemangageDialog::slot_treeWidgetItemClicked(QTreeWidgetItem* pTreeItem, int column)
{
	QString strDirPath = pTreeItem->data(column, Qt::UserRole).toString();

	
	m_FtpClientClass->execute_ls(strDirPath.toLocal8Bit().toStdString());//ִ��ls 

	auto vecFileData = m_FtpClientClass->Gets_FileName();

	common::delAllModelRow(m_modelFiles);
	for (int i = 0; i < vecFileData.size(); i++)
	{
		int j = i + 1;
		int newRowIndex = m_modelFiles->rowCount(); // ��ȡ��ǰ����
		m_modelFiles->insertRow(newRowIndex); // ��������

		QStandardItem* item = new QStandardItem(QString::number(j));
		item->setTextAlignment(Qt::AlignCenter);  // �����ı����ж���
		item->setCheckable(true); // ����Ϊ�ɹ�ѡ
		item->setCheckState(Qt::Unchecked); // ��ʼΪ����ѡ;
		m_modelFiles->setItem(newRowIndex, 0, item);

	
		QModelIndex index = m_modelFiles->index(newRowIndex, 0);
		m_modelFiles->setData(index, strDirPath, Qt::UserRole);  // �����ļ�����Ŀ¼;
		m_modelFiles->setData(index, QString::fromLocal8Bit(vecFileData[i][1].c_str()), Qt::UserRole+1);  //�����ļ�ʱ�� ;

		item = new QStandardItem(QString::fromLocal8Bit(vecFileData[i][0].c_str()));
		item->setTextAlignment(Qt::AlignCenter);  // �����ı����ж���
		m_modelFiles->setItem(newRowIndex, 1, item);

		

		QPushButton* buttonYes = new QPushButton(m_strDolwnloadText);
		buttonYes->setObjectName("itemBtnDownload");
		buttonYes->setProperty("row", newRowIndex); // set custom property
		buttonYes->setProperty("column", 2);

		connect(buttonYes, SIGNAL(clicked()), this, SLOT(slot_itemBtnDownload()));
		ui->tableViewFile->setIndexWidget(m_modelFiles->index(newRowIndex, 2), buttonYes);

		QPushButton* buttonNo = new QPushButton(QString::fromLocal8Bit("ɾ��"));
		buttonNo->setObjectName("itemBtnDel");
		buttonNo->setProperty("row", newRowIndex); // set custom property
		buttonNo->setProperty("column", 3);

		connect(buttonNo, SIGNAL(clicked()), this, SLOT(slot_itemBtnDel()));
		ui->tableViewFile->setIndexWidget(m_modelFiles->index(newRowIndex, 3), buttonNo);
	}
	// ע��Ҫ����Ҫ��Ҫ�лظ�Ŀ¼;
}

void FilemangageDialog::slot_itemBtnDownload()
{
	int row = ui->tableViewFile->currentIndex().row();

	auto strFileName = m_modelFiles->item(row,1)->text();
	QString dirPath = ui->treeWidget->currentItem()->data(0, Qt::UserRole).toString();
	QString fileAllPath = dirPath + "\\" + strFileName;
	//fileAllPath.replace("/", "\\\\");

	fileAllPath.replace("\\", "\\\\");
	if (!common::bAdministrator) // ��ͨ�û�
	{
		table_DownloadApproval stDownloadApproval;
		stDownloadApproval.userID = common::iUserID;
		stDownloadApproval.filePath = fileAllPath.toLocal8Bit().toStdString();
		stDownloadApproval.fileType = strFileName.mid(strFileName.lastIndexOf(".") + 1).toStdString();  // ���ص�֮��Ĳ���

		stDownloadApproval.fileTime= common::string_to_datetime(m_modelFiles->item(row, 0)->data(Qt::UserRole + 1).toString().toStdString());
		stDownloadApproval.applicationTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
		stDownloadApproval.status = 0;
		if (db::databaseDI::Instance().add_download_approval_info(stDownloadApproval))
		{
			flushTableViewDownload();
		}
	}
	else
	{
		//	QString strDirPath=m_modelFiles->item(row, 0)->data(Qt::UserRole).toString();
		QString directory = QFileDialog::getExistingDirectory(nullptr, QString::fromLocal8Bit("ѡ������Ŀ¼"), QDir::currentPath());
		if (directory.isEmpty())
		{
			return;
		}

		std::string str = directory.toLocal8Bit().toStdString();
		std::wstring wstr = directory.toStdWString();
		const wchar_t* lpcwstr = wstr.c_str();
		SetCurrentDirectory(lpcwstr);//���õ�ǰĿ¼

		QString newFilePath = directory + "\\" + strFileName;
		newFilePath.replace("/", "\\\\");
		m_FtpClientClass->execute_getFile(fileAllPath.toLocal8Bit().toStdString(), newFilePath.toLocal8Bit().toStdString());
	}
}

void FilemangageDialog::slot_itemBtnDel()
{
	int row = ui->tableViewFile->currentIndex().row();
	

	if (m_modelFiles->item(row, 1) != nullptr)
	{
		auto strFileName = m_modelFiles->item(row, 1)->text();
		//if (!m_FtpClientClass->newConnection())
		//	return;
		QString dirPath = ui->treeWidget->currentItem()->data(0, Qt::UserRole).toString();
		QString delFilePath = dirPath + "\\" + strFileName;
		m_FtpClientClass->execute_Filedelete(delFilePath.toLocal8Bit().toStdString());

		m_modelFiles->removeRow(row);
	}
	
}

void FilemangageDialog::slot_btnUploading()
{
	if (ui->treeWidget->currentItem() == nullptr)
	{
		return;
	}
	
	// �����ļ�ѡ��Ի���
	QString strFilePath = QFileDialog::getOpenFileName(nullptr, QString::fromLocal8Bit("ѡ���ϴ��ļ�"));

	if (strFilePath.isEmpty())
		return;

	QFileInfo fileInfo(strFilePath);
	QString directoryPath = fileInfo.path();

	
	std::wstring wstr = directoryPath.toStdWString();
	const wchar_t* lpcwstr = wstr.c_str();
	SetCurrentDirectory(lpcwstr);//���õ�ǰĿ¼

	//strFilePath.replace("/", "\\\\");
	/*if (!m_FtpClientClass->newConnection())
		return;*/
	//directoryPath.replace()
	directoryPath.replace("/", "\\\\");

	QString dirPath = ui->treeWidget->currentItem()->data(0, Qt::UserRole).toString();
	QString UploadingPath = dirPath + "\\" + fileInfo.fileName();

	m_FtpClientClass->execute_putFile(fileInfo.absoluteFilePath().toLocal8Bit().toStdString(), UploadingPath.toLocal8Bit().toStdString());
	slot_treeWidgetItemClicked(ui->treeWidget->currentItem(), 0);
}

void FilemangageDialog::slot_btnUploadingDir()
{
	QString directory = QFileDialog::getExistingDirectory(
		nullptr,               // ������
		QString::fromLocal8Bit("ѡ��һ��Ŀ¼"),      // �Ի������
		"",                   // Ĭ��Ŀ¼
		QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks // ѡ��
	);

	if (directory.isEmpty()) {
		return;
	}
	
	
	QTreeWidgetItem* pItem = ui->treeWidget->currentItem();
	if (pItem == nullptr)
		return;
	QFileInfo fileInfo(directory);
	QString strDstDir = pItem->data(0, Qt::UserRole).toString()+ "\\"+fileInfo.fileName();
	traverseUploadDir(directory, strDstDir);
	flushFtpDirShow();
}

void FilemangageDialog::slot_treeWidgteCustomContextMenuRequested(const QPoint& pos)
{
	QTreeWidgetItem* pItem = ui->treeWidget->itemAt(pos);
	if (pItem == nullptr)
		return;

	if (!common::bAdministrator)  // �ǹ���Ա;
	{
		if (pItem->data(0, Qt::UserRole + 1).toInt()==1)
		{
			return;
		}
	}


	/*if (pItem == m_pRootItem)
	{
		m_actionDownload->setEnabled(false);
		m_actionRename->setEnabled(false);
		m_actionDel->setEnabled(false);
	}
	else 
	{
		m_actionDownload->setEnabled(true);
		m_actionRename->setEnabled(true);
		m_actionDel->setEnabled(true);
	}*/

	m_pMenu->exec(QCursor::pos());
	/*if (pItem)
	{*/
		//
		//QMenu menu;
		//QAction* add = menu.addAction(QString::fromLocal8Bit("�½��ļ���"));
		//QAction* del = menu.addAction(QString::fromLocal8Bit("ɾ���ļ���"));
		//QAction* download = menu.addAction(m_strDolwnloadText);
		//QAction* rename = menu.addAction(QString::fromLocal8Bit("������"));
		//
		//connect(add, &QAction::triggered, [=]()
		//	{
		//		QString DirName = QInputDialog::getText(this, QString::fromLocal8Bit("�½�"), QString::fromLocal8Bit("�����½��ļ������ƣ�"));
		//		if (!DirName.isEmpty())	// �û��������ļ�����
		//		{
		//			QString dirPath = pItem->data(0, Qt::UserRole).toString();
		//	
		//			QString strPath = pItem->data(0, Qt::UserRole).toString() + "\\" + DirName;
		//			m_FtpClientClass->execute_mkdirFolder(strPath.toLocal8Bit().toStdString());

		//			QTreeWidgetItem* pNewItem = new QTreeWidgetItem();
		//					
		//			pNewItem->setText(0, DirName);
		//			pNewItem->setData(0, Qt::UserRole, strPath);
		//			pNewItem->setIcon(0, QIcon(":/image/Dir.png"));
		//			pNewItem->setToolTip(0, DirName);

		//			pItem->addChild(pNewItem);
		//						
		//		}
		//	});

		//connect(del, &QAction::triggered, [=]()
		//	{
		//		QTreeWidgetItem* pParentItem = pItem->parent();
		//		if (!pParentItem)
		//			return;
		//		QString parentDir = pParentItem->data(0, Qt::UserRole).toString();
		//		QString dirPath = pParentItem->data(0, Qt::UserRole).toString() + "\\" + pItem->text(0);
		//		dirPath.replace("/", "\\\\");
		//		parentDir.replace("/", "\\\\");
		//	
		//	   //m_FtpClientClass->execute_delFolder(pItem->text(0).toLocal8Bit().toStdString());
		//		m_FtpClientClass->execute_deleteFileList(dirPath.toLocal8Bit().toStdString());
		//		
		//		pParentItem->removeChild(pItem); // �Ȼ�ȡ childItem
		//		delete pItem;
		//	});

		//connect(download, &QAction::triggered, [=]()  // �����ļ��м��������ļ��м����ļ�;
		//	{
		//		//QTreeWidgetItem* pParentItem = pItem->parent();
		//		QString dirPath = pItem->data(0, Qt::UserRole).toString();
		//		//QString dirPath = pParentItem->data(0, Qt::UserRole).toString() + "/" + pItem->text(0);
		//		
		//		//dirPath.replace("/", "\\\\");
		//		dirPath.replace("\\", "\\\\");

		//		if (!common::bAdministrator) // ��ͨ�û�
		//		{
		//			table_DownloadApproval stDownloadApproval;
		//			stDownloadApproval.userID = common::iUserID;
		//			stDownloadApproval.filePath = dirPath.toLocal8Bit().toStdString();
		//			stDownloadApproval.fileType = "dir";  
		//			stDownloadApproval.fileTime = common::string_to_datetime(pItem->data(0,Qt::UserRole + 1).toString().toStdString());
		//			
		//			stDownloadApproval.applicationTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
		//			stDownloadApproval.status = 0;
		//			db::databaseDI::Instance().add_download_approval_info(stDownloadApproval);
		//		}
		//		else
		//		{
		//			QString directory = QFileDialog::getExistingDirectory(nullptr, QString::fromLocal8Bit("ѡ������Ŀ¼"), QDir::currentPath());
		//			if (directory.isEmpty())
		//				return;
		//			QString newDirPath = directory + "/" + pItem->text(0);
		//			newDirPath.replace("/", "\\\\");

		//			g_pMainWindow->showGif();
		//			
		//			QApplication::processEvents(QEventLoop::ExcludeSocketNotifiers);
		//			downloadFtpDir(dirPath, newDirPath);

		//			g_pMainWindow->closeGif();
		//		}
		//		
		//		
		//	});

		//connect(rename, &QAction::triggered, [=]()
		//	{
		//		QString oldDir = pItem->data(0, Qt::UserRole).toString();

		//		QTreeWidgetItem* pParentItem = pItem->parent();
		//		if (pParentItem == nullptr)
		//		{
		//			QMessageBox::warning(this, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("��Ŀ¼��ֹ������"));
		//			return;
		//		}
		//		QString DirName = QInputDialog::getText(this, QString::fromLocal8Bit("������"), QString::fromLocal8Bit("�����½��ļ������ƣ�"));
		//		QString newDir = pParentItem->data(0, Qt::UserRole).toString() + "\\" + DirName;
		//		if (m_FtpClientClass->execute_rename(oldDir.toLocal8Bit().toStdString(), newDir.toLocal8Bit().toStdString()))
		//		{
		//			pItem->setText(0, DirName);
		//			pItem->setData(0, Qt::UserRole, newDir);
		//		}

		//	});

		//if (pItem == m_pRootItem)
		//{
		//	rename->setEnabled(false);
		//	download->setEnabled(false);
		//}

		//menu.exec(QCursor::pos());
	//}

}

void FilemangageDialog::slot_ItemDownloadBtnClicked()
{
	QPushButton* pButton = (QPushButton*)sender();
	int row = pButton->property("row").toInt();
	int column = pButton->property("column").toInt();
	int approval = pButton->property("approval").toInt();

	QModelIndex index = m_modelDownload->index(row, 0);
	int id = m_modelDownload->data(index, Qt::UserRole).toInt();
	QModelIndex indexFilePath = m_modelDownload->index(row, 4);
	QString strFilaPath = m_modelDownload->data(indexFilePath, Qt::UserRole).toString();

	QString strFileType=m_modelDownload->item(row, 5)->text();

	QString strFileName = m_modelDownload->item(row, 4)->text();
	if (strFileType == "dir")  // �����ļ���
	{
		QString directory = QFileDialog::getExistingDirectory(nullptr, QString::fromLocal8Bit("ѡ������Ŀ¼"), QDir::currentPath());
		if (directory.isEmpty())
			return;
		QString newDirPath = directory + "\\" + strFileName;
		newDirPath.replace("/", "\\\\");

		g_pMainWindow->showGif();
		//QMessageBox::warning(this, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("����ϵ����Ա����Թ���Ա�������"));
		// m_msgBox->show();
		QApplication::processEvents(QEventLoop::ExcludeSocketNotifiers);
		int ret =downloadFtpDir(strFilaPath, newDirPath);
		g_pMainWindow->closeGif();
		if (ret == -1)
		{
			QMessageBox::warning(this, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("Ҫ���ص�ftpĿ¼��ɾ��"));
			return;
		}
	}
	else  
	{       // �����ļ�
		QString directory = QFileDialog::getExistingDirectory(nullptr, QString::fromLocal8Bit("ѡ������Ŀ¼"), QDir::currentPath());
		if (directory.isEmpty())
		{
			return;
		}

		std::string str = directory.toLocal8Bit().toStdString();
		std::wstring wstr = directory.toStdWString();
		const wchar_t* lpcwstr = wstr.c_str();
		SetCurrentDirectory(lpcwstr);//���õ�ǰĿ¼

		/*if (!m_FtpClientClass->newConnection())
			return;*/

			//m_FtpClientClass->execute_getFile(fileAllPath.toLocal8Bit().toStdString());
		QString newFilePath = directory + "\\" + strFileName;
		newFilePath.replace("/", "\\\\");
		m_GifDialog->show();
		QApplication::processEvents(QEventLoop::ExcludeSocketNotifiers);
		int ret =m_FtpClientClass->execute_getFile(strFilaPath.toLocal8Bit().toStdString(), newFilePath.toLocal8Bit().toStdString());
		m_GifDialog->close();
		if (ret == 1)
		{
			QMessageBox::warning(this, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("��Ҫ���ص�Ftp�ļ���ɾ��"));
		}
	}

}

void FilemangageDialog::slot_actionMkdir()
{
	QTreeWidgetItem* pItem = ui->treeWidget->currentItem();

	QString text = pItem->text(0);

	QString DirName = QInputDialog::getText(this, QString::fromLocal8Bit("�½�"), QString::fromLocal8Bit("�����½��ļ������ƣ�"));
	if (!DirName.isEmpty())	// �û��������ļ�����
	{
		QString dirPath = pItem->data(0, Qt::UserRole).toString();

		QString strPath = pItem->data(0, Qt::UserRole).toString() + "\\" + DirName;
		m_FtpClientClass->execute_mkdirFolder(strPath.toLocal8Bit().toStdString());

		QTreeWidgetItem* pNewItem = new QTreeWidgetItem();

		pNewItem->setText(0, DirName);
		pNewItem->setData(0, Qt::UserRole, strPath);
		pNewItem->setIcon(0, QIcon(":/image/Dir.png"));
		pNewItem->setToolTip(0, DirName);

		pItem->addChild(pNewItem);
	}
}

void FilemangageDialog::slot_actionDelDir()
{
	QTreeWidgetItem* pItem = ui->treeWidget->currentItem();
	if (pItem == nullptr)
		return;
	QTreeWidgetItem* pParentItem = pItem->parent();
	if (!pParentItem)
		return;
	QString parentDir = pParentItem->data(0, Qt::UserRole).toString();
	QString dirPath = pParentItem->data(0, Qt::UserRole).toString() + "\\" + pItem->text(0);
	dirPath.replace("/", "\\\\");
	parentDir.replace("/", "\\\\");

	//m_FtpClientClass->execute_delFolder(pItem->text(0).toLocal8Bit().toStdString());
	m_FtpClientClass->execute_deleteFileList(dirPath.toLocal8Bit().toStdString());

	pParentItem->removeChild(pItem); // �Ȼ�ȡ childItem
	delete pItem;
}

void FilemangageDialog::slot_actionDownload()
{
	QTreeWidgetItem* pItem = ui->treeWidget->currentItem();
	if (pItem == nullptr)
		return;

	QString dirPath = pItem->data(0, Qt::UserRole).toString();

	dirPath.replace("\\", "\\\\");

	if (!common::bAdministrator) // ��ͨ�û�
	{
		table_DownloadApproval stDownloadApproval;
		stDownloadApproval.userID = common::iUserID;
		stDownloadApproval.filePath = dirPath.toLocal8Bit().toStdString();
		stDownloadApproval.fileType = "dir";
		stDownloadApproval.fileTime = common::string_to_datetime(pItem->data(0, Qt::UserRole + 1).toString().toStdString());

		stDownloadApproval.applicationTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
		stDownloadApproval.status = 0;
		db::databaseDI::Instance().add_download_approval_info(stDownloadApproval);
	}
	else
	{
		QString directory = QFileDialog::getExistingDirectory(nullptr, QString::fromLocal8Bit("ѡ������Ŀ¼"), QDir::currentPath());
		if (directory.isEmpty())
			return;
		QString newDirPath = directory + "/" + pItem->text(0);
		newDirPath.replace("/", "\\\\");

		g_pMainWindow->showGif();

		QApplication::processEvents(QEventLoop::ExcludeSocketNotifiers);
		downloadFtpDir(dirPath, newDirPath);

		g_pMainWindow->closeGif();
	}
}

void FilemangageDialog::slot_actioxnRename()
{
	QTreeWidgetItem* pItem = ui->treeWidget->currentItem();
	if (pItem == nullptr)
		return;

	QString oldDir = pItem->data(0, Qt::UserRole).toString();

	QTreeWidgetItem* pParentItem = pItem->parent();
	if (pParentItem == nullptr)
	{
		QMessageBox::warning(this, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("��Ŀ¼��ֹ������"));
		return;
	}
	QString DirName = QInputDialog::getText(this, QString::fromLocal8Bit("������"), QString::fromLocal8Bit("�����½��ļ������ƣ�"));
	QString newDir = pParentItem->data(0, Qt::UserRole).toString() + "\\" + DirName;
	if (m_FtpClientClass->execute_rename(oldDir.toLocal8Bit().toStdString(), newDir.toLocal8Bit().toStdString()))
	{
		pItem->setText(0, DirName);
		pItem->setData(0, Qt::UserRole, newDir);
	}
}

void FilemangageDialog::slot_tableViewFilesItemChanged(QStandardItem* item)
{
	if (item->checkState() == Qt::Checked)
	{
		qDebug() << item->text() << "is checked";
	}
	else {
		qDebug() << item->text() << "is unchecked";
	}
}

void FilemangageDialog::slot_treeWidgetItemDoubleClicked(QTreeWidgetItem* item, int column)
{
	
}