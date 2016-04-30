#ifndef HANDLER_SERVER_H
#define HANDLER_SERVER_H

#include <QObject>
#include <QJsonObject>
#include <QJsonArray>
#include <QTcpSocket>
#include <QJsonDocument>

class handler_server : public QObject
{
    Q_OBJECT
public:
    explicit handler_server(QObject *parent = 0);
    void doConnect(QString server_ip, quint16 server_port);

signals:
    void on_login();

public slots:
    void connected();
    void disconnected();
    void sendMessageJSONObject(QJsonObject message);
    void readMessage();

private:
    QTcpSocket *socket;
    int player_id;
};

/* Universal connection handler */
extern handler_server connection;
#endif // HANDLER_SERVER_H
