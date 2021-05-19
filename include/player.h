#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QtMath>
#include "paddle.h"
#include "config.h"

enum class PlayerPosition {
    Left = 0,
    Right = 1,
    Default = 2
};

class Player : public QObject {
    Q_OBJECT

    public:
        Player(PlayerPosition pos, bool computer = false);
        ~Player();
        void update_paddle();
        void set_up_pressed(bool is_pressed);
        void set_down_pressed(bool is_pressed);
        void set_score(quint16 new_score);
        void set_goal(qreal new_goal);
        void update(qreal ball_y);
        void update_score_text();
        void update_new_config();
        Paddle* get_paddle() const;
        bool get_is_computer() const;
        QGraphicsTextItem* get_score_text() const;
        quint16 get_score() const;
        void scored();
        void color_changed();
        void multiplayer_resize();

    public slots:
        void set_computer();
        void calculate_goal(QPointF ball_pos, qreal ball_angle);

    private:
        qreal goal;
        Paddle* paddle;
        quint16 score;
        PlayerPosition position;
        bool is_computer;
        bool up_pressed;
        bool down_pressed;
        QGraphicsTextItem* score_text;
        void setup_score_text();
};

#endif // PLAYER_H
