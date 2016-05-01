#include "interface.h"

interface::interface(QObject *parent) : QObject(parent)
{
    connect(&connection, SIGNAL(on_login()), this, SLOT(do_login()));
    /* Creating the user interface */
    w_login = new login;
    w_ready = new ready;
    w_gameplay = new gameplay;
    connect(&connection, SIGNAL(on_login()), w_login, SLOT(do_destroy()));
    w_login->show();
}

void interface::do_login()
{
    connect(&connection, SIGNAL(on_ready()), w_ready, SLOT(do_wait()));
    connect(&connection, SIGNAL(on_start()), this, SLOT(do_start()));
    w_ready->show();
}

void interface::do_start()
{
    w_ready->hide();
    connect(&connection, SIGNAL(on_clients()), w_gameplay, SLOT(do_listclient()));
    w_gameplay->show();
}
