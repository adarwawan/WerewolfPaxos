#include "client.h"

client connection;

client::client(QObject *parent) : QObject(parent)
{

}

void client::doConnect(QString server_ip, quint16 server_port)
{
    socket = new QTcpSocket(this);
    connect(socket, SIGNAL(connected()),this, SLOT(connected()));
    connect(socket, SIGNAL(disconnected()),this, SLOT(disconnected()));
    connect(socket, SIGNAL(readyRead()),this, SLOT(readMessage()));

    qDebug() << "connecting...";

    socket->connectToHost(server_ip, server_port);
    if (!socket->waitForConnected(3000)){
        qDebug() << "Error: " << socket->errorString();
    }
}

void client::connected()
{
    qDebug() << "connected...";
}

void client::disconnected()
{
    qDebug() << "disconnected...";
}

void client::sendMessageJSONObject(QJsonObject message)
{
    qDebug() << "writing...";
    qDebug() << message;


    QJsonDocument json_document;
    json_document.setObject(message);
    if (socket->write(json_document.toJson(QJsonDocument::Compact) + "\r\n") < 0){
        qDebug() << "Error: " << socket->errorString();
    }
}

void client::readMessage()
{
    QByteArray message = socket->readAll();

    qDebug() << "reading...";
    //qDebug() << message;

    QList<QByteArray> message_list= message.split('\n');
    qDebug() << message_list;

    QJsonDocument json_document;
    QJsonObject json_object;
    QJsonValue type;
    for (int i=0; i<message_list.size(); i++){
        json_document = QJsonDocument::fromJson(message_list.at(i));
        json_object = json_document.object();
        qDebug() << json_document;
    }

}
