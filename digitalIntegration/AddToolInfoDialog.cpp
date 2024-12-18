#include <QMessageBox>
#include <QFileDialog>


#include "AddToolInfoDialog.h"
#include "ui_AddToolInfoDialog.h"

#include"globel.h"
#include "common.h"
#include "databaseDI.h"

AddToolInfoDialog::AddToolInfoDialog(int module,QWidget *parent) :m_iModule(module),
    QDialog(parent),
    ui(new Ui::AddToolInfoDialog)
{
    ui->setupUi(this);
    //ui->lineEditHost->setMaxLength(15);
    ui->lineEditToolName->setMaxLength(20);
    //ui->lineEditToolPath->setMaxLength(15);
    ui->lineEdit->setMaxLength(100);
	ui->lineEditIP1->setMaxLength(15);
	ui->lineEditIP2->setMaxLength(15);
	ui->lineEditIP3->setMaxLength(15);
	ui->lineEditIP4->setMaxLength(15);
	ui->lineEditIP5->setMaxLength(15);
	ui->lineEditIP6->setMaxLength(15);
    connect(ui->btnOK, &QPushButton::clicked, this, &AddToolInfoDialog::slot_btnOk);
	connect(ui->btnChooseImage, &QPushButton::clicked, this, &AddToolInfoDialog::slot_btnChooseImage);

	//聚焦
	setTabOrder(ui->lineEditToolName, ui->lineEditToolPath);
	setTabOrder(ui->lineEditToolPath,ui->lineEdit);
	setTabOrder(ui->lineEdit,ui->lineEditIP1);
	setTabOrder(ui->lineEditIP1,ui->lineEditIP2);
	setTabOrder(ui->lineEditIP2,ui->lineEditIP3);
	setTabOrder(ui->lineEditIP3,ui->lineEditIP4);
	setTabOrder(ui->lineEditIP4,ui->lineEditIP5);
	setTabOrder(ui->lineEditIP5,ui->lineEditIP6);
	
}

AddToolInfoDialog::~AddToolInfoDialog()
{
    delete ui;
}

//void AddToolInfoDialog::getToolsData(table_ip& toolsData)
//{
//	//toolData.host=ui->lineEditHost->text().toStdString();
//	toolsData.software = ui->lineEditToolName->text().toStdString();
//	//QString strPath = ui->lineEditToolPath->text();
//	//strPath.replace("\\","\\\\");
//	//toolData.path = strPath.toStdString();
//	toolsData.icoPath = ui->lineEditIconPath->text().replace("\\", "\\\\").toStdString();
//	toolsData.ip = ui->lineEditIP1->text().toStdString();
//}
void AddToolInfoDialog::getToolsData(table_ip& toolsData,std::string ipdata[6])
{
	//toolData.host=ui->lineEditHost->text().toStdString();
	toolsData.software = ui->lineEditToolName->text().toStdString();
	//QString strPath = ui->lineEditToolPath->text();
	//strPath.replace("\\","\\\\");
	//toolData.path = strPath.toStdString();
	toolsData.toolPath = ui->lineEditToolPath->text().replace("\\", "\\\\").toStdString();
	toolsData.icoPath = ui->lineEdit->text().replace("\\", "\\\\").toStdString();
	ipdata[0] = ui->lineEditIP1->text().toStdString();
	ipdata[1] = ui->lineEditIP2->text().toStdString();
	ipdata[2] = ui->lineEditIP3->text().toStdString();
	ipdata[3] = ui->lineEditIP4->text().toStdString();
	ipdata[4] = ui->lineEditIP5->text().toStdString();
	ipdata[5] = ui->lineEditIP6->text().toStdString();
}


void AddToolInfoDialog::slot_btnOk()
{

    /*if (ui->lineEditHost->text().toStdString().empty())
    {
        QMessageBox::warning(this, QString::fromLocal8Bit("警告"), QString::fromLocal8Bit("主机不能为空!"));
        return;
    }*/
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
    /*if (ui->lineEdit->text().toStdString().empty())
    {
        QMessageBox::warning(this, QString::fromLocal8Bit("警告"), QString::fromLocal8Bit("图标路径不能为空!"));
        return;
    }*/
	if ((ui->lineEditIP1->text().toStdString().empty() 
		|| ui->lineEditIP2->text().toStdString().empty() 
		|| ui->lineEditIP3->text().toStdString().empty()
		|| ui->lineEditIP4->text().toStdString().empty() 
		|| ui->lineEditIP5->text().toStdString().empty() 
		|| ui->lineEditIP6->text().toStdString().empty())
		&& m_iModule == 1)
	{
		QMessageBox::warning(this, QString::fromLocal8Bit("警告"), QString::fromLocal8Bit("IP不能为空!"));
		return;
	}
	
    this->accept();
 
}

void AddToolInfoDialog::slot_btnChooseImage()
{
	// 弹出文件选择对话框，过滤条件为PNG和JPG文件
	QString fileName = QFileDialog::getOpenFileName(this, "选择图片", "", "Images (*.png *.jpg *.jpeg)");

	// 检查用户是否选择了文件
	if (!fileName.isEmpty()) {
		// 在此处理所选文件（例如，显示文件路径）
	   // QMessageBox::information(this, "选择的文件", "您选择的文件: " + fileName);
		ui->lineEdit->setText(fileName);
	}
}

QLineEdit* AddToolInfoDialog::getlineEditIP1()
{
	return ui->lineEditIP1;
}
QLineEdit* AddToolInfoDialog::getlineEditIP2()
{
	return ui->lineEditIP2;
}
QLineEdit* AddToolInfoDialog::getlineEditIP3()
{
	return ui->lineEditIP3;
}
QLineEdit* AddToolInfoDialog::getlineEditIP4()
{
	return ui->lineEditIP4;
}
QLineEdit* AddToolInfoDialog::getlineEditIP5()
{
	return ui->lineEditIP5;
}
QLineEdit* AddToolInfoDialog::getlineEditIP6()
{
	return ui->lineEditIP6;
}
QLabel* AddToolInfoDialog::getlabelIP1()
{
	return ui->labelIP1;
}
QLabel* AddToolInfoDialog::getlabelIP2()
{
	return ui->labelIP2;
}
QLabel* AddToolInfoDialog::getlabelIP3()
{
	return ui->labelIP3;
}
QLabel* AddToolInfoDialog::getlabelIP4()
{
	return ui->labelIP4;
}
QLabel* AddToolInfoDialog::getlabelIP5()
{
	return ui->labelIP5;
}
QLabel* AddToolInfoDialog::getlabelIP6()
{
	return ui->labelIP6;
}
