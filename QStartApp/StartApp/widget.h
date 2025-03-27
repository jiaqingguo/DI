#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTimer>
#include <QMenu>
#include <QContextMenuEvent>
#include "Listen.h"

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

    void StartProgram(const std::string& strPath,LoadingProgressCallBack callBack);

    void HwndListen();

    void InitResource(const std::string& str);

    void showGifDialog();

    void closeGifDialog();

    void setCloseCallBack(LoadingProgressCallBack callBack);

	void contextMenuEvent(QContextMenuEvent *event);

private slots:
    void slot_btnOpenExplorer();
    void slot_btnAppShow();
    

private:
    Ui::Widget *ui;

    QTimer* _t = nullptr;

    bool _gifShow = false;

    Listen* m_pListen = nullptr;// = new Listen;
    GifDialog* m_pGifDialog = nullptr;


	QMenu *m_Menu = nullptr;
};
#endif // WIDGET_H
