#ifndef PIEBRIDGE_H
#define PIEBRIDGE_H
#include <QtCharts/QChartView>
#include <QtCharts/QValueAxis>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts/QChart>
#include "abstractBridge.h"

class PieBridge : public AbstractBridge
{
public:
    PieBridge(QObject *p = nullptr);
    QWidget* UpdateData(const QList<DataFile>&);
    ~PieBridge();
private:
    QtCharts::QChartView *view;  // указатель на виджет, отображающий информацию в виде круговой диаграммы
    QtCharts::QChart *model; // указатель на модель, из которой строится круговая диаграмма
};

#endif // PIEBRIDGE_H
