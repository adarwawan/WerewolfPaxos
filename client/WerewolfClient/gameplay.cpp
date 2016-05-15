#include "gameplay.h"
#include "ui_gameplay.h"

gameplay::gameplay(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::gameplay)
{
    ui->setupUi(this);
    ui->listPlayerTable->setColumnCount(1);
    QStringList tableHeader;
    tableHeader<<"username";
    ui->listPlayerTable->setHorizontalHeaderLabels(tableHeader);
}

gameplay::~gameplay()
{
    delete ui;
}

void gameplay::do_changephase(QJsonObject json_object)
{
    int id = connection.getPlayerId();
    ui->idText->setText(QString::number(id));
    ui->usernameText->setText(connection.getPlayerName());
    ui->roleText->setText(connection.getRole());
    QString tPhase = json_object.value("time").toString();
    connection.setCurrentTime(tPhase);
    ui->phaseText->setText(tPhase);
    ui->daysText->setText(QString::number(json_object.value("days").toInt()));
    if (json_object.contains("friend")) {
        QJsonArray data = json_object.value("friend").toArray();
    }

    QJsonObject json_address;
    json_address.insert("method", "client_address");
    connection.sendMessage(json_address);
}

void gameplay::do_populate_players(){

}
