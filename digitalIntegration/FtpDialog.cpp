#include<QStandardItemModel>
#include <QFileInfo>
#include <QMenu>
#include <QDebug>

#include <Ws2tcpip.h>

#include "FtpDialog.h"
#include "ui_FtpDialog.h"
//#include "FtpClientWidget.h"
#include "common.h"
#include "qftp.h"
#include "CtrlNetwork.h"
#include "databaseDI.h"
#include "GifDialog.h"



FtpDialog::FtpDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FtpDialog)
{
    ui->setupUi(this);
    m_pGifDialog = new GifDialog();
    m_pUDP = new CCtrlNetwork();
    m_pUDP->init(54110);
    ui->stackedWidget->setCurrentIndex(0);
    ui->tabWidget->setCurrentIndex(0);
   
    connect(ui->pushButton, &QPushButton::clicked, this, &FtpDialog::slot_btnFlush);
   // m_mapAdminFtp.clear();
}

FtpDialog::~FtpDialog()
{
    delete ui;
}

void FtpDialog::initConnectFtp()
{
  //  m_mapAdminFtp.clear();
    ui->comboBox->clear();

   // QString strLinuxFtpIp = "192.168.10.240";
    QString strLinuxFtpIp = common::strLinuxFtpIp;
    ui->comboBox->addItem(QString::fromLocal8Bit("�洢������"), strLinuxFtpIp);
    

    int i = 1;
    for (auto st : common::setHostName)
    {
        QString  strFtpIP = QString::fromStdString(st.ip);
        ui->comboBox->addItem(QString::fromStdString(st.hostname), QString::fromStdString(st.ip));
 
        i++;
    }
    if (i != 7)
    {
        return;
    }
   // QString strUser =QString::fromStdString( common::stUser.UserName);
    ui->page0->connectToFtpServer(ui->comboBox->itemText(0),ui->comboBox->itemData(0, Qt::UserRole).toString(), "N BPC", common::strFtpPwd);
   // ui->page0->setIsLinuxFtpServer(true);

    ui->page1->connectToFtpServer(ui->comboBox->itemText(1), ui->comboBox->itemData(1, Qt::UserRole).toString(), common::strLoginUserName, common::strFtpPwd);
    ui->page2->connectToFtpServer(ui->comboBox->itemText(2), ui->comboBox->itemData(2, Qt::UserRole).toString(), common::strLoginUserName, common::strFtpPwd);
    ui->page3->connectToFtpServer(ui->comboBox->itemText(3), ui->comboBox->itemData(3, Qt::UserRole).toString(), common::strLoginUserName, common::strFtpPwd);
    ui->page4->connectToFtpServer(ui->comboBox->itemText(4), ui->comboBox->itemData(4, Qt::UserRole).toString(), common::strLoginUserName, common::strFtpPwd);
    ui->page5->connectToFtpServer(ui->comboBox->itemText(5), ui->comboBox->itemData(5, Qt::UserRole).toString(), common::strLoginUserName, common::strFtpPwd);
    ui->page6->connectToFtpServer(ui->comboBox->itemText(6),ui->comboBox->itemData(6, Qt::UserRole).toString(), common::strLoginUserName, common::strFtpPwd);

    connect(ui->page0, &FtpClientWidget::signal_ableUI, this, &FtpDialog::slot_ableUI);
    connect(ui->page1, &FtpClientWidget::signal_ableUI, this, &FtpDialog::slot_ableUI);
    connect(ui->page2, &FtpClientWidget::signal_ableUI, this, &FtpDialog::slot_ableUI);
    connect(ui->page3, &FtpClientWidget::signal_ableUI, this, &FtpDialog::slot_ableUI);
    connect(ui->page4, &FtpClientWidget::signal_ableUI, this, &FtpDialog::slot_ableUI);
    connect(ui->page5, &FtpClientWidget::signal_ableUI, this, &FtpDialog::slot_ableUI);
    connect(ui->page6, &FtpClientWidget::signal_ableUI, this, &FtpDialog::slot_ableUI);

    connect(ui->page0, &FtpClientWidget::signal_compress, this, &FtpDialog::slot_compress);
    connect(ui->page1, &FtpClientWidget::signal_compress, this, &FtpDialog::slot_compress);
    connect(ui->page2, &FtpClientWidget::signal_compress, this, &FtpDialog::slot_compress);
    connect(ui->page3, &FtpClientWidget::signal_compress, this, &FtpDialog::slot_compress);
    connect(ui->page4, &FtpClientWidget::signal_compress, this, &FtpDialog::slot_compress);
    connect(ui->page5, &FtpClientWidget::signal_compress, this, &FtpDialog::slot_compress);
    connect(ui->page6, &FtpClientWidget::signal_compress, this, &FtpDialog::slot_compress);
    connect(ui->page0, &FtpClientWidget::signal_unCompress, this, &FtpDialog::slot_unCompress);
    connect(ui->page1, &FtpClientWidget::signal_unCompress, this, &FtpDialog::slot_unCompress);
    connect(ui->page2, &FtpClientWidget::signal_unCompress, this, &FtpDialog::slot_unCompress);
    connect(ui->page3, &FtpClientWidget::signal_unCompress, this, &FtpDialog::slot_unCompress);
    connect(ui->page4, &FtpClientWidget::signal_unCompress, this, &FtpDialog::slot_unCompress);
    connect(ui->page5, &FtpClientWidget::signal_unCompress, this, &FtpDialog::slot_unCompress);
    connect(ui->page6, &FtpClientWidget::signal_unCompress, this, &FtpDialog::slot_unCompress);

    connect(ui->page0, &FtpClientWidget::signal_del, this, &FtpDialog::slot_del);
    connect(ui->page1, &FtpClientWidget::signal_del, this, &FtpDialog::slot_del);
    connect(ui->page2, &FtpClientWidget::signal_del, this, &FtpDialog::slot_del);
    connect(ui->page3, &FtpClientWidget::signal_del, this, &FtpDialog::slot_del);
    connect(ui->page4, &FtpClientWidget::signal_del, this, &FtpDialog::slot_del);
    connect(ui->page5, &FtpClientWidget::signal_del, this, &FtpDialog::slot_del);
    connect(ui->page6, &FtpClientWidget::signal_del, this, &FtpDialog::slot_del);

    // ��ʼ������Աftp;

    connect(ui->comboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &FtpDialog::slot_comboBoxChanged);
    if (common::bAdministrator) // ����Ա;
    {
        // ���صڶ�����ǩҳ
        ui->tabWidget->removeTab(1); // �Ƴ� Tab 2
      //  m_strDolwnloadText = QString::fromLocal8Bit("����");
    }
    else
    {
        m_modelDownload = new QStandardItemModel();
        m_modelDownload->setColumnCount(11);
        m_modelDownload->setHeaderData(0, Qt::Horizontal, QString::fromLocal8Bit("���"));
        m_modelDownload->setHeaderData(1, Qt::Horizontal, QString::fromLocal8Bit("������"));
        m_modelDownload->setHeaderData(2, Qt::Horizontal, QString::fromLocal8Bit("���ڲ���"));
        m_modelDownload->setHeaderData(3, Qt::Horizontal, QString::fromLocal8Bit("����ʱ��"));
        m_modelDownload->setHeaderData(4, Qt::Horizontal, QString::fromLocal8Bit("����"));
        m_modelDownload->setHeaderData(5, Qt::Horizontal, QString::fromLocal8Bit("����IP"));
        m_modelDownload->setHeaderData(6, Qt::Horizontal, QString::fromLocal8Bit("�ļ���"));
        m_modelDownload->setHeaderData(7, Qt::Horizontal, QString::fromLocal8Bit("�ļ�����"));
        m_modelDownload->setHeaderData(8, Qt::Horizontal, QString::fromLocal8Bit("����ʱ��"));
        m_modelDownload->setHeaderData(9, Qt::Horizontal, QString::fromLocal8Bit("״̬"));
        m_modelDownload->setHeaderData(10,Qt::Horizontal, QString::fromLocal8Bit("����"));

        ui->tableViewDownload->setModel(m_modelDownload);
        common::setTableViewBasicConfiguration(ui->tableViewDownload);

        ui->tableViewDownload->verticalHeader()->setVisible(false);

        ui->tableViewDownload->setContextMenuPolicy(Qt::CustomContextMenu);
        //connect(ui->tableViewDownload, &QTableView::customContextMenuRequested, this, &FtpDialog::slot_tableViewDownloadContextMenu);
        flushTableViewDownload();
        ui->tableViewDownload->setContextMenuPolicy(Qt::CustomContextMenu);
      //  connect(ui->tableViewDownload, &QTableView::customContextMenuRequested, this, &FtpDialog::slot_tableViewDownloadContextMenu);
        connect(ui->tabWidget, &QTabWidget::currentChanged, this, [this](int index) {
            if (index == 1)
            {
                flushTableViewDownload();
            }
           
            });
    }

}

void FtpDialog::flushTableViewDownload()
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

        item = new QStandardItem(QString::fromStdString(stData.ftpName));
        item->setTextAlignment(Qt::AlignCenter);  // �����ı����ж���
        m_modelDownload->setItem(newRowIndex, 4, item);

        item = new QStandardItem(QString::fromStdString(stData.ftpIp));
        item->setTextAlignment(Qt::AlignCenter);  // �����ı����ж���
        m_modelDownload->setItem(newRowIndex, 5, item);

        QString filePath = QString::fromStdString(stData.filePath);
        QFileInfo fileInfo1(filePath);
        item = new QStandardItem(fileInfo1.fileName());
        item->setTextAlignment(Qt::AlignCenter);  // �����ı����ж���
        m_modelDownload->setItem(newRowIndex, 6, item);
        QModelIndex indexFilePath = m_modelDownload->index(newRowIndex, 6);
        m_modelDownload->setData(indexFilePath, filePath, Qt::UserRole);


        item = new QStandardItem(QString::fromStdString(stData.fileType));
        item->setTextAlignment(Qt::AlignCenter);  // �����ı����ж���
        m_modelDownload->setItem(newRowIndex, 7, item);

        item = new QStandardItem(QString::fromStdString(stData.fileTime));
        item->setTextAlignment(Qt::AlignCenter);  // �����ı����ж���
        m_modelDownload->setItem(newRowIndex, 8, item);




        // add button to the last column
        QPushButton* buttonD = new QPushButton(QString::fromLocal8Bit("����"));
        buttonD->setObjectName("itemBtnYes");
        buttonD->setProperty("row", newRowIndex); // set custom property
        buttonD->setProperty("column", 10);
        buttonD->setProperty("approval", 1);
        connect(buttonD, SIGNAL(clicked()), this, SLOT(slot_ItemDownloadBtnClicked()));
        ui->tableViewDownload->setIndexWidget(m_modelDownload->index(newRowIndex, 10), buttonD);
        //buttonD->setEnabled(false);


        if (stData.status == 1)
        {
            item = new QStandardItem(QString::fromLocal8Bit("��ͨ��"));
            item->setForeground(QBrush(QColor(Qt::green)));
            item->setTextAlignment(Qt::AlignCenter);  // �����ı����ж���
            m_modelDownload->setItem(newRowIndex, 9, item);
            buttonD->setEnabled(true);

        }
        else if (stData.status == 0)
        {
            item = new QStandardItem(QString::fromLocal8Bit("�����"));
            item->setForeground(QBrush(QColor("#33C1FF")));
            item->setTextAlignment(Qt::AlignCenter);  // �����ı����ж���
            m_modelDownload->setItem(newRowIndex, 9, item);
            buttonD->setEnabled(false);
        }
        else if (stData.status == 2)
        {
            item = new QStandardItem(QString::fromLocal8Bit("�Ѳ���"));
            item->setTextAlignment(Qt::AlignCenter);  // �����ı����ж���
            item->setForeground(QBrush(QColor(Qt::red)));
            m_modelDownload->setItem(newRowIndex, 9, item);
            buttonD->setEnabled(false);

        }
        i++;
    }
}



QByteArray  FtpDialog::serializeFtpUdpData(const st_udp& data)
{
    QByteArray byteArray;
    QDataStream stream(&byteArray, QIODevice::WriteOnly);
    stream << data.str1 << data.str2 << data.str3;
    return byteArray;
}

void FtpDialog::slot_orderFinsh(int iFlag)
{
    m_pGifDialog->close();
    QWidget* pwiget = ui->stackedWidget->currentWidget();
    FtpClientWidget* p = qobject_cast<FtpClientWidget*>(pwiget);
    if (p)
    {
        p->Connect();
        p->Flush();
    }
    ui->comboBox->setEnabled(true);
    ui->pushButton->setEnabled(true);
    
}

void FtpDialog::slot_ableUI(bool b,QString str)
{
    ui->comboBox->setEnabled(b);
    ui->pushButton->setEnabled(b);
    if (b)
    {
        m_pGifDialog->close();
    }
    else
    {
        m_pGifDialog->setTitleText(str);
        m_pGifDialog->show();
    }
}

void FtpDialog::slot_compress(bool bLinuxServer, QString strIp, QString strArg1, QString strArg2)
{
    struct sockaddr_in m_r_addr;
    m_r_addr.sin_family = AF_INET;
    m_r_addr.sin_port = htons(6667);
   // inet_pton(AF_INET, "192.168.0.147", &m_r_addr.sin_addr.s_addr);

    inet_pton(AF_INET, strIp.toStdString().c_str(), &m_r_addr.sin_addr.s_addr);
    st_udp stUdpData;

    if (bLinuxServer)
    {
        stUdpData.str1 = "Luncompress";
    }
    else
    {
        stUdpData.str1 = "Wcompress";
    }
    stUdpData.str2 = strArg1;
    stUdpData.str3 = strArg2;

    QByteArray byteArray= serializeFtpUdpData(stUdpData);
  //  const char* sendData = order.toStdString().c_str();
    int sendSize = m_pUDP->sendDataTo(byteArray, byteArray.size(), (sockaddr*)&m_r_addr);
    if (sendSize <= 0)
    {
        qDebug() << " send compress order faleid";
    }
    else
    {
        m_pGifDialog->setTitleText(QString::fromLocal8Bit("����ѹ���ļ�"));
        m_pGifDialog->show();

        QWidget* pwiget = ui->stackedWidget->currentWidget();
        FtpClientWidget* p = qobject_cast<FtpClientWidget*>(pwiget);
        if (p)
        {
            p->DisConnect();
        }
        ui->comboBox->setEnabled(false);
        ui->pushButton->setEnabled(false);


        slot_orderFinsh(1);
    }
}

void FtpDialog::slot_unCompress(bool bLinuxServer, QString strIp, QString strArg1)
{
    struct sockaddr_in m_r_addr;
    m_r_addr.sin_family = AF_INET;
    m_r_addr.sin_port = htons(6667);

    inet_pton(AF_INET, strIp.toStdString().c_str(), &m_r_addr.sin_addr.s_addr);

    st_udp stUdpData;

    if (bLinuxServer)
    {
        stUdpData.str1 = "Luncompress";
    }
    else
    {
        stUdpData.str1 = "Wuncompress";
    }
    stUdpData.str2 = strArg1;
    QByteArray byteArray = serializeFtpUdpData(stUdpData);
    //  const char* sendData = order.toStdString().c_str();
    int sendSize = m_pUDP->sendDataTo(byteArray, byteArray.size(), (sockaddr*)&m_r_addr);
    if (sendSize <= 0)
    {
        qDebug() << " send uncompress order faleid";
    }
    else
    {
        m_pGifDialog->setTitleText(QString::fromLocal8Bit("���ڽ�ѹ�ļ�"));
        m_pGifDialog->show();

        QWidget* pwiget = ui->stackedWidget->currentWidget();
        FtpClientWidget* p = qobject_cast<FtpClientWidget*>(pwiget);
        if (p)
        {
            p->DisConnect();
           
        }
        ui->comboBox->setEnabled(false);
        ui->pushButton->setEnabled(false);


        slot_orderFinsh(1);
    }
   
}

void FtpDialog::slot_del(bool bLinuxServer, QString strIp, QString strArg1)
{
    struct sockaddr_in m_r_addr;
    m_r_addr.sin_family = AF_INET;
    m_r_addr.sin_port = htons(6667);

    inet_pton(AF_INET, strIp.toStdString().c_str(), &m_r_addr.sin_addr.s_addr);

    st_udp stUdpData;

    if (bLinuxServer)
    {
        stUdpData.str1 = "Ldel";
    }
    else
    {
        stUdpData.str1 = "Wdel";
    }
    stUdpData.str2 = strArg1;

    QByteArray byteArray = serializeFtpUdpData(stUdpData);
    //  const char* sendData = order.toStdString().c_str();
    int sendSize = m_pUDP->sendDataTo(byteArray, byteArray.size(), (sockaddr*)&m_r_addr);
    if (sendSize <= 0)
    {
        qDebug() << " send uncompress order faleid";
    }
    else
    {
        m_pGifDialog->setTitleText(QString::fromLocal8Bit("����ɾ��"));
        m_pGifDialog->show();

        QWidget* pwiget = ui->stackedWidget->currentWidget();
        FtpClientWidget* p = qobject_cast<FtpClientWidget*>(pwiget);
        if (p)
        {
            p->DisConnect();
        }
        ui->comboBox->setEnabled(false);
        ui->pushButton->setEnabled(false);

        slot_orderFinsh(1);
    }
}



void FtpDialog::slot_btnFlush()
{
    QWidget* pwiget = ui->stackedWidget->currentWidget();
    FtpClientWidget* p = qobject_cast<FtpClientWidget*>(pwiget);
    if (p)
    {
        p->Flush();
    }
}

void FtpDialog::slot_ItemDownloadBtnClicked()
{
    QPushButton* pButton = (QPushButton*)sender();
    int row = pButton->property("row").toInt();
    int column = pButton->property("column").toInt();
    int approval = pButton->property("approval").toInt();

    QModelIndex index = m_modelDownload->index(row, 0);
    int id = m_modelDownload->data(index, Qt::UserRole).toInt();
    QModelIndex indexFilePath = m_modelDownload->index(row, 6);
    QString strFilaPath = m_modelDownload->data(indexFilePath, Qt::UserRole).toString();

    QString strFileType = m_modelDownload->item(row, 7)->text();

    QString strFileName = m_modelDownload->item(row, 6)->text();

    QString strHostIp= m_modelDownload->item(row, 5)->text();

    bool bDir = (strFileType == "dir" ? true : false);
   
    if (strHostIp == ui->comboBox->itemData(0))
    {
        ui->page0->ApprovalDownload(strFileName, strFilaPath, bDir);
    }
    else if (strHostIp == ui->comboBox->itemData(1))
    {
        ui->page1->ApprovalDownload(strFileName, strFilaPath, bDir);
    }
    else if (strHostIp == ui->comboBox->itemData(2))
    {
        ui->page2->ApprovalDownload(strFileName, strFilaPath, bDir);
    }
    else if (strHostIp == ui->comboBox->itemData(3))
    {
        ui->page3->ApprovalDownload(strFileName, strFilaPath, bDir);
    }
    else if (strHostIp == ui->comboBox->itemData(4))
    {
        ui->page4->ApprovalDownload(strFileName, strFilaPath, bDir);
    }
    else if (strHostIp == ui->comboBox->itemData(5))
    {
        ui->page5->ApprovalDownload(strFileName, strFilaPath, bDir);
    }
    else if (strHostIp == ui->comboBox->itemData(6))
    {
        ui->page6->ApprovalDownload(strFileName, strFilaPath, bDir);
    }

}

void FtpDialog::slot_tableViewDownloadContextMenu(const QPoint& pos)
{
    QMenu menu(this);

    // ��Ӳ˵���
    QAction* flushAction = menu.addAction(QString::fromLocal8Bit("ˢ��"));


    // ִ�в˵�����ȡ��ѡ����
    QAction* selectedAction = menu.exec(ui->tableViewDownload->mapToGlobal(pos));

    if (selectedAction == flushAction) {
        flushTableViewDownload();
    }
}

void FtpDialog::slot_createUserDir(const QString strDirName)
{
 
    ui->page0->createUserDir(strDirName);
    ui->page1->createUserDir(strDirName);
    ui->page2->createUserDir(strDirName);
    ui->page3->createUserDir(strDirName);
    ui->page4->createUserDir(strDirName);
    ui->page5->createUserDir(strDirName);
    ui->page6->createUserDir(strDirName);

 
    
}
void FtpDialog::slot_comboBoxChanged(int index)
{
    ui->stackedWidget->setCurrentIndex(index);
    QWidget *pwiget =ui->stackedWidget->currentWidget();
    FtpClientWidget* p = qobject_cast<FtpClientWidget*>(pwiget);
    if (p)
    {
        p->Flush();
    }
}