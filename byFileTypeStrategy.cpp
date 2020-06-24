#include "byFileTypeStrategy.h"
#include <QTextStream>
#include <QFileInfo>
#include <QString>
#include <QFile>
#include <QDir>
// функция вычисления размера вложенной папки
// на вход подаётся QString - путь к папке, ссылка на QHash<QString, quint64> - объект, содержащий информацию о размере, занимаемом каждым типом в папке (QString - тип данных, quint64 - размер в байтах)
void ByFileTypeStrategy::folderSize(const QString &path, QHash<QString, quint64> &hash) {
    QDir dir(path);

    foreach (QFileInfo folder, dir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot | QDir::Hidden | QDir::System | QDir::NoSymLinks))
    {
        folderSize(folder.path() + '/' + folder.fileName(), hash);
    }

    foreach (QFileInfo file, dir.entryInfoList(QDir::Files | QDir::NoDotAndDotDot | QDir::Hidden | QDir::System))
    {
        if (file.isSymLink()) {
            QFile fileOpen(file.absoluteFilePath());
            fileOpen.open(QIODevice::ReadOnly);
            hash[file.suffix()] += fileOpen.size();
            fileOpen.close();
            continue;
        }
        hash[file.suffix()] += file.size();
    }
}

QList<DataFile> ByFileTypeStrategy::explore(const QString &path) {
    QFileInfo pathInfo(path);
    QTextStream out(stdout);
    QList<DataFile> result;
    if (pathInfo.exists() == false) {// проверка объекта на существование
        out << "Object does not exist.\n" << flush;
    }

    if (QFileInfo(path + '/').isDir()) {// проверка на неполноту пути
        pathInfo.setFile(path + '/');
    }

    if (pathInfo.isDir() && !pathInfo.isSymLink()) {// проверка на то, что на входе была подана папка
        if (pathInfo.dir().isEmpty()) {
            out << "Folder is empty.\n" << flush;
        }

        QDir dir(pathInfo.absoluteFilePath());
        QHash<QString, quint64> hash;

        foreach (QFileInfo folder, dir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot | QDir::Hidden | QDir::System | QDir::NoSymLinks))
        {
            folderSize(folder.path() + '/' + folder.fileName(), hash); // проводятся вычисления с папкой
        }
        foreach (QFileInfo file, dir.entryInfoList(QDir::Files | QDir::NoDotAndDotDot | QDir::Hidden | QDir::System))
        {
            if (file.isSymLink()) { // проверка на ярлык
                QFile fileOpen(file.absoluteFilePath());
                fileOpen.open(QIODevice::ReadOnly);
                hash[file.suffix()] += fileOpen.size();
                fileOpen.close();
                continue;
            }
            hash[file.suffix()] += file.size();
        }

        QStringList types; // массив типов
        quint64 totalSize = 0; // итоговый размер папки

        for (auto iterator = hash.begin(); iterator != hash.end(); iterator++) { // вычисление итогового размера папки и заполнение массива типов
            totalSize += *iterator;
            types.append(iterator.key());
        }


        types.sort(); // сортировка типов по их названиям

        for (int i = 0; i < types.size(); i++) {
            if (totalSize!= 0) {
                if (!types[i].isEmpty()){
                    result.append(DataFile(types[i], hash[types[i]], ((double)hash[types[i]] / totalSize) * 100));
                }
                else{
                    result.append(DataFile("Without extension", hash[types[i]], ((double)hash[types[i]] / totalSize) * 100));
                }
            }
            else {
                  result.append(DataFile("Folder has size 0", hash[types[i]], ((double)hash[types[i]] / totalSize) * 100));

            }
        }
    } else { // обработка файла, не являющегося папокй
        quint64 fileSize = pathInfo.size();
        if (pathInfo.isSymLink()) {
            QFile fileOpen(pathInfo.absoluteFilePath());
            fileOpen.open(QIODevice::ReadOnly);
            fileSize = fileOpen.size();
            fileOpen.close();
        }
         result.append(DataFile(pathInfo.suffix(), fileSize, 100));
    }
    return result;
}
