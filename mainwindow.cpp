#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QItemSelectionModel>
#include <QTableView>
#include <QTreeView>
#include "byFileTypeStrategy.h"
#include "byFolderStrategy.h"
#include "fileBrowserDataModel.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->folderTreeView->header()->setSectionResizeMode(QHeaderView::ResizeToContents); // установка задания размера первого столбца в зависимости от длины отображающихся элементов
    groupingStrategy=new ByFolderStrategy();
    path = QDir::homePath();
    dirModel = new QFileSystemModel(this); // создание модели файловой системы и формирование отображения дерева папок
    dirModel->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs | QDir::Hidden | QDir::System);
    dirModel->setRootPath(path);
    ui->folderTreeView->setModel(dirModel);
    ui->folderTreeView->expandAll();
    QTableView* view = new QTableView;
    table = view;
    fileModel = new FileBrowserDataModel();
    view->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->setModel(fileModel);//Заносим модель в дерево
    ui->splitter->addWidget(table);
    // соединение сигнала выбора директории со слотом отображения информации
    connect(ui->folderTreeView->selectionModel(), SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)), this, SLOT(on_selectionChangedSlot(const QItemSelection &, const QItemSelection &)));
}

void MainWindow::infoShow(bool refreshData = true) {
    QList<DataFile> data;
    if (refreshData) {
        data = groupingStrategy->Explore(path);
        fileModel->setNewData(data);

    } else {
        fileModel->setNewData(data);
    }
}

void MainWindow::on_selectionChangedSlot(const QItemSelection &selected, const QItemSelection &deselected) {
    Q_UNUSED(deselected);
    QModelIndexList indexs = selected.indexes(); // получение индекса выбранной папки
    QString filePath = ""; // получение пути выбранной папки
    if (indexs.count() >= 1) {
        QModelIndex ix =  indexs.constFirst();
        filePath = dirModel->filePath(ix);
    }
    path = filePath; // сохранение пути
    infoShow();
}

MainWindow::~MainWindow() {
    delete ui;
    delete dirModel;
    delete groupingStrategy;
    delete table;
}

void MainWindow::on_folder_triggered() {
    delete groupingStrategy;
    groupingStrategy = new ByFolderStrategy();
    infoShow(true);
}

void MainWindow::on_fileType_triggered() {
    delete groupingStrategy;
    groupingStrategy = new ByFileTypeStrategy();
    infoShow(true);
}

void MainWindow::on_table_triggered() {
    infoShow(false);
}
