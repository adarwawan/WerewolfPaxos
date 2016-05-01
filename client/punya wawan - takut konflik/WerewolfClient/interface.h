#ifndef INTERFACE_H
#define INTERFACE_H

#include <QObject>
#include "login.h"
#include "ready.h"
#include "comm_server.h"
#include "gameplay.h"

class interface : public QObject
{
    Q_OBJECT
public:
    explicit interface(QObject *parent = 0);

signals:

public slots:
    void do_login();
    void do_start();

private:
    login *w_login;
    ready *w_ready;
    gameplay *w_gameplay;
};

#endif // INTERFACE_H
