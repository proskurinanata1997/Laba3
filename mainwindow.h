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
#include "tableBridge.h"
#include "barBridge.h"
#include "pieBridge.h"
#include "observer.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

private slots:
    void on_selectionChangedSlot(const QItemSelection &selected, const QItemSelection &deselected); // слот, активирующийся при выборе директории
    void on_folder_triggered();
    void on_fileType_triggered();
    void on_table_triggered();
    void on_barChart_triggered();
    void on_pieChart_triggered();

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QFileSystemModel *dirModel; // модель файловой системы
    AbstractStrategy *groupingStrategy; // указатель на стратегию
    QList<DataFile> data;
    Observer observer;
    QString path; // путь к нужной папке
    void infoShow(bool, int);
    int indexModel;
    QWidget* pr;
};

#endif // MAINWINDOW_H
