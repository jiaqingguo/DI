#ifndef GIFDIALOG_H
#define GIFDIALOG_H

#include <QDialog>

namespace Ui {
class GifDialog;
}

class GifDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GifDialog(QWidget *parent = nullptr);
    ~GifDialog();

private:
    Ui::GifDialog *ui;
};

#endif // GIFDIALOG_H
