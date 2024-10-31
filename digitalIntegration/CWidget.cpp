#include "CWidget.h"

CWidget::CWidget(QWidget *parent) : QWidget(parent)
{

}

void CWidget::closeEvent(QCloseEvent* event)
{
	emit signal_softwareClose();
	QWidget::closeEvent(event);
}
