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
    virtual QList<DataFile> explore (const QString &) = 0; // абстрактная функция вычисления информации о размерах содержимого папки
    // на вход подаётся QString - путь к папке, на выходе QList<DatFile> - список данных о размере каждого элемента папки
};

#endif // ABSTRACTSTRATEGY_H
