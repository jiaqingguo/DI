#include "ApprovalProgressDialog.h"
#include "ui_ApprovalProgressDialog.h"
#include "globel.h"
#include "databaseDI.h"
#include "common.h"

#include "CTableView.h"
#include <QStandardItemModel>
#include <QScrollBar>
#include <QDebug>
#include <QKeyEvent>
#include <QFileInfo>


ApprovalProgressDialog::ApprovalProgressDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::ApprovalProgressDialog)
{
	ui->setupUi(this);
	setWindowIcon(QIcon(":/image/ApprovalProgress.png"));
	ui->stackedWidget->setCurrentIndex(0);
	//ui->stackedWidget->setFocusPolicy(Qt::NoFocus);

	ui->lineEditDataQueryValue->setPlaceholderText(QString::fromLocal8Bit("����������ֵ"));
	ui->lineEditUserQueryValue->setPlaceholderText(QString::fromLocal8Bit("����������ֵ"));

	QRegExp regex("[0-9]+");
	QRegExpValidator* validator = new QRegExpValidator(regex, this);
	ui->lineEditDataApprovalPage->setValidator(validator);
	ui->lineEditUserPage->setValidator(validator);

	m_modelDataApproval = new QStandardItemModel();
	m_modelDataApproval->setColumnCount(10);
	m_modelDataApproval->setHeaderData(0, Qt::Horizontal, QString::fromLocal8Bit("���"));
	m_modelDataApproval->setHeaderData(1, Qt::Horizontal, QString::fromLocal8Bit("������"));
	m_modelDataApproval->setHeaderData(2, Qt::Horizontal, QString::fromLocal8Bit("���ڲ���"));
	m_modelDataApproval->setHeaderData(3, Qt::Horizontal, QString::fromLocal8Bit("����ʱ��"));
	m_modelDataApproval->setHeaderData(4, Qt::Horizontal, QString::fromLocal8Bit("�ļ���"));
	m_modelDataApproval->setHeaderData(5, Qt::Horizontal, QString::fromLocal8Bit("�ļ�����"));
	m_modelDataApproval->setHeaderData(6, Qt::Horizontal, QString::fromLocal8Bit("����ʱ��"));
	m_modelDataApproval->setHeaderData(7, Qt::Horizontal, QString::fromLocal8Bit("״̬"));
	m_modelDataApproval->setHeaderData(8, Qt::Horizontal, QString::fromLocal8Bit("����"));
	m_modelDataApproval->setHeaderData(9, Qt::Horizontal, QString::fromLocal8Bit("����"));


	/* QStringList labels = QObject::trUtf8("ID,����,value,ʱ��,���").simplified().split(",");
	 model->setHorizontalHeaderLabels(labels);*/
	ui->tableView->setModel(m_modelDataApproval);
	common::setTableViewBasicConfiguration(ui->tableView);
	//ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	//ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);   // ѡ������
	//ui->tableView->verticalHeader()->setDefaultSectionSize(28);
	ui->tableView->verticalHeader()->setVisible(false);

	//ui->comboBoxDataField->addItem("");
	ui->comboBoxDataField->addItem(QString::fromLocal8Bit("������"));
	ui->comboBoxDataField->addItem(QString::fromLocal8Bit("���ڲ���"));
	//ui->comboBoxDataField->addItem(QString::fromLocal8Bit("����ʱ��"));
	ui->comboBoxDataField->addItem(QString::fromLocal8Bit("�ļ���"));
	ui->comboBoxDataField->addItem(QString::fromLocal8Bit("�ļ�����"));
	//ui->comboBoxDataField->addItem(QString::fromLocal8Bit("����ʱ��"));
	ui->comboBoxDataField->addItem(QString::fromLocal8Bit("״̬"));


	m_modelUser = new QStandardItemModel();
	m_modelUser->setColumnCount(11);

	m_modelUser->setHeaderData(0, Qt::Horizontal, QString::fromLocal8Bit("������"));
	m_modelUser->setHeaderData(1, Qt::Horizontal, QString::fromLocal8Bit("���ڲ���"));
	m_modelUser->setHeaderData(2, Qt::Horizontal, QString::fromLocal8Bit("����ʱ��"));
	m_modelUser->setHeaderData(3, Qt::Horizontal, QString::fromLocal8Bit("�û���"));
	m_modelUser->setHeaderData(4, Qt::Horizontal, QString::fromLocal8Bit("����"));
	m_modelUser->setHeaderData(5, Qt::Horizontal, QString::fromLocal8Bit("ְλ"));
	m_modelUser->setHeaderData(6, Qt::Horizontal, QString::fromLocal8Bit("�ֻ���"));
	m_modelUser->setHeaderData(7, Qt::Horizontal, QString::fromLocal8Bit("Ȩ��"));
	m_modelUser->setHeaderData(8, Qt::Horizontal, QString::fromLocal8Bit("״̬"));
	m_modelUser->setHeaderData(9, Qt::Horizontal, QString::fromLocal8Bit("����"));
	m_modelUser->setHeaderData(10, Qt::Horizontal, QString::fromLocal8Bit("����"));
	ui->tableViewUser->setModel(m_modelUser);
	common::setTableViewBasicConfiguration(ui->tableViewUser);
	// ui->tableViewUser->verticalHeader()->setDefaultSectionSize(28);
	ui->tableViewUser->verticalHeader()->setVisible(false);



	/*  connect(ui->btnData, &QPushButton::clicked, [this]() {
		  ui->stackedWidget->setCurrentIndex(0);
		  });
	  connect(ui->btnUser, &QPushButton::clicked, [this]() {
		  ui->stackedWidget->setCurrentIndex(1);
		  });*/
	ui->btnData->setFocusPolicy(Qt::NoFocus); // ���ð�ť���Զ���ý���
	ui->btnUser->setFocusPolicy(Qt::NoFocus); // ���ð�ť���Զ���ý���

	ui->btnDataQuery->setFocusPolicy(Qt::NoFocus);
	ui->btnUserQuery->setFocusPolicy(Qt::NoFocus);

	ui->btnData->setStyleSheet(strQssBlue);
	ui->btnUser->setStyleSheet(strQssGray);
	connect(ui->btnData, &QPushButton::clicked, this, &ApprovalProgressDialog::slot_btnDataShow);
	connect(ui->btnUser, &QPushButton::clicked, this, &ApprovalProgressDialog::slot_btnUserShow);


	connect(ui->btnUserLast, &QPushButton::clicked, this, &ApprovalProgressDialog::slot_btnLast);
	connect(ui->btnUserNext, &QPushButton::clicked, this, &ApprovalProgressDialog::slot_btnNext);
	connect(ui->lineEditUserPage, &QLineEdit::editingFinished, this, &ApprovalProgressDialog::slot_pageTo);

	connect(ui->btnDataApprovalLast, &QPushButton::clicked, this, &ApprovalProgressDialog::slot_DataApprovalBtnLast);
	connect(ui->btnDataApprovalNext, &QPushButton::clicked, this, &ApprovalProgressDialog::slot_DataApprovalBtnNext);
	connect(ui->lineEditDataApprovalPage, &QLineEdit::editingFinished, this, &ApprovalProgressDialog::slot_DataApprovalPageTo);

	ui->lineEditUserPage->setText(QString::number(1));
	//QScrollBar* scrollBar = (QScrollBar*)ui->tableViewUser->verticalScrollBar();
	// connect(scrollBar, SIGNAL(valueChanged(int)), this, SLOT(scrollMove(int)));


	//ui->comboBoxUserField->addItem("");
	ui->comboBoxUserField->addItem(QString::fromLocal8Bit("������"));
	ui->comboBoxUserField->addItem(QString::fromLocal8Bit("���ڲ���"));
	//ui->comboBoxUserField->addItem(QString::fromLocal8Bit("����ʱ��"));
	ui->comboBoxUserField->addItem(QString::fromLocal8Bit("�û���"));
	ui->comboBoxUserField->addItem(QString::fromLocal8Bit("����"));
	ui->comboBoxUserField->addItem(QString::fromLocal8Bit("ְλ"));
	ui->comboBoxUserField->addItem(QString::fromLocal8Bit("�ֻ���"));
	ui->comboBoxUserField->addItem(QString::fromLocal8Bit("Ȩ��"));
	ui->comboBoxUserField->addItem(QString::fromLocal8Bit("״̬"));
	connect(ui->comboBoxUserField, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_combocUserCurrentIndexChanged(int)));
	connect(ui->btnDataQuery, &QPushButton::clicked, this, &ApprovalProgressDialog::slot_dataApprovalQuery); // ����������ѯ
	connect(ui->btnUserQuery, &QPushButton::clicked, this, &ApprovalProgressDialog::slot_userQuery); // �û�������ѯ

	connect(ui->btnFlushDownload, &QPushButton::clicked, this, &ApprovalProgressDialog::slot_btnFlushDownload);
	init();
}

ApprovalProgressDialog::~ApprovalProgressDialog()
{
	delete ui;
}

void ApprovalProgressDialog::init()
{

	getDownloadData(m_listDataApproval);
	m_DataApprovalTotalRows = m_listDataApproval.size();
	if (m_DataApprovalTotalRows <= common::tableViewPageRows)
	{
		m_DataApprovalTatalPage = 1;
	}
	else
	{
		m_DataApprovalTatalPage = m_DataApprovalTotalRows / common::tableViewPageRows;
		if (m_DataApprovalTatalPage % common::tableViewPageRows != 0)
		{
			m_DataApprovalTatalPage++;
		}
	}

	ui->labelDataApprovalPageShow->setText(QString("%1/%2").arg(1).arg(m_DataApprovalTatalPage));
	ui->lineEditDataApprovalPage->setText("1");

	auto listDataApproval = processList(m_listDataApproval, common::onePageRows, 0);
	flushDownloadTableShow(listDataApproval, 0);


	db::databaseDI::Instance().get_user_list(m_listUser);
	m_UserTotalRows = m_listUser.size();

	if (m_UserTotalRows <= common::tableViewPageRows)
	{
		m_UserTotalpage = 1;
	}
	else
	{
		m_UserTotalpage = m_UserTotalRows / common::tableViewPageRows;
		if (m_UserTotalpage % common::tableViewPageRows != 0)
		{
			m_UserTotalpage++;
		}
	}

	ui->labelUserPage->setText(QString("%1/%2").arg(1).arg(m_UserTotalpage));
	ui->lineEditUserPage->setText("1");

	auto listData = processList(m_listUser, common::onePageRows, 0);
	flushUserTableShow(listData);



}


void ApprovalProgressDialog::autoFlushDownloadData()
{
	getDownloadData(m_listDataApproval);
	m_DataApprovalTotalRows = m_listDataApproval.size();
	int curPage = ui->lineEditDataApprovalPage->text().toInt();
	int offsetRows = (curPage)*common::onePageRows;

	auto listDataApproval = processList(m_listDataApproval, common::onePageRows, offsetRows);
	flushDownloadTableShow(listDataApproval, offsetRows);
}

void ApprovalProgressDialog::flushDownloadTableShow(std::list<table_DownloadApproval>& listData, const int& offsetRows)
{
	common::delAllModelRow(m_modelDataApproval);
	//  ��ѯ���ݿ���ʾ;
   // 
	int i = offsetRows;
	for (auto& stData : listData)
	{

		/* table_user stUserData;
		 db::databaseDI::Instance().get_user_by_condition(stUserData,stData.userID);
		 stData.userName = stUserData.name;
		 stData.department = stUserData.department;*/

		int newRowIndex = m_modelDataApproval->rowCount(); // ��ȡ��ǰ����
		m_modelDataApproval->insertRow(newRowIndex); // ��������

		QStandardItem* item = new QStandardItem(QString::number(i + 1));
		item->setTextAlignment(Qt::AlignCenter);  // �����ı����ж���
		//item->setData(QString::fromStdString(stData.name), Qt::ToolTipRole);
		m_modelDataApproval->setItem(newRowIndex, 0, item);

		QModelIndex index = m_modelDataApproval->index(newRowIndex, 0);
		m_modelDataApproval->setData(index, stData.id, Qt::UserRole);  // ����id;
		//  item->setText(QString::fromStdString(stData.name));

		item = new QStandardItem(QString::fromStdString(stData.userName));
		item->setTextAlignment(Qt::AlignCenter);  // �����ı����ж���
		m_modelDataApproval->setItem(newRowIndex, 1, item);

		item = new QStandardItem(QString::fromStdString(stData.department));
		item->setTextAlignment(Qt::AlignCenter);  // �����ı����ж���
		m_modelDataApproval->setItem(newRowIndex, 2, item);

		item = new QStandardItem(QDateTime::fromTime_t(stData.applicationTime).toString("yyyy/MM/dd HH:mm:ss"));
		item->setTextAlignment(Qt::AlignCenter);  // �����ı����ж���
		m_modelDataApproval->setItem(newRowIndex, 3, item);


		QString filePath = QString::fromLocal8Bit(stData.filePath.c_str());
		QFileInfo fileInfo1(filePath);

		item = new QStandardItem(fileInfo1.fileName());
		item->setTextAlignment(Qt::AlignCenter);  // �����ı����ж���
		m_modelDataApproval->setItem(newRowIndex, 4, item);


		item = new QStandardItem(QString::fromStdString(stData.fileType));
		item->setTextAlignment(Qt::AlignCenter);  // �����ı����ж���
		m_modelDataApproval->setItem(newRowIndex, 5, item);

		item = new QStandardItem(QDateTime::fromTime_t(stData.fileTime).toString("yyyy/MM/dd HH:mm:ss"));
		item->setTextAlignment(Qt::AlignCenter);  // �����ı����ж���
		m_modelDataApproval->setItem(newRowIndex, 6, item);




		// add button to the last column
		QPushButton* buttonYes = new QPushButton(QString::fromLocal8Bit("ͬ��"));
		buttonYes->setObjectName("itemBtnYes");
		buttonYes->setProperty("row", newRowIndex); // set custom property
		buttonYes->setProperty("column", 8);
		buttonYes->setProperty("approval", 1);
		connect(buttonYes, SIGNAL(clicked()), this, SLOT(slot_DataItemBtnClicked()));
		ui->tableView->setIndexWidget(m_modelDataApproval->index(newRowIndex, 8), buttonYes);

		QPushButton* buttonNo = new QPushButton(QString::fromLocal8Bit("����"));
		buttonNo->setObjectName("itemBtnNo");
		buttonNo->setProperty("row", newRowIndex); // set custom property
		buttonNo->setProperty("column", 9);
		buttonNo->setProperty("approval", 2);

		connect(buttonNo, SIGNAL(clicked()), this, SLOT(slot_DataItemBtnClicked()));
		ui->tableView->setIndexWidget(m_modelDataApproval->index(newRowIndex, 9), buttonNo);
		if (stData.status == 1)
		{
			item = new QStandardItem(QString::fromLocal8Bit("��ͨ��"));
			item->setForeground(QBrush(QColor(Qt::green)));
			item->setTextAlignment(Qt::AlignCenter);  // �����ı����ж���
			m_modelDataApproval->setItem(newRowIndex, 7, item);
			buttonNo->setEnabled(false);
			buttonYes->setEnabled(false);
		}
		else if (stData.status == 0)
		{
			item = new QStandardItem(QString::fromLocal8Bit("�����"));
			item->setForeground(QBrush(QColor("#33C1FF")));
			item->setTextAlignment(Qt::AlignCenter);  // �����ı����ж���
			m_modelDataApproval->setItem(newRowIndex, 7, item);
		}
		else if (stData.status == 2)
		{
			item = new QStandardItem(QString::fromLocal8Bit("�Ѳ���"));
			item->setTextAlignment(Qt::AlignCenter);  // �����ı����ж���
			item->setForeground(QBrush(QColor(Qt::red)));
			m_modelDataApproval->setItem(newRowIndex, 7, item);
			buttonNo->setEnabled(false);
			buttonYes->setEnabled(false);

		}
		i++;
	}
}


template<typename T>
std::list<T> ApprovalProgressDialog::processList(const std::list<T>& listData, const int& num, const int& offsetRows)
{
	std::list<T> listTemp;
	auto it = listData.begin();
	std::advance(it, offsetRows); // ����ǰ offsetRows ������

	for (int i = 0; i < num && it != listData.end(); ++i, ++it)
	{
		listTemp.push_back(*it); // �������ݣ�
	}
	return listTemp;
}


void ApprovalProgressDialog::getDownloadData(std::list<table_DownloadApproval>& listData)
{
	db::databaseDI::Instance().get_download_approval_list(listData);

	for (auto& stData : listData)
	{

		table_user stUserData;
		db::databaseDI::Instance().get_user_by_condition(stUserData, stData.userID);
		stData.userName = stUserData.UserName;
		stData.department = stUserData.department;
	}
}

void ApprovalProgressDialog::flushUserTableShow(std::list<table_user>& listUser)
{
	common::delAllModelRow(m_modelUser);
	//  ��ѯ���ݿ���ʾ;

	for (auto& stData : listUser)
	{
		int newRowIndex = m_modelUser->rowCount(); // ��ȡ��ǰ����
		m_modelUser->insertRow(newRowIndex); // ��������

		QStandardItem* item = new QStandardItem(QString::fromStdString(stData.name));
		item->setTextAlignment(Qt::AlignCenter);  // �����ı����ж���
		//item->setData(QString::fromStdString(stData.name), Qt::ToolTipRole);
		m_modelUser->setItem(newRowIndex, 0, item);

		QModelIndex index = m_modelUser->index(newRowIndex, 0);
		m_modelUser->setData(index, stData.PKID, Qt::UserRole);  // ����id;
		//  item->setText(QString::fromStdString(stData.name));

		item = new QStandardItem(QString::fromStdString(stData.department));
		item->setTextAlignment(Qt::AlignCenter);  // �����ı����ж���
		m_modelUser->setItem(newRowIndex, 1, item);
		item = new QStandardItem(QDateTime::fromTime_t(stData.CreateTime).toString("yyyy/MM/dd HH:mm:ss"));
		item->setTextAlignment(Qt::AlignCenter);  // �����ı����ж���
		m_modelUser->setItem(newRowIndex, 2, item);
		item = new QStandardItem(QString::fromStdString(stData.UserName));
		item->setTextAlignment(Qt::AlignCenter);  // �����ı����ж���
		m_modelUser->setItem(newRowIndex, 3, item);
		item = new QStandardItem(QString::fromStdString(stData.Password));
		item->setTextAlignment(Qt::AlignCenter);  // �����ı����ж���
		m_modelUser->setItem(newRowIndex, 4, item);
		item = new QStandardItem(QString::fromStdString(stData.JobTitle));
		item->setTextAlignment(Qt::AlignCenter);  // �����ı����ж���
		m_modelUser->setItem(newRowIndex, 5, item);
		item = new QStandardItem(QString::fromStdString(stData.PhoneNumber));
		item->setTextAlignment(Qt::AlignCenter);  // �����ı����ж���
		m_modelUser->setItem(newRowIndex, 6, item);

		if (stData.Pop == 0)
		{
			item = new QStandardItem(QString::fromLocal8Bit("����Ա"));
			item->setTextAlignment(Qt::AlignCenter);  // �����ı����ж���
			m_modelUser->setItem(newRowIndex, 7, item);
		}
		else {
			item = new QStandardItem(QString::fromLocal8Bit("��ͨ�û�"));
			item->setTextAlignment(Qt::AlignCenter);  // �����ı����ж���
			m_modelUser->setItem(newRowIndex, 7, item);
		}

		// add button to the last column
		QPushButton* buttonYes = new QPushButton(QString::fromLocal8Bit("ͬ��"));
		buttonYes->setObjectName("itemBtnYes");
		buttonYes->setProperty("row", newRowIndex); // set custom property
		buttonYes->setProperty("column", 9);
		buttonYes->setProperty("approval", 1);
		connect(buttonYes, SIGNAL(clicked()), this, SLOT(slot_ItemBtnClicked()));
		ui->tableViewUser->setIndexWidget(m_modelUser->index(newRowIndex, 9), buttonYes);

		QPushButton* buttonNo = new QPushButton(QString::fromLocal8Bit("����"));
		buttonNo->setObjectName("itemBtnNo");
		buttonNo->setProperty("row", newRowIndex); // set custom property
		buttonNo->setProperty("column", 10);
		buttonNo->setProperty("approval", 2);

		connect(buttonNo, SIGNAL(clicked()), this, SLOT(slot_ItemBtnClicked()));
		ui->tableViewUser->setIndexWidget(m_modelUser->index(newRowIndex, 10), buttonNo);
		if (stData.approval == 1)
		{
			item = new QStandardItem(QString::fromLocal8Bit("��ͨ��"));
			item->setForeground(QBrush(QColor(Qt::green)));
			item->setTextAlignment(Qt::AlignCenter);  // �����ı����ж���
			m_modelUser->setItem(newRowIndex, 8, item);
			buttonNo->setEnabled(false);
			buttonYes->setEnabled(false);
		}
		else if (stData.approval == 0)
		{
			item = new QStandardItem(QString::fromLocal8Bit("�����"));
			item->setForeground(QBrush(QColor("#33C1FF")));
			item->setTextAlignment(Qt::AlignCenter);  // �����ı����ж���
			m_modelUser->setItem(newRowIndex, 8, item);
		}
		else if (stData.approval == 2)
		{
			item = new QStandardItem(QString::fromLocal8Bit("�Ѳ���"));
			item->setTextAlignment(Qt::AlignCenter);  // �����ı����ж���
			item->setForeground(QBrush(QColor(Qt::red)));
			m_modelUser->setItem(newRowIndex, 8, item);
			buttonNo->setEnabled(false);
			buttonYes->setEnabled(false);

		}

	}
}

void  ApprovalProgressDialog::slot_btnDataShow()
{
	ui->btnData->setStyleSheet(strQssBlue);
	ui->btnUser->setStyleSheet(strQssGray);
	ui->stackedWidget->setCurrentIndex(0);
}
void  ApprovalProgressDialog::slot_btnUserShow()
{
	ui->btnData->setStyleSheet(strQssGray);
	ui->btnUser->setStyleSheet(strQssBlue);
	ui->stackedWidget->setCurrentIndex(1);


	autoFlushDownloadData();
}



void ApprovalProgressDialog::slot_DataApprovalBtnLast()
{

	int curPage = ui->lineEditDataApprovalPage->text().toInt();
	if (curPage <= 1) return;

	curPage--;
	int offsetRows = (curPage - 1) * common::onePageRows;

	auto listDataApproval = processList(m_listDataApproval, common::onePageRows, offsetRows);
	flushDownloadTableShow(listDataApproval, offsetRows);

	ui->labelDataApprovalPageShow->setText(QString("%1/%2").arg(curPage).arg(m_DataApprovalTatalPage));
	ui->lineEditDataApprovalPage->setText(QString::number(curPage));

}

void ApprovalProgressDialog::slot_DataApprovalBtnNext()
{

	int curPage = ui->lineEditDataApprovalPage->text().toInt();
	if (curPage >= m_DataApprovalTatalPage) return;

	int offsetRows = curPage * common::onePageRows;

	auto listDataApproval = processList(m_listDataApproval, common::onePageRows, offsetRows);
	flushDownloadTableShow(listDataApproval, offsetRows);
	curPage++;
	ui->labelDataApprovalPageShow->setText(QString("%1/%2").arg(curPage).arg(m_DataApprovalTatalPage));
	ui->lineEditDataApprovalPage->setText(QString::number(curPage));
}

void ApprovalProgressDialog::slot_DataApprovalPageTo()
{
	ui->lineEditDataApprovalPage->setFocus();
	if (ui->lineEditDataApprovalPage->text().isEmpty()) return;

	int curPage = ui->lineEditDataApprovalPage->text().toInt();
	if (curPage <= 0)
	{
		curPage = 1;
		ui->labelDataApprovalPageShow->setText(QString("%1/%2").arg(1).arg(m_DataApprovalTatalPage));
		ui->lineEditDataApprovalPage->setText(QString::number(curPage));


		auto listDataApproval = processList(m_listDataApproval, common::onePageRows, 0);
		flushDownloadTableShow(listDataApproval, 0);


	}
	else if (curPage > m_DataApprovalTatalPage)
	{
		curPage = m_DataApprovalTatalPage;
		ui->labelDataApprovalPageShow->setText(QString("%1/%2").arg(curPage).arg(m_DataApprovalTatalPage));
		ui->lineEditDataApprovalPage->setText(QString::number(curPage));

		int offsetRows = (curPage - 1) * common::onePageRows;


		auto listDataApproval = processList(m_listDataApproval, common::onePageRows, offsetRows);
		flushDownloadTableShow(listDataApproval, offsetRows);

	}
	else
	{
		ui->labelDataApprovalPageShow->setText(QString("%1/%2").arg(curPage).arg(m_DataApprovalTatalPage));
		ui->lineEditDataApprovalPage->setText(QString::number(curPage));

		int offsetRows = (curPage - 1) * common::onePageRows;

		auto listDataApproval = processList(m_listDataApproval, common::onePageRows, offsetRows);
		flushDownloadTableShow(listDataApproval, offsetRows);
	}

}

// ��һҳ;
void ApprovalProgressDialog::slot_btnLast()
{
	int curPage = ui->lineEditUserPage->text().toInt();
	if (curPage <= 1) return;

	curPage--;
	int offsetRows = (curPage - 1) * common::onePageRows;

	auto listData = processList(m_listUser, common::onePageRows, offsetRows);
	flushUserTableShow(listData);

	ui->lineEditUserPage->setText(QString::number(curPage));
	ui->labelUserPage->setText(QString("%1/%2").arg(curPage).arg(m_UserTotalpage));
}

void ApprovalProgressDialog::slot_btnNext()
{
	int curPage = ui->lineEditUserPage->text().toInt();
	if (curPage >= m_UserTotalpage) return;


	int offsetRows = curPage * common::onePageRows;

	auto listData = processList(m_listUser, common::onePageRows, offsetRows);
	flushUserTableShow(listData);

	curPage++;
	ui->lineEditUserPage->setText(QString::number(curPage));
	ui->labelUserPage->setText(QString("%1/%2").arg(curPage).arg(m_UserTotalpage));
}

void ApprovalProgressDialog::slot_pageTo()
{
	//  ui->stackedWidget->setCurrentIndex(1);
	//  ui->lineEditUserPage->setFocus();
	if (ui->lineEditUserPage->text().isEmpty()) return;

	int curPage = ui->lineEditUserPage->text().toInt();
	if (curPage <= 0)
	{
		curPage = 1;
		ui->labelUserPage->setText(QString("%1/%2").arg(1).arg(m_UserTotalpage));
		ui->lineEditUserPage->setText(QString::number(curPage));

		db::databaseDI::Instance().get_user_list(m_listUser);
		auto listData = processList(m_listUser, common::onePageRows, 0);
		flushUserTableShow(listData);
	}
	else if (curPage > m_UserTotalpage)
	{
		curPage = m_UserTotalpage;
		ui->labelUserPage->setText(QString("%1/%2").arg(curPage).arg(m_UserTotalpage));
		ui->lineEditUserPage->setText(QString::number(curPage));

		int offsetRows = (curPage - 1) * common::onePageRows;

		db::databaseDI::Instance().get_user_list(m_listUser);
		auto listData = processList(m_listUser, common::onePageRows, offsetRows);
		flushUserTableShow(listData);

	}
	else
	{
		ui->labelUserPage->setText(QString("%1/%2").arg(curPage).arg(m_UserTotalpage));
		ui->lineEditUserPage->setText(QString::number(curPage));

		int offsetRows = (curPage - 1) * common::onePageRows;

		db::databaseDI::Instance().get_user_list(m_listUser);
		auto listData = processList(m_listUser, common::onePageRows, offsetRows);
		flushUserTableShow(listData);
	}
	// return true;
	 // ����һ��ģ��Ļس��¼�
	 //QKeyEvent* keyEvent = new QKeyEvent(QEvent::KeyPress, Qt::Key_Enter, Qt::NoModifier);

	 //// ����ģ���¼��� QlineEdit���Է�ֹ�����л�
	 //QCoreApplication::postEvent(ui->lineEditUserPage, keyEvent);
}

void ApprovalProgressDialog::slot_scrollMove(int value)
{

}




void ApprovalProgressDialog::slot_combocUserCurrentIndexChanged(int index)
{
	//for (int row = 0; row < m_modelUser->rowCount(); ++row)
	//{
	//    QStandardItem* item = m_modelUser->item(row, 1); // ��ȡĳ�е���
	//    if (item && item->text() == "11")
	//    {
	//        ui->tableViewUser->hideRow(row);
	//    }
	//}
}

void ApprovalProgressDialog::slot_dataApprovalQuery()
{
	//�������� ��ѯ;
	int index = ui->comboBoxDataField->currentIndex();
	//  std::string strFields = userTable_to_string((EUserTable)index);
	QString strQueryValue = ui->lineEditDataQueryValue->text();

	if (ui->checkBox_1->isChecked() == false)
	{
		if (strQueryValue.size() <= 0)
		{
			getDownloadData(m_listDataApproval);
		}
		else
		{
			getDownloadData(m_listDataApproval);
			if (index == 0)
			{
				std::string strValue = strQueryValue.toStdString();
				auto it = m_listDataApproval.begin();
				while (it != m_listDataApproval.end())
				{

					if ((*it).userName != strValue)
					{
						it = m_listDataApproval.erase(it); // ɾ��������������Ԫ�أ�������ָ����һ��Ԫ�صĵ�����
					}
					else
					{
						++it;
					}
				}
			}
			else if (index == 1)
			{
				std::string strValue = strQueryValue.toStdString();
				auto it = m_listDataApproval.begin();
				while (it != m_listDataApproval.end())
				{
					if ((*it).department != strValue)
					{
						it = m_listDataApproval.erase(it); // ɾ��������������Ԫ�أ�������ָ����һ��Ԫ�صĵ�����
					}
					else
					{
						++it;
					}
				}
			}
			//else if (index == 2)
			//{

			//	auto it = m_listDataApproval.begin();
			//	while (it != m_listDataApproval.end())
			//	{
			//		if (QDateTime::fromTime_t((*it).applicationTime).toString("yyyy/MM/dd HH:mm:ss") != strQueryValue)
			//		{
			//			it = m_listDataApproval.erase(it); // ɾ��������������Ԫ�أ�������ָ����һ��Ԫ�صĵ�����
			//		}
			//		else
			//		{
			//			++it;
			//		}
			//	}
			//}
			else if (index == 2)
			{
				std::string strValue = strQueryValue.toStdString();


				auto it = m_listDataApproval.begin();
				while (it != m_listDataApproval.end())
				{
					QString filePath = QString::fromLocal8Bit((*it).filePath.c_str());
					QFileInfo fileInfo1(filePath);

					if (!fileInfo1.fileName().contains(strQueryValue))
					{
						it = m_listDataApproval.erase(it); // ɾ��������������Ԫ�أ�������ָ����һ��Ԫ�صĵ�����
					}
					else
					{
						++it;
					}
				}
			}
			else if (index == 3)
			{
				std::string strValue = strQueryValue.toStdString();
				auto it = m_listDataApproval.begin();
				while (it != m_listDataApproval.end())
				{
					if ((*it).fileType != strValue)
					{
						it = m_listDataApproval.erase(it); // ɾ��������������Ԫ�أ�������ָ����һ��Ԫ�صĵ�����
					}
					else
					{
						++it;
					}
				}

			}
			//else if (index == 4)
			//{
			//	auto it = m_listDataApproval.begin();
			//	while (it != m_listDataApproval.end())
			//	{
			//		if (QDateTime::fromTime_t((*it).applicationTime).toString("yyyy/MM/dd HH:mm:ss") != strQueryValue)
			//		{
			//			it = m_listDataApproval.erase(it); // ɾ��������������Ԫ�أ�������ָ����һ��Ԫ�صĵ�����
			//		}
			//		else
			//		{
			//			++it;
			//		}
			//	}

			//}
			else if (index == 4)
			{
				int state = -1;
				if (strQueryValue == QString::fromLocal8Bit("��ͨ��"))
				{
					state = 1;
				}
				else if (strQueryValue == QString::fromLocal8Bit("�Ѳ���"))
				{
					state = 2;
				}
				else if (strQueryValue == QString::fromLocal8Bit("�����"))
				{
					state = 0;
				}
				auto it = m_listDataApproval.begin();
				while (it != m_listDataApproval.end())
				{
					if ((*it).status != state)
					{
						it = m_listDataApproval.erase(it); // ɾ��������������Ԫ�أ�������ָ����һ��Ԫ�صĵ�����
					}
					else
					{
						++it;
					}
				}
			}
		}
	}
	else if (ui->checkBox_1->isChecked() == true)
	{
		if (strQueryValue.size() <= 0)
		{
			getDownloadData(m_listDataApproval);
			QDateTime origin_time = QDateTime::fromString("1970/01/01 08:00", "yyyy/MM/dd HH:mm");
			QDateTime startDatetime = ui->dateTimeEdit1_start->dateTime();
			QDateTime endDatetime = ui->dateTimeEdit2_end->dateTime();
			qint64 nStartSteps = origin_time.msecsTo(startDatetime);
			qint64 nEndSteps = origin_time.msecsTo(endDatetime);
			if (nStartSteps > nEndSteps)
			{
				QMessageBox mesg;
				mesg.warning(this, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("��ѯ��ʼʱ�����ڽ���ʱ��!"));
				return;
			}

			auto it = m_listDataApproval.begin();
			while (it != m_listDataApproval.end())
			{

				if ((QDateTime::fromTime_t((*it).applicationTime).toString("yyyy/MM/dd HH:mm:ss") <= startDatetime.toString("yyyy/MM/dd HH:mm:ss")) ||
					(QDateTime::fromTime_t((*it).applicationTime).toString("yyyy/MM/dd HH:mm:ss") >= endDatetime.toString("yyyy/MM/dd HH:mm:ss")))
				{
					it = m_listDataApproval.erase(it); // ɾ��������������Ԫ�أ�������ָ����һ��Ԫ�صĵ�����
				}
				else
				{
					++it;
				}
			}
		}
		else
		{
			getDownloadData(m_listDataApproval);
			QDateTime origin_time = QDateTime::fromString("1970/01/01 08:00", "yyyy/MM/dd HH:mm");
			QDateTime startDatetime = ui->dateTimeEdit1_start->dateTime();
			QDateTime endDatetime = ui->dateTimeEdit2_end->dateTime();
			qint64 nStartSteps = origin_time.msecsTo(startDatetime);
			qint64 nEndSteps = origin_time.msecsTo(endDatetime);
			if (nStartSteps > nEndSteps)
			{
				QMessageBox mesg;
				mesg.warning(this, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("��ѯ��ʼʱ�����ڽ���ʱ��!"));
				return;
			}

			auto it = m_listDataApproval.begin();
			while (it != m_listDataApproval.end())
			{

				if ((QDateTime::fromTime_t((*it).applicationTime).toString("yyyy/MM/dd HH:mm:ss") <= startDatetime.toString("yyyy/MM/dd HH:mm:ss")) ||
					(QDateTime::fromTime_t((*it).applicationTime).toString("yyyy/MM/dd HH:mm:ss") >= endDatetime.toString("yyyy/MM/dd HH:mm:ss")))
				{
					it = m_listDataApproval.erase(it); // ɾ��������������Ԫ�أ�������ָ����һ��Ԫ�صĵ�����
				}
				else
				{
					++it;
				}
			}
			//��ʱ�������Ļ����ϣ�����ǰ�ߵ��ж�
			if (index == 0)
			{
				std::string strValue = strQueryValue.toStdString();
				auto it = m_listDataApproval.begin();
				while (it != m_listDataApproval.end())
				{

					if ((*it).userName != strValue)
					{
						it = m_listDataApproval.erase(it); // ɾ��������������Ԫ�أ�������ָ����һ��Ԫ�صĵ�����
					}
					else
					{
						++it;
					}
				}
			}
			else if (index == 1)
			{
				std::string strValue = strQueryValue.toStdString();
				auto it = m_listDataApproval.begin();
				while (it != m_listDataApproval.end())
				{
					if ((*it).department != strValue)
					{
						it = m_listDataApproval.erase(it); // ɾ��������������Ԫ�أ�������ָ����һ��Ԫ�صĵ�����
					}
					else
					{
						++it;
					}
				}
			}
			//else if (index == 2)
			//{

			//	auto it = m_listDataApproval.begin();
			//	while (it != m_listDataApproval.end())
			//	{
			//		if (QDateTime::fromTime_t((*it).applicationTime).toString("yyyy/MM/dd HH:mm:ss") != strQueryValue)
			//		{
			//			it = m_listDataApproval.erase(it); // ɾ��������������Ԫ�أ�������ָ����һ��Ԫ�صĵ�����
			//		}
			//		else
			//		{
			//			++it;
			//		}
			//	}
			//}
			else if (index == 2)
			{
				std::string strValue = strQueryValue.toStdString();


				auto it = m_listDataApproval.begin();
				while (it != m_listDataApproval.end())
				{
					QString filePath = QString::fromLocal8Bit((*it).filePath.c_str());
					QFileInfo fileInfo1(filePath);

					if (!fileInfo1.fileName().contains(strQueryValue))
					{
						it = m_listDataApproval.erase(it); // ɾ��������������Ԫ�أ�������ָ����һ��Ԫ�صĵ�����
					}
					else
					{
						++it;
					}
				}
			}
			else if (index == 3)
			{
				std::string strValue = strQueryValue.toStdString();
				auto it = m_listDataApproval.begin();
				while (it != m_listDataApproval.end())
				{
					if ((*it).fileType != strValue)
					{
						it = m_listDataApproval.erase(it); // ɾ��������������Ԫ�أ�������ָ����һ��Ԫ�صĵ�����
					}
					else
					{
						++it;
					}
				}

			}
			//else if (index == 4)
			//{
			//	auto it = m_listDataApproval.begin();
			//	while (it != m_listDataApproval.end())
			//	{
			//		if (QDateTime::fromTime_t((*it).applicationTime).toString("yyyy/MM/dd HH:mm:ss") != strQueryValue)
			//		{
			//			it = m_listDataApproval.erase(it); // ɾ��������������Ԫ�أ�������ָ����һ��Ԫ�صĵ�����
			//		}
			//		else
			//		{
			//			++it;
			//		}
			//	}

			//}
			else if (index == 4)
			{
				int state = -1;
				if (strQueryValue == QString::fromLocal8Bit("��ͨ��"))
				{
					state = 1;
				}
				else if (strQueryValue == QString::fromLocal8Bit("�Ѳ���"))
				{
					state = 2;
				}
				else if (strQueryValue == QString::fromLocal8Bit("�����"))
				{
					state = 0;
				}
				auto it = m_listDataApproval.begin();
				while (it != m_listDataApproval.end())
				{
					if ((*it).status != state)
					{
						it = m_listDataApproval.erase(it); // ɾ��������������Ԫ�أ�������ָ����һ��Ԫ�صĵ�����
					}
					else
					{
						++it;
					}
				}
			}
		}
	}

	m_DataApprovalTotalRows = m_listDataApproval.size();
	if (m_DataApprovalTotalRows <= common::tableViewPageRows)
	{
		m_DataApprovalTatalPage = 1;
	}
	else
	{
		m_DataApprovalTatalPage = m_DataApprovalTotalRows / common::tableViewPageRows;
		if (m_DataApprovalTatalPage % common::tableViewPageRows != 0)
		{
			m_DataApprovalTatalPage++;
		}
	}

	ui->labelDataApprovalPageShow->setText(QString("%1/%2").arg(1).arg(m_DataApprovalTatalPage));
	ui->lineEditDataApprovalPage->setText("1");

	auto listDataApproval = processList(m_listDataApproval, common::onePageRows, 0);

	flushDownloadTableShow(listDataApproval, 0);
}

void ApprovalProgressDialog::slot_userQuery()
{
	int index = ui->comboBoxUserField->currentIndex();
	std::string strFields = userTable_to_string((EUserTable)index);
	QString strQueryValue = ui->lineEditUserQueryValue->text();
	if (ui->checkBox_2->isChecked() == false)
	{
		if (strQueryValue.size() <= 0)
		{
			db::databaseDI::Instance().get_user_list(m_listUser);

		}
		else
		{
			db::databaseDI::Instance().get_user_list(m_listUser);
			if (index == 0)
			{
				std::string strValue = strQueryValue.toStdString();
				auto it = m_listUser.begin();
				while (it != m_listUser.end())
				{

					if ((*it).name != strValue)
					{
						it = m_listUser.erase(it); // ɾ��������������Ԫ�أ�������ָ����һ��Ԫ�صĵ�����
					}
					else
					{
						++it;
					}
				}
			}
			else if (index == 1)
			{
				std::string strValue = strQueryValue.toStdString();
				auto it = m_listUser.begin();
				while (it != m_listUser.end())
				{
					if ((*it).department != strValue)
					{
						it = m_listUser.erase(it); // ɾ��������������Ԫ�أ�������ָ����һ��Ԫ�صĵ�����
					}
					else
					{
						++it;
					}
				}
			}
			//else if (index == 2)
			//{

			//	auto it = m_listUser.begin();
			//	while (it != m_listUser.end())
			//	{
			//		if (QDateTime::fromTime_t((*it).CreateTime).toString("yyyy/MM/dd HH:mm") != strQueryValue)
			//		{
			//			it = m_listUser.erase(it); // ɾ��������������Ԫ�أ�������ָ����һ��Ԫ�صĵ�����
			//		}
			//		else
			//		{
			//			++it;
			//		}
			//	}
			//}
			else if (index == 2)
			{
				std::string strValue = strQueryValue.toStdString();
				auto it = m_listUser.begin();
				while (it != m_listUser.end())
				{
					if ((*it).UserName != strValue)
					{
						it = m_listUser.erase(it); // ɾ��������������Ԫ�أ�������ָ����һ��Ԫ�صĵ�����
					}
					else
					{
						++it;
					}
				}
			}
			else if (index == 3)
			{
				std::string strValue = strQueryValue.toStdString();
				auto it = m_listUser.begin();
				while (it != m_listUser.end())
				{
					if ((*it).Password != strValue)
					{
						it = m_listUser.erase(it); // ɾ��������������Ԫ�أ�������ָ����һ��Ԫ�صĵ�����
					}
					else
					{
						++it;
					}
				}
			}
			else if (index == 4)
			{
				std::string strValue = strQueryValue.toStdString();
				auto it = m_listUser.begin();
				while (it != m_listUser.end())
				{
					if ((*it).JobTitle != strValue)
					{
						it = m_listUser.erase(it); // ɾ��������������Ԫ�أ�������ָ����һ��Ԫ�صĵ�����
					}
					else
					{
						++it;
					}
				}
			}
			else if (index == 5)
			{
				std::string strValue = strQueryValue.toStdString();
				auto it = m_listUser.begin();
				while (it != m_listUser.end())
				{
					if ((*it).PhoneNumber != strValue)
					{
						it = m_listUser.erase(it); // ɾ��������������Ԫ�أ�������ָ����һ��Ԫ�صĵ�����
					}
					else
					{
						++it;
					}
				}
			}
			else if (index == 6)
			{
				int  pop = -1;
				if (strQueryValue == QString::fromLocal8Bit("����Ա"))
				{
					pop = 0;
				}
				else if (strQueryValue == QString::fromLocal8Bit("��ͨ�û�"))
				{
					pop = 1;
				}
				auto it = m_listUser.begin();
				while (it != m_listUser.end())
				{
					if ((*it).Pop != pop)
					{
						it = m_listUser.erase(it); // ɾ��������������Ԫ�أ�������ָ����һ��Ԫ�صĵ�����
					}
					else
					{
						++it;
					}
				}
			}
			else if (index == 7)
			{
				int state = -1;
				if (strQueryValue == QString::fromLocal8Bit("��ͨ��"))
				{
					state = 1;
				}
				else if (strQueryValue == QString::fromLocal8Bit("�Ѳ���"))
				{
					state = 2;
				}
				else if (strQueryValue == QString::fromLocal8Bit("�����"))
				{
					state = 0;
				}
				auto it = m_listUser.begin();
				while (it != m_listUser.end())
				{
					if ((*it).approval != state)
					{
						it = m_listUser.erase(it); // ɾ��������������Ԫ�أ�������ָ����һ��Ԫ�صĵ�����
					}
					else
					{
						++it;
					}
				}
			}

			/* db::databaseDI::Instance().get_user_list_by_condition(m_listUser, strFields,strValue.toStdString());
		   */
		}
	}
	else if (ui->checkBox_2->isChecked() == true)
	{
		if (strQueryValue.size() <= 0)
		{
			db::databaseDI::Instance().get_user_list(m_listUser);
			QDateTime origin_time = QDateTime::fromString("1970/01/01 08:00", "yyyy/MM/dd HH:mm");
			QDateTime startDatetime = ui->dateTimeEdit3_start->dateTime();
			QDateTime endDatetime = ui->dateTimeEdit4_end->dateTime();
			qint64 nStartSteps = origin_time.msecsTo(startDatetime);
			qint64 nEndSteps = origin_time.msecsTo(endDatetime);
			if (nStartSteps > nEndSteps)
			{
				QMessageBox mesg;
				mesg.warning(this, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("��ѯ��ʼʱ�����ڽ���ʱ��!"));
				return;
			}

			auto it = m_listUser.begin();
			while (it != m_listUser.end())
			{

				if ((QDateTime::fromTime_t((*it).CreateTime).toString("yyyy/MM/dd HH:mm:ss") <= startDatetime.toString("yyyy/MM/dd HH:mm:ss")) ||
					(QDateTime::fromTime_t((*it).CreateTime).toString("yyyy/MM/dd HH:mm:ss") >= endDatetime.toString("yyyy/MM/dd HH:mm:ss")))
				{
					it = m_listUser.erase(it); // ɾ��������������Ԫ�أ�������ָ����һ��Ԫ�صĵ�����
				}
				else
				{
					++it;
				}
			}
		}
		else
		{
			db::databaseDI::Instance().get_user_list(m_listUser);
			QDateTime origin_time = QDateTime::fromString("1970/01/01 08:00", "yyyy/MM/dd HH:mm");
			QDateTime startDatetime = ui->dateTimeEdit3_start->dateTime();
			QDateTime endDatetime = ui->dateTimeEdit4_end->dateTime();
			qint64 nStartSteps = origin_time.msecsTo(startDatetime);
			qint64 nEndSteps = origin_time.msecsTo(endDatetime);
			if (nStartSteps > nEndSteps)
			{
				QMessageBox mesg;
				mesg.warning(this, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("��ѯ��ʼʱ�����ڽ���ʱ��!"));
				return;
			}

			auto it = m_listUser.begin();
			while (it != m_listUser.end())
			{

				if ((QDateTime::fromTime_t((*it).CreateTime).toString("yyyy/MM/dd HH:mm:ss") <= startDatetime.toString("yyyy/MM/dd HH:mm:ss")) ||
					(QDateTime::fromTime_t((*it).CreateTime).toString("yyyy/MM/dd HH:mm:ss") >= endDatetime.toString("yyyy/MM/dd HH:mm:ss")))
				{
					it = m_listUser.erase(it); // ɾ��������������Ԫ�أ�������ָ����һ��Ԫ�صĵ�����
				}
				else
				{
					++it;
				}
			}

			//��ʱ�������Ļ����ϣ�����ǰ�ߵ��ж���������
			if (index == 0)
			{
				std::string strValue = strQueryValue.toStdString();
				auto it = m_listUser.begin();
				while (it != m_listUser.end())
				{

					if ((*it).name != strValue)
					{
						it = m_listUser.erase(it); // ɾ��������������Ԫ�أ�������ָ����һ��Ԫ�صĵ�����
					}
					else
					{
						++it;
					}
				}
			}
			else if (index == 1)
			{
				std::string strValue = strQueryValue.toStdString();
				auto it = m_listUser.begin();
				while (it != m_listUser.end())
				{
					if ((*it).department != strValue)
					{
						it = m_listUser.erase(it); // ɾ��������������Ԫ�أ�������ָ����һ��Ԫ�صĵ�����
					}
					else
					{
						++it;
					}
				}
			}
			//else if (index == 2)
			//{

			//	auto it = m_listUser.begin();
			//	while (it != m_listUser.end())
			//	{
			//		if (QDateTime::fromTime_t((*it).CreateTime).toString("yyyy/MM/dd HH:mm") != strQueryValue)
			//		{
			//			it = m_listUser.erase(it); // ɾ��������������Ԫ�أ�������ָ����һ��Ԫ�صĵ�����
			//		}
			//		else
			//		{
			//			++it;
			//		}
			//	}
			//}
			else if (index == 2)
			{
				std::string strValue = strQueryValue.toStdString();
				auto it = m_listUser.begin();
				while (it != m_listUser.end())
				{
					if ((*it).UserName != strValue)
					{
						it = m_listUser.erase(it); // ɾ��������������Ԫ�أ�������ָ����һ��Ԫ�صĵ�����
					}
					else
					{
						++it;
					}
				}
			}
			else if (index == 3)
			{
				std::string strValue = strQueryValue.toStdString();
				auto it = m_listUser.begin();
				while (it != m_listUser.end())
				{
					if ((*it).Password != strValue)
					{
						it = m_listUser.erase(it); // ɾ��������������Ԫ�أ�������ָ����һ��Ԫ�صĵ�����
					}
					else
					{
						++it;
					}
				}
			}
			else if (index == 4)
			{
				std::string strValue = strQueryValue.toStdString();
				auto it = m_listUser.begin();
				while (it != m_listUser.end())
				{
					if ((*it).JobTitle != strValue)
					{
						it = m_listUser.erase(it); // ɾ��������������Ԫ�أ�������ָ����һ��Ԫ�صĵ�����
					}
					else
					{
						++it;
					}
				}
			}
			else if (index == 5)
			{
				std::string strValue = strQueryValue.toStdString();
				auto it = m_listUser.begin();
				while (it != m_listUser.end())
				{
					if ((*it).PhoneNumber != strValue)
					{
						it = m_listUser.erase(it); // ɾ��������������Ԫ�أ�������ָ����һ��Ԫ�صĵ�����
					}
					else
					{
						++it;
					}
				}
			}
			else if (index == 6)
			{
				int  pop = -1;
				if (strQueryValue == QString::fromLocal8Bit("����Ա"))
				{
					pop = 0;
				}
				else if (strQueryValue == QString::fromLocal8Bit("��ͨ�û�"))
				{
					pop = 1;
				}
				auto it = m_listUser.begin();
				while (it != m_listUser.end())
				{
					if ((*it).Pop != pop)
					{
						it = m_listUser.erase(it); // ɾ��������������Ԫ�أ�������ָ����һ��Ԫ�صĵ�����
					}
					else
					{
						++it;
					}
				}
			}
			else if (index == 7)
			{
				int state = -1;
				if (strQueryValue == QString::fromLocal8Bit("��ͨ��"))
				{
					state = 1;
				}
				else if (strQueryValue == QString::fromLocal8Bit("�Ѳ���"))
				{
					state = 2;
				}
				else if (strQueryValue == QString::fromLocal8Bit("�����"))
				{
					state = 0;
				}
				auto it = m_listUser.begin();
				while (it != m_listUser.end())
				{
					if ((*it).approval != state)
					{
						it = m_listUser.erase(it); // ɾ��������������Ԫ�أ�������ָ����һ��Ԫ�صĵ�����
					}
					else
					{
						++it;
					}
				}
			}
		}
	}

	m_UserTotalRows = m_listUser.size();

	if (m_UserTotalRows < common::tableViewPageRows)
	{
		m_UserTotalpage = 1;
	}
	else
	{
		m_UserTotalpage = m_UserTotalRows / common::tableViewPageRows;
		if (m_UserTotalpage % common::tableViewPageRows != 0)
		{
			m_UserTotalpage++;
		}
	}

	ui->labelUserPage->setText(QString("%1/%2").arg(1).arg(m_UserTotalpage));
	ui->lineEditUserPage->setText("1");

	auto listData = processList(m_listUser, common::onePageRows, 0);
	flushUserTableShow(listData);

}
void ApprovalProgressDialog::slot_spinBoxEnter()
{
	// spinBox->setFocus();
}
void ApprovalProgressDialog::slot_btnFlushDownload()
{
	autoFlushDownloadData();
}
void ApprovalProgressDialog::slot_DataItemBtnClicked()
{
	QPushButton* pButton = (QPushButton*)sender();
	int row = pButton->property("row").toInt();
	int column = pButton->property("column").toInt();
	int approval = pButton->property("approval").toInt();

	QModelIndex index = m_modelDataApproval->index(row, 0);
	int id = m_modelDataApproval->data(index, Qt::UserRole).toInt();

	if (!db::databaseDI::Instance().update_download_approval_status(id, approval))
	{
		qDebug() << "db::databaseDI::Instance().update_user_state  error----";
		return;
	}

	if (approval == 1)
	{
		auto item = m_modelDataApproval->item(row, 7);
		item->setText(QString::fromLocal8Bit("��ͨ��"));
		item->setForeground(QBrush(QColor(Qt::green)));
	}
	else if (approval == 2)
	{
		auto item = m_modelDataApproval->item(row, 7);
		item->setText(QString::fromLocal8Bit("�Ѳ���"));
		item->setTextAlignment(Qt::AlignCenter);  // �����ı����ж���
		item->setForeground(QBrush(QColor(Qt::red)));
	}

	// ��ȡ��ťָ��
	index = m_modelDataApproval->index(row, 8);
	QWidget* widget = ui->tableView->indexWidget(index);
	if (widget)
	{
		QPushButton* pButtonYes = qobject_cast<QPushButton*>(widget);
		if (pButtonYes)
		{
			pButtonYes->setEnabled(false);
		}
	}
	index = m_modelDataApproval->index(row, 9);
	widget = ui->tableView->indexWidget(index);
	if (widget)
	{
		QPushButton* pButtonNo = qobject_cast<QPushButton*>(widget);
		if (pButtonNo)
		{
			pButtonNo->setEnabled(false);
		}
	}

	ui->tableView->setCurrentIndex(index);
}

void ApprovalProgressDialog::slot_ItemBtnClicked()
{
	QPushButton* pButton = (QPushButton*)sender();
	int row = pButton->property("row").toInt();
	int column = pButton->property("column").toInt();
	int approval = pButton->property("approval").toInt();

	QModelIndex index = m_modelUser->index(row, 0);
	int id = m_modelUser->data(index, Qt::UserRole).toInt();

	if (!db::databaseDI::Instance().update_user_state(id, approval))
	{
		qDebug() << "db::databaseDI::Instance().update_user_state  error----";
		return;
	}

	if (approval == 1)
	{
		auto item = m_modelUser->item(row, 8);
		item->setText(QString::fromLocal8Bit("��ͨ��"));
		item->setForeground(QBrush(QColor(Qt::green)));
	}
	else if (approval == 2)
	{
		auto item = m_modelUser->item(row, 8);
		item->setText(QString::fromLocal8Bit("�Ѳ���"));
		item->setTextAlignment(Qt::AlignCenter);  // �����ı����ж���
		item->setForeground(QBrush(QColor(Qt::red)));
	}

	// ��ȡ��ťָ��
	index = m_modelUser->index(row, 9);
	QWidget* widget = ui->tableViewUser->indexWidget(index);
	if (widget)
	{
		QPushButton* pButtonYes = qobject_cast<QPushButton*>(widget);
		if (pButtonYes)
		{
			pButtonYes->setEnabled(false);
		}
	}
	index = m_modelUser->index(row, 10);
	widget = ui->tableViewUser->indexWidget(index);
	if (widget)
	{
		QPushButton* pButtonNo = qobject_cast<QPushButton*>(widget);
		if (pButtonNo)
		{
			pButtonNo->setEnabled(false);
		}
	}

	ui->tableViewUser->setCurrentIndex(index);
}

