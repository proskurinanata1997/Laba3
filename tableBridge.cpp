#include "tableBridge.h"

TableBridge::TableBridge(QObject *p): AbstractBridge(p) {
    QTableView *view_ptr = new QTableView();
    model = new FileBrowserDataModel();
    view_ptr->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    view = view_ptr;
    view->setModel(model);
};

TableBridge::~TableBridge() {
    delete view; // удаление виджета
    delete model; // удаление модели
}

QWidget* TableBridge::UpdateData(const QList<DataFile> &data) {
    model->setNewData(data);
    return view;
}
