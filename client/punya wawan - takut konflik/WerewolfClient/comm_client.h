#ifndef COMM_CLIENT_H
#define COMM_CLIENT_H

#include <QObject>
#include <QUdpSocket>
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

    signals:

    public slots:
        void readMessage();
        void sendMessage(QString recv_address, QString recv_port, QJsonObject message);

    private:
        QUdpSocket *socket;
};

/* Universal client connection handler */
extern comm_client conn_client;

#endif // COMM_CLIENT_H
