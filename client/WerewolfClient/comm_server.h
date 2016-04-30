#ifndef COMM_SERVER_H
#define COMM_SERVER_H

#include <QObject>
#include <QJsonObject>
#include <QJsonArray>
#include <QTcpSocket>
#include <QJsonDocument>
#include <QJsonValue>

class comm_server : public QObject
{
    Q_OBJECT
public:
    explicit comm_server(QObject *parent = 0);
    void doConnect(QString server_ip, quint16 server_port);

signals:
    void on_login();

public slots:
    void connected();
    void disconnected();
    void sendMessage(QJsonObject message);
    void readMessage();

private:
    QTcpSocket *socket;
    int player_id;
    QJsonValue last_method;
};

/* Universal connection handler */
extern comm_server connection;
#endif // COMM_SERVER_H
