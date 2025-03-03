#include "CustomTitleWidget.h"
#include "ui_CustomTitleWidget.h"

CustomTitleWidget::CustomTitleWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CustomTitleWidget)
{
    ui->setupUi(this);
}

CustomTitleWidget::~CustomTitleWidget()
{
    delete ui;
}
