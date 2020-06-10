#ifndef TABLE_H
#define TABLE_H
#include <QAbstractTableModel>
#include <QHeaderView>
#include <QTableView>
#include "fileBrowserDataModel.h"

class Table
{
public:
    Table();
    QWidget* UpdateData(const QList<DataFile>&); // функция обработки данных
    ~Table();

private:
    QAbstractItemView *view; // указатель на виджет, отображающий информацию в виде таблицы
    QAbstractTableModel *model; // указатель на модель, из которой строится таблица
    QObject *parent;
};

#endif // TABLE_H
