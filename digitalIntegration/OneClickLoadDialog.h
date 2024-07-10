#ifndef ONECLICKLOADDIALOG_H
#define ONECLICKLOADDIALOG_H

#include <QDialog>

namespace Ui {
class OneClickLoadDialog;
}

class OneClickLoadDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OneClickLoadDialog(QWidget *parent = nullptr);
    ~OneClickLoadDialog();

private:
    Ui::OneClickLoadDialog *ui;
};

#endif // ONECLICKLOADDIALOG_H
