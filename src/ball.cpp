#include "../include/ball.h"

Ball::Ball() : vx(0.f), vy(0.f), m_is_moving(false), ball_speed(Config::get<qreal>("ball_speed")),
    QGraphicsRectItem(
        -Config::get<quint16>("ball_width") / 2,
        -Config::get<quint16>("ball_height") / 2,
        Config::get<quint16>("ball_width"),
        Config::get<quint16>("ball_height")
) {
    // Set ball color to white
    const QBrush BALL_COLOR = (QBrush)Qt::white;
    this->setBrush(BALL_COLOR);

    // ball_speed = Config::get<qreal>("ball_speed");
    // qDebug() << ball_speed;
    // qDebug() << Config::get<qreal>("ball_speed");
}

Ball::~Ball() {}

void Ball::move() {
    if (!m_is_moving) return;

    // Time passed since last frame
    const qreal dt = 1.f / Config::get<qreal>("fps");

    // Update the ball's coordinates depending on its velocity
    qreal dx = vx * dt;
    qreal dy = vy * dt;

    this->setPos(this->x() + dx, this->y() + dy);
}

void Ball::collision(Paddle* p1, Paddle* p2) {
    if (!m_is_moving) return;

    quint16 board_w = Config::get<quint16>("board_width");
    quint16 board_h = Config::get<quint16>("board_height");
    quint16 ball_w = Config::get<quint16>("ball_width");
    quint16 ball_h = Config::get<quint16>("ball_height");

    // Check if the ball is colliding with any of the two player paddles
    // If so, send it back with a different angle depending
    // on where the ball collided with the paddle
    if (this->collidesWithItem(p1))
        generate_new_angle(p1);
    else if (this->collidesWithItem(p2))
        generate_new_angle(p2);

    // Check if the ball is colliding with the top or the bottom of the board
    // If so invert its y axis velocity
    if (this->y() - ball_h / 2 <= -board_h / 2) {
        vy = -vy;
        this->setY(-board_h / 2 + ball_h / 2);
    } else if (this->y() + ball_h / 2 >= board_h / 2) {
        vy = -vy;
        this->setY(board_h / 2 - ball_h / 2);
    }

    // Check if the ball is colliding with the left or the right of the board
    // If so, the other player has scored
    if (this->x() <= -board_w / 2)
        emit player_scored(2);
    else if (this->x() + ball_w >= board_w / 2)
        emit player_scored(1);
}

void Ball::generate_new_angle(Paddle* p) {
    // Speed up the ball by a certain rate in percent
    // qreal ball_speed = Config::get<qreal>("ball_speed");
    qreal speed_up_rate = Config::get<qreal>("ball_speed_up_rate");

    ball_speed += (ball_speed / 100) * speed_up_rate;

    quint16 p_h = Config::get<quint16>("paddle_height");
    quint16 b_h = Config::get<quint16>("ball_height");

    // Calculate the distance between the center of the paddle 
    // and the center of the ball on the y axis
    qreal dy = p->y() - (this->y()); 

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
    qreal direction = p->x() > 0 ? -1 : 1;
    vx = direction * ball_speed * qCos(new_angle);
    vy = ball_speed * -qSin(new_angle);
}

void Ball::reset(PlayerPosition new_side) {
    m_is_moving = false;
    if (new_side != PlayerPosition::Default)
        side = new_side;

    ball_speed = Config::get<qreal>("ball_speed");
    quint16 board_w = Config::get<quint16>("board_width");
    quint16 ball_h = Config::get<quint16>("ball_height");
    quint16 paddle_spacing = Config::get<quint16>("paddle_spacing");

    if (side == PlayerPosition::Left)
        this->setPos(-board_w / 2 + 2 * paddle_spacing, -ball_h / 2);
    else
        this->setPos(board_w / 2 - 2 * paddle_spacing, -ball_h / 2);
}

void Ball::launch() {
    qreal ball_speed = Config::get<qreal>("ball_speed");
    qreal max_angle = Config::get<qreal>("max_bounce_angle");

    qreal random_angle = QRandomGenerator::global()->bounded(0, 2 * max_angle) - max_angle;
    random_angle = random_angle * (M_PI / 180);

    qint8 dir = side == PlayerPosition::Left ? 1 : -1;

    vx = dir * ball_speed * qCos(random_angle);
    vy = ball_speed * qSin(random_angle);
    m_is_moving = true;
}

bool Ball::is_moving() const {
    return m_is_moving;
}
