#ifndef BYFOLDERSTRATEGY_H
#define BYFOLDERSTRATEGY_H
#include <QString>
#include<abstractStrategy.h>

class ByFolderStrategy : public AbstractStrategy
{
public:
    ByFolderStrategy() {};
    QList<DataFile> explore (const QString &);

private:
    quint64 folderSize(const QString &); // функция вычисления размера папки
    // на вход подаётся QString - путь к папке, на выходе quint64 - размер папки в байтах
};

#endif // BYFOLDERSTRATEGY_H
