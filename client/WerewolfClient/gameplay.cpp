#include "gameplay.h"
#include "ui_gameplay.h"

gameplay::gameplay(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::gameplay)
{
    ui->setupUi(this);
    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), &conn_client, SLOT(prepare_proposal()));

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
    ui->listPlayerTable->setRowCount(connection.getClient().size());
    ui->listPlayerTable->setColumnCount(1);
    QStringList tableHeader;
    tableHeader<<"username";
    ui->listPlayerTable->setHorizontalHeaderLabels(tableHeader);
    for (int i = 0; i< connection.getClient().size(); i++) {
        ui->listPlayerTable->setItem(0, i, new QTableWidgetItem("YA"));
    }

    timer->stop();
    if ( connection.getCurrentTime() == 1 ) {
        connection.setKpuId(-1);

        qDebug() << "Start Ngirim Proposal";

        int clientID = static_cast<int>(connection.getPlayerId());
        if (((clientID + 1) == connection.getClient().size()) || ((clientID + 1) == (connection.getClient().size() - 1)))
        {
            /* Ngirim Proposal Terus-terusan sampe kpu_id diterima */
            qDebug() << "Ngirim Proposal";

            if (connection.getKpuId() == -1){
                timer->start(1000);
            } else {
                timer->stop();
            }
        }
    }
}
