#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QItemSelectionModel>
#include <QTableView>
#include <QTreeView>

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
    bridge = new TableBridge(this);
    ui->splitter->addWidget(bridge->UpdateData(data));
    // соединение сигнала выбора директории со слотом отображения информации
    connect(ui->folderTreeView->selectionModel(), SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)), this, SLOT(on_selectionChangedSlot(const QItemSelection &, const QItemSelection &)));
}

void MainWindow::infoShow(bool changeData, AbstractBridge *br = nullptr) {
    if (changeData) {
        data = groupingStrategy->Explore(path);
        bridge->UpdateData(data);
    } else {
        QList<int> width = ui->splitter->sizes();
        delete bridge;
        bridge = br;
        ui->splitter->addWidget(bridge->UpdateData(data));
        ui->splitter->setSizes(width);
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
    infoShow(true);
}

MainWindow::~MainWindow() {
    delete ui;
    delete dirModel;
    delete groupingStrategy;
    delete bridge;
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
    infoShow(false, new TableBridge(this));
}

void MainWindow::on_barChart_triggered() {
    infoShow(false, new BarBridge(this));
}

void MainWindow::on_pieChart_triggered() {
    infoShow(false, new PieBridge(this));
}
