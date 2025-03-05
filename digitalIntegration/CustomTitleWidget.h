#ifndef CUSTOMTITLEWIDGET_H
#define CUSTOMTITLEWIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include <QScreen>
#include <QApplication>

namespace Ui {
class CustomTitleWidget;
}

class CustomTitleWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CustomTitleWidget(QWidget *parent = nullptr);
    ~CustomTitleWidget();

    void SetUserName(const QString & str);
protected:
//    // ʵ�ִ����϶�
//    void mousePressEvent(QMouseEvent* event) override {
//        if (event->button() == Qt::LeftButton) {
//            m_dragging = true;
//#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
//            m_dragPosition = event->globalPosition().toPoint() - window()->geometry().topLeft();
//#else
//            m_dragPosition = event->globalPos() - window()->geometry().topLeft();
//#endif
//            event->accept();
//        }
//    }
        // ʵ�ִ����϶�
//    void mousePressEvent(QMouseEvent* event) override {
//        if (event->button() == Qt::LeftButton) {
//            m_dragging = true;
//
//            // ������������״̬���Ȼָ�Ϊ����״̬
//            if (window()->isMaximized()) {
//                window()->showNormal();
//                // ��������λ�ã�ʹ��������
//                QPoint localPos = event->pos();
//                QPoint globalPos = mapToGlobal(localPos);
//                QRect normalGeometry = window()->normalGeometry();
//                m_dragPosition = globalPos - normalGeometry.topLeft();
//        }
//            else {
//#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
//                m_dragPosition = event->globalPosition().toPoint() - window()->geometry().topLeft();
//#else
//                m_dragPosition = event->globalPos() - window()->geometry().topLeft();
//#endif
//            }
//            event->accept();
//    }
//}
//
//    void mouseMoveEvent(QMouseEvent* event) override {
//        if (m_dragging && (event->buttons() & Qt::LeftButton)) 
//        {
//            #if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
//              window()->move(event->globalPosition().toPoint() - m_dragPosition);
//            #else
//                 window()->move(event->globalPos() - m_dragPosition);
//            #endif
//                 event->accept();
//        }
//    }
//
//    void mouseReleaseEvent(QMouseEvent* event) override {
//        if (event->button() == Qt::LeftButton) {
//            m_dragging = false;
//            event->accept();
//        }
//    }
//
//    // ˫���������л����/����״̬
//    void mouseDoubleClickEvent(QMouseEvent* event) override {
//        if (event->button() == Qt::LeftButton) {
//            toggleMaximizeWindow();
//            event->accept();
//        }
//    }
    // ʵ�ִ����϶�
    void mousePressEvent(QMouseEvent* event) override {
        if (event->button() == Qt::LeftButton) {
            // ������������״̬����ֹ�϶�
            if (window()->isMaximized()) {
                return;
            }

            m_dragging = true;
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
            m_dragPosition = event->globalPosition().toPoint() - window()->geometry().topLeft();
#else
            m_dragPosition = event->globalPos() - window()->geometry().topLeft();
#endif
            event->accept();
        }
    }

    void mouseMoveEvent(QMouseEvent* event) override {
        if (m_dragging && (event->buttons() & Qt::LeftButton)) {
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
            window()->move(event->globalPosition().toPoint() - m_dragPosition);
#else
            window()->move(event->globalPos() - m_dragPosition);
#endif
            event->accept();
        }
    }

    void mouseReleaseEvent(QMouseEvent* event) override {
        if (event->button() == Qt::LeftButton) {
            m_dragging = false;
            event->accept();
        }
    }

    // ˫���������л����/����״̬
    void mouseDoubleClickEvent(QMouseEvent* event) override {
        if (event->button() == Qt::LeftButton) {
            toggleMaximizeWindow();
            event->accept();
        }
    }


signals:
    void signal_Maximized();
private slots:
    // ��С������
    void minimizeWindow() {
        window()->showMinimized();
    }

    // ���/��ԭ����
    void toggleMaximizeWindow()
    {
        emit signal_Maximized();
    }
    //    if (m_showMax) 
    //    {
    //        m_showMax = false;
    //        window()->showNormal();
    //    }
    //    else 
    //    {
    //        m_showMax = true;
    //        emit signal_Maximized();
    //       /* window()->showMaximized();*/
    //    }
    //}

    // �رմ���
    void closeWindow() {
        window()->close();
    }

private:
    bool m_showMax = true;
    bool m_dragging;
    QPoint m_dragPosition;
private:
    Ui::CustomTitleWidget *ui;


};

#endif // CUSTOMTITLEWIDGET_H
