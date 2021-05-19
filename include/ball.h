#ifndef BALL_H
#define BALL_H

#include <QtWidgets>
#include <QtMath>
#include <QDebug>
#include <QDataStream>
#include <QRandomGenerator>
#include <QSoundEffect>
#include "config.h"
#include "paddle.h"
#include "player.h"

class Ball : public QObject, public QGraphicsRectItem {
    Q_OBJECT 

    public:
        Ball();
        ~Ball();
        void move();
        void collision(Paddle* p1, Paddle* p2);
        void reset(PlayerPosition new_side = PlayerPosition::Default);
        void launch();
        bool get_is_moving() const;
        void update_new_config();
        void color_changed();
        void multiplayer_resize();

    signals:
        void player_scored(int player);
        void ball_bounce_paddle(QPointF ball_pos, qreal ball_angle, int player);

    public slots:
        void sfx_volume_changed(qreal volume);

    private:
        qreal vy, vx;
        qreal ball_speed;
        qreal base_speed;
        bool is_moving;
        PlayerPosition side;
        QSoundEffect ball_bounce_sfx;
        QSoundEffect point_scored_sfx;
        void generate_new_angle(Paddle* p, int player);
};

#endif // BALL_H
