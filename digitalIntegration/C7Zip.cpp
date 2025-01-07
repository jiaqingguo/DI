#include <QApplication>
#include <QProcess>

#include <QDebug>
#include "C7Zip.h"

C7Zip::C7Zip(QObject *parent) : QObject(parent)
{
    m_str7zipExePath = QApplication::applicationDirPath() + "/7-Zip/7z.exe";
    m_str7zipExePath.replace("/", "\\\\");
}

void C7Zip::Compress(const QString arg1, const QString arg2)
{
    QProcess process;
    QStringList arguments;

    // 添加 7zip 解压命令参数
    arguments << "a" << arg1 << arg2;// << "-y";

    // 启动 7zip 程序
    process.start(m_str7zipExePath, arguments);

    // 等待进程完成
    if (!process.waitForFinished()) {
        qWarning() << "Failed to extract archive:" << process.errorString();
        return;
    }

    // 输出 7zip 的输出信息
    QByteArray output = process.readAllStandardOutput();
    qDebug() << output;
}

void C7Zip::ExtractFile(const QString src, const QString dst)
{
    QProcess process;
    QStringList arguments;

    // 添加 7zip 解压命令参数
    arguments << "x" << src << "-o" + dst;// << "-y";

    // 启动 7zip 程序
    process.start(m_str7zipExePath, arguments);

    // 等待进程完成
    if (!process.waitForFinished()) {
        qWarning() << "Failed to extract archive:" << process.errorString();
        return;
    }

    // 输出 7zip 的输出信息
    QByteArray output = process.readAllStandardOutput();
    qDebug() << output;
}
