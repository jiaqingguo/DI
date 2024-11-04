#ifndef CAXWIDGET_H
#define CAXWIDGET_H

#include <QAxWidget>

class CAxWidget : public QAxWidget
{
public:
    CAxWidget();

protected:
    void changeEvent(QEvent* e) override;
};

#endif // CAXWIDGET_H
