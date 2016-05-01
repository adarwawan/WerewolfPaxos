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

void gameplay::do_listclient() {
    ui->listPlayerTable->clearContents();
    for (int i=0; i < connection.getClients().size(); i++) {
        listPlayer l = connection.getClients().at(i);
        ui->listPlayerTable->setItem(i,0,new QTableWidgetItem(l.getUsername()));
    }
}

void gameplay::do_start(QJsonObject json_object)
{
    ui->usernameText->setText(connection.getPlayerName());
    ui->idText->setText(QString::number(connection.getPlayerId()));

    QString tPhase = json_object.value("time").toString();
    if (tPhase == "day") {
        connection.setCurrentPhase(0);
    }
    else {
        connection.setCurrentPhase(1);
    }
    ui->phaseText->setText(tPhase);

    connection.setCurrentDay(1);
    connection.setPlayerRole(json_object.value("role").toString());

    ui->roleText->setText(connection.getPlayerRole());
    ui->daysText->setText(QString::number(connection.getCurrentDay()));
    ui->friendText->setText(connection.getFriends());

    QJsonObject json_address;
    json_address.insert("method", "client_address");
    connection.sendMessage(json_address);
}

void gameplay::do_changephase(QJsonObject json_object)
{

}
