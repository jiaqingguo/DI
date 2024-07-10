#ifndef CTABLEVIEW_H
#define CTABLEVIEW_H

#include <QTableView>
#include <QStandardItemModel>

class CTableView : public QTableView {
    Q_OBJECT

public:
       CTableView(QWidget* parent = nullptr);
   
protected:
    void resizeEvent(QResizeEvent* event) override;
   
signals:
    void signal_resize();

  
};
#endif // CTABLEVIEW_H
