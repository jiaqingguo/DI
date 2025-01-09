#include "CDoublePushButton.h"



void CDoublePushButton::mouseDoubleClickEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        emit signal_doubleClicked();  // 发射自定义的双击信号
    }
    // 调用基类的处理，以确保默认行为被保留
    QPushButton::mouseDoubleClickEvent(event);
}

void CDoublePushButton::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::RightButton) {
        emit signal_rightClicked();  // 发射自定义的右键点击信号
    }
    // 调用基类的处理，以确保默认行为被保留
    QPushButton::mousePressEvent(event);
}
