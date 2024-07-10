#ifndef CPAGEDTABLEMODEL_H
#define CPAGEDTABLEMODEL_H
#include <QStandardItemModel>
#include <vector>
#include <QString>

class CPagedTableModel : public QStandardItemModel {
    Q_OBJECT

public:
    CPagedTableModel(QObject *parent = nullptr) : QStandardItemModel(parent), currentPage(0), pageSize(10) {}

    void setData(const std::vector<std::vector<QString>> &data)
    {
        this->data1 = data;
        beginResetModel();
        endResetModel();
    }

    int rowCount(const QModelIndex &parent = QModelIndex()) const override {
        Q_UNUSED(parent);
        int totalRows = data1.size();
        int startRow = currentPage * pageSize;
        return std::min(pageSize, totalRows - startRow);
    }

    int columnCount(const QModelIndex &parent = QModelIndex()) const override {
        Q_UNUSED(parent);
        return data1.empty() ? 0 : data1[0].size();
    }

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override {
        if (!index.isValid() || role != Qt::DisplayRole) {
            return QVariant();
        }

        int startRow = currentPage * pageSize;
        return data1[startRow + index.row()][index.column()];
    }

    void setPage(int page) {
        if (page >= 0 && page <= (data1.size() - 1) / pageSize) {
            currentPage = page;
            beginResetModel();
            endResetModel();
        }
    }

    int pageCount() const {
        return (data1.size() + pageSize - 1) / pageSize;
    }

private:
    std::vector<std::vector<QString>> data1;
    int currentPage;
    int pageSize;
};

#endif // CPAGEDTABLEMODEL_H
