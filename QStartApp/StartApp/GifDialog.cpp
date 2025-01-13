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
   setWindowTitle(QString::fromLocal8Bit("��������"));
   
    //ui->toolButton->setIcon(QIcon(":/image/waiting.png"));
    //ui->toolButton->setText(QString::fromLocal8Bit("�ȴ���..."));
    //ui->toolButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    //ui->toolButton->setStyleSheet("background-color:rgba(0,0,0,0);font-size: 18px;");
    //ui->toolButton->setFocusPolicy(Qt::NoFocus);
    //// ���ð�ť�ı�
    //ui->toolButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon); // ����ͼ�����ϣ���������
    //ui->toolButton->setIconSize(QSize(138, 130)); // ����ͼ���СΪ138x138����
 


  // ui->toolButton->setVisible(false);
   // ���� QLabel��������ʾ GIF
  
   ui->label->setWindowTitle("GIF ��ʾ");
    ui->label->setAlignment(Qt::AlignCenter); // ������ʾ
    ui->label->setScaledContents(true);      // �����������ţ������Զ��Ŵ�/��С
   // ���� QMovie�����ڼ��� GIF �ļ�
   QMovie* movie = new QMovie(":/image/loading2.gif"); // �滻Ϊ��� GIF ·��

   // ��� GIF �Ƿ���سɹ�
   if (!movie->isValid()) {
       ui->label->setText("�޷����� GIF �ļ�");
   }
   else {
       // �� QMovie ����Ϊ QLabel ������
       ui->label->setMovie(movie);

       // ��ʼ���� GIF
       movie->start();
   }

   // ��ʾ QLabel
   ui->label->resize(400, 300);  // �ɸ�����Ҫ�������ڴ�С

}

GifDialog::~GifDialog()
{
    delete ui;
}

void GifDialog::setTitleText(QString text)
{
    setWindowTitle(text);
}
