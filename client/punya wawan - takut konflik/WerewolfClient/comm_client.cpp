#include "comm_client.h"
#include <cstdlib>

comm_client::comm_client(QObject *parent, comm_server *server)
{
    // create a QUDP socket
    socket = new QUdpSocket(this);
    this->server = server;

    // The most common way to use QUdpSocket class is
    // to bind to an address and port using bind()
    // bool QAbstractSocket::bind(const QHostAddress & address,
    //     quint16 port = 0, BindMode mode = DefaultForPlatform)
    socket->bind(QHostAddress::LocalHost, 1234);

    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
}

void comm_client::SendMessage(QString recv_address, int recv_port,QJsonObject message)
{
    int v1 = rand() % 100;
    if (v1 < 85) {
    qDebug() << "writing...";
    qDebug() << message;
    last_method = message.value("method").toString();
    QJsonDocument json_document;
    json_document.setObject(message);
    socket->writeDatagram(json_document.toJson(QJsonDocument::Compact) + "\r\n",QHostAddress(recv_address), recv_port);
    }
}

void comm_client::readyRead()
{
    // when data comes in
    QByteArray buffer;
    buffer.resize(socket->pendingDatagramSize());

    QHostAddress sender;
    quint16 senderPort;

    // qint64 QUdpSocket::readDatagram(char * data, qint64 maxSize,
    //                 QHostAddress * address = 0, quint16 * port = 0)
    // Receives a datagram no larger than maxSize bytes and stores it in data.
    // The sender's host address and port is stored in *address and *port
    // (unless the pointers are 0).

    socket->readDatagram(buffer.data(), buffer.size(),
                         &sender, &senderPort);
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
       if (json_object.contains("method")) {
            QJsonValue method;
            method = json_object.value("method");
          if (method == "vote_now") {
                QJsonObject tempvote;
                QString phase = json_object.value("phase").toString();
            if(phase == "day"){
                QVector<listPlayer> tempTab = server->getClients();
                tempvote.insert("method", "vote_civilian");
                tempvote.insert("player_id", player_id);
                for (int i=0; i<tempTab.length();i++ ){
                    listPlayer l;
                    l = connection.getClients().at(i);
                   SendMessage(l.getUdpAddress(), l.getUdpPort(),tempvote);
                }
            } else if (phase == "night"){
                tempvote.insert("method", "vote_werewolf");
                tempvote.insert("player_id", player_id);
                 QVector<listPlayer> tempTab = connection.getClients();
                for (int i=0; i<tempTab.length();i++ ){
                    listPlayer l;
                    l = connection.getClients().at(i);
                   SendMessage(l.getUdpAddress(), l.getUdpPort(),tempvote);
              }
            }
          }
        }
    }
}

void comm_client::prepareProposal(QJsonObject json_object){
    int curid[2];
    QJsonArray json_array = json_object.take("proposal_id").toArray();

        curid[0]= (long)json_array.at(0).toInt();
        curid[1]= (long)json_array.at(1).toInt();
        QJsonObject temp;
        bool valid = false;
        if(curid[0] > max_proposed_id[0]){
            valid= true;
        } else if (curid[0] == max_proposed_id[0]){
            if(curid[1] > max_proposed_id[1]){
                valid=true;
            }
        }
        if (valid){
            temp.insert("status", "ok");
            temp.insert("description","accepted");
            temp.insert("previous_id", acc_kpu_id);
        } else {
            temp.insert("status","fail");
            temp.insert("description", "rejected");
        }
        QVector<listPlayer> tempTab = connection.getClients();
        for (int i=0; i<tempTab.length();i++ ){
            listPlayer l;
            l = connection.getClients().at(i);
           SendMessage(l.getUdpAddress(), l.getUdpPort(),temp);
        }
}

void comm_client::acceptProposal(QJsonObject json_object){
    int curid[2];
    QJsonArray json_array = json_object.take("proposal_id").toArray();
    curid[0]= json_array.at(0).toInt();
    curid[1]= json_array.at(1).toInt();
    QJsonObject temp;
    bool valid = false;
    QString kpu_id = "";
    if(curid[0] > max_proposed_id[0]){
        if(curid[1] > max_proposed_id[1]){
            kpu_id = json_object.value("kpu_id").toString();
        if(acc_kpu_id == "" || kpu_id == acc_kpu_id)
            valid = true;
        }

    }

    if (valid){
        temp.insert("status", "ok");
        temp.insert("description","accepted");
    } else {
        temp.insert("status","fail");
        temp.insert("description", "rejected");
    }
    QVector<listPlayer> tempTab = server->getClients();
    for (int i=0; i<tempTab.length();i++ ){
        listPlayer l;
        l = connection.getClients().at(i);
       SendMessage(l.getUdpAddress(), l.getUdpPort(),temp);
    }
}

void comm_client::vote_werewolf(QJsonObject json){
    QString jsonvote;
    QJsonObject temp;
    int player_id = json.value("player_id").toInt();
    int totalPlayerId = connection.getClients().length();
    if(player_id <= totalPlayerId){
        temp.insert("status", "ok");
        temp.insert("description","vote werewolf accepted");
        totalVote++;

    } else {
        temp.insert("status","fail");
        temp.insert("description", "vote werewolf rejected");
    }
    QVector<listPlayer> tempTab = server->getClients();
    for (int i=0; i<tempTab.length();i++ ){
        listPlayer l;
        l = connection.getClients().at(i);
       SendMessage(l.getUdpAddress(), l.getUdpPort(),temp);
    }

}

void comm_client::vote_civilian(QJsonObject json){
    QString jsonVote;
    QJsonObject temp;

    int player_id = json.value("player_id").toInt();
    int totalPlayerId = server->getClients().size();
    if(player_id <= totalPlayerId){
        temp.insert("status", "ok");
        temp.insert("description","vote civilian accepted");
        totalVote++;

    } else{
        temp.insert("status","fail");
        temp.insert("description", "vote civilan rejected");
    }
    QVector<listPlayer> tempTab = server->getClients();
    for (int i=0; i<tempTab.length();i++ ){
        listPlayer l;
        l = connection.getClients().at(i);
       SendMessage(l.getUdpAddress(), l.getUdpPort(),temp);
    }

}

void comm_client::sendvote_civilian(int player_id){
    QString jsonVote;
    QJsonObject temp;

    temp.insert("method","vote_civilian");
    temp.insert("player_id", player_id);
    QVector<listPlayer> tempTab = server->getClients();
    for (int i=0; i<tempTab.length();i++ ){
        listPlayer l;
        l = connection.getClients().at(i);
       SendMessage(l.getUdpAddress(), l.getUdpPort(),temp);
    }
}

void comm_client::sendvote_werewolf(int player_id){
    QString jsonVote;
    QJsonObject temp;

    temp.insert("method","vote_werewolf");
    temp.insert("player_id", player_id);
    QVector<listPlayer> tempTab = server->getClients();
    for (int i=0; i<tempTab.length();i++ ){
        listPlayer l;
        l = connection.getClients().at(i);
       SendMessage(l.getUdpAddress(), l.getUdpPort(),temp);
    }
}

void comm_client::propose(int player_id){
    QString json;
    QJsonObject temp;
    temp.insert("method","prepare_proposal");
    QJsonArray ja;
    ja.insert(0,++sequence);
    ja.insert(1, player_id);
    temp.insert("proposal_id", ja);
    QVector<listPlayer> tempTab = server->getClients();
    for (int i=0; i<tempTab.length();i++ ){
        listPlayer l;
        l = connection.getClients().at(i);
       SendMessage(l.getUdpAddress(), l.getUdpPort(),temp);
    }

}

void comm_client::accept(int player_id){
    QString json;
    QJsonObject temp;
    temp.insert("method","accept_proposal");
    QJsonArray ja;
    ja.insert(0,++sequence);
    ja.insert(1, player_id);
    temp.insert("proposal_id", ja);
    QVector<listPlayer> tempTab = server->getClients();
    for (int i=0; i<tempTab.length();i++ ){
        listPlayer l;
        l = connection.getClients().at(i);
       SendMessage(l.getUdpAddress(), l.getUdpPort(),temp);
    }
}
