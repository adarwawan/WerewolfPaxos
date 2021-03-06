#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include <QHostAddress>
#include <QNetworkInterface>
#include "comm_server.h"
#include "comm_client.h"

namespace Ui {
class login;
}

class login : public QMainWindow
{
        Q_OBJECT

    public:
        explicit login(QWidget *parent = 0);
        ~login();

    private slots:
        void do_destroy();
        void on_buttonPlay_clicked();
        void do_wait();
        void on_buttonReady_clicked();
        void do_wait_ready();

    private:
        Ui::login *ui;

        /* Login property */
        QString nickname;

};

#endif // LOGIN_H
