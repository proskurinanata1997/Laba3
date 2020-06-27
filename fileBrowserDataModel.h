#ifndef FILESIZEDATAMODEL_H
#define FILESIZEDATAMODEL_H
#include <QAbstractTableModel>
#include <QList>
#include <QString>
#include "data.h"

class FileBrowserDataModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    FileBrowserDataModel(QObject *parent = nullptr, const QList<DataFile> &dt = QList<DataFile>());
    int rowCount(const QModelIndex &parent) const override; //возвращает количество строчек
    int columnCount(const QModelIndex &parent) const override; //возвращает количество столбцов
    QVariant data(const QModelIndex &index, int role) const override; //возвращает элемент модели
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override; // возвращает заголовок элементов модели
    void setNewData(QList<DataFile> dataFile);
private:
    enum NameColumn { // индексация столбцов модели
        NAME,
        SIZE,
        PERCENT
    };
    QList<DataFile> dataModel; // данные модели
};

#endif
