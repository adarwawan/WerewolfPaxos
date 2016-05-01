#ifndef HANDLER_CLIENT_H
#define HANDLER_CLIENT_H

#include <QObject>
#include <QJsonObject>
#include <QJsonArray>
#include <QUdpSocket>
#include <QString>

class handler_client : public QObject
{
    Q_OBJECT
public:
    explicit handler_client(QObject *parent = 0);
    void SendMessage(QString s);
    void SendMessage(QHostAddress IPadr, quint16 port, QString s);
    void prepareProposal(QJsonObject json_object);
    void acceptProposal(QJsonObject json_object);
    void vote_werewolf(QJsonObject json);
    void vote_civilian(QJsonObject json);
    void sendvote_civilian(int player_id);
    void sendvote_werewolf(int player_id);
    void propose(int player_id);
    void accept(int player_id);

signals:

public slots:
    void readyRead();

private:
    QUdpSocket *socket;
};
#endif // HANDLER_CLIENT_H
