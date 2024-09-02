#include "fingerDlg.h"

#include "RegisterDialog.h"
#include "ui_RegisterDialog.h"
#include "mainwindow.h"
#include "databaseDI.h"
#include "globel.h"
#include <QDebug>
#include <QMessagebox>

RegisterDialog::RegisterDialog(QWidget* parent) :
    QDialog(parent),
    ui(new Ui::RegisterDialog)
{
    ui->setupUi(this);
    setWindowTitle(QString::fromLocal8Bit("用户注册"));
    setWindowIcon(QIcon(":/image/Register.png"));
    ui->stackedWidget->setCurrentIndex(0);
    ui->labelUser->setText(QString::fromLocal8Bit("<font color='red'>*</font><font color='black'>用户名</font>"));
    ui->labelPassword->setText(QString::fromLocal8Bit("<font color='red'>*</font><font color='black'>密码</font>"));
    ui->labelName->setText(QString::fromLocal8Bit("<font color='red'>*</font><font color='black'>使用人</font>"));


    ui->lineEditUserName->setMaxLength(10); // 限制最多输入10个字符
   
    QRegExp rx("[0-9a-zA-Z]{19}");
    ui->lineEditPassword->setValidator(new QRegExpValidator(rx));

    QMetaObject::Connection conn = connect(ui->btnRegister, &QPushButton::clicked, this, &RegisterDialog::slot_btnRegister);
    connect(ui->btnFingerprintInput, &QPushButton::clicked, this, &RegisterDialog::slot_btnFingerprintInput);

}

RegisterDialog::~RegisterDialog()
{
    delete ui;
}

void RegisterDialog::slot_btnRegister()
{
    table_user stUser;
    stUser.UserName = ui->lineEditUserName->text().toStdString();
    stUser.Password = ui->lineEditPassword->text().toStdString();
    stUser.name = ui->lineEditName->text().toStdString();
    stUser.department = ui->lineEditDepartment->text().toStdString();
    stUser.JobTitle = ui->lineEditJobTtile->text().toStdString();
    stUser.PhoneNumber = ui->lineEditPhoneNumber->text().toStdString();
    stUser.CreateTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    stUser.approval = 0;
    if (stUser.UserName.empty() || stUser.Password.empty() || stUser.name.empty())
    {
        QMessageBox::warning(this, QString::fromLocal8Bit("警告"), QString::fromLocal8Bit("* 数据不能为空!"));
        return;
    }
    table_user stTemp;
    stTemp.UserName = "";
    stTemp.Password = "";
    db::databaseDI::Instance().get_user(stTemp, stUser.UserName);
    if (stTemp.UserName.empty())
    {
        if (ui->comboBox->currentIndex() == 0)
        {
            stUser.Pop = 0;
            if (!db::databaseDI::Instance().add_user_info(stUser))
            {
                QMessageBox::warning(this, QString::fromLocal8Bit("数据库"), QString::fromLocal8Bit("用户注册失败!"));
                return;
            }
            ui->stackedWidget->setCurrentIndex(1);
        }
        else
        {
            stUser.Pop = 1;
            if (!db::databaseDI::Instance().add_user_info(stUser))
            {
                QMessageBox::warning(this, QString::fromLocal8Bit("数据库"), QString::fromLocal8Bit("用户注册失败!"));
                return;
            }  
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
            if (ui->comboBox->currentIndex() == 0)
            {
                stUser.Pop = 0;
                if (!db::databaseDI::Instance().add_user_info(stUser))
                {
                    QMessageBox::warning(this, QString::fromLocal8Bit("数据库"), QString::fromLocal8Bit("用户注册失败!"));
                    return;
                }
                ui->stackedWidget->setCurrentIndex(1);
            }
            else
            {
                stUser.Pop = 1;
                if (!db::databaseDI::Instance().add_user_info(stUser))
                {
                    QMessageBox::warning(this, QString::fromLocal8Bit("数据库"), QString::fromLocal8Bit("用户注册失败!"));
                    return;
                }
                this->accept();
            }
        }
    }
  
}

void RegisterDialog::slot_btnFingerprintInput()
{
   
    
    //this->accept();
    //close();
	//g_pMainWindow->show();

	if (NULL != m_hDevice)
	{
		if (!m_bRegister)
		{
			m_bRegister = TRUE;
			m_enrollIdx = 0;
			//ui->label_7->setText(QString::fromLocal8Bit("请连续按3次手指"));
			QMessageBox::information(this, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("请连续按3次手指"));
			//SetDlgItemText(IDC_EDIT_RESULT, _T("Doing register, please press your finger 3 times!"));
		}
	}
	//QMessageBox::information(this, QString::fromLocal8Bit("注册"), QString::fromLocal8Bit("注册完成，请等待管理员审核!"));
	close();

}