#ifndef ALGORITM_H
#define ALGORITM_H
#include <QtCharts/QChart>
#include <QtCharts/QBarSeries>
#include <QtCharts/QChartView>
#include <QtCharts/QValueAxis>
#include <QtCharts/QBarSet>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include "adapter.h"
class AlgorytmChart : public Adapter
{
public:
    AlgorytmChart(){
        view = new QtCharts::QChartView();
        model = new QtCharts::QChart();
        view->setRenderHint(QPainter::Antialiasing);
        view->setChart(model);
        drowLegend();
    }
    QWidget* UpdateData(const QList<DataFile>& data){
        model->removeAllSeries();
        model->addSeries(drowChart(data));
        model->setAnimationOptions(QtCharts::QChart::SeriesAnimations);
        return view;
    }
protected:
    virtual QtCharts::QAbstractSeries* drowChart(const QList<DataFile> &data)=0;
    void drowLegend(){
        model->legend()->setVisible(true);
        model->legend()->setAlignment(Qt::AlignRight);
    }
    QtCharts::QChart *model;
    QtCharts::QChartView *view;

};
#endif // ALGORITM_H
