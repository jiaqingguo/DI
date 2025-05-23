﻿#include <QTextCodec>
#include <QApplication>
#include <QSettings>
#include <QMessageBox>
#include <QFontDatabase>

#include "mainwindow.h"

#include "databaseDI.h"
#include "LoginDialog.h"
#include "common.h"
#include "globel.h"


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
            common::strDbIp = settings.value("serverIp").toString();
            common::strDbUser = settings.value("user").toString();
           // common::strDbPassword = settings.value("password").toString();
        }
      /*  else if (section == "FTP")
        {
            common::strLinuxFtpIp= settings.value("serverIp").toString();
            common::strFtpAccount = settings.value("account").toString();
            common::strFtpPwd = settings.value("password").toString();
            common::strFtpAdminPwd = settings.value("adminpassword").toString();
        }*/
        else if (section == "Ax")
        {
            common::strAxCLSID = settings.value("CLSID","{8B918B82-7985-4C24-89DF-C33AD2BBFBCD}").toString();
          
        }
        else 
        {
            common::strVipPath = settings.value("vipPath").toString();
        }
          // 结束当前节的切换
        settings.endGroup();
    }



    db::databaseDI::Instance().setDbLoginData(common::strDbIp.toStdString(), common::strDbUser.toStdString(), "123456");
    if (!db::databaseDI::Instance().open())
    {
        QMessageBox::warning(nullptr, QString::fromLocal8Bit("警告"), QString::fromLocal8Bit("数据库连接失败"));
        return 0;
    }
    table_configuration stData;
    if (db::databaseDI::Instance().get_configuration(stData))
    {
        common::strLinuxFtpIp = QString::fromStdString(stData.ftpServerIp);
        common::strFtpAccount = QString::fromStdString(stData.ftpServerAccount);
        common::strFtpPwd = QString::fromStdString(stData.ftpPwd);
        common::strFtpAdminPwd = QString::fromStdString(stData.ftpServerPwd);
    }




    // 加载字体文件
    QFontDatabase fontDB;
    QString fontPath = ":/image/SourceHanSansSC.otf";
    int fontId = fontDB.addApplicationFont(fontPath);

    // 检查字体是否已经被加载
    if (fontId != -1)
    {
        //获取导入的字体文件中，有几种字体样式，比如字体文件中存在粗体和普通字体样式，需要逐一设置
        QStringList fontFamilies = fontDB.applicationFontFamilies(fontId);
        foreach(QString fontFamily, fontFamilies)
        {
            // 设置字体
            QFont font(fontFamily);
            a.setFont(font);
        }
    }
    else
    {
       /* qDebug() << "Load font failed";*/
        return -1;
    }
 
    MainWindow w;
    if (!w.showLoginDialog())
    {
		return 0;
    }
   
    return a.exec();
}
