﻿//#include "fingerDlg.h"

#include "RegisterDialog.h"
#include "ui_RegisterDialog.h"
#include "mainwindow.h"
#include "databaseDI.h"
#include "globel.h"
#include "common.h"
#include <QDebug>
#include <QMessagebox>

RegisterDialog::RegisterDialog(QWidget* parent) :
	QDialog(parent),
	ui(new Ui::RegisterDialog)
{
	ui->setupUi(this);
	setWindowFlags(Qt::FramelessWindowHint);
	setWindowTitle(QString::fromLocal8Bit("用户注册"));
	setWindowIcon(QIcon(":/image/registerIcon.png"));
	ui->stackedWidget->setCurrentIndex(0);
	/*ui->labelUser->setText(QString::fromLocal8Bit("<font color='black' face='黑体' >用户名</font><font color='red'>*</font>"));
	ui->labelPassword->setText(QString::fromLocal8Bit("<font color='black'>密码</font><font color='red'>*</font>"));
	ui->labelName->setText(QString::fromLocal8Bit("<font color='black'>使用人</font><font color='red'>*</font>"));*/


	ui->lineEditUserName->setMaxLength(20); // 限制最多输入20个字符
	ui->lineEditPassword->setMaxLength(20);
	QRegExp rx("[0-9a-zA-Z]{19}");
	ui->lineEditUserName->setValidator(new QRegExpValidator(rx));
	ui->lineEditPassword->setEchoMode(QLineEdit::Password);
	//ui->lineEditPassword->setValidator(new QRegExpValidator(rx));
	//聚焦
	setTabOrder(ui->lineEditUserName,ui->lineEditPassword);
	setTabOrder(ui->lineEditPassword,ui->lineEditName);
	setTabOrder(ui->lineEditName,ui->lineEditDepartment);
	setTabOrder(ui->lineEditDepartment,ui->lineEditJobTtile);
	setTabOrder(ui->lineEditJobTtile,ui->lineEditPhoneNumber);

	QMetaObject::Connection conn = connect(ui->btnRegister, &QPushButton::clicked, this, &RegisterDialog::slot_btnRegister);
	//connect(ui->btnFingerprintInput, &QPushButton::clicked, this, &RegisterDialog::slot_btnFingerprintInput);

	ui->comboBoxRoot->setCurrentIndex(1);
	ui->comboBoxRoot->setEnabled(false);

	//init_ui();
	connect(ui->btnRegistClose, &QPushButton::clicked, this, &RegisterDialog::close);
}

RegisterDialog::~RegisterDialog()
{
	delete ui;
}

void RegisterDialog::slot_btnRegister()
{
	table_user stTemp;
	common::stUser.UserName = ui->lineEditUserName->text().toStdString();
	common::stUser.Password = ui->lineEditPassword->text().toStdString();
	common::stUser.name = ui->lineEditName->text().toStdString();
	common::stUser.department = ui->lineEditDepartment->text().toStdString();
	common::stUser.JobTitle = ui->lineEditJobTtile->text().toStdString();
	common::stUser.PhoneNumber = ui->lineEditPhoneNumber->text().toStdString();
	common::stUser.CreateTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	common::stUser.approval = 0;
	if (common::stUser.UserName.empty() || common::stUser.Password.empty() || common::stUser.name.empty())
	{
		QMessageBox::warning(this, QString::fromLocal8Bit("警告"), QString::fromLocal8Bit("* 数据不能为空!"));
		return;
	}
	
	stTemp.UserName = "";
	stTemp.Password = "";
	db::databaseDI::Instance().get_user(stTemp, common::stUser.UserName);
	if (stTemp.UserName.empty())
	{
		if (ui->comboBoxRoot->currentIndex() == 0)
		{
			common::stUser.Pop = 0;

			if (!db::databaseDI::Instance().add_user_info(common::stUser))
			{
				QMessageBox::warning(this, QString::fromLocal8Bit("数据库"), QString::fromLocal8Bit("用户注册失败!"));
				return;
			}
			MessageBox(NULL, TEXT("注册完成，请等待管理员审核!"), TEXT("提示"), 0);
			
			this->accept();

			//ui->stackedWidget->setCurrentIndex(1);
			
		}
		else
		{
			common::stUser.Pop = 1;

			if (!db::databaseDI::Instance().add_user_info(common::stUser))
			{
				QMessageBox::warning(this, QString::fromLocal8Bit("数据库"), QString::fromLocal8Bit("用户注册失败!"));
				return;
			}
			MessageBox(NULL, TEXT("注册完成，请等待管理员审核!"), TEXT("提示"), 0);
			
			this->accept();
		}
	}
	else
	{
		if (stTemp.approval == 0)
		{
			QMessageBox::information(this, QString::fromLocal8Bit("数据库"), QString::fromLocal8Bit("早已注册，请等待管理员审核!"));
			return;
		}
		else if (stTemp.approval == 1)
		{
			QMessageBox::warning(this, QString::fromLocal8Bit("数据库"), QString::fromLocal8Bit("用户已注册!"));
			return;
		}
		if (stTemp.approval == 2) // 已经驳回的用户名 再次注册
		{
			if (ui->comboBoxRoot->currentIndex() == 0)
			{
				common::stUser.Pop = 0;

				if (!db::databaseDI::Instance().add_user_info(common::stUser))
				{
					QMessageBox::warning(this, QString::fromLocal8Bit("数据库"), QString::fromLocal8Bit("用户注册失败!"));
					return;
				}
				MessageBox(NULL, TEXT("注册完成，请等待管理员审核!"), TEXT("提示"), 0);
				
				this->accept();
				//ui->stackedWidget->setCurrentIndex(1);
			}
			else
			{
				common::stUser.Pop = 1;

				if (!db::databaseDI::Instance().add_user_info(common::stUser))
				{
					QMessageBox::warning(this, QString::fromLocal8Bit("数据库"), QString::fromLocal8Bit("用户注册失败!"));
					return;
				}
				MessageBox(NULL, TEXT("注册完成，请等待管理员审核!"), TEXT("提示"), 0);
				
				this->accept();
			}
		}
	}

}

//void RegisterDialog::slot_btnFingerprintInput()
//{
	//this->accept();
	//close();
	//g_pMainWindow->show();

	//if (NULL != m_hDevice)
	//{
	//	if (!m_bRegister)
	//	{
	//		m_bRegister = TRUE;
	//		m_enrollIdx = 0;
	//		//ui->label_7->setText(QString::fromLocal8Bit("注册指纹，请按3次手指"));


	//		connect(timer, &QTimer::timeout, this, &RegisterDialog::slot_updateLabelText);
	//		timer->start(500);
	//	}
	//}
	//QMessageBox::information(this, QString::fromLocal8Bit("注册"), QString::fromLocal8Bit("注册完成，请等待管理员审核!"));
	//close();

//}
//void RegisterDialog::slot_updateLabelText()
//{
//	static QString texts[] = { QString::fromLocal8Bit("开始指纹登记, 请按压手指3次"), QString::fromLocal8Bit("您仍需要按2次"), QString::fromLocal8Bit("您仍需要按1次") };
//	if (m_enrollIdx < 3) {
//		ui->label_7->setText(texts[m_enrollIdx]);
//		///++m_enrollIdx;
//	}
//	else {
//		// 当文本变化三次后，可以停止定时器
//		// 假设timer是定时器的成员变量
//		timer->stop();
//		m_enrollIdx = 0; // 重置计数器，以便可以重复使用
//	}
//}
void RegisterDialog::init()
{
	ui->btnFingerprintInput->hide();
	ui->lineEditUserName->clear();
	ui->lineEditPassword->clear();
	ui->lineEditName->clear();
	ui->lineEditDepartment->clear();
	ui->lineEditJobTtile->clear();
	ui->lineEditPhoneNumber->clear();

	ui->stackedWidget->setCurrentIndex(0);
	//ui->label_7->setText(QString::fromLocal8Bit("注册指纹，请按3次手指"));
	//m_enrollIdx = 3;
	//this->slot_btnFingerprintInput();
}
void RegisterDialog::init_ui()
{
	ui->lineEditUserName->setStyleSheet("QLineEdit { border: 1px solid gray;border-radius: 5px;}");
	ui->lineEditPassword->setStyleSheet("QLineEdit { border: 1px solid gray;border-radius: 5px;}");
	ui->lineEditName->setStyleSheet("QLineEdit { border: 1px solid gray;border-radius: 5px;}");
	ui->lineEditDepartment->setStyleSheet("QLineEdit { border: 1px solid gray;border-radius: 5px;}");
	ui->lineEditJobTtile->setStyleSheet("QLineEdit { border: 1px solid gray;border-radius: 5px;}");
	ui->lineEditPhoneNumber->setStyleSheet("QLineEdit { border: 1px solid gray;border-radius: 5px;}");
	ui->comboBoxRoot->setStyleSheet("QComboBox { border: 1px solid gray; border-radius: 5px; }");
	ui->btnRegister->setStyleSheet("QPushButton { color: white; border: 0.5px solid gray;border-radius: 10px;background-color: rgb(10, 135, 250)}");
}