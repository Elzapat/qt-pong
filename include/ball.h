#ifndef BALL_H
#define BALL_H

#include <QtWidgets>
#include <QtMath>
#include <QDebug>
#include <QDataStream>
#include "config.h"
#include "paddle.h"

class Ball : public QObject, public QGraphicsRectItem {
    Q_OBJECT 

    public:
        Ball();
        ~Ball();
        void move();
        void collision(Paddle* p1, Paddle* p2);

    private:
        qreal vy, vx;
        void generate_new_angle(Paddle* p);
};

#endif
