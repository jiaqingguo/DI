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
	//setWindowFlags(Qt::FramelessWindowHint);
	ui->widget_2->hide();
	setWindowIcon(QIcon(":/image/InforIcon.png"));
    //ui->lineEditHost->setMaxLength(15);
    ui->lineEditToolName->setMaxLength(20);
    //ui->lineEditToolPath->setMaxLength(15);
    ui->lineEdit->setMaxLength(100);
    connect(ui->btnOK, &QPushButton::clicked, this, &AddToolInfoDialog::slot_btnOk);
	connect(ui->btnChooseImage, &QPushButton::clicked, this, &AddToolInfoDialog::slot_btnChooseImage);
	connect(ui->accelerateRadioButton,&QRadioButton::clicked, this, &AddToolInfoDialog::slot_btnhideWidget);
	connect(ui->nodeRadioButton, &QRadioButton::clicked, this, &AddToolInfoDialog::slot_btnhideWidget2);

	ui->IpcomboBox1->addItem(QString::fromLocal8Bit("节点1"));
	ui->IpcomboBox1->addItem(QString::fromLocal8Bit("节点2"));
	ui->IpcomboBox2->addItem(QString::fromLocal8Bit("节点3"));
	ui->IpcomboBox2->addItem(QString::fromLocal8Bit("节点4"));
	ui->IpcomboBox3->addItem(QString::fromLocal8Bit("节点5"));
	ui->IpcomboBox3->addItem(QString::fromLocal8Bit("节点6"));
	ui->label4->setVisible(false);
	ui->label5->setVisible(false);
	ui->label6->setVisible(false);
	ui->IpcomboBox1->setVisible(false);
	ui->IpcomboBox2->setVisible(false);
	ui->IpcomboBox3->setVisible(false);
	ui->accelerateRadioButton->setChecked(true);
	//init_ui();
	connect(ui->btnAddToolClose, &QPushButton::clicked, this, &AddToolInfoDialog::close);
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
void AddToolInfoDialog::getToolsData(table_ip& toolsData)
{
	toolsData.software = ui->lineEditToolName->text().toStdString();
	//QString strPath = ui->lineEditToolPath->text();
	//strPath.replace("\\","\\\\");
	toolsData.toolPath = ui->lineEditToolPath->text().replace("\\", "\\\\").toStdString();
	toolsData.icoPath = ui->lineEdit->text().replace("\\", "\\\\").toStdString();
}


void AddToolInfoDialog::slot_btnOk()
{

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
    if (ui->lineEdit->text().toStdString().empty())
    {
        QMessageBox::warning(this, QString::fromLocal8Bit("警告"), QString::fromLocal8Bit("图标路径不能为空!"));
        return;
    }
	/*if (!(ui->accelerateRadioButton->isChecked() && ui->nodeRadioButton->isChecked()))
	{
		QMessageBox::warning(this, QString::fromLocal8Bit("警告"), QString::fromLocal8Bit("需选择计算节点或者指定节点!"));
		return;
	}*/
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

void AddToolInfoDialog::slot_btnhideWidget()
{
	ui->label4->setVisible(false);
	ui->label5->setVisible(false);
	ui->label6->setVisible(false);
	ui->IpcomboBox1->setVisible(false);
	ui->IpcomboBox2->setVisible(false);
	ui->IpcomboBox3->setVisible(false);
	//ui->widget->layout()->update();
	ui->widget->adjustSize();
}

void AddToolInfoDialog::slot_btnhideWidget2()
{
	ui->label4->setVisible(true);
	ui->label5->setVisible(true);
	ui->label6->setVisible(true);
	ui->IpcomboBox1->setVisible(true);
	ui->IpcomboBox2->setVisible(true);
	ui->IpcomboBox3->setVisible(true);
}

QRadioButton* AddToolInfoDialog::getAccelerateRadio()
{
	return ui->accelerateRadioButton;
}
QRadioButton* AddToolInfoDialog::getnodeRadio()
{
	return ui->nodeRadioButton;
}
QLabel* AddToolInfoDialog::getlabel4()
{
	return ui->label4;
}
QLabel* AddToolInfoDialog::getlabel5()
{
	return ui->label5;
}
QLabel* AddToolInfoDialog::getlabel6()
{
	return ui->label6;
}
QComboBox* AddToolInfoDialog::getipComboBox1()
{
	return ui->IpcomboBox1;
}
QComboBox* AddToolInfoDialog::getipComboBox2()
{
	return ui->IpcomboBox2;
}
QComboBox* AddToolInfoDialog::getipComboBox3()
{
	return ui->IpcomboBox3;
}
QWidget* AddToolInfoDialog::getwidget()
{
	return ui->widget;
}

void AddToolInfoDialog::init_ui()
{
	ui->lineEditToolName->setStyleSheet("QLineEdit { border: 1px solid gray;border-radius: 5px;}");
	ui->lineEditToolPath->setStyleSheet("QLineEdit { border: 1px solid gray;border-radius: 5px;}");
	ui->lineEdit->setStyleSheet("QLineEdit { border: 1px solid gray;border-radius: 5px;}");
	ui->btnChooseImage->setStyleSheet("QPushButton { border: 1px solid gray;border-radius: 5px;}");;
	ui->IpcomboBox1->setStyleSheet("QComboBox { border: 1px solid gray;border-radius: 5px;}");
	ui->IpcomboBox2->setStyleSheet("QComboBox { border: 1px solid gray;border-radius: 5px;}");
	ui->IpcomboBox3->setStyleSheet("QComboBox { border: 1px solid gray;border-radius: 5px;}");
	ui->btnOK->setStyleSheet("QPushButton { color: white; border: 0.5px solid gray;border-radius: 10px;background-color: rgb(10, 135, 250)}");
}



