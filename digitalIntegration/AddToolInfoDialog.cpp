#include<QMessageBox>
#include "AddToolInfoDialog.h"
#include "ui_AddToolInfoDialog.h"

#include"globel.h"
#include "common.h"
#include "databaseDI.h"

AddToolInfoDialog::AddToolInfoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddToolInfoDialog)
{
    ui->setupUi(this);
    //ui->lineEditHost->setMaxLength(15);
    ui->lineEditToolName->setMaxLength(15);
    //ui->lineEditToolPath->setMaxLength(15);
    ui->lineEditIconPath->setMaxLength(15);
    connect(ui->btnOK, &QPushButton::clicked, this, &AddToolInfoDialog::slot_btnOk);

	std::set<std::string> conboBoxip;
	if (db::databaseDI::Instance().get_ip_data_by_number(conboBoxip, common::iLoginNum))
	{
		for (const std::string &ip : conboBoxip)
		{
			ui->comboBoxIP->addItem(QString::fromStdString(ip));
		}
	}
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
	QString temp = ui->comboBoxIP->currentText();
	toolsData.ip = temp.toStdString();
}


void AddToolInfoDialog::slot_btnOk()
{

    /*if (ui->lineEditHost->text().toStdString().empty())
    {
        QMessageBox::warning(this, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("��������Ϊ��!"));
        return;
    }*/
    if (ui->lineEditToolName->text().toStdString().empty())
    {
        QMessageBox::warning(this, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("�������Ʋ���Ϊ��!"));
        return;
    }
   /* if (ui->lineEditToolPath->text().toStdString().empty())
    {
        QMessageBox::warning(this, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("����·������Ϊ��!"));
        return;
    }*/
    if (ui->lineEditIconPath->text().toStdString().empty())
    {
        QMessageBox::warning(this, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("ͼ��·������Ϊ��!"));
        return;
    }
    this->accept();
   
}
