#include < QIcon>
#include "GifDialog.h"
#include "ui_GifDialog.h"

GifDialog::GifDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GifDialog)
{
    ui->setupUi(this);
   setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowStaysOnTopHint);
    setWindowTitle(QString::fromLocal8Bit("��������"));
   // ui->toolButton->setFixedSize(55, 64);
    ui->toolButton->setIcon(QIcon(":/image/waiting.png"));
    //	ui->toolButton->setIconSize(QSize(50, 46));
    ui->toolButton->setText(QString::fromLocal8Bit("�ȴ���..."));
    ui->toolButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    ui->toolButton->setStyleSheet("background-color:rgba(0,0,0,0);font-size: 18px;");
    ui->toolButton->setFocusPolicy(Qt::NoFocus);
    // ���ð�ť�ı�
    ui->toolButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon); // ����ͼ�����ϣ���������
    ui->toolButton->setIconSize(QSize(138, 130)); // ����ͼ���СΪ138x138����
    
  //  ui->toolButton->show();
   // ui->toolButton->setFixedSize(55, 64);
}

GifDialog::~GifDialog()
{
    delete ui;
}