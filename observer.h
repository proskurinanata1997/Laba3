#ifndef OBSERVER_H
#define OBSERVER_H
#include "abstractBridge.h"
#include "data.h"
#include "tableBridge.h"
#include "barBridge.h"
#include "pieBridge.h"
#include <QVector>

class Observer
{
public:
    Observer();
    QWidget*  UpdateData(QList<DataFile>&, int);
    ~Observer();

private:
    QVector<AbstractBridge*>  massivBridge;
};

#endif // OBSERVER_H
