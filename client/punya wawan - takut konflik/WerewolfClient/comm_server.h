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

signals:
    void on_login();
    void on_ready();
    void on_start();
    void on_clients();

public slots:
    void connected();
    void disconnected();
    void sendMessage(QJsonObject message);
    void readMessage();

private:
    QTcpSocket *socket;
    int player_id;
    QString last_method;
    QVector<listPlayer> clients;
    QString player_role;
};

/* Universal connection handler */
extern comm_server connection;
#endif // COMM_SERVER_H
