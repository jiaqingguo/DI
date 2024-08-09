#ifndef GIFTHREAD_H
#define GIFTHREAD_H

#include <QThread>

class GifThread : public QThread
{
    Q_OBJECT
public:
    GifThread();
signals:
    void threadFinished(); // �����߳̽������ź�

protected:
    void run() override;
};

#endif // GIFTHREAD_H
