#include "ready.h"
#include "ui_ready.h"

ready::ready(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ready)
{
    ui->setupUi(this);
    ui->listPlayerTable->setColumnCount(1);
    QStringList tableHeader;
    tableHeader<<"username";
    ui->listPlayerTable->setHorizontalHeaderLabels(tableHeader);
}

ready::~ready()
{
    delete ui;
}

void ready::do_show()
{
    this->show();
}

void ready::do_hide()
{
    this->hide();
}

void ready::on_readyButton_clicked()
{
    QJsonObject json_object;
    json_object.insert("method", "ready");
    connection.sendMessage(json_object);
}

void ready::do_wait() {
    ui->readyButton->setDisabled(true);
    ui->label->setText("Waiting the other players");
}

void ready::do_listclient() {
    ui->listPlayerTable->clearContents();
    for (int i=0; i < connection.getClients().size(); i++) {
        listPlayer l = connection.getClients().at(i);
        ui->listPlayerTable->setItem(i,0,new QTableWidgetItem(l.getUsername()));
    }
}
