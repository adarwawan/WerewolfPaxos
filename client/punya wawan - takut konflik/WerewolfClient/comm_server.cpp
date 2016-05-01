#include "comm_server.h"

comm_server connection;

comm_server::comm_server(QObject *parent) : QObject(parent)
{

}

void comm_server::doConnect(QString server_ip, quint16 server_port)
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

QVector<listPlayer> comm_server::getClients() {
    return clients;
}

int comm_server::getPlayerId(){
    return player_id;
}

QString comm_server::getPlayerName(){
    return player_name;
}

QString comm_server::getPlayerRole(){
    return player_role;
}

int comm_server::getCurrentPhase() {
    return current_phase;
}

int comm_server::getCurrentDay() {
    return current_day;
}

QString comm_server::getFriends(){
    return friends;
}

void comm_server::setPlayerId(int _id) {
    player_id = _id;
}

void comm_server::setPlayerName(QString _name) {
    player_name = _name;
}

void comm_server::setPlayerRole(QString _role) {
    player_role = _role;
}

void comm_server::setCurrentPhase(int _phase) {
    current_phase = _phase;
}

void comm_server::setCurrentDay(int _day) {
    current_day = _day;
}

void comm_server::setFriends(QString _friends) {
    friends = _friends;
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

    last_method = message.value("method").toString();

    QJsonDocument json_document;
    json_document.setObject(message);
    if (socket->write(json_document.toJson(QJsonDocument::Compact) + "\r\n") < 0){
        qDebug() << "Error: " << socket->errorString();
    }
}

void comm_server::readMessage()
{
    QByteArray message = socket->readAll();

    qDebug() << "reading...";

    QList<QByteArray> message_list= message.split('\n');
    qDebug() << message_list;

    QJsonDocument json_document;
    QJsonObject json_object;
    for (int i = 0; i < message_list.size()-1; i++) {
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

                }
                else if (status == "fail" || status == "error") {
                    qDebug() << json_object.value("description");
                }
            }
            else if (last_method == "client_address") {
                qDebug() << last_method;
                if (status == "ok") {
                    clients.clear();
                    QJsonObject json_client;
                    for (int i=0; i<json_object.value("clients").toArray().size(); i++){
                        json_client = json_object.value("clients").toArray().at(i).toObject();
                        int _player_id = json_client.value("player_id").toInt();
                        int _is_alive = json_client.value("is_alive").toInt();
                        QString _address = json_client.value("address").toString();
                        int _port = json_client.value("port").toInt();
                        QString _username = json_client.value("username").toString();
                        QString _role;
                        if (_is_alive == 0) {
                            _role = json_client.value("role").toString();
                        }
                        else {
                            _role = "";
                        }
                        listPlayer client(_player_id, _is_alive, _address, _port, _username, _role);
                        clients.push_back(client);
                    }
                    emit on_clients();
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
                QJsonObject json_object_respond;
                json_object_respond.insert("status", "ok");
                connection.sendMessage(json_object_respond);
                player_role = json_object.value("role").toString();
                emit on_start(json_object);
            }
            else if (method == "change_phase") {
                qDebug() << "ini change phase";
            }
            else if (method == "vote_now") {
                qDebug() << "ini vote now";
            }
            else if (method == "game_over") {
                qDebug() << "ini game over";
            }
        }
    }
}
