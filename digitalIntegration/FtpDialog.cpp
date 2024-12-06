#include "FtpDialog.h"
#include "ui_FtpDialog.h"
//#include "FtpClientWidget.h"

FtpDialog::FtpDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FtpDialog)
{
    ui->setupUi(this);
  
    connect(ui->comboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &FtpDialog::slot_comboBoxChanged);
}

FtpDialog::~FtpDialog()
{
    delete ui;
}

void FtpDialog::initConnectFtp()
{
    ui->page1->connectToFtpServer(ui->comboBox->currentText(), "N BPC", "jh123456");
}
void FtpDialog::slot_comboBoxChanged(int index)
{
    ui->stackedWidget->setCurrentIndex(index);
}