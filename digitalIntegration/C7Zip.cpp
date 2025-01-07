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

    // ��� 7zip ��ѹ�������
    arguments << "a" << arg1 << arg2;// << "-y";

    // ���� 7zip ����
    process.start(m_str7zipExePath, arguments);

    // �ȴ��������
    if (!process.waitForFinished()) {
        qWarning() << "Failed to extract archive:" << process.errorString();
        return;
    }

    // ��� 7zip �������Ϣ
    QByteArray output = process.readAllStandardOutput();
    qDebug() << output;
}

void C7Zip::ExtractFile(const QString src, const QString dst)
{
    QProcess process;
    QStringList arguments;

    // ��� 7zip ��ѹ�������
    arguments << "x" << src << "-o" + dst;// << "-y";

    // ���� 7zip ����
    process.start(m_str7zipExePath, arguments);

    // �ȴ��������
    if (!process.waitForFinished()) {
        qWarning() << "Failed to extract archive:" << process.errorString();
        return;
    }

    // ��� 7zip �������Ϣ
    QByteArray output = process.readAllStandardOutput();
    qDebug() << output;
}
