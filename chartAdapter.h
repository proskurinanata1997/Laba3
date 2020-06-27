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
class ChartAdapter : public Adapter
{
public:
    ChartAdapter(){
        view = new QtCharts::QChartView();
        model = new QtCharts::QChart();
        view->setRenderHint(QPainter::Antialiasing);
        view->setChart(model);
        showLegend();
    }
    QWidget* updateData(const QList<DataFile>& data){
        model->removeAllSeries();
        model->addSeries(putDataInSeries(data));
        model->setAnimationOptions(QtCharts::QChart::SeriesAnimations);
        return view;
    }
protected:
    virtual QtCharts::QAbstractSeries* putDataInSeries(const QList<DataFile> &data)=0;
    void showLegend(){
        model->legend()->setVisible(true);
        model->legend()->setAlignment(Qt::AlignRight);
    }
    QtCharts::QChart *model;
    QtCharts::QChartView *view;

};
#endif // ALGORITM_H
