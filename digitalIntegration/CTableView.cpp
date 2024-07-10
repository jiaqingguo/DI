#include "CTableView.h"

CTableView::CTableView(QWidget* parent) : QTableView(parent)
{

}

void CTableView::resizeEvent(QResizeEvent* event) 
{

  //  emit signal_resize();
    QTableView::resizeEvent(event);

}
