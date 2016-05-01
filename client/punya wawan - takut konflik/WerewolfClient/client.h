#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonArray>
#include <QJsonObject>
#include <QCloseEvent>
#include <QTableWidgetItem>


class client : public QObject
{
    Q_OBJECT
public:
    explicit client(QObject *parent = 0);

signals:

public slots:
};

#endif // CLIENT_H
