#ifndef CWIDGET_H
#define CWIDGET_H

#include <QWidget>
#include <qaxwidget.h>

class CWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CWidget(QWidget *parent = nullptr);

    QString m_ip="";
    QString m_softwareName = "";
    QString m_account = "";
    QAxWidget* m_pAxWidget = nullptr;
protected:
    void closeEvent(QCloseEvent* event) override;
signals:
    void signal_softwareClose();

};

#endif // CWIDGET_H
