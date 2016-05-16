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
    explicit comm_client(QObject *parent = 0);
    void doListen(quint16 client_port);
    void SendMessage(QString s);
    void SendMessage(QString recv_address, quint16 recv_port,QJsonObject message, int tag);
    void vote_werewolf(QJsonObject json);
    void vote_civilian(QJsonObject json);
    void sendvote_civilian(int player_id);
    void sendvote_werewolf(int player_id);
    void propose(int player_id);
    void accept(int player_id);
    int getCounterLocal();
    int getCounterPrepare();
    int getCounterAccept();
    void setCounter(int c);
    int getLastKPU();
    void setLastKPU(int c);
    void resetVote();
    void resetCounter();
    std::map<int, int> vote_map;
signals:
    void on_fail_or_error(QString);
    void on_accept_prepare_proposal(QJsonObject,QHostAddress,quint16);
    void on_accept_accept_proposal(QJsonObject, QHostAddress, quint16);

public slots:
    void readMessage();
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
    QString last_sent_method;
    QString player_role;
    int current_phase;
    int current_day;
    int is_kpu;
    QString friends;
    int hardcode_player;

};

extern comm_client conn_client;
#endif // COMM_CLIENT_H

