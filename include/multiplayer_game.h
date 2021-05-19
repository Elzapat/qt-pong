#ifndef MULTIPLAYER_GAME_H
#define MULTIPLAYER_GAME_H

#include <QTcpSocket>
#include "config.h"

class MultiplayerGame : public QObject {
    Q_OBJECT

    public:
        MultiplayerGame(QTcpSocket* s);
        ~MultiplayerGame();
        void key_event(int key, QString action);
        int get_side() const;

    public slots:
        void ready_read();
        void disconnect_socket();

    signals:
        void multiplayer_ball_move(qreal x, qreal y);
        void multiplayer_score_point(quint8 player);
        void multiplayer_player_move(int player, qreal x, qreal y);
        void multiplayer_score(int player);
        void multiplayer_player_won(int player);
        void multiplayer_game_end();

    private:
        QTcpSocket* server;
        int side;
};

#endif // MULTIPLAYER_GAME_H
