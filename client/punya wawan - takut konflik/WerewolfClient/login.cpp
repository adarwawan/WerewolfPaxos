#include "login.h"
#include "ui_login.h"

login::login(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::login),
    nickname("user_name")
{
    ui->setupUi(this);
}

login::~login()
{
    delete ui;
}

void login::do_destroy()
{
    delete this;
}

void login::on_buttonPlay_clicked()
{
    nickname = ui->username->text();
    connection.setPlayerName(nickname);
    QString server_ip = ui->address->text();
    qint16 server_port = ui->tcp_port->text().toInt();
    qint16 client_port = ui->udp_port->text().toInt();

    connection.doConnect(server_ip, server_port);
    conn_client.doListen(client_port);

    QJsonObject json_object;
    json_object.insert("method", "join");
    json_object.insert("username", nickname.toStdString().c_str());
    foreach (const QHostAddress &address, QNetworkInterface::allAddresses()) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol && address != QHostAddress(QHostAddress::LocalHost))
            json_object.insert("udp_address", address.toString());
    }
    json_object.insert("udp_port", client_port);
    connection.sendMessage(json_object);
}
