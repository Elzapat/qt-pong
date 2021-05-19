#include "../include/multiplayer_game.h"

MultiplayerGame::MultiplayerGame(QTcpSocket* s) : server(s), side(0) {
    this->connect(server, SIGNAL(readyRead()), this, SLOT(ready_read()));
    this->connect(server, SIGNAL(errorOccurred(QAbstractSocket::SocketError)), this, SLOT(disconnect_socket()));
    this->connect(server, &QAbstractSocket::disconnected, this, [this] { emit multiplayer_game_end(); });;
}

MultiplayerGame::~MultiplayerGame() {
    // delete server;
    Config::reset_to_default();
}

void MultiplayerGame::ready_read() {
    QByteArray data = server->readAll();

    quint8 i = 0;
    QStringList packets;
    for (QByteArray packet_bytes : data.split('%')) {
        packets.append(QString::fromLocal8Bit(packet_bytes));
        // Limit the number of simultaneous packets to avoid the client
        // processing the packets way slower than they come and
        // running out of memory
        if (++i >= 5) break;
    }

    for (QString packet : packets) {
        QStringList args = packet.split(';');

        if (args[0] == "ball")
            emit multiplayer_ball_move(args[1].toDouble(), args[2].toDouble());
        else if (args[0] == "side")
            side = args[1].toInt();
        else if (args[0] == "move")
            emit multiplayer_player_move(args[1].toInt(), args[2].toDouble(), args[3].toDouble());
        else if (args[0] == "score")
            emit multiplayer_score(args[1].toInt());
        else if (args[0] == "won")
            emit multiplayer_player_won(args[1].toInt());
    }
}

void MultiplayerGame::key_event(int key, QString action) {
    if (side == 0) return;

    QString value = action == "down" ? "1" : "0";

    if (side == 1) {
        if (key == Config::get<int>("player_1_up", "controls"))
            server->write(("move;up;" + value + '%').toLocal8Bit());
        else if (key == Config::get<int>("player_1_down", "controls"))
            server->write(("move;down;" + value + '%').toLocal8Bit());
    } else if (side == 2) {
        if (key == Config::get<int>("player_2_up", "controls"))
            server->write(("move;up;" + value + '%').toLocal8Bit());
        else if (key == Config::get<int>("player_2_down", "controls"))
            server->write(("move;down;" + value + '%').toLocal8Bit());
    }
}

int MultiplayerGame::get_side() const {
    return side;
}

void MultiplayerGame::disconnect_socket() {
    server->disconnectFromHost();
    // delete server;
}
