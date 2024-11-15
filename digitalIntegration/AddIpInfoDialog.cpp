
#include "AddIpInfoDialog.h"
#include "ui_AddIpInfoDialog.h"
#include "globel.h"

AddIpInfoDialog::AddIpInfoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddIpInfoDialog)
{
    ui->setupUi(this);
    ui->lineEditHost->setMaxLength(15);
    ui->lineEditIp->setMaxLength(15);
    connect(ui->btnOK, &QPushButton::clicked, this, &AddIpInfoDialog::slot_btnOk);
}

AddIpInfoDialog::~AddIpInfoDialog()
{
    delete ui;
}

void AddIpInfoDialog::getIpData(table_ip& stIp)
{
    stIp.host = ui->lineEditHost->text().toStdString();
    stIp.ip = ui->lineEditIp->text().toStdString();

}



void AddIpInfoDialog::slot_btnOk()
{

    this->accept();
}

