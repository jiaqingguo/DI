#include "CDoublePushButton.h"



void CDoublePushButton::mouseDoubleClickEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        emit signal_doubleClicked();  // �����Զ����˫���ź�
    }
    // ���û���Ĵ�����ȷ��Ĭ����Ϊ������
    QPushButton::mouseDoubleClickEvent(event);
}

void CDoublePushButton::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::RightButton) {
        emit signal_rightClicked();  // �����Զ�����Ҽ�����ź�
    }
    // ���û���Ĵ�����ȷ��Ĭ����Ϊ������
    QPushButton::mousePressEvent(event);
}
