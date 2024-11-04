
#include <QEvent>��
#include <QDebug>
#include "CAxWidget.h"

CAxWidget::CAxWidget()
{

}

void CAxWidget::changeEvent(QEvent* e)
{

    // ��ӡ�¼�����
    switch (e->type()) {
    case QEvent::None:
        qDebug() << "Event Type: QEvent::None";
        break;
    case QEvent::FocusIn:
        qDebug() << "Event Type: QEvent::FocusIn";
        break;
    case QEvent::FocusOut:
        qDebug() << "Event Type: QEvent::FocusOut";
        break;
    case QEvent::Show:
        qDebug() << "Event Type: QEvent::Show";
        break;
    case QEvent::Hide:
        qDebug() << "Event Type: QEvent::Hide";
        break;
    case QEvent::Resize:
        qDebug() << "Event Type: QEvent::Resize";
        break;
    case QEvent::Move:
        qDebug() << "Event Type: QEvent::Move";
        break;
        // �ڴ���Ӹ����¼�����
        // ...
    default:
        int type = e->type();
        qDebug() << "Event Type:" << e->type() << type;
        break;
    }
}
