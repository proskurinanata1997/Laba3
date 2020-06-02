#ifndef BYFOLDERSTRATEGY_H
#define BYFOLDERSTRATEGY_H
#include <QString>
#include<abstractStrategy.h>

class ByFolderStrategy : public AbstractStrategy
{
public:
    ByFolderStrategy() {};
    QList<DataFile> Explore (const QString &);

private:
    quint64 FolderSize(const QString &);
};

#endif // BYFOLDERSTRATEGY_H
