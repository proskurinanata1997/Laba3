#include "pieBridge.h"

PieBridge::PieBridge(QObject *p): AbstractBridge(p) {
    view = new QtCharts::QChartView();
    model = new QtCharts::QChart();
    view->setRenderHint(QPainter::Antialiasing);
    view->setChart(this->model);
};

PieBridge::~PieBridge() {
    delete view;
}

QWidget* PieBridge::UpdateData(const QList<DataFile> &data) {
    model->removeAllSeries();
    QtCharts::QPieSeries *series = new QtCharts::QPieSeries(); // серия элементов диаграммы
    for (auto i = data.begin(); i != data.end(); i++) {
        series->append(new QtCharts::QPieSlice(i->name + " (" + QString::number(i->percentage, 'f', 2) + "%)", i->percentage));
    }
    model->addSeries(series); // занесение данных в диаграмму
    model->setAnimationOptions(QtCharts::QChart::SeriesAnimations);
    model->legend()->setVisible(true);
    model->legend()->setAlignment(Qt::AlignRight);
    return view;
}
