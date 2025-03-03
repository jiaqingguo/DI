#ifndef CUSTOMTITLEWIDGET_H
#define CUSTOMTITLEWIDGET_H

#include <QWidget>

namespace Ui {
class CustomTitleWidget;
}

class CustomTitleWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CustomTitleWidget(QWidget *parent = nullptr);
    ~CustomTitleWidget();

private:
    Ui::CustomTitleWidget *ui;
};

#endif // CUSTOMTITLEWIDGET_H
