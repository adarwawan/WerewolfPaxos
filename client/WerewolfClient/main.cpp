#include "interface.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    interface ui;

    return a.exec();
}
