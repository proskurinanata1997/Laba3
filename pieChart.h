#ifndef PIECHART_H
#define PIECHART_H
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts/QChart>
#include "algorytmChart.h"
class PieChart: public AlgorytmChart
{
public:
    PieChart();
private:
    QtCharts::QAbstractSeries* drowChart (const QList<DataFile>&);
};

#endif // PIECHART_H
