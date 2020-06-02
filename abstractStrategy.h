#ifndef ABSTRACTSTRATEGY_H
#define ABSTRACTSTRATEGY_H
#include <QString>
#include <QList>
#include<data.h>
class AbstractStrategy
{
public:
    explicit AbstractStrategy() {};
    virtual ~AbstractStrategy() {};
    virtual QList<DataFile> Explore (const QString &) = 0;
};

#endif // ABSTRACTSTRATEGY_H
