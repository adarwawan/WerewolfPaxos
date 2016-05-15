#ifndef COMM_SERVER_H
#define COMM_SERVER_H

#include "listplayer.h"
#include <QObject>
#include <QJsonObject>
#include <QJsonArray>
#include <QTcpSocket>
#include <QJsonDocument>
#include <QJsonValue>
#include <QVector>

class comm_server : public QObject
{
    Q_OBJECT
public:
    explicit comm_server(QObject *parent = 0);
    void doConnect(QString server_ip, quint16 server_port);
    QVector<listPlayer> getClients();

    int getPlayerId();
    QString getPlayerName();
    QString getPlayerRole();
    int getCurrentPhase();
    int getCurrentDay();
    int getIsKpu();
    QString getFriends();

    void setPlayerId(int _id);
    void setPlayerName(QString _name);
    void setPlayerRole(QString _role);
    void setCurrentPhase(int _phase);
    void setCurrentDay(int _day);
    void setIsKpu(int _kpu);
    void setFriends(QString _friends);

signals:
    void on_login();
    void on_ready();
    void on_start(QJsonObject);
    void on_clients();
    void on_changephase(QJsonObject);
    void on_destroy();

public slots:
    void connected();
    void disconnected();
    void sendMessage(QJsonObject message);
    void readMessage();

private:
    QTcpSocket *socket;
    int player_id;
    QString player_name;
    QString last_method;
    QVector<listPlayer> clients;
    QString player_role;
    int current_phase;
    int current_day;
    int is_kpu;
    QString friends;
};

/* Universal connection handler */
extern comm_server connection;
#endif // COMM_SERVER_H
