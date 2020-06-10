#include "table.h"

Table::Table(){
    QTableView *view_ptr = new QTableView(); // создание виджета
    view_ptr->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); // установление отображение на всю ширину и высоту виджета
    view = view_ptr; // сохранение виджета
};

Table::~Table() {
    delete view;
}

QWidget* Table::UpdateData(const QList<DataFile> &data) { //функция обработки данных
    model = new FileBrowserDataModel(parent, data);
    view->setModel(model); // занесение модели в виджет
    return view;
}
