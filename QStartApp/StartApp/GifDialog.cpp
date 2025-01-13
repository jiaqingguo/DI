#include < QIcon>
#include "GifDialog.h"
#include "ui_GifDialog.h"

#include <QMovie>

GifDialog::GifDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GifDialog)
{
    ui->setupUi(this);
   setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowStaysOnTopHint);
   setWindowTitle(QString::fromLocal8Bit("正在下载"));
   
    //ui->toolButton->setIcon(QIcon(":/image/waiting.png"));
    //ui->toolButton->setText(QString::fromLocal8Bit("等待中..."));
    //ui->toolButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    //ui->toolButton->setStyleSheet("background-color:rgba(0,0,0,0);font-size: 18px;");
    //ui->toolButton->setFocusPolicy(Qt::NoFocus);
    //// 设置按钮文本
    //ui->toolButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon); // 设置图标在上，文字在下
    //ui->toolButton->setIconSize(QSize(138, 130)); // 设置图标大小为138x138像素
 


  // ui->toolButton->setVisible(false);
   // 创建 QLabel，用于显示 GIF
  
   ui->label->setWindowTitle("GIF 演示");
    ui->label->setAlignment(Qt::AlignCenter); // 居中显示
    ui->label->setScaledContents(true);      // 启用内容缩放，允许自动放大/缩小
   // 创建 QMovie，用于加载 GIF 文件
   QMovie* movie = new QMovie(":/image/loading2.gif"); // 替换为你的 GIF 路径

   // 检查 GIF 是否加载成功
   if (!movie->isValid()) {
       ui->label->setText("无法加载 GIF 文件");
   }
   else {
       // 将 QMovie 设置为 QLabel 的内容
       ui->label->setMovie(movie);

       // 开始播放 GIF
       movie->start();
   }

   // 显示 QLabel
   ui->label->resize(400, 300);  // 可根据需要调整窗口大小

}

GifDialog::~GifDialog()
{
    delete ui;
}

void GifDialog::setTitleText(QString text)
{
    setWindowTitle(text);
}
