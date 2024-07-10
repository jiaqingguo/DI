#include <QKeyEvent>
#include "CLineEdit.h"

//CLineEdit::CLineEdit()
//{
//
//}

void CLineEdit::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
        // 处理回车键事件，但不改变焦点
        event->accept();
        // 你可以在这里添加其他逻辑
    }
    else {
        QLineEdit::keyPressEvent(event);
    }

}
