#include "FtpDialog.h"
#include "ui_FtpDialog.h"
//#include "FtpClientWidget.h"
#include "common.h"
#include "qftp.h"

FtpDialog::FtpDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FtpDialog)
{
    ui->setupUi(this);
  
    ui->stackedWidget->setCurrentIndex(0);
    connect(ui->comboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &FtpDialog::slot_comboBoxChanged);
    m_mapAdminFtp.clear();
}

FtpDialog::~FtpDialog()
{
    delete ui;
}

void FtpDialog::initConnectFtp()
{
    m_mapAdminFtp.clear();
    ui->comboBox->clear();

    QString strLinuxFtpIp = "192.168.10.240";
    ui->comboBox->addItem(QString::fromLocal8Bit("存储服务器"), strLinuxFtpIp);
    
 /*   QFtp* pFtp = new QFtp;
    if (pFtp->state() != QFtp::LoggedIn)
    {
        pFtp->connectToHost(strLinuxFtpIp, 21);
        pFtp->login("shareadmin", "123456");
    }

    m_mapAdminFtp[strLinuxFtpIp]= pFtp;*/

    int i = 1;
    for (auto st : common::setHostName)
    {
        QString  strFtpIP = QString::fromStdString(st.ip);
        ui->comboBox->addItem(QString::fromStdString(st.hostname), QString::fromStdString(st.ip));
       
       /* QFtp* pFtp = new QFtp;
        if (pFtp->state() != QFtp::LoggedIn)
        {
            pFtp->connectToHost(strFtpIP, 21);
            pFtp->login("shareadmin", "123456");
        }
        m_mapAdminFtp[strLinuxFtpIp] = pFtp;*/
        i++;
    }
    if (i != 7)
    {
        return;
    }
   // QString strUser =QString::fromStdString( common::stUser.UserName);
    ui->page0->connectToFtpServer(ui->comboBox->itemData(0, Qt::UserRole).toString(), common::strLoginUserName, "123456");
    ui->page1->connectToFtpServer(ui->comboBox->itemData(1, Qt::UserRole).toString(), common::strLoginUserName, "123456");
    ui->page2->connectToFtpServer(ui->comboBox->itemData(2, Qt::UserRole).toString(), common::strLoginUserName, "123456");
    ui->page3->connectToFtpServer(ui->comboBox->itemData(3, Qt::UserRole).toString(), common::strLoginUserName, "123456");
    ui->page4->connectToFtpServer(ui->comboBox->itemData(4, Qt::UserRole).toString(), common::strLoginUserName, "123456");
    ui->page4->connectToFtpServer(ui->comboBox->itemData(5, Qt::UserRole).toString(), common::strLoginUserName, "123456");
    ui->page6->connectToFtpServer(ui->comboBox->itemData(6, Qt::UserRole).toString(), common::strLoginUserName, "123456");

    connect(ui->page0, &FtpClientWidget::signal_ableUI, this, &FtpDialog::slot_ableUI);


    // 初始化管理员ftp;

    


}

void FtpDialog::slot_ableUI(bool b)
{
    ui->comboBox->setEnabled(b);
}

void FtpDialog::slot_createUserDir(const QString strDirName)
{
    //QMap<QString, QFtp*>::iterator it;
    //for (it = m_mapAdminFtp.begin(); it != m_mapAdminFtp.end(); ++it) 
    //{
    //    QString key = it.key(); // 获取map中的键
    //    QFtp* ftp = it.value(); // 获取map中的值（即QFtp对象）

    //    if (it.value()->state() != QFtp::LoggedIn)
    //    {
    //        it.value()->connectToHost(it.key(), 21);
    //        it.value()->login("shareadmin", "123456");
    //    }
    //    // 调用QFtp对象的某个函数（以someFunction()为例）
    //    it.value()->mkdir(strDirName);
    //}
    ui->page0->createUserDir(strDirName);
    ui->page1->createUserDir(strDirName);
    ui->page2->createUserDir(strDirName);
    ui->page3->createUserDir(strDirName);
    ui->page4->createUserDir(strDirName);
    ui->page6->createUserDir(strDirName);


}
void FtpDialog::slot_comboBoxChanged(int index)
{
    ui->stackedWidget->setCurrentIndex(index);
}