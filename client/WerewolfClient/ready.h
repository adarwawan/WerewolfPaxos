#ifndef READY_H
#define READY_H

#include <QWidget>
#include <QJsonObject>
#include "comm_server.h"

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
    void do_show();
    void do_hide();
    void on_readyButton_clicked();
};

#endif // READY_H
