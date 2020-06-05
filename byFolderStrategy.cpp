#include <byFolderStrategy.h>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QString>
#include <QTextStream>

quint64 ByFolderStrategy::FolderSize(const QString &path) {
    QDir directory(path); // текущая директория
    quint64 size = QFileInfo(path + "/.").size();
    foreach (QFileInfo folder, directory.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot | QDir::Hidden | QDir::System | QDir::NoSymLinks))
    {
        size += FolderSize(folder.path() + '/' + folder.fileName()); // вычисляется размер папки
    }

    foreach (QFileInfo file, directory.entryInfoList(QDir::Files | QDir::NoDotAndDotDot | QDir::Hidden | QDir::System))
    {
        if (file.isSymLink()) { // проверка на ярлык
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

QList<DataFile> ByFolderStrategy::Explore (const QString &path)
{
    QFileInfo pathInfo(path);
    QTextStream out(stdout);
    QList<DataFile> result; // список данных о размере каждого элемента папки

    if (pathInfo.exists() == false) {
        out << "Object does not exist\n" << flush;
        return QList<DataFile>();
    }

    if (QFileInfo(path + '/').isDir()) {// проверка на неполноту пути
        pathInfo.setFile(path + '/');
    }

    if (pathInfo.isDir() && !pathInfo.isSymLink()) {// проверка на то, что на входе была подана папка
        if (pathInfo.dir().isEmpty()) {// проверка папки на пустоту
            out << "Folder is empty\n" << flush;
            return QList<DataFile>();
        }

        QDir dir(pathInfo.absoluteFilePath());
        quint64 totalSize = QFileInfo(pathInfo.absoluteFilePath() + '.').size(), tempSize; // 1 - итоговый размер папки (начальное значение задаётся такое, чтобы вычислить реальный размер папки), 2 - временная переменная
        QList<quint64> sizes; // массив размера объектов

        //вычисление размеров объектов, цикл по всем папкам в текущей папке
        foreach (QFileInfo folder, dir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot | QDir::Hidden | QDir::System, QDir::Name))
        {
            if (folder.isSymLink()) { // проверка на ссылку
                if (folder.fileName().mid(folder.fileName().lastIndexOf('.') + 1) == "lnk") { // проверка на ярлык
                    continue; // пропускаем ярлыки
                } else {
                    tempSize = 0; // символические ссылки ничего не весят
                }
            } else {
                tempSize = FolderSize(folder.path() + '/' + folder.fileName()); // вычисляется размер папки
            }
            sizes.append(tempSize);
            totalSize += tempSize;
        }
        //цикл по всем файлам в папке
        foreach (QFileInfo file, dir.entryInfoList(QDir::Files | QDir::NoDotAndDotDot | QDir::Hidden | QDir::System, QDir::Name))
        {
            if (file.isSymLink()) { // проверка на ярлык
                QFile fileOpen(file.absoluteFilePath());
                fileOpen.open(QIODevice::ReadOnly);
                fileOpen.close();
            } else {
                tempSize = file.size();
            }
            sizes.append(tempSize);
            totalSize += tempSize;
        }

        if (totalSize == 0) {// если папка ничего не весит, то выходим из функции
            out << "Folder has size 0\n" << flush;
            return QList<DataFile>();
        }

        auto i = sizes.begin();//вывод результатов
        foreach (QFileInfo folder, dir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot | QDir::Hidden | QDir::System, QDir::Name))
        {
            if (folder.isSymLink() && folder.fileName().mid(folder.fileName().lastIndexOf('.') + 1) == "lnk") { // проверка на ярлык
                continue;
            }
            result.append(DataFile(folder.fileName(), *i, ((double)*i / totalSize) * 100));
            i++;
        }
        foreach (QFileInfo file, dir.entryInfoList(QDir::Files | QDir::NoDotAndDotDot | QDir::Hidden | QDir::System, QDir::Name))
        {
            result.append(DataFile(file.fileName(), *i, ((double)*i / totalSize) * 100));
            i++;
        }
    } else { // обработка файла, не являющегося папкой
        quint64 fileSize = pathInfo.size(); // вычисляется размер файла
        if (pathInfo.isSymLink()) { // проверка на ярлык
            QFile fileOpen(pathInfo.absoluteFilePath());
            fileOpen.open(QIODevice::ReadOnly);
            fileSize = fileOpen.size();
            fileOpen.close();
        }
        result.append(DataFile(pathInfo.fileName(), fileSize, 100));
    }
    return result;
}
