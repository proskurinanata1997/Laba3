#ifndef TABLEBRIDGE_H
#define TABLEBRIDGE_H
#include <QAbstractItemModel>
#include <QHeaderView>
#include <QTableView>
#include "fileBrowserDataModel.h"
#include "adapter.h"

class TableAdapter : public Adapter
{
public:
    TableAdapter(QObject *p = nullptr);
    QWidget* updateData(const QList<DataFile>&);
    ~TableAdapter();
private:
    QAbstractItemView *view; // указатель на виджет, отображающий информацию в виде таблицы
    FileBrowserDataModel *model; // указатель на модель, из которой строится таблица
};

#endif // TABLEBRIDGE_H
