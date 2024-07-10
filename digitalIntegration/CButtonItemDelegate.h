#ifndef CBUTTONITEMDELEGATE_H
#define CBUTTONITEMDELEGATE_H
#include <QItemDelegate>
#include <QPushButton>

class ButtonDelegate : public QItemDelegate {
    Q_OBJECT

public:
    explicit ButtonDelegate(QObject* parent = nullptr) : QItemDelegate(parent) {}

    QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const override {
        if (index.column() >= index.model()->columnCount() - 3) {
            QPushButton* button = new QPushButton(parent);
            button->setText(index.column() == index.model()->columnCount() - 3 ? "增加" : index.column() == index.model()->columnCount() - 2 ? "修改" : "删除");
            connect(button, &QPushButton::clicked, [this, button, index]() { // 显式捕获 this
               // emit commitData(button, index);
                });
            return button;
        }
        return QItemDelegate::createEditor(parent, option, index);
    }

    void setEditorData(QWidget* editor, const QModelIndex& index) const override {
        // 不需要设置数据，因为按钮不需要数据
    }

    void setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const override {
        // 不需要设置模型数据，因为按钮不修改模型数据
    }

signals:
    void commitData(QWidget* editor, const QModelIndex& index);
};




#endif // CBUTTONITEMDELEGATE_H
