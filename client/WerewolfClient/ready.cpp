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
