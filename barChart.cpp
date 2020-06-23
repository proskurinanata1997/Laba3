#include "barChart.h"

BarChart::BarChart(){
    axisY = new QtCharts::QValueAxis();
    axisY->setRange(0,100);
    model->addAxis(axisY, Qt::AlignLeft);
}
QtCharts::QAbstractSeries* BarChart::drowChart(const QList<DataFile> &data){


    QtCharts::QBarSeries *series = new QtCharts::QBarSeries(); // серия элементов диаграммы
    for (auto i = data.begin(); i != data.end(); i++) {
        QtCharts::QBarSet *set = new QtCharts::QBarSet(i->name + " (" + QString::number(i->percentage, 'f', 2) + "%)");
        set->operator<<(i->percentage);
        series->append(set); // занесение элемента диаграммы в серию
    }
    return series;
}
