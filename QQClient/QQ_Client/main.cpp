#include <QApplication>
#include "src/ui/loginform.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoginForm l;
    l.show();

    return a.exec();
}
