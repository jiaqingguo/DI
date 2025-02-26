#ifndef INFORMATIONCONFIHURATIONDIALOG_H
#define INFORMATIONCONFIHURATIONDIALOG_H

#include <QDialog>
#include <QStyledItemDelegate>
#include <QPainter>
class QStandardItemModel;
class AddToolInfoDialog;
class AddIpInfoDialog;
class QModelIndex;

namespace Ui {
class InformationConfihurationDialog;
}

class InformationConfihurationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit InformationConfihurationDialog(QWidget *parent = nullptr);
    ~InformationConfihurationDialog();

    void init();
    void initFaceData();

    void flushToolModelData(QStandardItemModel* model,const int &module);
    void flushIpModelData(QStandardItemModel* model);
    //void flushIpModelData(QStandardItemModel* model, const int& module);
    
    void clearModelData(QStandardItemModel* model);
    void delAllModelRow(QStandardItemModel* model);

	/*QPushButton *getbtnToolAdd1();
	QPushButton *getbtnToolAdd2();
	QPushButton *getbtnToolAdd3();
	QPushButton *getbtnToolAdd4();
	QPushButton *getbtnToolDel1();
	QPushButton *getbtnToolDel2();
	QPushButton *getbtnToolDel3();
	QPushButton *getbtnToolDel4();*/

private slots:
    void slot_btnToolAdd();

    void slot_btnIpAdd();


    void slot_btnToolDel();
    void slot_btnIpDel();

	void slot_btnShowModule1();
	void slot_btnShowModule2();
	void slot_btnShowModule3();
	void slot_btnShowModule4();

signals:
    void signal_updateToolIcon(int module);
    //void slot_tooltip(QModelIndex index);
private:
    Ui::InformationConfihurationDialog *ui;
    QStandardItemModel* m_modelTool1 = nullptr;
    QStandardItemModel* m_modelTool2 = nullptr;
    QStandardItemModel* m_modelTool3 = nullptr;
    QStandardItemModel* m_modelTool4 = nullptr;
    QStandardItemModel* m_modelIP1 = nullptr;
    //QStandardItemModel* m_modelIP2 = nullptr;
    //QStandardItemModel* m_modelIP3 = nullptr;
    //QStandardItemModel* m_modelIP4 = nullptr;

    AddToolInfoDialog* m_AddToolInfoDialog = nullptr;
    AddIpInfoDialog* m_AddIpInfoDialog = nullptr;

	int module = 1;

  
};
// 自定义委托
class BackgroundDelegate : public QStyledItemDelegate {
public:
	explicit BackgroundDelegate(QObject *parent = nullptr) : QStyledItemDelegate(parent) {}

	void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override {
		// 先调用基类的 paint 方法，绘制默认的单元格内容
		QStyledItemDelegate::paint(painter, option, index);
		// 如果是奇数行，绘制背景图片
		if (index.row() % 2 == 1)
		{
			QPixmap background(":/image/listBackground.png");  // 加载背景图片
			painter->drawPixmap(option.rect, background);  // 绘制背景图片
		}
		// 绘制单元格内容（文本或其他内容）
		QStyledItemDelegate::paint(painter, option, index);
	}
};

#endif // INFORMATIONCONFIHURATIONDIALOG_H
