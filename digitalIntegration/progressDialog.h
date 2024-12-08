#ifndef PROGRESSDIALOG_H
#define PROGRESSDIALOG_H

#include <QDialog>

namespace Ui {
class progressDialog;
}

class progressDialog : public QDialog
{
    Q_OBJECT

public:
    explicit progressDialog(QWidget *parent = nullptr);
    ~progressDialog();

    //void setMessage()
private:
    Ui::progressDialog *ui;
};

#endif // PROGRESSDIALOG_H
