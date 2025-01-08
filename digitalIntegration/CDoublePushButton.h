#ifndef CDOUBLEPUSHBUTTON_H
#define CDOUBLEPUSHBUTTON_H
#include <QPushButton>

class CDoublePushButton : public QPushButton
{
    Q_OBJECT
public:
    CDoublePushButton();
protected:
    // 重写鼠标双击事件处理函数
    //void mouseDoubleClickEvent(QMouseEvent* event) override;
};

#endif // CDOUBLEPUSHBUTTON_H
