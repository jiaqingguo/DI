#include <QKeyEvent>
#include "CLineEdit.h"

//CLineEdit::CLineEdit()
//{
//
//}

void CLineEdit::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
        // ����س����¼��������ı佹��
        event->accept();
        // �������������������߼�
    }
    else {
        QLineEdit::keyPressEvent(event);
    }

}
