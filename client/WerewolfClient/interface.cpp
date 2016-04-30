#include "interface.h"

interface::interface(QObject *parent) : QObject(parent)
{
    connect(&connection, SIGNAL(on_login()), this, SLOT(on_login()));
    /* Creating the user interface */
    w_login = new login;
    w_ready = new ready;
    connect(&connection, SIGNAL(on_login()), w_login, SLOT(do_destroy()));
    w_login->show();
}

void interface::on_login()
{
    w_ready->show();
}
