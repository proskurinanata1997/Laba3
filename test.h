#ifndef TEST_H
#define TEST_H
#include <byFileTypeStrategy.h>
#include <byFolderStrategy.h>
#include <QTextStream>
#include <QTextCodec>
#include <windows.h>

class Test {
public:
    explicit Test () {
        QTextStream out(stdout);
        SetConsoleOutputCP(1251);

        /* Набор тестов:
         * Тест 1: не пустая папка без вложений
         * Тест 2: не пустая папка, содержащая как файлы, так и папки, с вложениями уровня больше 1
         * Тест 3: не пустая папка, содержащая как файлы, так и папки, с вложениями уровня больше 1, в том числе и скрытые папки, ярлыки
         * Тест 4: пустая папка
         * Тест 5: не пустая папка без вложений, вес которой составляет 0 байт
         * Тест 6: не пустая папка, содержащая только папку
         * Тест 7: объект, не являющийся папкой
         * Тест 8: несуществующий объект
         */

        QString path = QString::fromUtf8("../Lab3/Tests/Test0");
        for (int i = 1; i < 9; i++) {
            switch (i) {
                case 7: {
                    path.append(".txt");
                }
                default: {
                    path[18] = QChar('0' + i);
                }
            }
            out << path << "\n\n" << flush;
            strategy = new ByFolderStrategy();
            out << DataToString(strategy->Explore(path)) << '\n' << flush;
            delete strategy;
            strategy = new ByFileTypeStrategy();
            out << '\n' << flush;
            out << DataToString(strategy->Explore(path)) << '\n' << flush;
            delete strategy;
            out << '\n' << flush;
        }
    }
private:
    AbstractStrategy *strategy;
    QString DataToString(QList<DataFile> data) {
        QString result;
        for (auto i = data.begin(); i != data.end(); i++) {
            result += i->name + ", size percentage: ";
            if (i->percentage < 0.01 && i->percentage > 0) {
                result += "< 0.01%\n";
            } else {
                result += QString::number(i->percentage) + "%\n";
            }
        }
        return result;
    }
};

#endif // TEST_H
