#ifndef BYFILETYPESTRATEGY_H
#define BYFILETYPESTRATEGY_H
#include <QFileInfo>
#include <QString>
#include <abstractStrategy.h>

class ByFileTypeStrategy : public AbstractStrategy
{
public:
    ByFileTypeStrategy() {};
    QList<DataFile> Explore (const QString &);

private:
    void FolderSize(const QString &, QHash<QString, quint64> &);
    QString FileType(const QFileInfo &);
};
#endif // BYFILETYPESTRATEGY_H
