#ifndef LISTPLAYER_H
#define LISTPLAYER_H

#include <QString>

class listPlayer
{
public:
    listPlayer();
    listPlayer(int, int, QString, int, QString, QString);
    void setPlayerId(int);
    void setIsAlive(int);
    void setUdpAddress(QString);
    void setUdpPort(int);
    void setUsername(QString);
    void setRole(QString);

    int getPlayerId();
    int getIsAlive();
    QString getUdpAddress();
    int getUdpPort();
    QString getUsername();
    QString getRole();

private:
    int player_id;
    int is_alive;
    QString udp_address;
    int udp_port;
    QString username;
    QString role;
};

#endif // LISTPLAYER_H
