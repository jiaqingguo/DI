#include "progressDialog.h"
#include "ui_progressDialog.h"

progressDialog::progressDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::progressDialog)
{
    ui->setupUi(this);
}

progressDialog::~progressDialog()
{
    delete ui;
}
