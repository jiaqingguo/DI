#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
class Listen;
class GifDialog;

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

    void showGifDialog();

    void closeGifDialog();

private slots:
    void slot_btnOpenExplorer();
    void slot_btnAppShow();
    

private:
    Ui::Widget *ui;

    Listen* m_pListen = nullptr;// = new Listen;
    GifDialog* m_pGifDialog = nullptr;
};
#endif // WIDGET_H
