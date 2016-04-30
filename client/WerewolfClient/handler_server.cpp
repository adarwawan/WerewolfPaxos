#include "handler_server.h"

handler_server connection;

handler_server::handler_server(QObject *parent) : QObject(parent)
{

}

void handler_server::doConnect(QString server_ip, quint16 server_port)
{
    socket = new QTcpSocket(this);
    connect(socket, SIGNAL(connected()),this, SLOT(connected()));
    connect(socket, SIGNAL(disconnected()),this, SLOT(disconnected()));
    connect(socket, SIGNAL(readyRead()),this, SLOT(readMessage()));

    qDebug() << "connecting...";

    socket->connectToHost(server_ip, server_port);
    qDebug() << server_ip;
    qDebug() << server_port;
    if (!socket->waitForConnected(3000)){
        qDebug() << "Error: " << socket->errorString();
    }
}

void handler_server::connected()
{
    qDebug() << "connected...";
}

void handler_server::disconnected()
{
    qDebug() << "disconnected...";
}

void handler_server::sendMessageJSONObject(QJsonObject message)
{
    qDebug() << "writing...";
    qDebug() << message;


    QJsonDocument json_document;
    json_document.setObject(message);
    if (socket->write(json_document.toJson(QJsonDocument::Compact) + "\r\n") < 0){
        qDebug() << "Error: " << socket->errorString();
    }
}

void handler_server::readMessage()
{
    QByteArray message = socket->readAll();

    qDebug() << "reading...";
    //qDebug() << message;

    QList<QByteArray> message_list= message.split('\n');
    qDebug() << message_list;

    QJsonDocument json_document;
    QJsonObject json_object;
    QJsonValue method;
    for (int i = 0; i < message_list.size(); i++) {
        json_document = QJsonDocument::fromJson(message_list.at(i));
        json_object = json_document.object();

        method = json_object.value("status");
        if (method == "ok"){
            player_id = json_object.value("player_id").toInt();
            emit on_login();
        }
    }
}
