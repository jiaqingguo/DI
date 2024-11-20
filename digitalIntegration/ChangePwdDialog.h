#ifndef CHANGEPWDDIALOG_H
#define CHANGEPWDDIALOG_H

#include <QDialog>

namespace Ui {
class ChangePwdDialog;
}

class ChangePwdDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChangePwdDialog(QWidget *parent = nullptr);
    ~ChangePwdDialog();

private slots:
    void  slot_btnModify();
private:
    Ui::ChangePwdDialog *ui;
};

#endif // CHANGEPWDDIALOG_H
