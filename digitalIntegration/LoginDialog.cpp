#include "fingerDlg.h"

#include <QValidator>
#include <QMessageBox>

#include <set>

#include "LoginDialog.h"
#include "ui_LoginDialog.h"

#include "globel.h"
#include "mainwindow.h"
#include "databaseDI.h"
#include "RegisterDialog.h"
#include "common.h"


LoginDialog::LoginDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::LoginDialog)
{
	ui->setupUi(this);
	setWindowTitle(("��ӭʹ����������Ӳ��һ�廯ƽ̨"));
	ui->stackedWidget->setCurrentIndex(0);
	//setWindowTitle(GBK_STRING("��ӭʹ����������Ӳ��һ�廯ƽ̨"));
	QRegExp rx("[0-9a-zA-Z]{19}");
	ui->leUser->setValidator(new QRegExpValidator(rx));
	ui->lePassword->setValidator(new QRegExpValidator(rx));
	ui->leUser->setAttribute(Qt::WA_InputMethodEnabled, false);
	ui->lePassword->setAttribute(Qt::WA_InputMethodEnabled, false);


	ui->lblPwd->setStyleSheet("border-image: url(:/image/password.png); color: rgb(255, 102, 102);");
	connect(ui->btnLogin, &QPushButton::clicked, this, &LoginDialog::slot_btnLoginClicked);
	connect(ui->btnRegister, &QPushButton::clicked, this, &LoginDialog::slot_btnExitClicked);
	connect(ui->leUser, &QLineEdit::textChanged, this, &LoginDialog::slot_leUserTextChanged);
	connect(ui->leUser, &QLineEdit::editingFinished, this, &LoginDialog::slot_leUserEditingFinished);
	connect(ui->lePassword, &QLineEdit::textChanged, this, &LoginDialog::slot_lePwdTextChanged);
	connect(ui->lePassword, &QLineEdit::editingFinished, this, &LoginDialog::slot_lePwdEditingFinished);
	//connect(ui->btnFingerprint, &QPushButton::clicked, this, &LoginDialog::slot_btnFingerprintClicked);

	this->m_fingerDlg = new fingerDlg();
	/*this->m_fingerDlg->finger_init();*/
	connect(this->m_fingerDlg, &fingerDlg::login_succ, this, &LoginDialog::slot_login_succ);
	connect(this->m_fingerDlg, &fingerDlg::regist_succ, this, &LoginDialog::slot_regist_succ);
	connect(this->m_fingerDlg, &fingerDlg::no_regist_finger, this, &LoginDialog::slot_no_regist_finger);

	this->registerDialog = new RegisterDialog();
}

LoginDialog::~LoginDialog()
{
	delete ui;
}

void LoginDialog::Init(bool bClearPwd)
{
	// �����ʱ��
	clearTimer();
}

int LoginDialog::GetUserID()
{
	return m_userID;
}

int LoginDialog::GetLoginState()
{
	return m_iState;
}

int LoginDialog::GetPop()
{
	return m_pop;
}

QString LoginDialog::GetUser()
{
	return m_sUser;
}

void LoginDialog::UpdateLoginResult(short iRes)
{
	// �����ʱ��
	clearTimer();
}

void LoginDialog::slot_btnLoginClicked()
{

	m_sUser = ui->leUser->text();
	QString sPassword = ui->lePassword->text();
	if (m_sUser.isEmpty())
	{
		ui->leUser->setPlaceholderText(GBK_STRING("�û�������Ϊ��"));
		ui->leUser->setStyleSheet("border-image: url(:/image/lineedit_error.png); color: rgb(255, 102, 102);");
		ui->leUser->setFocus();
		ui->lblUser->setStyleSheet("border-image: url(:/image/user_error.png);");
		return;
	}

	if (sPassword.isEmpty())
	{
		ui->lePassword->setPlaceholderText(GBK_STRING("���벻��Ϊ��"));
		ui->lePassword->setStyleSheet("border-image: url(:/image/lineedit_error.png); color: rgb(255, 102, 102);");
		ui->lePassword->setFocus();
		ui->lblPwd->setStyleSheet("border-image: url(:/image/password.png); color: rgb(255, 102, 102);");
		return;
	}

	// ���ݿ��ѯ�û�������

	if (!db::databaseDI::Instance().is_exist_user(m_sUser.toStdString(), sPassword.toStdString()))
	{

		QMessageBox::warning(this, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("��������ȷ���û�������!"));
		return;
	}

	table_user stData;
	stData.UserName = "";
	stData.Password = "";
	db::databaseDI::Instance().get_user(stData, m_sUser.toStdString());

	if (stData.approval == 0)
	{
		QMessageBox::warning(this, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("����ϵ����Ա����Թ���Ա�������"));
		return;
	}
	else if (stData.approval == 2)
	{
		//QMessageBox::warning(this, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("����Ա��˲���));
		QMessageBox::warning(this, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("��������ȷ���û�������!"));
		return;
	}
	if (stData.loginStatus == 1)
	{
		QMessageBox::warning(this, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("�û��ѵ�¼�������ظ���¼��"));
		return;
	}

	//db::databaseDI::Instance().get_user_login_number(common::iLoginNum);
	if (common::iLoginNum >= 6)
	{
		QMessageBox::warning(this, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("����ͬʱ��¼�����û������������¼��"));
		return;
	}

	m_userID = stData.PKID;
	common::iUserID = stData.PKID;


	/*int pop = -1;
	db::databaseDI::Instance().get_pop(pop, m_sUser.toStdString(), sPassword.toStdString());*/
	if (stData.Pop == 0)
	{
		this->m_fingerDlg->finger_init();

		m_pop = 0;
		common::bAdministrator = true;
		ui->btnFingerprint->hide();
		ui->stackedWidget->setCurrentIndex(1);
		this->slot_btnFingerprintClicked();
	}
	else
	{
		m_pop = 1;
		common::bAdministrator = false;
		int loginStatus = 1;
		db::databaseDI::Instance().update_user_LoginStatus(m_userID, loginStatus);
		db::databaseDI::Instance().get_user_login_number(common::iLoginNum);
		//db::databaseDI::Instance().get_ip_data_by_number(common::setHostIps, common::iLoginNum);
		db::databaseDI::Instance().get_ip_data_by_number( common::iLoginNum, common::setHostData);
		this->accept();
	}
}

void LoginDialog::slot_btnExitClicked()
{
	this->m_fingerDlg->finger_init();
	registerDialog->init();
	registerDialog->exec();
	
}

void LoginDialog::slot_btnFingerprintClicked()
{
	if (NULL != m_hDevice)
	{
		if (m_bRegister)
		{
			m_bRegister = FALSE;
			//QMessageBox::information(this, QString::fromLocal8Bit("��ʾ"), QString::fromLocal8Bit("Start verify last register template"));
			//SetDlgItemText(IDC_EDIT_RESULT, _T("Start verify last register template"));
		}
		m_bIdentify = TRUE;

	}
	int i = 1;
	db::databaseDI::Instance().get_ip_data_by_number(i, common::setHostData);
	//this->accept();


}

void LoginDialog::slot_timeout()
{
	// �����ʱ��
	clearTimer();
}

void LoginDialog::setWindowTitle(QString strTitle)
{

}


void LoginDialog::clearTimer()
{
	/*if (m_Timer.isActive())
	{
		m_Timer.stop();
	}*/
}

void LoginDialog::slot_leUserTextChanged(const QString& text)
{
	ui->leUser->setStyleSheet("border-image: url(:/image/lineedit.png); color: black;");
	ui->leUser->setPlaceholderText(GBK_STRING("�����������û���"));
	ui->lblUser->setStyleSheet("border-image: url(:/image/user_focusin.png);");
}

void LoginDialog::slot_leUserEditingFinished()
{
	ui->lblUser->setStyleSheet("border-image: url(:/image/user_focusin.png);");
}

void LoginDialog::slot_lePwdTextChanged(const QString& text)
{
	ui->lePassword->setStyleSheet("color: black;");
	ui->lePassword->setPlaceholderText(GBK_STRING("��������������"));
	ui->lblPwd->setStyleSheet("border-image: url(:/image/password.png); ");
}

void LoginDialog::slot_lePwdEditingFinished()
{
	ui->lblPwd->setStyleSheet("border-image: url(:/image/password.png);");
}

void LoginDialog::slot_login_succ()
{
	int loginStatus = 1;
	db::databaseDI::Instance().update_user_LoginStatus(common::iUserID, loginStatus);

	db::databaseDI::Instance().get_user_login_number(common::iLoginNum);
//	db::databaseDI::Instance().get_ip_data_by_number(common::setHostIps, common::iLoginNum);
	db::databaseDI::Instance().get_ip_data_by_number( common::iLoginNum, common::setHostData);

	this->accept();

	if (m_fingerDlg != nullptr)
		delete m_fingerDlg;
}

void LoginDialog::slot_regist_succ()
{
	registerDialog->close();
}

void LoginDialog::slot_no_regist_finger()
{
	ui->stackedWidget->setCurrentIndex(0);
}
