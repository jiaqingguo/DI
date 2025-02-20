#include <qmessagebox.h>

#include "ChangePwdDialog.h"
#include "ui_ChangePwdDialog.h"
#include "databaseDI.h"
#include "globel.h"


ChangePwdDialog::ChangePwdDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChangePwdDialog)
{
    ui->setupUi(this);
    setWindowTitle(QString::fromLocal8Bit("修改密码"));
    setWindowIcon(QIcon(":/image/Register.png"));
    connect(ui->btnModify, &QPushButton::clicked, this, &ChangePwdDialog::slot_btnModify);
	ui->lineEditPassword->setEchoMode(QLineEdit::Password);
	ui->lineEditNewPwd->setEchoMode(QLineEdit::Password);
	ui->lineEditConfrimPwd->setEchoMode(QLineEdit::Password);

	ui->btnModify->setStyleSheet("QPushButton { color: white; border: 0.5px solid gray;border-radius: 10px;background-color: rgb(10, 135, 250)}");
	ui->lineEditUserName->setStyleSheet("QLineEdit { border: 1px solid gray;border-radius: 5px;}");
	ui->lineEditPassword->setStyleSheet("QLineEdit { border: 1px solid gray;border-radius: 5px;}");
	ui->lineEditNewPwd->setStyleSheet("QLineEdit { border: 1px solid gray;border-radius: 5px;}");
	ui->lineEditConfrimPwd->setStyleSheet("QLineEdit { border: 1px solid gray;border-radius: 5px;}");
}

ChangePwdDialog::~ChangePwdDialog()
{
    delete ui;
}

void ChangePwdDialog::slot_btnModify()
{
    QString strUserName = ui->lineEditUserName->text();
    if (strUserName.isEmpty())
    {
        QMessageBox::information(this, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("请输入用户名"));
        return;
    }
    QString strOriginalpwd = ui->lineEditPassword->text();
    QString strNewPwd = ui->lineEditNewPwd->text();
	QString strConfirmPwd = ui->lineEditConfrimPwd->text();
    table_user stData;

	if (strNewPwd != strConfirmPwd)
	{
		QMessageBox::information(this, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("两次输入的新密码不一致，请重新输入"));
		return;
	}
    if (db::databaseDI::Instance().get_user_by_condition(stData, strUserName.toStdString()))
    {
        if (stData.UserName.empty())
        {
            QMessageBox::information(this, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("用户名不存在或审批未通过"));
            return;
        }

        if (strOriginalpwd != QString::fromStdString(stData.Password))
        {
            QMessageBox::information(this, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("原密码不正确"));
            return;
        }

        if (strOriginalpwd == strNewPwd)
        {
            QMessageBox::information(this, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("密码一致，无序修改"));
            return;
        }

        if (db::databaseDI::Instance().update_user_pwd(stData.PKID, strNewPwd.toStdString()))
        {
            QMessageBox::information(this, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("密码修改成功"));
            this->accept();
        }

    }

}
