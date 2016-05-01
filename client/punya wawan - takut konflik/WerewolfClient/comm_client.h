#ifndef COMM_CLIENT_H
#define COMM_CLIENT_H

#include "comm_server.h"
#include <QObject>
#include <QUdpSocket>
<<<<<<< HEAD
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include "comm_server.h"

class comm_client : public QObject
{
        Q_OBJECT
    public:
        explicit comm_client(QObject *parent = 0);
        void doListen(quint16 client_port);
=======
#include <QJsonObject>
#include <QJsonArray>
#include <QTcpSocket>
#include <QJsonDocument>
#include <QJsonValue>
#include <QVector>

class comm_client : public QObject
{
    Q_OBJECT
public:
    explicit comm_client(QObject *parent = 0);
    void SendMessage(QString s);
    void SendMessage(QString recv_address, int recv_port,QJsonObject message);
    void prepareProposal(QJsonObject json_object);
    void acceptProposal(QJsonObject json_object);
    void vote_werewolf(QJsonObject json);
    void vote_civilian(QJsonObject json);
    void sendvote_civilian(int player_id);
    void sendvote_werewolf(int player_id);
    void propose(int player_id);
    void accept(int player_id);

signals:
>>>>>>> 58aeb9909bcbed8bd7c9e05d07cdba6c2119dc74

    signals:

<<<<<<< HEAD
    public slots:
        void readMessage();
        void sendMessage(QString recv_address, QString recv_port, QJsonObject message);
=======
private:
    int totalVote=0;
    QString acc_kpu_id;
    QString prev_kpu_id;
    QString max_proposed_id;
    int sequence =0;
    QUdpSocket *socket;
    int player_id;
    QString player_name;
    QString last_method;
    QString player_role;
    int current_phase;
    int current_day;
    int is_kpu;
    QString friends;
>>>>>>> 58aeb9909bcbed8bd7c9e05d07cdba6c2119dc74

    private:
        QUdpSocket *socket;
};

/* Universal client connection handler */
extern comm_client conn_client;

#endif // COMM_CLIENT_H
<<<<<<< HEAD
=======

>>>>>>> 58aeb9909bcbed8bd7c9e05d07cdba6c2119dc74
