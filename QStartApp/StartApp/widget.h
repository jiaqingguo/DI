#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
class Listen;

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    void StartProgram(const std::string& strPath);

    void HwndListen();

    void InitResource(const std::string& str);
private slots:
    void slot_btnOpenExplorer();
private:
    Ui::Widget *ui;

    Listen* m_pListen = nullptr;// = new Listen;
};
#endif // WIDGET_H
