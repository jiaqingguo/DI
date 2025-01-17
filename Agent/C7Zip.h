#ifndef C7ZIP_H
#define C7ZIP_H

#include <QObject>

class C7Zip : public QObject
{
    Q_OBJECT
public:
    explicit C7Zip(QObject *parent = nullptr);


    // arg1要压缩的zip路径，arg2 想要压缩的目录;
    void Compress(const QString arg1, const QString arg2);


    // src 要解压的路径，dst解压完的路径;
    int ExtractFile(const QString src, const QString dst);

signals:
private:
    QString m_str7zipExePath;
};

#endif // C7ZIP_H
