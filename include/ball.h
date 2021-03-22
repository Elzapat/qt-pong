#ifndef BALL_H
#define BALL_H

#include <QtWidgets>
#include <QtMath>
#include <QDebug>
#include <QDataStream>
#include <QRandomGenerator>
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
        void reset(PlayerPosition new_side);
        void launch();
        bool is_moving() const;

    signals:
        void player_scored(quint8 player);

    private:
        qreal vy, vx;
        qreal ball_speed;
        bool m_is_moving;
        PlayerPosition side;
        void generate_new_angle(Paddle* p);
};

#endif
