#ifndef ABSTRACTBRIDGE_H
#define ABSTRACTBRIDGE_H
#include <QWidget>
#include <QList>
#include "data.h"

class Adapter
{
public:
    Adapter(QObject *p = nullptr): parent(p) {};
    virtual QWidget* updateData(const QList<DataFile>&) = 0;// абстрактная функция обработки данных, на вход принимает QList<DataFile> - данные о размерах элементов папки, на выходе QWidget* - указатель на виджет, отображающий информацию в нужном виде
    virtual ~Adapter() {};
protected:
    QObject *parent;
};
#endif // ABSTRACTBRIDGE_H
