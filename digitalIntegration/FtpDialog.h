#ifndef FTPDIALOG_H
#define FTPDIALOG_H

#include <QDialog>
#include <QMap>

class FtpClientClass;
class QFtp;

namespace Ui {
class FtpDialog;
}

class FtpDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FtpDialog(QWidget *parent = nullptr);
    ~FtpDialog();

    void initConnectFtp();

public slots:
    void slot_createUserDir(const QString strDirName);
private slots:
    void slot_comboBoxChanged(int index);
    void slot_ableUI(bool b);

    void slot_btnFlush();

private:
    Ui::FtpDialog *ui;
   
    QMap<QString, QFtp*> m_mapAdminFtp;
};

#endif // FTPDIALOG_H
