#ifndef TABLEBRIDGE_H
#define TABLEBRIDGE_H
#include <QAbstractItemModel>
#include <QHeaderView>
#include <QTableView>
#include "fileBrowserDataModel.h"
#include "adapter.h"

class TableBridge : public Adapter
{
public:
    TableBridge(QObject *p = nullptr);
    QWidget* UpdateData(const QList<DataFile>&);
    ~TableBridge();
private:
    QAbstractItemView *view; // указатель на виджет, отображающий информацию в виде таблицы
    FileBrowserDataModel *model; // указатель на модель, из которой строится таблица
};

#endif // TABLEBRIDGE_H
