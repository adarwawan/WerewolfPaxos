#include "login.h"
#include "ui_login.h"

login::login(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::login),
    nickname("user_name")
{
    ui->setupUi(this);
    ui->buttonReady->setDisabled(true);
}

login::~login()
{
    delete ui;
}

void login::do_destroy()
{
    delete this;
}

void login::do_wait_ready() {
    ui->buttonPlay->setDisabled(true);
    ui->labelReady->setText("Are you ready?");
    ui->buttonReady->setDisabled(false);
}

void login::on_buttonPlay_clicked()
{
    ui->buttonReady->setDisabled(false);
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
    json_object.insert("udp_address", connection.getLocalAddress().toStdString().c_str());
    json_object.insert("udp_port", client_port);
    connection.sendMessage(json_object);
}

void login::on_buttonReady_clicked()
{
    QJsonObject json_object;
    json_object.insert("method", "ready");
    connection.sendMessage(json_object);
}

void login::do_wait() {
    ui->buttonReady->setDisabled(true);
    ui->labelReady->setText("Waiting the other players...");
}
