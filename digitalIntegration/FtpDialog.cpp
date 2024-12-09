#include "FtpDialog.h"
#include "ui_FtpDialog.h"
//#include "FtpClientWidget.h"
#include "common.h"

FtpDialog::FtpDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FtpDialog)
{
    ui->setupUi(this);
  
    ui->stackedWidget->setCurrentIndex(0);
    connect(ui->comboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &FtpDialog::slot_comboBoxChanged);
}

FtpDialog::~FtpDialog()
{
    delete ui;
}

void FtpDialog::initConnectFtp()
{
    ui->comboBox->clear();
    ui->comboBox->addItem(QString::fromLocal8Bit("´æ´¢·þÎñÆ÷"), "192.168.0.132");
    int i = 1;
    for (auto st : common::setHostName)
    {
        ui->comboBox->addItem(QString::fromStdString(st.hostname), QString::fromStdString(st.ip));
        i++;
    }
    if (i != 7)
    {
        return;
    }
    ui->page0->connectToFtpServer(ui->comboBox->itemData(0,Qt::UserRole).toString(), "N BPC", "jh123456");
    ui->page1->connectToFtpServer(ui->comboBox->itemData(1,Qt::UserRole).toString(), "N BPC", "jh123456");
    ui->page2->connectToFtpServer(ui->comboBox->itemData(2, Qt::UserRole).toString(), "N BPC", "jh123456");
    ui->page3->connectToFtpServer(ui->comboBox->itemData(3, Qt::UserRole).toString(), "N BPC", "jh123456");
    ui->page4->connectToFtpServer(ui->comboBox->itemData(4, Qt::UserRole).toString(), "N BPC", "jh123456");
    ui->page6->connectToFtpServer(ui->comboBox->itemData(6, Qt::UserRole).toString(), "N BPC", "jh123456");

    connect(ui->page0, &FtpClientWidget::signal_ableUI, this, &FtpDialog::slot_ableUI);
}

void FtpDialog::slot_ableUI(bool b)
{
    ui->comboBox->setEnabled(b);
}
void FtpDialog::slot_comboBoxChanged(int index)
{
    ui->stackedWidget->setCurrentIndex(index);
}