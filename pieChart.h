#ifndef PIECHART_H
#define PIECHART_H
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts/QChart>
#include "chartAdapter.h"
class PieChart: public ChartAdapter
{
public:
    PieChart();
private:
    QtCharts::QAbstractSeries* putDataInSeries (const QList<DataFile>&);
};

#endif // PIECHART_H
