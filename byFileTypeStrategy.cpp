#include "byFileTypeStrategy.h"
#include <QFile>
#include <QFileInfo>
#include <QString>
#include <QDir>
#include <QTextStream>

QString ByFileTypeStrategy::FileType(const QFileInfo &file) {
    if (file.isSymLink()) {
        if (file.fileName().mid(file.fileName().lastIndexOf('.') + 1) == "lnk") {
            return ".link";
        }
        return "symlink";
    }
    if (file.isDir()) {
        return "directory";
    }
    QString fileName = file.fileName();
    int i = fileName.lastIndexOf('.'); // поиск символа
    if (i == -1) { // неизвестный тип (отсутствует символ)
        return "unknown";
    }
    return fileName.mid(i); // возвращение типа файла
}

void ByFileTypeStrategy::FolderSize(const QString &path, QHash<QString, quint64> &hash) {
    QDir dir(path);
    quint64 temp = QFileInfo(path + "/.").size();
    if (temp) {
        hash[FileType(QFileInfo(path + "/."))] += temp;
    }
    foreach (QFileInfo folder, dir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot | QDir::Hidden | QDir::System | QDir::NoSymLinks))
    {
        FolderSize(folder.path() + '/' + folder.fileName(), hash); // проводятся вычисления с вложенной папкой
    }
    foreach (QFileInfo file, dir.entryInfoList(QDir::Files | QDir::NoDotAndDotDot | QDir::Hidden | QDir::System))
    {
        if (file.isSymLink()) { // проверка на ярлык
            QFile fileOpen(file.absoluteFilePath());
            fileOpen.open(QIODevice::ReadOnly);
            hash[FileType(file)] += fileOpen.size();
            fileOpen.close();
            continue;
        }
        hash[FileType(file)] += file.size();
    }
}

QList<DataFile> ByFileTypeStrategy::Explore (const QString &path)
{
    QFileInfo pathInfo(path);
    QTextStream out(stdout);
    QList<DataFile> result; // список данных о размере, занимаемом каждым типом в папке

    if (pathInfo.exists() == false) {
        out << "Object does not exist\n" << flush;
        return QList<DataFile>();
    }

    if (QFileInfo(path + '/').isDir()) {// проверка на неполноту пути
        pathInfo.setFile(path + '/');
    }

    if (pathInfo.isDir() && !pathInfo.isSymLink()) { // проверка на то, что на входе была подана папка
        if (pathInfo.dir().isEmpty()) {
            out << "Folder is empty.\n" << flush;
            return QList<DataFile>();
        }

        QDir dir(pathInfo.absoluteFilePath());
        QHash<QString, quint64> hash;
        quint64 temp = QFileInfo(pathInfo.absoluteFilePath() + '.').size();
        if (temp) {
            hash[FileType(QFileInfo(pathInfo.absoluteFilePath() + '.'))] = temp;
        }

        //вычисление размеров объектов
        foreach (QFileInfo folder, dir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot | QDir::Hidden | QDir::System | QDir::NoSymLinks))
        {
            FolderSize(folder.path() + '/' + folder.fileName(), hash); // проводятся вычисления с папкой
        }
        foreach (QFileInfo file, dir.entryInfoList(QDir::Files | QDir::NoDotAndDotDot | QDir::Hidden | QDir::System))
        {
            if (file.isSymLink()) { // проверка на ярлык
                QFile fileOpen(file.absoluteFilePath());
                fileOpen.open(QIODevice::ReadOnly);
                hash[FileType(file)] += fileOpen.size();
                fileOpen.close();
                continue;
            }
            hash[FileType(file)] += file.size();
        }

        QStringList types; // массив типов
        quint64 totalSize = 0; // итоговый размер папки

        for (auto i = hash.begin(); i != hash.end(); i++) {// вычисление итогового размера папки и заполнение массива типов
            totalSize += *i;
            types.append(i.key());
        }
        if (totalSize == 0) { // если папка ничего не весит, то выходим из функции
            out << "Folder has size 0.\n" << flush;
            return QList<DataFile>();
        }
        types.sort(); // сортировка типов по их названиям
        //сохранение результатов
        for (int i = 0; i < types.size(); i++) {
            result.append(DataFile(types[i], hash[types[i]], ((double)hash[types[i]] / totalSize) * 100));
        }
    } else { // обработка файла, не являющегося папокй
        quint64 fileSize = pathInfo.size();
        #if defined(Q_OS_WIN)
        if (pathInfo.isSymLink()) { // проверка на ярлык
            QFile fileOpen(pathInfo.absoluteFilePath());
            fileOpen.open(QIODevice::ReadOnly);
            fileSize = fileOpen.size();
            fileOpen.close();
        }
        #endif
        result.append(DataFile(FileType(pathInfo), fileSize, 100));
    }
    return result;
}
