#ifndef BYFILETYPESTRATEGY_H
#define BYFILETYPESTRATEGY_H
#include <QFileInfo>
#include <QString>
#include <abstractStrategy.h>

class ByFileTypeStrategy : public AbstractStrategy
{
public:
    ByFileTypeStrategy() {};
    QList<DataFile> explore (const QString &);

private:
    void folderSize(const QString &, QHash<QString, quint64> &); // функция вычисления размера вложенной папки
    // на вход подаётся QString - путь к папке, ссылка на QHash<QString, quint64> - объект, содержащий информацию о размере, занимаемом каждым типом в папке (QString - тип данных, quint64 - размер в байтах)
};
#endif // BYFILETYPESTRATEGY_H
