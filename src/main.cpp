#include "MainWindow.h"

#include <QApplication>
// TODO: �� ������� ������������    +
// TODO: �������� .gitignore
// TODO: ��� ������
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
