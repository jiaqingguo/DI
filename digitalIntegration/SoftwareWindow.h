#ifndef SOFTWAREWINDOW_H
#define SOFTWAREWINDOW_H

#include <QWidget>

namespace Ui {
class SoftwareWindow;
}

class SoftwareWindow : public QWidget
{
    Q_OBJECT

public:
    explicit SoftwareWindow(QWidget *parent = nullptr);
    ~SoftwareWindow();

private:
    Ui::SoftwareWindow *ui;
};

#endif // SOFTWAREWINDOW_H
