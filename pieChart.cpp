#include "pieChart.h"

PieChart::PieChart(){};

QtCharts::QAbstractSeries* PieChart::drowChart(const QList<DataFile>& data){
    QtCharts::QPieSeries *series = new QtCharts::QPieSeries(); // серия элементов диаграммы
    for (auto i = data.begin(); i != data.end(); i++) {
        series->append(new QtCharts::QPieSlice(i->name + " (" + QString::number(i->percentage, 'f', 2) + "%)", i->percentage));
    }
return series;
}
