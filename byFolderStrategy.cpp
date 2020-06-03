#include <byFolderStrategy.h>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QString>
#include <QTextStream>

quint64 ByFolderStrategy::FolderSize(const QString &path) {
    QDir directory(path); // текущая директория
    quint64 size = QFileInfo(path + "/.").size();
    //цикл по всем папкам в текущей папке
    foreach (QFileInfo folder, directory.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot | QDir::Hidden | QDir::System | QDir::NoSymLinks))
    {
        size += FolderSize(folder.path() + '/' + folder.fileName()); // вычисляется размер папки
    }

    //цикл по всем файлам в папке
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

