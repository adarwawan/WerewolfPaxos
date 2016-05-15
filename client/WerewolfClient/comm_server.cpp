#include "comm_server.h"

comm_server connection;

comm_server::comm_server(QObject *parent) : QObject(parent)
{
    last_method = "";
}

void comm_server::doConnect(QString server_ip, quint16 server_port)
{
    socket = new QTcpSocket(this);
    connect(socket, SIGNAL(connected()), this, SLOT(connected()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(socket, SIGNAL(readyRead()), this, SLOT(readMessage()));

    qDebug() << "connecting...";

    socket->connectToHost(server_ip, server_port);
    if (!socket->waitForConnected(3000)){
        qDebug() << "Error: " << socket->errorString();
    } else{
        local_address = socket->localAddress();
        foreach (const QHostAddress &local_address_, QNetworkInterface::allAddresses()) {
            if (local_address_.protocol() == QAbstractSocket::IPv4Protocol && local_address_ != QHostAddress(QHostAddress::LocalHost))
            local_address = local_address_.toString();
        }
    }
}

QVector<listPlayer> comm_server::getClient() {
    return client;
}

QString comm_server::getLocalAddress(){
    return local_address.toString();
}

QJsonArray comm_server::getClients() {
    return clients;
}

QVector<QString> comm_server::getFriends() {
    return friends;
}

QString comm_server::getRole() {
    return player_role;
}

int comm_server::getPlayerId() {
    return player_id;
}

QString comm_server::getPlayerName() {
    return player_name;
}

void comm_server::setPlayerName(QString _name) {
    player_name = _name;
}

int comm_server::getClientIdByUsername(QString username) {
    for (int i=0; i<clients.size(); i++){
        if (clients.at(i).toObject().value("username").toString() == username) {
            return clients.at(i).toObject().value("player_id").toInt();
        }
    }
    return -1;
}

QJsonObject comm_server::getClientDataByUsername(QString username) {
    QJsonObject ret;
    for (int i=0; i<clients.size(); i++){
        if (clients.at(i).toObject().value("username").toString() == username) {
            ret = clients.at(i).toObject();
        }
    }
    return ret;
}

QJsonObject comm_server::getClientDataById(int id) {
    QJsonObject ret;
    for (int i=0; i<clients.size(); i++){
        if (clients.at(i).toObject().value("player_id").toInt() == id) {
            ret = clients.at(i).toObject();
        }
    }
    return ret;
}

QJsonArray comm_server::getNonFriends() {
    QJsonArray ret;
    for (int i=0; i<clients.size(); i++) {
        bool is_friend = false;
        for (int j=0; j<friends.size(); j++) {
            if ( friends.at(j) == clients.at(i).toObject().value("username").toString() ) {
                is_friend = true;
            }
        }
        if (!is_friend) {
            ret.insert(0, clients.at(i).toObject().value("username").toString());
        }
    }
    return ret;
}

int comm_server::getCurrentTime() {
    return current_phase;
}

void comm_server::setCurrentTime(QString _current_phase) {
    if (_current_phase == "night") {
        current_phase = 0;
    } else {
        current_phase = 1;
    }
}


void comm_server::connected()
{
    qDebug() << "connected...";
}

void comm_server::disconnected()
{
    qDebug() << "disconnected...";
}

void comm_server::sendMessage(QJsonObject message)
{
    qDebug() << "writing...";
    qDebug() << message;

    QJsonDocument json_document;
    json_document.setObject(message);
    if (socket->write(json_document.toJson(QJsonDocument::Compact) + "\n") < 0) {
        qDebug() << "Error: " << socket->errorString();
    }

    last_method = message.value("method").toString();
}

void comm_server::readMessage()
{
    QByteArray message = socket->readAll();
    QList<QByteArray> message_list= message.split('\n');
    qDebug() << message_list;

    QJsonDocument json_document;
    QJsonObject json_object;
    for (int i = 0; i < message_list.size(); i++) {
        json_document = QJsonDocument::fromJson(message_list.at(i));
        json_object = json_document.object();

        // Cari tau dulu ini respon apa method
        if (json_object.contains("status")) {
            QJsonValue status;
            status = json_object.value("status");
            if (last_method == "join") {
                qDebug() << last_method;
                if (status == "ok") {
                    player_id = json_object.value("player_id").toInt();
                    emit on_login();
                }
                else if (status == "fail" || status == "error") {
                    qDebug() << json_object.value("description");
                }
            }
            else if (last_method == "ready") {
                qDebug() << last_method;
                if (status == "ok") {
                    qDebug() << json_object.value("description");
                    emit on_ready();
                }
                else if (status == "error") {
                    qDebug() << json_object.value("description");
                }
            }
            else if (last_method == "leave") {
                qDebug() << last_method;
                if (status == "ok") {
                    QApplication::quit();
                }
                else if (status == "fail" || status == "error") {
                    qDebug() << json_object.value("description");
                }
            }
            else if (last_method == "client_address") {
                qDebug() << last_method;
                if (status == "ok") {
                    int size_ = clients.size();
                    for (int i=0; i<size_; i++){
                        clients.removeFirst();
                    }

                    QJsonObject client_;
                    for (int i=0; i<json_object.value("clients").toArray().size(); i++) {
                        client_ = json_object.value("clients").toArray().at(i).toObject();
                        clients.push_back(client_);
                    }
                    //emit on_get_clients();
                }
                else if (status == "fail" || status == "error") {
                    qDebug() << json_object.value("description");
                }
            }
            else if (last_method == "vote_result_werewolf") {
                qDebug() << last_method;
                if (status == "ok") {
                    //emit on_wait();
                }
                else if (status == "fail" || status == "error") {
                    qDebug() << json_object.value("description");
                }
            }
            else if (last_method == "vote_result_civilian") {
                qDebug() << last_method;
                if (status == "ok") {
                    //emit on_wait();
                }
                else if (status == "fail" || status == "error") {
                    qDebug() << json_object.value("description");
                }
            }
            else if (last_method == "vote_result") {
                qDebug() << last_method;
                if (status == "ok") {
                    //emit on_wait();
                }
                else if (status == "fail" || status == "error") {
                    qDebug() << json_object.value("description");
                }
            }
        }
        else if (json_object.contains("method")) {
            QJsonValue method;
            method = json_object.value("method");
            if (method == "start") {
                qDebug() << "ini start";
                player_role = json_object.value("role").toString();

                QString friend_;
                for (int i=0; i<json_object.value("friend").toArray().size(); i++) {
                    friend_ = json_object.value("friend").toArray().at(i).toString();
                    friends.push_back(friend_);
                }
                emit on_start();
                emit on_changephase(json_object);
            }
            else if (method == "change_phase") {
                qDebug() << "ini change phase";
                emit on_changephase(json_object);
            }
            else if (method == "vote_now") {
                qDebug() << "ini vote now";
                //emit on_vote_now();
            }
            else if (method == "game_over") {
                qDebug() << "ini game over";
            }
        }
    }
}
