#ifndef INTERFACE_H
#define INTERFACE_H

#include <QObject>
#include "login.h"
#include "ready.h"
#include "handler_server.h"

class interface : public QObject
{
    Q_OBJECT
public:
    explicit interface(QObject *parent = 0);

signals:

public slots:
    void on_login();

private:
    login *w_login;
    ready *w_ready;
};

#endif // INTERFACE_H
