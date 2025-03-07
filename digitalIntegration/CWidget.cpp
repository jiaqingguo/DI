#include "CWidget.h"

CWidget::CWidget(QWidget *parent) : QWidget(parent)
{

}

CWidget::~CWidget()
{
    if (m_pAxWidget != nullptr)
    {
       m_pAxWidget->dynamicCall("Disconnect()");
       m_pAxWidget->dynamicCall("RequestClose()");//关闭插件
       delete m_pAxWidget;
       m_pAxWidget = nullptr;
    }
}

void CWidget::closeEvent(QCloseEvent* event)
{
    if (m_pAxWidget)
    {
        m_pAxWidget->dynamicCall("Disconnect()");
        m_pAxWidget->dynamicCall("RequestClose()");//关闭插件
        delete m_pAxWidget;
        m_pAxWidget = nullptr;
    }
	emit signal_softwareClose();
    
	QWidget::closeEvent(event);
}
