#ifndef READY_H
#define READY_H

#include <QWidget>

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
};

#endif // READY_H
