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
    table_user stData;
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
