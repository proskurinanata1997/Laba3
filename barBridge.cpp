#include "barBridge.h"

BarBridge::BarBridge(QObject *p): AbstractBridge(p) {
    view = new QtCharts::QChartView(); // создание виджета
    model = new QtCharts::QChart();
    axisY = new QtCharts::QValueAxis();
    axisY->setRange(0,100);
    model->addAxis(axisY, Qt::AlignLeft);
    view->setRenderHint(QPainter::Antialiasing);
    view->setChart(this->model);
};

BarBridge::~BarBridge() {
    delete view;
}

QWidget* BarBridge::UpdateData(const QList<DataFile> &data) {
    model->removeAllSeries();
    //DataFile others(0, 0, 0.0);
    QtCharts::QBarSeries *series = new QtCharts::QBarSeries(); // серия элементов диаграммы
    for (auto i = data.begin(); i != data.end(); i++) {
        QtCharts::QBarSet *set = new QtCharts::QBarSet(i->name + " (" + QString::number(i->percentage, 'f', 2) + "%)");
        set->operator<<(i->percentage);
        series->append(set); // занесение элемента диаграммы в серию
    }
    model->addSeries(series);
    model->setAnimationOptions(QtCharts::QChart::SeriesAnimations);
    series->attachAxis(axisY);
    model->legend()->setVisible(true);
    model->legend()->setAlignment(Qt::AlignRight);
    return view;
}
