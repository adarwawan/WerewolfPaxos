#include "interface.h"
#include "handler_client.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    interface ui;
    handler_client client;
    client.SendMessage("HELLO");
    client.SendMessage("quit");
    client.SendMessage("HELLO");
    return a.exec();
}
