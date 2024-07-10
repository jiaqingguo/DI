#ifndef ONECLICKSAVEDIALOG_H
#define ONECLICKSAVEDIALOG_H

#include <QDialog>

namespace Ui {
class OneClickSaveDialog;
}

class OneClickSaveDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OneClickSaveDialog(QWidget *parent = nullptr);
    ~OneClickSaveDialog();

private:
    Ui::OneClickSaveDialog *ui;
};

#endif // ONECLICKSAVEDIALOG_H
