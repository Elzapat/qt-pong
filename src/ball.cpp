#include "../include/ball.h"

Ball::Ball() : vx(Config::get<qreal>("ball_speed")), vy(0.f),
    QGraphicsRectItem(
        -Config::get<quint16>("ball_width") / 2,
        -Config::get<quint16>("ball_height") / 2,
        Config::get<quint16>("ball_width"),
        Config::get<quint16>("ball_height")
) {
    // Set ball color to white
    const QBrush BALL_COLOR = (QBrush)Qt::white;
    this->setBrush(BALL_COLOR);
}

Ball::~Ball() {}

void Ball::move() {
    // Time passed since last frame
    const qreal dt = 1.f / Config::get<qreal>("fps");

    // Update the ball's coordinates depending on its velocity
    qreal dx = vx * dt;
    qreal dy = vy * dt;

    this->setPos(this->x() + dx, this->y() + dy);
}

void Ball::collision(Paddle* p1, Paddle* p2) {
    // Check if the ball is colliding with any of the two player paddles
    // If so, send it back with a different angle depending
    // on where the ball collided with the paddle
    if (this->collidesWithItem(p1)) {
        generate_new_angle(p1);
    } else if (this->collidesWithItem(p2)) {
        generate_new_angle(p2);
    }

    // Check if the ball is colliding with the top or the bottom of the board
    // If so invert its y axis velocity
    quint16 board_h = Config::get<quint16>("board_height");
    quint16 ball_h = Config::get<quint16>("ball_height");
    if (this->y() - ball_h / 2 <= -board_h / 2) {
        vy = -vy;
        this->setY(-board_h / 2 + ball_h / 2);
    } else if (this->y() + ball_h / 2 >= board_h / 2) {
        vy = -vy;
        this->setY(board_h / 2 - ball_h / 2);
    }
}

void Ball::generate_new_angle(Paddle* p) {
    quint16 p_h = Config::get<quint16>("paddle_height");
    quint16 b_h = Config::get<quint16>("ball_height");

    // Calculate the distance between the center of the paddle 
    // and the center of the ball on the y axis
    qreal dy = (p->y() + p_h / 2) - (this->y() + b_h / 2); 

    // We divide the distance with half of the paddle's height
    // in order to normalize it, so norm_dy will always be between
    // -1 and 1
    qreal norm_dy = dy / (p_h / 2); 

    // We get the new ball angle by multiplying the
    // maximum angle with the normalized distance
    qreal max_angle = Config::get<qreal>("max_bounce_angle");
    qreal new_angle = norm_dy * max_angle;

    // In case the new angle is somehow (it can very easily happen)
    // higher than the max angle, set it to the max angle
    if (new_angle > max_angle) {
        new_angle = max_angle;
    }

    // Convert the new angle in radians
    new_angle = new_angle * (M_PI / 180);

    // Calculate the new ball velocity on each axis
    qreal ball_speed = Config::get<qreal>("ball_speed");
    qreal direction = p->x() > 0 ? -1 : 1;
    vx = direction * ball_speed * qCos(new_angle);
    vy = ball_speed * -qSin(new_angle);
}
