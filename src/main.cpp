#include "MainWindow.h"

#include <QApplication>
// TODO: не хватает комментариев    +
// TODO: добавить .gitignore
// TODO: нет тестов
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
