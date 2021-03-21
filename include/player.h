#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include "paddle.h"
#include "config.h"

enum class PlayerPosition {
    Left = 0,
    Right = 1
};

class Player : public QObject {
    Q_OBJECT

    public:
        Player(PlayerPosition pos, bool computer = false);
        ~Player();
        void update_paddle();
        void set_up_pressed(bool is_pressed);
        void set_down_pressed(bool is_pressed);
        void update();
        void update_score_text();
        Paddle* paddle() const;
        QGraphicsTextItem* score_text() const;
        void scored();

    private:
        Paddle* m_paddle;
        quint16 score;
        PlayerPosition m_position;
        bool is_computer;
        bool up_pressed;
        bool down_pressed;
        QGraphicsTextItem* m_score_text;
        void setup_score_text();
};

#endif
