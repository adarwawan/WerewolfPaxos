#ifndef COMM_CLIENT_H
#define COMM_CLIENT_H

#include "comm_server.h"
#include <QObject>
#include <QUdpSocket>
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
    explicit comm_client(QObject *parent = 0, comm_server *server = NULL);
    void SendMessage(QString s);
    void SendMessage(QString recv_address, int recv_port,QJsonObject message);
    void vote_werewolf(QJsonObject json);
    void vote_civilian(QJsonObject json);
    void sendvote_civilian(int player_id);
    void sendvote_werewolf(int player_id);
    void propose(int player_id);
    void accept(int player_id);
    int getCounterLocal();
    void setCounter(int c);
    int getLastKPU();
    void setLastKPU(int c);
    void resetCounter();
signals:

public slots:
    void readyRead();
    void prepare_proposal();
    void prepareProposal(QJsonObject json_object);
    void acceptProposal(QJsonObject json_object);
    void accept_proposal();
private:
    int totalVote=0;
    int counter_local;
    int counter_prepare;
    int counter_accept;
    int last_KPU;
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
    comm_server *server;

};

extern comm_client conn_client;
#endif // COMM_CLIENT_H

