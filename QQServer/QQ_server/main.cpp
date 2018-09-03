#include "qqserverwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QQServerwindow w;
    w.show();

    return a.exec();
}
