#include "handler_client.h"
#include <cstdlib>

handler_client::handler_client(QObject *parent)
{
    // create a QUDP socket
    socket = new QUdpSocket(this);

    // The most common way to use QUdpSocket class is
    // to bind to an address and port using bind()
    // bool QAbstractSocket::bind(const QHostAddress & address,
    //     quint16 port = 0, BindMode mode = DefaultForPlatform)
    socket->bind(QHostAddress::LocalHost, 1234);

    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
}

void handler_client::SendMessage(QString s)
{
    QByteArray Data;
    Data.append("Hello from UDP");

    // Sends the datagram datagram
    // to the host address and at port.
    // qint64 QUdpSocket::writeDatagram(const QByteArray & datagram,
    //                      const QHostAddress & host, quint16 port)
    socket->writeDatagram(s, QHostAddress::LocalHost, 1234);
}

void handler_client::SendMessage(QHostAddress IPadr, quint16 port, QString s)
{
    QByteArray Data;
    v1 = rand() % 100;
    if(v1 < 85){
    Data.append(s);

    // Sends the datax gram datagram
    // to the host address and at port.
    // qint64 QUdpSocket::writeDatagram(const QByteArray & datagram,
    //                      const QHostAddress & host, quint16 port)
    socket->writeDatagram(Data,  IPadr, port,s);
    }
}

void handler_client::readyRead()
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
    if (buffer == "quit"){
        socket->close();
    }
    qDebug() << "Message from: " << sender.toString();
    qDebug() << "Message port: " << senderPort;
    qDebug() << "Message: " << buffer;
}

void handler_client::prepareProposal(QJsonObject json_object){
    QJsonArray json_array = json_object.take("proposal_id");
        long curid[2];
        curid[0]= json_array.at(0);
        curid[1]= json_array.at(1);
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

        QString response = json_object;//ubah ke string
        SendMessage(response);
}

void handler_client::acceptProposal(QJsonObject json_object){
    long curid[2];
    QJsonArray json_array = json_object.take("proposal_id");
    curid[0]= json_array.at(0);
    curid[1]= json_array.at(1);
    QJsonObject temp;
    bool valid = false;
    int kpu_id = -1;
    if(curid[0] > max_proposed_id[0]){
        if(curid[1] > max_proposed_id[1]){
            kpu_id = json_object.value("kpu_id").toString();
        if((acc_kpu_id = -1) || ((kpu_id == acc_kpu_id)))
            vlaid = true;
        }

    }

    if (valid){
        temp.insert("status", "ok");
        temp.insert("description","accepted");
    } else {
        temp.insert("status","fail");
        temp.insert("description", "rejected");
    }
    QString response = json_object;//ubah ke string
    SendMessage(response);
}

void handler_client::vote_werewolf(QJsonObject json){
    String jsonvote;
    QJsonObject temp;
    int player_id = json.value("player_id").toInt();
    int totalPlayerId = listPlayer.size()-1;
    if(player_id <= totalPlayerId){
        temp.insert("status", "ok");
        temp.insert("description","vote werewolf accepted");
        totalVote++;
        String response = temp.toString();
        SendMessage(response);//ini harusnya kirim kemana, harusnya ad mekanisme perhitungan vote
    } else {
        temp.insert("status","fail");
        temp.insert("description", "vote werewolf rejected");
    }

}

void handler_client::vote_civilian(QJsonObject json){
    String jsonVote;
    QJsonObject temp;



    int player_id = json.value("player_id").toInt();
    int totalPlayerId = listPlayer.size()-1;
    if(player_id <= totalPlayerId){
        temp.insert("status", "ok");
        temp.insert("description","vote civilian accepted");
        totalVote++;
        String response = temp.toString();
        SendMessage(response);//ini harusnya kirim kemana, harusnya ad mekanisme perhitungan vote
    } else{
        temp.insert("status","fail");
        temp.insert("description", "vote civilan rejected");
    }

}

void handler_client::sendvote_civilian(int player_id){
    QString jsonVote;
    QJsonObject temp;

    temp.insert("method","vote_civilian");
    temp.insert("player_id", player_id);
    jsonVote= temp.toString();
    //kirim kemana ini?
}

void handler_client::sendvote_werewolf(int player_id){
    QString jsonVote;
    QJsonObject temp;

    temp.insert("method","vote_werewolf");
    temp.insert("player_id", player_id);
    jsonVote= temp.toString();
    //kirim kemana ini?
}

void handler_client::propose(int player_id){
    QString json;
    QJsonObject temp;
    temp.insert("method","prepare_proposal");
    QJsonArray ja;
    ja.insert(0,++sequence);
    ja.insert(1, player_id);
    temp.insert("proposal_id", ja);
    json = temp.toString();
    //kirim ke siapa aj?
}

void handler_client::accept(int player_id){
    QString json;
    QJsonObject temp;
    temp.insert("method","accept_proposal");
    QJsonArray ja;
    ja.insert(0,++sequence);
    ja.insert(1, player_id);
    temp.insert("proposal_id", ja);
    json = temp.toString();
    //kirim ke siapa aj?
}
