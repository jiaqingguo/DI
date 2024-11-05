
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
    // 创建QSettings对象并指定INI文件路径
    QSettings settings(strIniPath, QSettings::IniFormat);

    // 获取INI文件中的所有节
    QStringList sections = settings.childGroups();

    // 遍历节列表
    foreach(const QString & section, sections)
    {
        // 切换到指定的节
        settings.beginGroup(section);

        // 获取该节下的所有键
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
          // 结束当前节的切换
        settings.endGroup();
    }



    db::databaseDI::Instance().setDbLoginData(common::strDbIp.toStdString(), common::strDbUser.toStdString(), common::strDbPassword.toStdString());
    if (!db::databaseDI::Instance().open())
    {
        QMessageBox::warning(nullptr, QString::fromLocal8Bit("警告"), QString::fromLocal8Bit("数据库连接失败"));
        return 0;
    }
    MainWindow w;
    if (!w.showLoginDialog())
    {
		return 0;
    }
   
    return a.exec();
}
