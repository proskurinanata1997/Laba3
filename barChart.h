#ifndef BARCHART_H
#define BARCHART_H
#include <QtCharts/QChartView>
#include <QtCharts/QValueAxis>
#include <QtCharts/QChart>
#include "algorytmChart.h"
class BarChart : public AlgorytmChart
{
public:
    BarChart();
private:
    QtCharts::QAbstractSeries* drowChart (const QList<DataFile>&);
    QtCharts::QValueAxis *axisY;
};
#endif // BARCHART_H
