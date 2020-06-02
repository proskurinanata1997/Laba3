#ifndef DATA_H
#define DATA_H
#include <QString>

struct DataFile {
    QString name; // Название файла
    quint64 size; // Размер файла в байтах
    double percentage; // Процентное соотношение к общему размеру папки

    DataFile(QString _name, quint64 _size, double _percentage): name(_name), size(_size), percentage(_percentage) {};
};

#endif // DATA_H
