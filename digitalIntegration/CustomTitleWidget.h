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
//    // 实现窗口拖动
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
        // 实现窗口拖动
//    void mousePressEvent(QMouseEvent* event) override {
//        if (event->button() == Qt::LeftButton) {
//            m_dragging = true;
//
//            // 如果窗口是最大化状态，先恢复为正常状态
//            if (window()->isMaximized()) {
//                window()->showNormal();
//                // 调整窗口位置，使其跟随鼠标
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
//    // 双击标题栏切换最大化/正常状态
//    void mouseDoubleClickEvent(QMouseEvent* event) override {
//        if (event->button() == Qt::LeftButton) {
//            toggleMaximizeWindow();
//            event->accept();
//        }
//    }



    // 实现窗口拖动
    void mousePressEvent(QMouseEvent* event) override 
	{
        if (event->button() == Qt::LeftButton) 
		{
            // 如果窗口是最大化状态，禁止拖动
            if (window()->isMaximized()) 
			{
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

    void mouseMoveEvent(QMouseEvent* event) override 
	{
        if (m_dragging && (event->buttons() & Qt::LeftButton)) 
		{
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
            window()->move(event->globalPosition().toPoint() - m_dragPosition);
#else
            window()->move(event->globalPos() - m_dragPosition);
#endif
            event->accept();
        }
    }

    void mouseReleaseEvent(QMouseEvent* event) override 
	{
        if (event->button() == Qt::LeftButton) 
		{
            m_dragging = false;
            event->accept();
        }
    }

    // 双击标题栏切换最大化/正常状态
    void mouseDoubleClickEvent(QMouseEvent* event) override 
	{
        if (event->button() == Qt::LeftButton) 
		{
            toggleMaximizeWindow();
            event->accept();
        }
    }

signals:
    void signal_Maximized();
	void signal_Minimized();
private slots:
    // 最小化窗口
    void minimizeWindow() 
	{
        //window()->showMinimized();
		emit signal_Minimized();
    }

    // 最大化/还原窗口
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

    // 关闭窗口
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
