#include "listplayer.h"

listPlayer::listPlayer()
{

}

listPlayer::listPlayer(int _id, int _is_alive, QString _udp_address, int _udp_port, QString _username, QString _role) {
    player_id = _id;
    is_alive = _is_alive;
    udp_address = _udp_address;
    udp_port = _udp_port;
    username = _username;
    role = _role;
}

void listPlayer::setPlayerId(int _id) {
    player_id = _id;
}

void listPlayer::setIsAlive(int _is_alive) {
    is_alive = _is_alive;
}

void listPlayer::setUdpAddress(QString _udp_address) {
    udp_address = _udp_address;
}

void listPlayer::setUdpPort(int _udp_port) {
    udp_port = _udp_port;
}

void listPlayer::setUsername(QString _username) {
    username = _username;
}

void listPlayer::setRole(QString _role) {
    role = _role;
}

int listPlayer::getPlayerId() {
    return player_id;
}

int listPlayer::getIsAlive() {
    return is_alive;
}

QString listPlayer::getUdpAddress() {
    return udp_address;
}

int listPlayer::getUdpPort() {
    return udp_port;
}

QString listPlayer::getUsername() {
    return username;
}

QString listPlayer::getRole() {
    return role;
}
