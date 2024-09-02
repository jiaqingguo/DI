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
    setWindowTitle(QString::fromLocal8Bit("�û�ע��"));
    setWindowIcon(QIcon(":/image/Register.png"));
    ui->stackedWidget->setCurrentIndex(0);
    ui->labelUser->setText(QString::fromLocal8Bit("<font color='red'>*</font><font color='black'>�û���</font>"));
    ui->labelPassword->setText(QString::fromLocal8Bit("<font color='red'>*</font><font color='black'>����</font>"));
    ui->labelName->setText(QString::fromLocal8Bit("<font color='red'>*</font><font color='black'>ʹ����</font>"));


    ui->lineEditUserName->setMaxLength(10); // �����������10���ַ�
   
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
        QMessageBox::warning(this, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("* ���ݲ���Ϊ��!"));
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
                QMessageBox::warning(this, QString::fromLocal8Bit("���ݿ�"), QString::fromLocal8Bit("�û�ע��ʧ��!"));
                return;
            }
            ui->stackedWidget->setCurrentIndex(1);
        }
        else
        {
            stUser.Pop = 1;
            if (!db::databaseDI::Instance().add_user_info(stUser))
            {
                QMessageBox::warning(this, QString::fromLocal8Bit("���ݿ�"), QString::fromLocal8Bit("�û�ע��ʧ��!"));
                return;
            }  
            this->accept();
        }
    }
    else
    {
        if (stTemp.approval == 0)
        {
            QMessageBox::information(this, QString::fromLocal8Bit("���ݿ�"), QString::fromLocal8Bit("����ע�ᣬ��ȴ�����Ա���!"));
            return;
        }
        else if (stTemp.approval == 1)
        {
            QMessageBox::warning(this, QString::fromLocal8Bit("���ݿ�"), QString::fromLocal8Bit("�û���ע��!"));
            return;
        }
        if (stTemp.approval == 2) // �Ѿ����ص��û��� �ٴ�ע��
        {
            if (ui->comboBox->currentIndex() == 0)
            {
                stUser.Pop = 0;
                if (!db::databaseDI::Instance().add_user_info(stUser))
                {
                    QMessageBox::warning(this, QString::fromLocal8Bit("���ݿ�"), QString::fromLocal8Bit("�û�ע��ʧ��!"));
                    return;
                }
                ui->stackedWidget->setCurrentIndex(1);
            }
            else
            {
                stUser.Pop = 1;
                if (!db::databaseDI::Instance().add_user_info(stUser))
                {
                    QMessageBox::warning(this, QString::fromLocal8Bit("���ݿ�"), QString::fromLocal8Bit("�û�ע��ʧ��!"));
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
			//ui->label_7->setText(QString::fromLocal8Bit("��������3����ָ"));
			QMessageBox::information(this, QString::fromLocal8Bit("��ʾ"), QString::fromLocal8Bit("��������3����ָ"));
			//SetDlgItemText(IDC_EDIT_RESULT, _T("Doing register, please press your finger 3 times!"));
		}
	}
	//QMessageBox::information(this, QString::fromLocal8Bit("ע��"), QString::fromLocal8Bit("ע����ɣ���ȴ�����Ա���!"));
	close();

}