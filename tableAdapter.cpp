#include "tableAdapter.h"

TableAdapter::TableAdapter(QObject *p): Adapter(p) {
    QTableView *view_ptr = new QTableView();
    model = new FileBrowserDataModel();
    view_ptr->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    view = view_ptr;
    view->setModel(model);
};

TableAdapter::~TableAdapter() {
    delete view; // удаление виджета
    delete model; // удаление модели
}

QWidget* TableAdapter::updateData(const QList<DataFile> &data) {
    model->setNewData(data);
    return view;
}
