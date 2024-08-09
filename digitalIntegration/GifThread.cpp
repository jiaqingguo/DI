#include <QMovie>
#include <QLabel>
#include <QDialog>
#include <QVBoxLayout>

#include "GifThread.h"

GifThread::GifThread()
{

}

void GifThread::run()
{
    // �������ضԻ���
    QDialog loadingDialog;
    loadingDialog.setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowStaysOnTopHint);
    loadingDialog.setFixedSize(200, 200);

    QLabel label(&loadingDialog);
    QVBoxLayout layout(&loadingDialog);
    loadingDialog.setWindowTitle(QString::fromLocal8Bit("������...."));
    layout.addWidget(&label);
    loadingDialog.setLayout(&layout);

    // ����QMovie���󲢼���GIFͼ��
    QMovie* movie = new QMovie(":/image/loading.gif");
    movie->setScaledSize(QSize(label.width(), label.height())); // ����GIFͼ��Ĵ�С
    label.setMovie(movie);
    movie->start();
    label.show();

    // ��ʾ���ضԻ���
    loadingDialog.exec();

}
