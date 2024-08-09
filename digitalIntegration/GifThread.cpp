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
    // 创建加载对话框
    QDialog loadingDialog;
    loadingDialog.setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowStaysOnTopHint);
    loadingDialog.setFixedSize(200, 200);

    QLabel label(&loadingDialog);
    QVBoxLayout layout(&loadingDialog);
    loadingDialog.setWindowTitle(QString::fromLocal8Bit("下载中...."));
    layout.addWidget(&label);
    loadingDialog.setLayout(&layout);

    // 创建QMovie对象并加载GIF图像
    QMovie* movie = new QMovie(":/image/loading.gif");
    movie->setScaledSize(QSize(label.width(), label.height())); // 设置GIF图像的大小
    label.setMovie(movie);
    movie->start();
    label.show();

    // 显示加载对话框
    loadingDialog.exec();

}
