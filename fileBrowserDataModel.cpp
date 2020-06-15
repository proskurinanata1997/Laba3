#include "fileBrowserDataModel.h"

FileBrowserDataModel::FileBrowserDataModel(QObject *parent, const QList<DataFile> &dt) :
    QAbstractTableModel(parent),
    dataModel(dt){}

int FileBrowserDataModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent)
    return dataModel.count();
}

int FileBrowserDataModel::columnCount(const QModelIndex &parent) const {
    Q_UNUSED(parent)
    return 3;
}

QVariant FileBrowserDataModel::headerData(int section, Qt::Orientation orientation, int role) const { //возвращает заголовок элементов модели
    if (role != Qt::DisplayRole) { // проверка на отоброжаемость роли
        return QVariant();
    }
    if (orientation == Qt::Vertical) { // проверка на вертикальную ориентацию
        return section + 1;
    }
    switch (section) { // проверка секции
    case NAME:
        return "Название";
    case SIZE:
        return "Размер";
    case PERCENT:
        return "В процентах";
    }
    return QVariant();
}

void FileBrowserDataModel::setNewData(QList<DataFile> dataFile)
{
    dataModel = dataFile;
}

QVariant FileBrowserDataModel::data(const QModelIndex &index, int role) const { //возвращает элемент модели
    if (!index.isValid() || dataModel.count() <= index.row() || (role != Qt::DisplayRole && role != Qt::EditRole)) { // проверка на правильность индекса
        return QVariant();
    }
    if (index.column() == 0) { // первый столбец (имя)
        return dataModel[index.row()].name;
    } else if (index.column() == 1) { // второй столбец (размер)
        QString result;
        if (dataModel[index.row()].size / 1073741824) { // ГБ
            result = QString::number((double)dataModel[index.row()].size / 1073741824, 'f', 2) + " GB";
        } else if (dataModel[index.row()].size / 1048576) { // МБ
            result = QString::number((double)dataModel[index.row()].size / 1048576, 'f', 2) + " MB";
        } else if (dataModel[index.row()].size / 1024) { // КБ
            result = QString::number((double)dataModel[index.row()].size / 1024, 'f', 2) + " KB";
        } else {
            result = QString::number(dataModel[index.row()].size, 'f', 2) + " Bytes";
        }
        return result;
    } else if (index.column() == 2) { // третий столбец (проценты)
        QString result;
        if (dataModel[index.row()].percentage > 0 && dataModel[index.row()].percentage < 0.01) { // проверка на малось
            result = "< 0.01%";
        } else {
            result = QString::number(dataModel[index.row()].percentage, 'f', 2) + '%';
        }
        return result;
    }
    return QVariant();
}
