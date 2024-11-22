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
    setWindowTitle(QString::fromLocal8Bit("�޸�����"));
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
        QMessageBox::information(this, QString::fromLocal8Bit("��ʾ"), QString::fromLocal8Bit("�������û���"));
        return;
    }
    QString strOriginalpwd = ui->lineEditPassword->text();
    QString strNewPwd = ui->lineEditNewPwd->text();
    table_user stData;
    if (db::databaseDI::Instance().get_user_by_condition(stData, strUserName.toStdString()))
    {
        if (stData.UserName.empty())
        {
            QMessageBox::information(this, QString::fromLocal8Bit("��ʾ"), QString::fromLocal8Bit("�û��������ڻ�����δͨ��"));
            return;
        }

        if (strOriginalpwd != QString::fromStdString(stData.Password))
        {
            QMessageBox::information(this, QString::fromLocal8Bit("��ʾ"), QString::fromLocal8Bit("ԭ���벻��ȷ"));
            return;
        }

        if (strOriginalpwd == strNewPwd)
        {
            QMessageBox::information(this, QString::fromLocal8Bit("��ʾ"), QString::fromLocal8Bit("����һ�£������޸�"));
            return;
        }

        if (db::databaseDI::Instance().update_user_pwd(stData.PKID, strNewPwd.toStdString()))
        {
            QMessageBox::information(this, QString::fromLocal8Bit("��ʾ"), QString::fromLocal8Bit("�����޸ĳɹ�"));
            this->accept();
        }

    }

}
