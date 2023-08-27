#include <QApplication>
#include"ckernel.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ckernel kernel;
    return a.exec();
}
