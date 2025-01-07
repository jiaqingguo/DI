#ifndef C7ZIP_H
#define C7ZIP_H

#include <QObject>

class C7Zip : public QObject
{
    Q_OBJECT
public:
    explicit C7Zip(QObject *parent = nullptr);


    // arg1Ҫѹ����zip·����arg2 ��Ҫѹ����Ŀ¼;
    void Compress(const QString arg1, const QString arg2);


    // src Ҫ��ѹ��·����dst��ѹ���·��;
    void ExtractFile(const QString src, const QString dst);

signals:
private:
    QString m_str7zipExePath;
};

#endif // C7ZIP_H
