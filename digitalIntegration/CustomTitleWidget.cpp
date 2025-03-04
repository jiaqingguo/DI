#include "CustomTitleWidget.h"
#include "ui_CustomTitleWidget.h"

CustomTitleWidget::CustomTitleWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CustomTitleWidget)
{
    ui->setupUi(this);

    // 连接按钮信号
        connect(ui->btnMinimize, &QPushButton::clicked, this, &CustomTitleWidget::minimizeWindow);
        connect(ui->btnMaximize, &QPushButton::clicked, this, &CustomTitleWidget::toggleMaximizeWindow);
        connect(ui->btnClose, &QPushButton::clicked, this, &CustomTitleWidget::closeWindow);
}

CustomTitleWidget::~CustomTitleWidget()
{
    delete ui;
}

void CustomTitleWidget::SetUserName(const QString& str)
{
    ui->labelUserName->setText(str);
}
