#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QAbstractItemView>
#include <QAbstractItemModel>
#include <QFileSystemModel>
#include <QItemSelection>
#include <QMainWindow>
#include "fileBrowserDataModel.h"
#include "byFileTypeStrategy.h"
#include "byFolderStrategy.h"
#include "data.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

private slots:
    void on_selectionChangedSlot(const QItemSelection &selected, const QItemSelection &deselected);
    void on_folder_triggered();
    void on_fileType_triggered();
    void on_table_triggered();

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QFileSystemModel *dirModel; // модель файловой системы
    AbstractStrategy *groupingStrategy; // указатель на стратегию
    FileBrowserDataModel *fileModel;
    QAbstractItemView *table; // указатель на способ отображения
    QString path; // путь к нужной папке
    void infoShow(bool); // функция, организующая отображение данных в окне
};

#endif // MAINWINDOW_H
