#include "ready.h"
#include "ui_ready.h"

ready::ready(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ready)
{
    ui->setupUi(this);
}

ready::~ready()
{
    delete ui;
}

void ready::do_destroy()
{
    delete this;
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
    ui->leaveButton->setDisabled(true);
    ui->label->setText("Waiting the other players...");
}

void ready::on_leaveButton_clicked()
{
    QJsonObject json_object;
    json_object.insert("method", "leave");
    connection.sendMessage(json_object);
}
