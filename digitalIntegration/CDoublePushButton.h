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
     //重写鼠标双击事件处理函数
    void mouseDoubleClickEvent(QMouseEvent* event) override;
    // 重写鼠标按下事件处理函数
    void mousePressEvent(QMouseEvent* event) override;
signals:
    void signal_doubleClicked();
    void signal_rightClicked();  // 自定义右键点击信号
};

#endif // CDOUBLEPUSHBUTTON_H
