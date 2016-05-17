#include "comm_client.h"
#include <cstdlib>

comm_client conn_client;

comm_client::comm_client(QObject *parent) : QObject(parent)
{
    last_KPU = -1;
    counter_accept = 0;
    counter_local = 0;
    counter_prepare = 0;
    hardcode_player = 6;
}

void comm_client::doListen(quint16 client_port) {
    socket = new QUdpSocket(this);
    qDebug() << "binding...";
    socket->bind(QHostAddress::Any, client_port);
    connect(socket, SIGNAL(readyRead()), this, SLOT(readMessage()));

}

void comm_client::SendMessage(QString recv_address, quint16 recv_port,QJsonObject message, int tag)
{
    double rand = qrand() % 100 + 1;
    if ((rand < 85) || (tag == 1)) {
        QJsonDocument json_document;
        json_document.setObject(message);
        qDebug() << "SEND UDP DATAGRAM: " << json_document;
        socket->writeDatagram((json_document.toJson(QJsonDocument::Compact) + "\n"), QHostAddress(recv_address), recv_port);
        if (message.value("method").toString() != ""){
            last_sent_method = message.value("method").toString();
        }
    } else {
        qDebug() << "Unreliable Connection";
    }
}

void comm_client::resetVote() {
    for (int i = 0; i < connection.getClients().size(); i++) {
        vote_map[i] = 0;
    }
}

void comm_client::readMessage()
{
    // when data comes in
    while (socket->hasPendingDatagrams()) {
        QByteArray message;
        message.resize(socket->pendingDatagramSize());

        QHostAddress sender_ip;
        quint16 sender_port;
        socket->readDatagram(message.data(), message.size(), &sender_ip, &sender_port);

        qDebug() << "reading...";

        QList<QByteArray> message_list = message.split('\n');
        qDebug() << message_list;

        QJsonDocument json_document;
        QJsonObject json_object;
        QJsonValue status, description;
        json_document = QJsonDocument::fromJson(message_list.at(0));
        json_object = json_document.object();

        // Cari tau dulu ini respon apa method
        if (json_object.contains("status")) {
            /* Response Proposer->Acceptor */
            status = json_object.value("status");

            if (status == "fail" || status == "error"){
                description = json_object.value("description");
                emit on_fail_or_error(description.toString());

            } else if (last_sent_method == "prepare_proposal" && status == "ok") {
                counter_prepare++;
                qDebug() << "Prepare Counter Sekarang = " << counter_prepare;
                if (counter_prepare == connection.getClients().size()-1) {
                    accept_proposal();
                }
            }

        }
       else if (json_object.contains("method")) {
            QJsonValue method;
            method = json_object.value("method");
            if (method == "prepare_proposal"){
                qDebug() <<"masuk sih";
                emit on_accept_prepare_proposal(json_object,sender_ip,sender_port);
            } else if (method == "accept_proposal"){
                emit on_accept_accept_proposal(json_object,sender_ip,sender_port);
            }else if (method == "vote_now") {
                QJsonObject tempvote;
                QString phase = json_object.value("phase").toString();
            if(phase == "day"){
                QVector<listPlayer> tempTab = connection.getClient();
                tempvote.insert("method", "vote_civilian");
                tempvote.insert("player_id", player_id);
                for (int i=0; i<tempTab.length();i++ ){
                    listPlayer l;
                    l = connection.getClient().at(i);
                   SendMessage(l.getUdpAddress(), l.getUdpPort(),tempvote,0);
                }
            } else if (phase == "night"){
                tempvote.insert("method", "vote_werewolf");
                tempvote.insert("player_id", player_id);
                 QVector<listPlayer> tempTab = connection.getClient();
                for (int i=0; i<tempTab.length();i++ ){
                    listPlayer l;
                    l = connection.getClient().at(i);
                   SendMessage(l.getUdpAddress(), l.getUdpPort(),tempvote,0);
              }
            }
          }
        }
    }
}

int comm_client::getLastKPU() {
    return last_KPU;
}

void comm_client::setCounter(int c) {
    counter_local = c;
}

int comm_client::getCounterPrepare() {
    return counter_prepare;
}

int comm_client::getCounterAccept() {
    return counter_accept;
}

void comm_client::setLastKPU(int c) {
    last_KPU = c;
}

int comm_client::getCounterLocal() {
    return counter_local;
}

void comm_client::prepare_proposal() {
    if (connection.getKpuId()) {
        int size = connection.getClients().size();
        int newcounter = conn_client.getCounterLocal() + 1;
        counter_prepare = 0;
        for (int i = 0; i < size; i++) {
            QJsonValue playerid;
            playerid = connection.getPlayerId();

            if (i != playerid.toInt()) {
                QJsonObject json_object = connection.getClients().at(i).toObject();
                qDebug() << json_object;
                QString address = json_object.value("address").toString();
                quint16 port = json_object.value("port").toInt();

                /* send message */
                QJsonObject message;
                QJsonArray json_array;

                json_array.insert(0,newcounter);
                json_array.insert(1,playerid);
                qDebug() << "Proposal-id: " << newcounter;
                qDebug() << "Your player id: " << playerid;
                conn_client.setCounter(newcounter);
                message.insert("method", "prepare_proposal");
                message.insert("proposal_id", json_array);

                conn_client.setLastKPU(playerid.toInt());
                SendMessage(address,port,message,0);

            }
        }
    }
}

void comm_client::accept_proposal() {
    int size = connection.getClients().size();
    int counter = conn_client.getCounterLocal();
    counter_prepare = 0;
    for (int i = 0; i < size; i++) {
        QJsonValue playerid;
        playerid = connection.getPlayerId();

        if (i != playerid.toInt()) {
            QJsonObject json_object = connection.getClients().at(i).toObject();
            qDebug() << json_object;
            QString address = json_object.value("address").toString();
            quint16 port = json_object.value("port").toInt();

            /* send message */
            QJsonObject message;
            QJsonArray json_array;

            json_array.insert(0,counter);
            json_array.insert(1,playerid);
            //qDebug() << "ini accept";
            qDebug() << "Proposal-id: " << counter;
            qDebug() << "Your player id: " << playerid;
            conn_client.setCounter(counter);
            message.insert("method", "accept_proposal");
            message.insert("proposal_id", json_array);
            message.insert("kpu_id", playerid);
            SendMessage(address,port,message,0);

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
        QVector<listPlayer> tempTab = connection.getClient();
        for (int i=0; i<tempTab.length();i++ ){
            listPlayer l;
            l = connection.getClient().at(i);
           SendMessage(l.getUdpAddress(), l.getUdpPort(),temp,0);
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
    QVector<listPlayer> tempTab = connection.getClient();
    for (int i=0; i<tempTab.length();i++ ){
        listPlayer l;
        l = connection.getClient().at(i);
       SendMessage(l.getUdpAddress(), l.getUdpPort(),temp,0);
    }
}

void comm_client::vote_werewolf(QJsonObject json){
    QString jsonvote;
    QJsonObject temp;
    int player_id = json.value("player_id").toInt();
    int totalPlayerId = connection.getClient().length();
    if(player_id <= totalPlayerId){
        temp.insert("status", "ok");
        temp.insert("description","vote werewolf accepted");
        totalVote++;

    } else {
        temp.insert("status","fail");
        temp.insert("description", "vote werewolf rejected");
    }
    QVector<listPlayer> tempTab = connection.getClient();
    for (int i=0; i<tempTab.length();i++ ){
        listPlayer l;
        l = connection.getClient().at(i);
       SendMessage(l.getUdpAddress(), l.getUdpPort(),temp,0);
    }

}

void comm_client::vote_civilian(QJsonObject json){
    QString jsonVote;
    QJsonObject temp;

    int player_id = json.value("player_id").toInt();
    int totalPlayerId = connection.getClient().size();
    if(player_id <= totalPlayerId){
        temp.insert("status", "ok");
        temp.insert("description","vote civilian accepted");
        totalVote++;

    } else{
        temp.insert("status","fail");
        temp.insert("description", "vote civilan rejected");
    }
    QVector<listPlayer> tempTab = connection.getClient();
    for (int i=0; i<tempTab.length();i++ ){
        listPlayer l;
        l = connection.getClient().at(i);
       SendMessage(l.getUdpAddress(), l.getUdpPort(),temp,0);
    }

}

void comm_client::sendvote_civilian(int player_id){
    QString jsonVote;
    QJsonObject temp;

    temp.insert("method","vote_civilian");
    temp.insert("player_id", player_id);
    QVector<listPlayer> tempTab = connection.getClient();
    for (int i=0; i<tempTab.length();i++ ){
        listPlayer l;
        l = connection.getClient().at(i);
       SendMessage(l.getUdpAddress(), l.getUdpPort(),temp,0);
    }
}

void comm_client::sendvote_werewolf(int player_id){
    QString jsonVote;
    QJsonObject temp;

    temp.insert("method","vote_werewolf");
    temp.insert("player_id", player_id);
    QVector<listPlayer> tempTab = connection.getClient();
    for (int i=0; i<tempTab.length();i++ ){
        listPlayer l;
        l = connection.getClient().at(i);
       SendMessage(l.getUdpAddress(), l.getUdpPort(),temp,0);
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
    QVector<listPlayer> tempTab = connection.getClient();
    for (int i=0; i<tempTab.length();i++ ){
        listPlayer l;
        l = connection.getClient().at(i);
        SendMessage(l.getUdpAddress(), l.getUdpPort(),temp,0);
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
    QVector<listPlayer> tempTab = connection.getClient();
    for (int i=0; i<tempTab.length();i++ ){
        listPlayer l;
        l = connection.getClient().at(i);
       SendMessage(l.getUdpAddress(), l.getUdpPort(),temp,0);
    }
}
