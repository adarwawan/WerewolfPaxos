#ifndef INTERFACE_H
#define INTERFACE_H

#include <QObject>
#include "login.h"
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

private:
    login *w_login;
    gameplay *w_gameplay;
};

#endif // INTERFACE_H
