#ifndef HANDLER_CLIENT_H
#define HANDLER_CLIENT_H

#include <QObject>
#include <QUdpSocket>
#include <QString>

class handler_client : public QObject
{
    Q_OBJECT
public:
    explicit handler_client(QObject *parent = 0);
    void HelloUDP();
    void SendMessage(QString s);
signals:

public slots:
    void readyRead();

private:
    QUdpSocket *socket;
};
#endif // HANDLER_CLIENT_H
