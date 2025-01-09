#ifndef CDOUBLEPUSHBUTTON_H
#define CDOUBLEPUSHBUTTON_H
#include <QPushButton>
#include <QMouseEvent>

class CDoublePushButton : public QPushButton
{
    Q_OBJECT
public:
    CDoublePushButton( QWidget* parent = nullptr)  {};
protected:
     //��д���˫���¼�������
    void mouseDoubleClickEvent(QMouseEvent* event) override;
    // ��д��갴���¼�������
    void mousePressEvent(QMouseEvent* event) override;
signals:
    void signal_doubleClicked();
    void signal_rightClicked();  // �Զ����Ҽ�����ź�
};

#endif // CDOUBLEPUSHBUTTON_H
