#include < QIcon>
#include "GifDialog.h"
#include "ui_GifDialog.h"

GifDialog::GifDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GifDialog)
{
    ui->setupUi(this);
   setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowStaysOnTopHint);
   setWindowTitle(QString::fromLocal8Bit("正在下载"));
   // setWindowTitle(strTille);
   // ui->toolButton->setFixedSize(55, 64);
    ui->toolButton->setIcon(QIcon(":/image/waiting.png"));
    //	ui->toolButton->setIconSize(QSize(50, 46));
    ui->toolButton->setText(QString::fromLocal8Bit("等待中..."));
    ui->toolButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    ui->toolButton->setStyleSheet("background-color:rgba(0,0,0,0);font-size: 18px;");
    ui->toolButton->setFocusPolicy(Qt::NoFocus);
    // 设置按钮文本
    ui->toolButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon); // 设置图标在上，文字在下
    ui->toolButton->setIconSize(QSize(138, 130)); // 设置图标大小为138x138像素
    
  //  ui->toolButton->show();
   // ui->toolButton->setFixedSize(55, 64);
}

GifDialog::~GifDialog()
{
    delete ui;
}

void GifDialog::setTitleText(QString text)
{
    setWindowTitle(text);
}
