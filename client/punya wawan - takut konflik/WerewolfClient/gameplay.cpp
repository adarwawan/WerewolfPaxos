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
