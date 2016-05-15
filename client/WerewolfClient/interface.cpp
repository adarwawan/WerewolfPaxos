#include "interface.h"

interface::interface(QObject *parent) : QObject(parent)
{
    connect(&connection, SIGNAL(on_start()), this, SLOT(do_login()));
    /* Creating the user interface */
    w_login = new login;
    w_gameplay = new gameplay;
    connect(&connection, SIGNAL(on_login()), w_login, SLOT(do_wait_ready()));
    connect(&connection, SIGNAL(on_ready()), w_login, SLOT(do_wait()));
    w_login->show();
}

void interface::do_login()
{
    connect(&connection, SIGNAL(on_changephase(QJsonObject)), w_gameplay, SLOT(do_changephase(QJsonObject)));
    connect(&connection, SIGNAL(on_get_clients()), w_gameplay, SLOT(do_populate_players()));
    w_login->hide();
    w_gameplay->show();
}
