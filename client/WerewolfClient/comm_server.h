#ifndef COMM_SERVER_H
#define COMM_SERVER_H

#include "listplayer.h"
#include <QObject>
#include <QJsonObject>
#include <QHostAddress>
#include <QNetworkInterface>
#include <QJsonArray>
#include <QTcpSocket>
#include <QJsonDocument>
#include <QJsonValue>
#include <QVector>
#include <QApplication>

class comm_server : public QObject
{
    Q_OBJECT
public:
    explicit comm_server(QObject *parent = 0);
    void doConnect(QString server_ip, quint16 server_port);

    QVector<listPlayer> getClient();
    QString getLocalAddress();
    QJsonArray getClients();
    QVector<QString> getFriends();
    QString getRole();
    int getPlayerId();
    QString getPlayerName();
    void setPlayerName(QString player_name_);
    int getClientIdByUsername(QString);
    QJsonObject getClientDataByUsername(QString);
    QJsonObject getClientDataById(int);
    int getDeadWerewolf();
    int getDeadPlayer();
    int getKpuId();
    void setCounter(int c);
    void setLastKPU(int c);
    void setKpuId(int id);
    QJsonArray getNonFriends();
    int getCurrentTime();
    void setCurrentTime(QString current_time_);

signals:
    void on_login();
    void on_ready();
    void on_start();
    void on_changephase(QJsonObject);
    void on_get_clients();

public slots:
    void connected();
    void disconnected();
    void sendMessage(QJsonObject message);
    void readMessage();

private:
    QTcpSocket *socket;
    QHostAddress local_address;
    int player_id;
    QString player_name;
    QString last_method;
    QString player_role;
    int current_phase;
    int current_day;
    QVector<QString> friends;
    QJsonArray clients;
    QVector<listPlayer> client;

    int kpu_id;
    bool game_over;
};

/* Universal connection handler */
extern comm_server connection;
#endif // COMM_SERVER_H
