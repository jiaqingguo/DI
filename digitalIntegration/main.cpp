
#include <QApplication>
#include <QSettings>
#include <QMessageBox>
#include "mainwindow.h"

#include "databaseDI.h"
#include "LoginDialog.h"
#include "common.h"


int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QString exeDir = QCoreApplication::applicationDirPath();
    QString strIniPath = exeDir + "/software.ini";
    // ����QSettings����ָ��INI�ļ�·��
    QSettings settings(strIniPath, QSettings::IniFormat);

    // ��ȡINI�ļ��е����н�
    QStringList sections = settings.childGroups();

    // �������б�
    foreach(const QString & section, sections)
    {
        // �л���ָ���Ľ�
        settings.beginGroup(section);

        // ��ȡ�ý��µ����м�
        QStringList keys = settings.allKeys();

        if (section == "TCP")
        {
            common::strFtpIp = settings.value("serverIp").toString();
            common::iFtpPort = settings.value("serverPort").toInt();
          /*  m_listenPort = settings.value("listenPort").toInt();
            m_plcName = settings.value("listenPort").toString().toStdString();*/


         
        }
        else if (section == "DB")
        {
            common::strDbIp = settings.value("ip").toString();
            common::strDbUser = settings.value("user").toString();
            common::strDbPassword = settings.value("password").toString();
        }
        else 
        {
            common::strVipPath = settings.value("vipPath").toString();
        }
          // ������ǰ�ڵ��л�
        settings.endGroup();
    }



    db::databaseDI::Instance().setDbLoginData(common::strDbIp.toStdString(), common::strDbUser.toStdString(), common::strDbPassword.toStdString());
    if (!db::databaseDI::Instance().open())
    {
        QMessageBox::warning(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("���ݿ�����ʧ��"));
        return 0;
    }
    MainWindow w;
    if (!w.showLoginDialog())
    {
		return 0;
    }
   
    return a.exec();
}
