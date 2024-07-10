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


ApprovalProgressDialog::ApprovalProgressDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ApprovalProgressDialog)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/image/ApprovalProgress.png"));
    ui->stackedWidget->setCurrentIndex(0);
    //ui->stackedWidget->setFocusPolicy(Qt::NoFocus);



    m_modelDataApproval = new QStandardItemModel();
    m_modelDataApproval->setColumnCount(12);
    m_modelDataApproval->setHeaderData(0, Qt::Horizontal, QString::fromLocal8Bit("���"));
    m_modelDataApproval->setHeaderData(1, Qt::Horizontal, QString::fromLocal8Bit("������"));
    m_modelDataApproval->setHeaderData(2, Qt::Horizontal, QString::fromLocal8Bit("���ڲ���"));
    m_modelDataApproval->setHeaderData(3, Qt::Horizontal, QString::fromLocal8Bit("����ʱ��"));
    m_modelDataApproval->setHeaderData(4, Qt::Horizontal, QString::fromLocal8Bit("����"));
    m_modelDataApproval->setHeaderData(5, Qt::Horizontal, QString::fromLocal8Bit("����ʱ��"));
    m_modelDataApproval->setHeaderData(6, Qt::Horizontal, QString::fromLocal8Bit("������"));
    m_modelDataApproval->setHeaderData(7, Qt::Horizontal, QString::fromLocal8Bit("�ļ���"));
    m_modelDataApproval->setHeaderData(8, Qt::Horizontal, QString::fromLocal8Bit("�ļ�����"));
    m_modelDataApproval->setHeaderData(9, Qt::Horizontal, QString::fromLocal8Bit("״̬"));
    m_modelDataApproval->setHeaderData(10, Qt::Horizontal, QString::fromLocal8Bit("����"));
    m_modelDataApproval->setHeaderData(11, Qt::Horizontal, QString::fromLocal8Bit("����"));

    /* QStringList labels = QObject::trUtf8("ID,����,value,ʱ��,���").simplified().split(",");
     model->setHorizontalHeaderLabels(labels);*/
    ui->tableView->setModel(m_modelDataApproval);
    common::setTableViewBasicConfiguration(ui->tableView);
    //ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    //ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);   // ѡ������
    //ui->tableView->verticalHeader()->setDefaultSectionSize(28);
    ui->tableView->verticalHeader()->setVisible(false);
   
    //for (int i = 0; i < 7; i++)
    //{
    //    m_modelDataApproval->setItem(i, 0, new QStandardItem(QString::number(i + 1)));
    //    m_modelDataApproval->setItem(i, 1, new QStandardItem(QString("hello qt tablview %1").arg(i)));
    //    m_modelDataApproval->setItem(i, 2, new QStandardItem("normal"));
    //    m_modelDataApproval->setItem(i, 3, new QStandardItem("normal"));
    //    m_modelDataApproval->setItem(i, 4, new QStandardItem("normal"));
    //    m_modelDataApproval->setItem(i, 5, new QStandardItem("normal"));
    //    m_modelDataApproval->setItem(i, 6, new QStandardItem("normal"));
    //    m_modelDataApproval->setItem(i, 7, new QStandardItem("normal"));
    //    m_modelDataApproval->setItem(i, 8, new QStandardItem("normal"));
    //    m_modelDataApproval->setItem(i, 9, new QStandardItem("normal"));

    //    // add button to the last column
    //    QPushButton* button = new QPushButton(QString::fromLocal8Bit("ͬ��"));
    //    button->setObjectName("itemBtnYes");
    //    button->setProperty("row", i); // set custom property
    //    button->setProperty("column", 7);
    //    button->setProperty("name", QString("hello qt tablview %1").arg(i));
    //    connect(button, SIGNAL(clicked()), this, SLOT(slot_ItemBtnClicked()));
    //    ui->tableView->setIndexWidget(m_modelDataApproval->index(i, 10), button);

    //    button = new QPushButton(QString::fromLocal8Bit("����"));
    //    button->setObjectName("itemBtnNo");
    //    button->setProperty("row", i); // set custom property
    //    button->setProperty("column", 8);
    //    button->setProperty("name", QString("hello qt tablview %1").arg(i));
    //    connect(button, SIGNAL(clicked()), this, SLOT(slot_ItemBtnClicked()));
    //    ui->tableView->setIndexWidget(m_modelDataApproval->index(i, 11), button);
    //}

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
    //ui->tableViewUser->setFixedHeight(common::tableViewHeight);
   
    connect(ui->btnData, &QPushButton::clicked, [this]() {
        ui->stackedWidget->setCurrentIndex(0);
        });
    connect(ui->btnUser, &QPushButton::clicked, [this]() {
        ui->stackedWidget->setCurrentIndex(1);
        });

    connect(ui->btnUserLast, &QPushButton::clicked, this, &ApprovalProgressDialog::slot_btnLast);
    connect(ui->btnUserNext, &QPushButton::clicked, this, &ApprovalProgressDialog::slot_btnNext);
    connect(ui->lineEditUserPage, &QLineEdit::editingFinished, this, &ApprovalProgressDialog::slot_pageTo);

    connect(ui->btnDataApprovalLast, &QPushButton::clicked, this, &ApprovalProgressDialog::slot_DataApprovalBtnLast);
    connect(ui->btnDataApprovalNext, &QPushButton::clicked, this, &ApprovalProgressDialog::slot_DataApprovalBtnNext);
    connect(ui->lineEditDataApprovalPage, &QLineEdit::editingFinished, this, &ApprovalProgressDialog::slot_DataApprovalPageTo);

    ui->lineEditUserPage->setText(QString::number(1));
    QScrollBar* scrollBar = (QScrollBar*)ui->tableViewUser->verticalScrollBar();
    connect(scrollBar, SIGNAL(valueChanged(int)), this, SLOT(scrollMove(int)));

    ui->comboBoxUserField->addItem(QString::fromLocal8Bit("������"));
    ui->comboBoxUserField->addItem(QString::fromLocal8Bit("���ڲ���"));
    ui->comboBoxUserField->addItem(QString::fromLocal8Bit("����ʱ��"));
    ui->comboBoxUserField->addItem(QString::fromLocal8Bit("�û���"));
    ui->comboBoxUserField->addItem(QString::fromLocal8Bit("����"));
    ui->comboBoxUserField->addItem(QString::fromLocal8Bit("ְλ"));
    ui->comboBoxUserField->addItem(QString::fromLocal8Bit("�ֻ���"));
    ui->comboBoxUserField->addItem(QString::fromLocal8Bit("Ȩ��"));
    ui->comboBoxUserField->addItem(QString::fromLocal8Bit("״̬"));
    connect(ui->comboBoxUserField, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_combocUserCurrentIndexChanged(int)));
    connect(ui->btnUserQuery, &QPushButton::clicked, this, &ApprovalProgressDialog::slot_userQuery); // ��ѯ

    init();
}

ApprovalProgressDialog::~ApprovalProgressDialog()
{
    delete ui;
}

void ApprovalProgressDialog::init()
{
    
    if (db::databaseDI::Instance().get_data_approval_count(m_DataApprovalTotalRows))
    {
        m_DataApprovalTatalPage = m_DataApprovalTotalRows / common::tableViewPageRows;
        if (m_DataApprovalTatalPage % common::tableViewPageRows != 0)
        {
            m_DataApprovalTatalPage++;
        }
        ui->labelDataApprovalPageShow->setText(QString("%1/%2").arg(1).arg(m_DataApprovalTatalPage));
        ui->lineEditDataApprovalPage->setText("1");
        std::list<table_dataApproval> listData;
        db::databaseDI::Instance().get_data_approval_list_by_condition(listData, common::onePageRows, 0);
        flushDataTableShow(listData, 0);
        
       // m_DataApprovalTatalPage
    }
   


    if (db::databaseDI::Instance().get_user_count(m_UserTotalRows))
    {
        m_UserTotalpage = m_UserTotalRows / common::tableViewPageRows;
        if (m_UserTotalpage % common::tableViewPageRows != 0)
        {
            m_UserTotalpage++;
        }
        ui->labelUserPage->setText(QString("%1/%2").arg(1).arg(m_UserTotalpage));
        ui->lineEditUserPage->setText("1");

        std::list<table_user> listUser;

        db::databaseDI::Instance().get_user_list_by_condition(listUser, common::onePageRows,0);
        flushUserTableShow(listUser); 
    }

    /*std::list<table_user> listUser;
    db::databaseDI::Instance().get_user_list(listUser);
    flushUserTableShow(listUser);*/
}

void ApprovalProgressDialog::flushDataTableShow(std::list<table_dataApproval> &listData, const int& offsetRows)
{
    common::delAllModelRow(m_modelDataApproval);
    //  ��ѯ���ݿ���ʾ;
   // 
    int i = offsetRows;
    for (auto& stData : listData)
    {
        int newRowIndex = m_modelDataApproval->rowCount(); // ��ȡ��ǰ����
        m_modelDataApproval->insertRow(newRowIndex); // ��������

        QStandardItem* item = new QStandardItem(QString::number(i+1));
        item->setTextAlignment(Qt::AlignCenter);  // �����ı����ж���
        //item->setData(QString::fromStdString(stData.name), Qt::ToolTipRole);
        m_modelDataApproval->setItem(newRowIndex, 0, item);
         
        QModelIndex index = m_modelDataApproval->index(newRowIndex, 0);
        m_modelDataApproval->setData(index, stData.id,Qt::UserRole);  // ����id;
        //  item->setText(QString::fromStdString(stData.name));

        item = new QStandardItem(QString::fromStdString(stData.proposer));
        item->setTextAlignment(Qt::AlignCenter);  // �����ı����ж���
        m_modelDataApproval->setItem(newRowIndex, 1, item);
       
        item = new QStandardItem(QString::fromStdString(stData.department));
        item->setTextAlignment(Qt::AlignCenter);  // �����ı����ж���
        m_modelDataApproval->setItem(newRowIndex, 2, item);

        item = new QStandardItem(QDateTime::fromTime_t(stData.applicationTime).toString("yyyy/MM/dd HH:mm:ss"));
        item->setTextAlignment(Qt::AlignCenter);  // �����ı����ж���
        m_modelDataApproval->setItem(newRowIndex, 3, item);

        item = new QStandardItem(QString::fromStdString(stData.host));
        item->setTextAlignment(Qt::AlignCenter);  // �����ı����ж���
        m_modelDataApproval->setItem(newRowIndex, 4, item);

        item = new QStandardItem(QDateTime::fromTime_t(stData.createTime).toString("yyyy/MM/dd HH:mm:ss"));
        item->setTextAlignment(Qt::AlignCenter);  // �����ı����ж���
        m_modelDataApproval->setItem(newRowIndex, 5, item);

        item = new QStandardItem(QString::fromStdString(stData.tool));
        item->setTextAlignment(Qt::AlignCenter);  // �����ı����ж���
        m_modelDataApproval->setItem(newRowIndex, 6, item);
        item = new QStandardItem(QString::fromStdString(stData.fileName));
        item->setTextAlignment(Qt::AlignCenter);  // �����ı����ж���
        m_modelDataApproval->setItem(newRowIndex, 7, item);

        item = new QStandardItem(QString::fromStdString(stData.fileType));
        item->setTextAlignment(Qt::AlignCenter);  // �����ı����ж���
        m_modelDataApproval->setItem(newRowIndex, 8, item);

        // add button to the last column
        QPushButton* buttonYes = new QPushButton(QString::fromLocal8Bit("ͬ��"));
        buttonYes->setObjectName("itemBtnYes");
        buttonYes->setProperty("row", newRowIndex); // set custom property
        buttonYes->setProperty("column", 10);
        buttonYes->setProperty("approval", 1);
        connect(buttonYes, SIGNAL(clicked()), this, SLOT(slot_DataItemBtnClicked()));
        ui->tableView->setIndexWidget(m_modelDataApproval->index(newRowIndex, 10), buttonYes);

        QPushButton* buttonNo = new QPushButton(QString::fromLocal8Bit("����"));
        buttonNo->setObjectName("itemBtnNo");
        buttonNo->setProperty("row", newRowIndex); // set custom property
        buttonNo->setProperty("column", 11);
        buttonNo->setProperty("approval", 2);

        connect(buttonNo, SIGNAL(clicked()), this, SLOT(slot_DataItemBtnClicked()));
        ui->tableView->setIndexWidget(m_modelDataApproval->index(newRowIndex, 11), buttonNo);
        if (stData.state == 1)
        {
            item = new QStandardItem(QString::fromLocal8Bit("��ͨ��"));
            item->setForeground(QBrush(QColor(Qt::green)));
            item->setTextAlignment(Qt::AlignCenter);  // �����ı����ж���
            m_modelDataApproval->setItem(newRowIndex, 9, item);
            buttonNo->setEnabled(false);
            buttonYes->setEnabled(false);
        }
        else if (stData.state == 0)
        {
            item = new QStandardItem(QString::fromLocal8Bit("�����"));
            item->setForeground(QBrush(QColor("#33C1FF")));
            item->setTextAlignment(Qt::AlignCenter);  // �����ı����ж���
            m_modelDataApproval->setItem(newRowIndex, 9, item);
        }
        else if (stData.state == 2)
        {
            item = new QStandardItem(QString::fromLocal8Bit("�Ѳ���"));
            item->setTextAlignment(Qt::AlignCenter);  // �����ı����ж���
            item->setForeground(QBrush(QColor(Qt::red)));
            m_modelDataApproval->setItem(newRowIndex, 9, item);
            buttonNo->setEnabled(false);
            buttonYes->setEnabled(false);

        }
        i++;
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

void ApprovalProgressDialog::slot_DataApprovalBtnLast()
{

    int curPage = ui->lineEditDataApprovalPage->text().toInt();
    if (curPage <= 1) return;

    curPage--;
    int offsetRows = (curPage - 1) * common::onePageRows;

    std::list<table_dataApproval> listData;
    db::databaseDI::Instance().get_data_approval_list_by_condition(listData, common::onePageRows, offsetRows);
    flushDataTableShow(listData, offsetRows);
    ui->labelDataApprovalPageShow->setText(QString("%1/%2").arg(curPage).arg(m_DataApprovalTatalPage));
    ui->lineEditDataApprovalPage->setText(QString::number(curPage));
  

}

void ApprovalProgressDialog::slot_DataApprovalBtnNext()
{

    int curPage = ui->lineEditDataApprovalPage->text().toInt();
    if (curPage >= m_DataApprovalTatalPage) return;

    int offsetRows = curPage * common::onePageRows;

    std::list<table_dataApproval> listData;
    db::databaseDI::Instance().get_data_approval_list_by_condition(listData, common::onePageRows, offsetRows);
    flushDataTableShow(listData, offsetRows);
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

        std::list<table_dataApproval> listData;
        db::databaseDI::Instance().get_data_approval_list_by_condition(listData, common::onePageRows, 0);
        flushDataTableShow(listData, 0);
    }
    else if (curPage > m_DataApprovalTatalPage)
    {
        curPage = m_DataApprovalTatalPage;
        ui->labelDataApprovalPageShow->setText(QString("%1/%2").arg(curPage).arg(m_DataApprovalTatalPage));
        ui->lineEditDataApprovalPage->setText(QString::number(curPage));

        int offsetRows = (curPage - 1) * common::onePageRows;

        std::list<table_dataApproval> listData;
        db::databaseDI::Instance().get_data_approval_list_by_condition(listData, common::onePageRows, offsetRows);
        flushDataTableShow(listData, offsetRows);

    }
    else
    {
        ui->labelDataApprovalPageShow->setText(QString("%1/%2").arg(curPage).arg(m_DataApprovalTatalPage));
        ui->lineEditDataApprovalPage->setText(QString::number(curPage));

        int offsetRows = (curPage - 1) * common::onePageRows;
        std: std::list<table_dataApproval> listData;
        db::databaseDI::Instance().get_data_approval_list_by_condition(listData, common::onePageRows, offsetRows);
        flushDataTableShow(listData, offsetRows);
    }

   
  
}

// ��һҳ;
void ApprovalProgressDialog::slot_btnLast()
{
    int curPage = ui->lineEditUserPage->text().toInt();
    if (curPage <= 1) return;
    
    curPage--;
    int offsetRows = (curPage-1) * common::onePageRows;
    std::list<table_user> listUser;
    db::databaseDI::Instance().get_user_list_by_condition(listUser, common::onePageRows, offsetRows);
    flushUserTableShow(listUser);

    ui->lineEditUserPage->setText(QString::number(curPage));
    ui->labelUserPage->setText(QString("%1/%2").arg(curPage).arg(m_UserTotalpage));
}

void ApprovalProgressDialog::slot_btnNext()
{
    int curPage = ui->lineEditUserPage->text().toInt();
    if (curPage >= m_UserTotalpage) return;


    int offsetRows = curPage * common::onePageRows;
    std::list<table_user> listUser;
    db::databaseDI::Instance().get_user_list_by_condition(listUser, common::onePageRows, offsetRows);
    flushUserTableShow(listUser);

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

        std::list<table_user> listUser;
        db::databaseDI::Instance().get_user_list_by_condition(listUser, common::onePageRows, 0);
        flushUserTableShow(listUser);
    }
    else if (curPage > m_UserTotalpage)
    {
        curPage = m_UserTotalpage;
        ui->labelUserPage->setText(QString("%1/%2").arg(curPage).arg(m_UserTotalpage));
        ui->lineEditUserPage->setText(QString::number(curPage));

        int offsetRows = (curPage - 1) * common::onePageRows;
        std::list<table_user> listUser;
        db::databaseDI::Instance().get_user_list_by_condition(listUser, common::onePageRows, offsetRows);
        flushUserTableShow(listUser);

    }
    else
    {
        ui->labelUserPage->setText(QString("%1/%2").arg(curPage).arg(m_UserTotalpage));
        ui->lineEditUserPage->setText(QString::number(curPage));

        int offsetRows = (curPage - 1) * common::onePageRows;
        std::list<table_user> listUser;
        db::databaseDI::Instance().get_user_list_by_condition(listUser, common::onePageRows, offsetRows);
        flushUserTableShow(listUser);
    }
   // return true;
    // ����һ��ģ��Ļس��¼�
    //QKeyEvent* keyEvent = new QKeyEvent(QEvent::KeyPress, Qt::Key_Enter, Qt::NoModifier);

    //// ����ģ���¼��� QlineEdit���Է�ֹ�����л�
    //QCoreApplication::postEvent(ui->lineEditUserPage, keyEvent);
}

void ApprovalProgressDialog::slot_scrollMove(int value)
{
    //qDebug() << "scrollMove";

    //int totalRow = ui->tableViewUser->model()->rowCount();    //the total row
    //int rowHeight = ui->tableViewUser->rowHeight(0);           //the row's height
    //int tableViewHeight = ui->tableViewUser->height();                //every row's height

    //int totalPage = totalRow / common::tableViewPageRows;
    //if (totalRow % common::tableViewPageRows != 0) totalPage++;

    //int last = 0;
    //int current = ui->tableViewUser->verticalScrollBar()->value();
    //int next = common::tableViewPageRows;
    //for (int page = 1; page <= totalPage; page++)
    //{
    //    if (current > last && current < next)
    //    {
    //        ui->lineEditUserPage->setText(QString::number(page));
    //        break;
    //    }
    //    last += common::tableViewPageRows;
    //    next += common::tableViewPageRows;
    //}
    //if (current >= common::tableViewPageRows * (totalPage - 1))
    //{
    //    ui->lineEditUserPage->setText(QString::number(totalPage));
    //}

}


//void ApprovalProgressDialog::slot_btnNext()
//{
//    int page = ui->lineEditUserPage->text().toInt();
//    if (page >= m_UserTotalpage) return;
//
//    int totalRow = ui->tableViewUser->model()->rowCount();
//    int totalPage = totalRow / common::tableViewPageRows;
//    if (totalRow % common::tableViewPageRows != 0) totalPage++;
//
//    ui->tableViewUser->verticalScrollBar()->setSliderPosition((page + 1) * common::tableViewPageRows);
//    if (page + 1 <= totalPage)
//    {
//        ui->lineEditUserPage->setText(QString::number(page + 1));
//    }
//    ui->labelUserPage->setText(QString("%1/%2").arg(page + 1).arg(m_UserTotalpage));
//}
//
//void ApprovalProgressDialog::slot_pageTo()
//{
//    if (ui->lineEditUserPage->text().isEmpty()) return;
//
//    int totalRow = ui->tableViewUser->model()->rowCount();   
//    int totalPage = totalRow / common::tableViewPageRows;
//    if (totalRow % common::tableViewPageRows != 0) totalPage++;
//
//    int page = ui->lineEditUserPage->text().toInt();
//    if (page <= 0) page = 1;
//    else if (page > totalPage) page = totalPage;
//    ui->lineEditUserPage->setText(QString::number(page));
//
//    ui->tableViewUser->verticalScrollBar()->setSliderPosition(common::tableViewPageRows * (page - 1));
//
//}
//
//void ApprovalProgressDialog::slot_scrollMove(int value)
//{
//    qDebug() << "scrollMove";
//
//    int totalRow = ui->tableViewUser->model()->rowCount();    //the total row
//    int rowHeight = ui->tableViewUser->rowHeight(0);           //the row's height
//    int tableViewHeight = ui->tableViewUser->height();                //every row's height
//
//    int totalPage = totalRow / common::tableViewPageRows;
//    if (totalRow % common::tableViewPageRows != 0) totalPage++;
//
//    int last = 0;
//    int current = ui->tableViewUser->verticalScrollBar()->value();
//    int next = common::tableViewPageRows;
//    for (int page = 1; page <= totalPage; page++)
//    {
//        if (current > last && current < next)
//        {
//            ui->lineEditUserPage->setText(QString::number(page));
//            break;
//        }
//        last += common::tableViewPageRows;
//        next += common::tableViewPageRows;
//    }
//    if (current >= common::tableViewPageRows * (totalPage - 1))
//    {
//        ui->lineEditUserPage->setText(QString::number(totalPage));
//    }
//    
//}

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

void ApprovalProgressDialog::slot_userQuery()
{
    int index = ui->comboBoxUserField->currentIndex();
    std::string strFields = userTable_to_string((EUserTable)index);
    QString strValue = ui->lineEditUserQueryValue->text();

    if (strValue.isEmpty())
    {
        std::list<table_user> listUser;
        db::databaseDI::Instance().get_user_list(listUser);
        flushUserTableShow(listUser);
    }
    else
    {
        int showTotalRows = 0;
        for (int row = 0; row < m_modelUser->rowCount(); ++row)
        {
            QStandardItem* item = m_modelUser->item(row, index); // ��ȡĳ�е���
            if (item && item->text() != strValue)
            {
                ui->tableViewUser->hideRow(row);
            }
            else
            {
                ui->tableViewUser->showRow(row);
                showTotalRows++;
            }
        }
        int totalRow = showTotalRows;
        if (totalRow < common::tableViewPageRows)
        {
            m_UserTotalpage = 1;
        }
        else
        {
            m_UserTotalpage = totalRow / common::tableViewPageRows;
            if (m_UserTotalpage % common::tableViewPageRows != 0) m_UserTotalpage++;
        }
        ui->labelUserPage->setText(QString("%1/%2").arg(1).arg(m_UserTotalpage));
        ui->lineEditUserPage->setText("1");
    }
    
}
void ApprovalProgressDialog::slot_DataItemBtnClicked()
{
    QPushButton* pButton = (QPushButton*)sender();
    int row = pButton->property("row").toInt();
    int column = pButton->property("column").toInt();
    int approval = pButton->property("approval").toInt();

    QModelIndex index = m_modelDataApproval->index(row, 0);
    int id = m_modelDataApproval->data(index, Qt::UserRole).toInt();

    if (!db::databaseDI::Instance().update_data_approval_state(id, approval))
    {
        qDebug() << "db::databaseDI::Instance().update_user_state  error----";
        return;
    }

    if (approval == 1)
    {
        auto item = m_modelDataApproval->item(row, 9);
        item->setText(QString::fromLocal8Bit("��ͨ��"));
        item->setForeground(QBrush(QColor(Qt::green)));
    }
    else if (approval == 2)
    {
        auto item = m_modelDataApproval->item(row, 9);
        item->setText(QString::fromLocal8Bit("�Ѳ���"));
        item->setTextAlignment(Qt::AlignCenter);  // �����ı����ж���
        item->setForeground(QBrush(QColor(Qt::red)));
    }

    // ��ȡ��ťָ��
    index = m_modelDataApproval->index(row, 10);
    QWidget* widget = ui->tableView->indexWidget(index);
    if (widget)
    {
        QPushButton* pButtonYes = qobject_cast<QPushButton*>(widget);
        if (pButtonYes)
        {
            pButtonYes->setEnabled(false);
        }
    }
    index = m_modelDataApproval->index(row, 11);
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
        auto item= m_modelUser->item(row, 8);
        item->setText(QString::fromLocal8Bit("��ͨ��"));
        item->setForeground(QBrush(QColor(Qt::green)));
    }
    else if(approval == 2)
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

