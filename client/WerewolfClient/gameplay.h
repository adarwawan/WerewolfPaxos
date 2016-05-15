#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include <QMainWindow>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QVector>
#include "comm_server.h"
#include "listplayer.h"

namespace Ui {
class gameplay;
}

class gameplay : public QMainWindow
{
    Q_OBJECT

public:
    explicit gameplay(QWidget *parent = 0);
    ~gameplay();

private:
    Ui::gameplay *ui;

private slots:
    void do_changephase(QJsonObject);
    void do_populate_players();
};

#endif // GAMEPLAY_H
