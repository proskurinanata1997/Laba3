#ifndef BARBRIDGE_H
#define BARBRIDGE_H
#include <QtCharts/QBarSeries>
#include <QtCharts/QChartView>
#include <QtCharts/QValueAxis>
#include <QtCharts/QBarSet>
#include <QtCharts/QChart>
#include "abstractBridge.h"

class BarBridge : public AbstractBridge
{
public:
    BarBridge(QObject *p = nullptr);
    QWidget* UpdateData(const QList<DataFile>&);
    ~BarBridge();
private:
    QtCharts::QChartView *view; // указатель на виджет, отображающий информацию в виде стоблчатой диаграммы
    QtCharts::QChart *model; // указатель на модель, из которой строится столбчатая диаграмма
    QtCharts::QValueAxis *axisY;
};
#endif // BARBRIDGE_H
