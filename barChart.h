#ifndef BARCHART_H
#define BARCHART_H
#include <QtCharts/QChartView>
#include <QtCharts/QValueAxis>
#include <QtCharts/QChart>
#include "chartAdapter.h"
class BarChart : public ChartAdapter
{
public:
    BarChart();
private:
    QtCharts::QAbstractSeries* putDataInSeries (const QList<DataFile>&);
    QtCharts::QValueAxis *axisY;
};
#endif // BARCHART_H
