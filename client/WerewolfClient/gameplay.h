#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include <QMainWindow>
#include <QTimer>
#include <QMutex>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QVector>
#include "comm_server.h"
#include "comm_client.h"
#include "listplayer.h"

namespace Ui {
class gameplay;
}

class gameplay : public QMainWindow
{
    Q_OBJECT

public:
    explicit gameplay(QWidget *parent = 0);
    ~gameplay();

private:
    Ui::gameplay *ui;
    QTimer *timer;
    QMutex mutex;

private slots:
    void do_changephase(QJsonObject);
    void do_populate_players();
    void do_proposal_prepare(QJsonObject message, QHostAddress sender_ip, quint16 sender_port);
    void do_proposal_accept(QJsonObject message, QHostAddress sender_ip, quint16 sender_port);
    void do_set_kpu_selected();
    void do_set_rule(QJsonObject message);
};

#endif // GAMEPLAY_H
