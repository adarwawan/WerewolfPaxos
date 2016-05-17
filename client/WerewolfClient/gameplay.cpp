#include "gameplay.h"
#include "ui_gameplay.h"

gameplay::gameplay(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::gameplay)
{
    ui->setupUi(this);
    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), &conn_client, SLOT(prepare_proposal()));
    ui->leaveButton->setDisabled(true);
    ui->killButton->setDisabled(true);
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
        QString friends = "";
        for (int i = 0; i < data.count(); i++) {
            friends = friends + data.at(i).toString() + ", ";
        }
        ui->friendText->setText(friends);
    }

    QJsonObject json_address;
    json_address.insert("method", "client_address");
    connection.sendMessage(json_address);
}


void gameplay::do_set_rule(QJsonObject message) {
    QString timeLabel = "?";
    if ( message.value("time").toString() == "day" ) {
        timeLabel = "Noon";
    } else {
        timeLabel = "Night";
    }

    connection.setCurrentTime(message.value("time").toString());
    connection.setKpuId(-1);

    /* Send list clients message */
    QJsonObject json_object;
    json_object.insert("method", "client_address");
    connection.sendMessage(json_object);
    conn_client.resetVote();
}


void gameplay::do_populate_players(){
    ui->listPlayerTable->setRowCount(connection.getClient().size());
    ui->listPlayerTable->setColumnCount(1);
    QStringList tableHeader;
    tableHeader<<"username";
    ui->listPlayerTable->setHorizontalHeaderLabels(tableHeader);
    for (int i = 0; i< connection.getClient().size(); i++) {
        listPlayer ap = connection.getClient().at(i);
        QString aa = ap.getUsername();

        if (ap.getIsAlive() == 0) {
            aa = "[DEAD] " + aa;
        }

        ui->listPlayerTable->setItem(0, i, new QTableWidgetItem(aa));

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

void gameplay::do_set_kpu_selected() {
    timer->stop();
    conn_client.setLastKPU(connection.getKpuId());
    QJsonObject message;
    message.insert("status","ok");
    connection.sendMessage(message);
}

void gameplay::do_proposal_prepare(QJsonObject message, QHostAddress sender_ip, quint16 sender_port) {
    mutex.lock();
    int c = message.value("proposal_id").toArray().at(0).toInt();
    int recentCounter = conn_client.getCounterLocal();
    int newKPU = message.value("proposal_id").toArray().at(1).toInt();
    int lastKPU = conn_client.getLastKPU();
    QJsonObject json_object;

    qDebug() << "DO_PROPOSAL_PREPARE";

    if ((recentCounter < c) || ((recentCounter == c) && (lastKPU  < newKPU))) {
        conn_client.setCounter(c);

        if (lastKPU == -1) {
            json_object.insert("status","ok");
            json_object.insert("description","accepted");
        } else {
            json_object.insert("status","ok");
            json_object.insert("description","accepted");
            json_object.insert("previous_accepted",lastKPU);
        }

        /* Kalo dia potensial jadi leader dan dia udah dapet proposal lain,
         * maka dia ngalah ga kirim proposal selama x ms */
        int size = connection.getClients().size();
        int clientID = static_cast<int>(connection.getPlayerId());
        if (((clientID) == size-1) || ((clientID) == (size - 2))) {
            if (conn_client.getCounterPrepare() >= (size-1)) {
                conn_client.accept_proposal();
            }
        }

        conn_client.setLastKPU(newKPU);
        conn_client.SendMessage(sender_ip.toString(), sender_port, json_object,0);

        qDebug() << "Accepting proposal from " << message.value("proposal_id").toArray().at(1) << " with value " << c;
    } else {
        json_object.insert("status","fail");
        json_object.insert("description","rejected");
        conn_client.SendMessage(sender_ip.toString(), sender_port, json_object,0);
    }
    mutex.unlock();
}

void gameplay::do_proposal_accept(QJsonObject message, QHostAddress sender_ip, quint16 sender_port) {
    mutex.lock();
    int c = message.value("proposal_id").toArray().at(0).toInt();
    int recentCounter = conn_client.getCounterLocal();
    int playerId = message.value("proposal_id").toArray().at(1).toInt();
    int lastKPU = conn_client.getLastKPU();
    int kpuId = message.value("kpu_id").toInt();
    QJsonObject json_object;

    qDebug() << "DO_PROPOSAL_ACCEPT";

    if ((recentCounter == c) && ((playerId == lastKPU) && (kpuId  == lastKPU))) {
        json_object.insert("status","ok");
        json_object.insert("description","accepted");

        conn_client.SendMessage(sender_ip.toString(), sender_port, json_object,0);
        qDebug() << "Konfirmasi KPU " << message.value("proposal_id").toArray().at(1) << " with value " << c;

        QJsonObject json_object_;
        json_object_.insert("method", "accepted_proposal");
        json_object_.insert("kpu_id", conn_client.getLastKPU());
        json_object_.insert("Description", "Kpu is selected");

        connection.sendMessage(json_object_);

    } else {
        json_object.insert("status","fail");
        json_object.insert("description","rejected");
        conn_client.SendMessage(sender_ip.toString(), sender_port, json_object,0);
    }
    mutex.unlock();
}

void gameplay::on_killButton_clicked()
{
    QJsonObject json_object;
    ui->killButton->setDisabled(true);
    int to_killed = ui->voteEdit->text().toInt();
    to_killed--;
    QString ap = QString::number(to_killed);
    if (connection.getCurrentTime() == 0) {
        json_object.insert("method", "vote_werewolf");
    }
    else {
        json_object.insert("method", "vote_civilian");
    }
    json_object.insert("player_id", to_killed);
    //Kirim to Client
    //connection.sendMessage(json_object);
}

void gameplay::do_game_over(QJsonObject message) {
    ui->killButton->setDisabled(true);
    ui->leaveButton->setDisabled(false);
    ui->leaveButton->setText("Leave Game");
    ui->killButton->setText("GAME OVER");
    QString winner = message.value("winner").toString();
    ui->statusbar->showMessage("Winner : " + winner);
}


void gameplay::on_leaveButton_clicked()
{
    QJsonObject json_object;
    json_object.insert("method", "leave");
    connection.sendMessage(json_object);
}

void gameplay::do_vote_now() {
    int i = connection.getPlayerId();
    listPlayer as = connection.getClient().at(i);
    if (as.getIsAlive() == 0) {
        ui->killButton->setText("You dead!");
        ui->killButton->setDisabled(true);
    }
    else {
        ui->killButton->setDisabled(false);
    }

}
