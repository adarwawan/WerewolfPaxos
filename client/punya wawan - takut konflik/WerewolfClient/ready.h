#ifndef READY_H
#define READY_H

#include <QWidget>
#include <QJsonObject>
#include <QVector>
#include "comm_server.h"
#include "listplayer.h"

namespace Ui {
class ready;
}

class ready : public QWidget
{
    Q_OBJECT

public:
    explicit ready(QWidget *parent = 0);
    ~ready();

private:
    Ui::ready *ui;

private slots:
    void do_destroy();
    void do_show();
    void do_hide();
    void do_wait();
    void on_readyButton_clicked();
    void on_leaveButton_clicked();
};

#endif // READY_H
