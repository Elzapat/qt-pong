#include "../include/ball.h"

Ball::Ball() : vx(0.f), vy(0.f), is_moving(false), ball_speed(Config::get<qreal>("ball_speed")),
    QGraphicsRectItem(
        0, 0,
        Config::get<quint16>("ball_width"),
        Config::get<quint16>("ball_height")
) {
    this->setBrush(Config::get<QColor>("ball_color"));

    // Initialize the sound effects
    qreal sfx_volume = Config::get<qreal>("sfx_volume", "audio") / 100.0;
    ball_bounce_sfx.setSource(QUrl::fromLocalFile("assets/audio/ball_bounce.wav"));
    point_scored_sfx.setSource(QUrl::fromLocalFile("assets/audio/point_scored.wav"));
    ball_bounce_sfx.setVolume(sfx_volume);
    point_scored_sfx.setVolume(sfx_volume);
}

Ball::~Ball() {}

void Ball::move() {
    if (!is_moving) return;

    // Time passed since last frame
    const qreal dt = 1.f / Config::get<qreal>("fps");

    // Update the ball's coordinates depending on its velocity
    qreal dx = vx * dt;
    qreal dy = vy * dt;

    this->setPos(this->x() + dx, this->y() + dy);
}

void Ball::collision(Paddle* p1, Paddle* p2) {
    if (!is_moving) return;

    quint16 board_w = Config::get<quint16>("board_width");
    quint16 board_h = Config::get<quint16>("board_height");
    quint16 ball_w = Config::get<quint16>("ball_width");
    quint16 ball_h = Config::get<quint16>("ball_height");

    // Check if the ball is colliding with any of the two player paddles
    // If so, send it back with a different angle depending
    // on where the ball collided with the paddle
    if (this->collidesWithItem(p1))
        generate_new_angle(p1, 1);
    else if (this->collidesWithItem(p2))
        generate_new_angle(p2, 2);

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
    if (this->x() <= -board_w / 2) {
        point_scored_sfx.play();
        emit player_scored(2);
    } else if (this->x() + ball_w >= board_w / 2) {
        point_scored_sfx.play();
        emit player_scored(1);
    }
}

void Ball::generate_new_angle(Paddle* p, int player) {
    // Play the Ball Bounce sound effect
    ball_bounce_sfx.play();

    // Speed up the ball by a certain rate in percent
    // qreal ball_speed = Config::get<qreal>("ball_speed");
    qreal speed_up_rate = Config::get<qreal>("ball_speed_up_rate");

    ball_speed += (ball_speed / 100) * speed_up_rate;

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
    if (new_angle > max_angle)
        new_angle = max_angle;
    else if (new_angle < -max_angle)
        new_angle = -max_angle;

    // Convert the new angle in radians
    new_angle = new_angle * (M_PI / 180);

    // Calculate the new ball velocity on each axis
    qreal direction = p->x() > 0 ? -1 : 1;
    vx = direction * ball_speed * qCos(new_angle);
    vy = ball_speed * -qSin(new_angle);

    emit ball_bounce_paddle(this->pos(), new_angle, player);
}

void Ball::reset(PlayerPosition new_side) {
    is_moving = false;
    if (new_side != PlayerPosition::Default)
        side = new_side;

    ball_speed = Config::get<qreal>("ball_speed");
    quint16 board_w = Config::get<quint16>("board_width");
    quint16 ball_h = Config::get<quint16>("ball_height");
    quint16 paddle_spacing = Config::get<quint16>("paddle_spacing");

    if (side == PlayerPosition::Left)
        this->setPos(-board_w / 2 + paddle_spacing + 100, -ball_h / 2);
    else
        this->setPos(board_w / 2 - paddle_spacing - 100, -ball_h / 2);
}

void Ball::launch() {
    ball_speed = Config::get<qreal>("ball_speed");
    base_speed = ball_speed;
    qreal max_angle = Config::get<qreal>("max_bounce_angle");

    qreal random_angle = QRandomGenerator::global()->bounded(0, 2 * max_angle) - max_angle;
    random_angle = random_angle * (M_PI / 180);

    qint8 dir = side == PlayerPosition::Left ? 1 : -1;

    vx = dir * ball_speed * qCos(random_angle);
    vy = ball_speed * -qSin(random_angle);
    is_moving = true;

    int player = side == PlayerPosition::Left ? 1 : 2;
    emit ball_bounce_paddle(this->pos(), random_angle, player);
}

bool Ball::get_is_moving() const {
    return is_moving;
}

void Ball::update_new_config() {
    quint16 ball_width = Config::get<quint16>("ball_width");
    quint16 ball_height = Config::get<quint16>("ball_height");
    quint16 new_ball_speed = Config::get<qreal>("ball_speed");

    this->setRect(0, 0, ball_width, ball_height);

    if (new_ball_speed != base_speed) {
        qreal ratio = new_ball_speed / base_speed;
        vx *= ratio;
        vy *= ratio;
        base_speed = new_ball_speed;
        ball_speed = new_ball_speed;
    }

    if (!is_moving) reset();
}

void Ball::sfx_volume_changed(qreal volume) {
    ball_bounce_sfx.setVolume(volume);
    point_scored_sfx.setVolume(volume);
}

void Ball::color_changed() {
    this->setBrush(Config::get<QColor>("ball_color"));
}
