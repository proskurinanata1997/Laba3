#ifndef OBSERVER_H
#define OBSERVER_H
#include "adapter.h"
#include "data.h"
#include "table.h"
#include "barChart.h"
#include "pieChart.h"
#include <QVector>

class Observer
{
public:
    Observer();
    QWidget*  UpdateData(QList<DataFile>&, unsigned int);
    ~Observer();

private:
    QVector<Adapter*>  massivBridge;
};

#endif // OBSERVER_H
