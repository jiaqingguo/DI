#include <QStandardItemModel>
#include <QFileDialog>
#include <QMovie>
#include <QMenu>
#include <QInputDialog>
#include <QLabel>
#include <QToolButton>
#include <QMessageBox>

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
		

		//if (m_FtpClientClass->newConnection())
		{
			m_FtpClientClass->execute_ls(strRootPath);//ִ��ls 

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

				std::string strDirPath = strRootPath + "\\" + vecFolderNames[i];
				createTreeChildNode(pItem, strDirPath);
				//createTreeChildNode(pItem, vecFolderNames[i]);
				pRootItem->addChild(pItem);
			}
		}
		
		

		return 1;
	}
}

void FilemangageDialog::createTreeChildNode( QTreeWidgetItem* pParentItem, const std::string strFolder)
{
	/*if (!m_FtpClientClass->newConnection())
		return;*/
//	m_FtpClientClass->execute_cdFloder(strFolder);//�������ļ���

	/*if (!m_FtpClientClass->newConnection())
		return;*/
	m_FtpClientClass->execute_ls(strFolder);//ִ��ls 
	
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
		std::string strDirPath = strFolder + "\\" + vecFolders[j];
		createTreeChildNode(pItem, strDirPath);
		//createTreeChildNode(pItem, vecFolders[j]);
		pParentItem->addChild(pItem);
	}
	
	/*if (!m_FtpClientClass->newConnection())
		return;*/
//	m_FtpClientClass->execute_cdGoback();//������һ��Ŀ¼
}

void FilemangageDialog::downloadFtpDir(const QString& strDirPath, const QString& newDirPath)
{
	QDir dir(newDirPath);
	if (!dir.exists())
	{
		if (!dir.mkdir(newDirPath))
		{
			//qDebug() << "�ļ��д���ʧ�ܣ�";
			return;
		}
	}
	
	/*if (!m_FtpClientClass->newConnection())
		return;*/
	//m_FtpClientClass->execute_cdFloder(strDirPath.toLocal8Bit().toStdString());//�������ļ���
	/*if (!m_FtpClientClass->newConnection())
		return;*/
	m_FtpClientClass->execute_ls(strDirPath.toLocal8Bit().toStdString());//ִ��ls 

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
		QString ftpDirPath = strDirPath + "\\\\" + QString::fromLocal8Bit(vecFtpDirData[j].c_str());
		QString newChildDirPath = newDirPath + "\\\\" + QString::fromLocal8Bit(vecFtpDirData[j].c_str());
		downloadFtpDir(ftpDirPath, newChildDirPath);
	}
	
	//emit signal_downloadFinsh();
}

void FilemangageDialog::slot_treeWidgetItemClicked(QTreeWidgetItem* pTreeItem, int column)
{
	QString strDirPath = pTreeItem->data(column, Qt::UserRole).toString();

	/*if (!m_FtpClientClass->newConnection())
		return;*/
//	m_FtpClientClass->execute_cdFloder(strDirPath.toLocal8Bit().toStdString());//�������ļ���

	/*if (!m_FtpClientClass->newConnection())
		return;*/
	m_FtpClientClass->execute_ls(strDirPath.toLocal8Bit().toStdString());//ִ��ls 

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
		m_modelFiles->setData(index, QString::fromLocal8Bit(vecFileData[i][1].c_str()), Qt::UserRole);  //�����ļ�ʱ�� ;

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
	int row = ui->tableView->currentIndex().row();

	auto strFileName = m_modelFiles->item(row,1)->text();
	QString dirPath = ui->treeWidget->currentItem()->data(0, Qt::UserRole).toString();
	QString fileAllPath = dirPath + "\\" + strFileName;
	fileAllPath.replace("/", "\\\\");

	
	if (!common::bAdministrator)
	{
		table_DownloadApproval stDownloadApproval;
		stDownloadApproval.userID = common::iUserID;
		stDownloadApproval.filePath = fileAllPath.toLocal8Bit().toStdString();
		stDownloadApproval.fileType = strFileName.mid(strFileName.lastIndexOf(".") + 1).toStdString();  // ���ص�֮��Ĳ���

		stDownloadApproval.fileTime= common::string_to_datetime(m_modelFiles->item(row, 0)->data(Qt::UserRole + 1).toString().toStdString());
		stDownloadApproval.applicationTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

		db::databaseDI::Instance().add_download_approval_info(stDownloadApproval);


		return;
	}

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

	/*if (!m_FtpClientClass->newConnection())
		return;*/
	
	//m_FtpClientClass->execute_getFile(fileAllPath.toLocal8Bit().toStdString());
	QString newFilePath= directory + "\\" + strFileName;
	newFilePath.replace("/", "\\\\");
	m_FtpClientClass->execute_getFile(fileAllPath.toLocal8Bit().toStdString(), newFilePath.toLocal8Bit().toStdString());
}

void FilemangageDialog::slot_itemBtnDel()
{
	int row = ui->tableView->currentIndex().row();
	//QPushButton* pButton = (QPushButton*)sender();
	//int row = pButton->property("row").toInt();
	//int column = pButton->property("column").toInt();

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

	m_FtpClientClass->execute_putFile(fileInfo.fileName().toLocal8Bit().toStdString(), UploadingPath.toLocal8Bit().toStdString());

}

void FilemangageDialog::slot_treeWidgteCustomContextMenuRequested(const QPoint& pos)
{
	QTreeWidgetItem* pItem = ui->treeWidget->itemAt(pos);
	if (pItem)
	{
		
		QMenu menu;
		QAction* add = menu.addAction(QString::fromLocal8Bit("�½��ļ���"));
		QAction* del = menu.addAction(QString::fromLocal8Bit("ɾ���ļ���"));
		QAction* download = menu.addAction(QString::fromLocal8Bit("����"));
		QAction* rename = menu.addAction(QString::fromLocal8Bit("������"));
		
		connect(add, &QAction::triggered, [=]()
			{
				QString DirName = QInputDialog::getText(this, QString::fromLocal8Bit("�½�"), QString::fromLocal8Bit("�����½��ļ������ƣ�"));
				if (!DirName.isEmpty())	// �û��������ļ�����
				{
					QString dirPath = pItem->data(0, Qt::UserRole).toString();
				//if (m_FtpClientClass->newConnection())
					{
					//	m_FtpClientClass->execute_cdFloder(dirPath.toLocal8Bit().toStdString());
					//if (m_FtpClientClass->newConnection())
						{
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

					//if (m_FtpClientClass->newConnection())
					{
						//m_FtpClientClass->execute_delFolder(pItem->text(0).toLocal8Bit().toStdString());
						m_FtpClientClass->execute_deleteFileList(dirPath.toLocal8Bit().toStdString());
						delete pItem;
					}
				//}

			});


		connect(download, &QAction::triggered, [=]()  // �����ļ��м��������ļ��м����ļ�;
			{
				QTreeWidgetItem* pParentItem = pItem->parent();
				QString dirPath = pParentItem->data(0, Qt::UserRole).toString() + "/" + pItem->text(0);
				dirPath.replace("/", "\\\\");
				QString directory = QFileDialog::getExistingDirectory(nullptr, QString::fromLocal8Bit("ѡ������Ŀ¼"), QDir::currentPath());
				if (directory.isEmpty())
					return;
				QString newDirPath = directory + "/" + pItem->text(0);
				newDirPath.replace("/", "\\\\");

			
				g_pMainWindow->showGif();
				//QMessageBox::warning(this, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("����ϵ����Ա����Թ���Ա�������"));
	 			// m_msgBox->show();
				 QApplication::processEvents(QEventLoop::ExcludeSocketNotifiers);
				 downloadFtpDir(dirPath, newDirPath);
				
				g_pMainWindow->closeGif();
				
			});

		connect(rename, &QAction::triggered, [=]()
			{
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
				}

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