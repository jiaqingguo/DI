#include<QMessageBox>
#include "AddToolInfoDialog.h"
#include "ui_AddToolInfoDialog.h"

#include"globel.h"

AddToolInfoDialog::AddToolInfoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddToolInfoDialog)
{
    ui->setupUi(this);
    ui->lineEditHost->setMaxLength(15);
    ui->lineEditToolName->setMaxLength(15);
    ui->lineEditToolPath->setMaxLength(15);
    ui->lineEditIconPath->setMaxLength(15);
    connect(ui->btnOK, &QPushButton::clicked, this, &AddToolInfoDialog::slot_btnOk);
}

AddToolInfoDialog::~AddToolInfoDialog()
{
    delete ui;
}


void AddToolInfoDialog::getToolsData(table_ip& toolsData)
{
    //toolData.host=ui->lineEditHost->text().toStdString();
    toolsData.software = ui->lineEditToolName->text().toStdString();
    //QString strPath = ui->lineEditToolPath->text();
    //strPath.replace("\\","\\\\");
    //toolData.path = strPath.toStdString();
    toolsData.icoPath = ui->lineEditIconPath->text().replace("\\", "\\\\").toStdString();
}
void AddToolInfoDialog::slot_btnOk()
{

    if (ui->lineEditHost->text().toStdString().empty())
    {
        QMessageBox::warning(this, QString::fromLocal8Bit("警告"), QString::fromLocal8Bit("主机不能为空!"));
        return;
    }
    if (ui->lineEditToolName->text().toStdString().empty())
    {
        QMessageBox::warning(this, QString::fromLocal8Bit("警告"), QString::fromLocal8Bit("工具名称不能为空!"));
        return;
    }
    if (ui->lineEditToolPath->text().toStdString().empty())
    {
        QMessageBox::warning(this, QString::fromLocal8Bit("警告"), QString::fromLocal8Bit("工具路径不能为空!"));
        return;
    }
    if (ui->lineEditIconPath->text().toStdString().empty())
    {
        QMessageBox::warning(this, QString::fromLocal8Bit("警告"), QString::fromLocal8Bit("图标路径不能为空!"));
        return;
    }
    this->accept();
   
}
