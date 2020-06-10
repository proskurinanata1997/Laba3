#include "byFolderStrategy.h"
#include <QTextStream>
#include <QFileInfo>
#include <QString>
#include <QFile>
#include <QDir>

quint64 ByFolderStrategy::FolderSize(const QString &path) {
    QDir dir(path); // текущая директория
    quint64 size = QFileInfo(path + "/.").size();

    foreach (QFileInfo folder, dir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot | QDir::Hidden | QDir::System | QDir::NoSymLinks))
    {
        size += FolderSize(folder.path() + '/' + folder.fileName());
    }
    foreach (QFileInfo file, dir.entryInfoList(QDir::Files | QDir::NoDotAndDotDot | QDir::Hidden | QDir::System))
    {
        if (file.isSymLink()) {
            QFile fileOpen(file.absoluteFilePath());
            fileOpen.open(QIODevice::ReadOnly);
            size += fileOpen.size();
            fileOpen.close();
            continue;
        }
        size += file.size();
    }

    return size;
}

QList<DataFile> ByFolderStrategy::Explore(const QString &path) {
    QFileInfo pathInfo(path);
    QTextStream out(stdout);
    QList<DataFile> result; // список данных о размере каждого элемента папки

    if (pathInfo.exists() == false) { // проверка объекта на существование
        out << "Object does not exist.\n" << flush;
        return QList<DataFile>();
    }

    if (QFileInfo(path + '/').isDir()) { // проверка на неполноту пути
        pathInfo.setFile(path + '/');
    }

    if (pathInfo.isDir() && !pathInfo.isSymLink()) { // проверка на то, что на входе была подана папка
        if (pathInfo.dir().isEmpty()) {
            out << "Folder is empty.\n" << flush;
            return QList<DataFile>();
        }

        QDir dir(pathInfo.absoluteFilePath());
        quint64 totalSize = QFileInfo(pathInfo.absoluteFilePath() + '.').size(), tempSize;
        QList<quint64> sizes; // массив размеров объектов

        foreach (QFileInfo folder, dir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot | QDir::Hidden | QDir::System, QDir::Name))
        {
            if (folder.isSymLink()) { // проверка на ссылку
                if (folder.fileName().mid(folder.fileName().lastIndexOf('.') + 1) == "lnk") { // проверка на ярлык
                    continue; // пропускаем ярлыки
                }
            } else {
                tempSize = FolderSize(folder.path() + '/' + folder.fileName());
            }
            sizes.append(tempSize);
            totalSize += tempSize;
        }
        foreach (QFileInfo file, dir.entryInfoList(QDir::Files | QDir::NoDotAndDotDot | QDir::Hidden | QDir::System, QDir::Name))
        {
            if (file.isSymLink()) {
                QFile fileOpen(file.absoluteFilePath());
                fileOpen.open(QIODevice::ReadOnly);
                tempSize = fileOpen.size();
                fileOpen.close();
            } else {
                tempSize = file.size();
            }
            sizes.append(tempSize);
            totalSize += tempSize;
        }
        // если папка ничего не весит, то выходим из функции
        if (totalSize == 0) {
            out << "The folder has size 0.\n" << flush;
        }

        auto iterator = sizes.begin();
        foreach (QFileInfo folder, dir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot | QDir::Hidden | QDir::System, QDir::Name))
        {
            if (folder.isSymLink() && folder.fileName().mid(folder.fileName().lastIndexOf('.') + 1) == "lnk") { // проверка на ярлык
                continue;
            }
            result.append(DataFile(folder.fileName(), *iterator, ((double)*iterator / totalSize) * 100));
            iterator++;
        }
        foreach (QFileInfo file, dir.entryInfoList(QDir::Files | QDir::NoDotAndDotDot | QDir::Hidden | QDir::System, QDir::Name))
        {
            result.append(DataFile(file.fileName(), *iterator, ((double)*iterator / totalSize) * 100));
            iterator++;
        }
    } else { // обработка файла, не являющегося папкой
        quint64 fileSize = pathInfo.size();
        if (pathInfo.isSymLink()) {
            QFile fileOpen(pathInfo.absoluteFilePath());
            fileOpen.open(QIODevice::ReadOnly);
            fileSize = fileOpen.size();
            fileOpen.close();
        }
        result.append(DataFile(pathInfo.fileName(), fileSize, 100));
    }
    return result;
}

