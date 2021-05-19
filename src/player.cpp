#include "../include/player.h"

Player::Player(PlayerPosition pos, bool computer) : is_computer(computer),
    up_pressed(false), down_pressed(false), position(pos), score(0), goal(0.f) {

    paddle = new Paddle();
    update_paddle();

    score_text = new QGraphicsTextItem(QString::number(score));
    setup_score_text();
}

Player::~Player() {
    delete paddle;
    delete score_text;
}

void Player::update_paddle() {
    quint16 p_h = Config::get<quint16>("paddle_height");
    quint16 p_s = Config::get<quint16>("paddle_spacing");
    quint16 b_w = Config::get<quint16>("board_width");

    if (position == PlayerPosition::Left)
        paddle->setPos(-b_w / 2 + p_s, paddle->y());
    else if (position == PlayerPosition::Right)
        paddle->setPos(b_w / 2 - p_s, paddle->y());
}

Paddle* Player::get_paddle() const {
    return paddle;
}

void Player::set_up_pressed(bool is_pressed) {
    // If this player is a computer, we don't take user input
    if (!is_computer) up_pressed = is_pressed;
} 

void Player::set_down_pressed(bool is_pressed) {
    // If this player is a computer, we don't take user input
    if (!is_computer) down_pressed = is_pressed;
}

void Player::update(qreal ball_y) {
    qreal paddle_speed = Config::get<qreal>("paddle_speed");
    qreal dt = 1.f / Config::get<qreal>("fps");

    // If the player is a computer, we make it go towards the goal
    if (is_computer) {
        qreal paddle_height = Config::get<qreal>("paddle_height");
        qreal distance = paddle_speed * dt;
        qreal paddle_middle_y = paddle->y() + paddle_height / 2.f;
        if (goal > paddle_middle_y - 4 * distance &&
                goal < paddle_middle_y + 4 * distance) {
            // up_pressed = down_pressed = false;
            up_pressed = false;
            down_pressed = false;
        } else if (goal < paddle_middle_y) {
            up_pressed = true;
            down_pressed = false;
        } else {
            up_pressed = false;
            down_pressed = true;
        }
    }

    // Update the paddle's position if the player is pressing the correct key
    if (up_pressed)
        paddle->setY(paddle->y() - paddle_speed * dt);
    else if (down_pressed)
        paddle->setY(paddle->y() + paddle_speed * dt);

    // If the paddle has gone out of the board's limits, bring it back
    quint16 p_h = Config::get<quint16>("paddle_height");
    quint16 b_h = Config::get<quint16>("board_height");
    if (paddle->y() < -b_h / 2)
        paddle->setY(-b_h / 2);
    else if (paddle->y() + p_h > b_h / 2)
        paddle->setY(b_h / 2 - p_h);
}

void Player::setup_score_text() {
    int id = QFontDatabase::addApplicationFont("assets/fonts/bit5x3.ttf");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont font(family);

    score_text->setDefaultTextColor(Config::get<QColor>("text_color"));
    score_text->setFont(font);

    update_score_text();
}

void Player::update_score_text() {
    // Update the score text with the new configuration
    quint16 text_size = Config::get<quint16>("text_size");
    quint16 board_width = Config::get<quint16>("board_width");
    quint16 board_height = Config::get<quint16>("board_height");
    qreal text_width = score_text->boundingRect().width();
    qreal text_height = score_text->boundingRect().width();

    score_text->setScale(text_size);

    if (position == PlayerPosition::Left)
        score_text->setPos(-board_width / 4 - (text_width / 2) * text_size, 
                -board_height / 4);
    else if (position == PlayerPosition::Right)
        score_text->setPos(board_width / 4 - (text_width / 2) * text_size,
                -board_height / 4);
}

QGraphicsTextItem* Player::get_score_text() const {
    return score_text;
}

void Player::scored() {
    // This player has scored
    score++;
    score_text->setPlainText(QString::number(score));
    update_score_text();
}

void Player::update_new_config() {
    update_paddle();
    update_score_text();
    paddle->update_new_config();
}

quint16 Player::get_score() const {
    return score;
}

void Player::set_score(quint16 new_score) {
    score = new_score;
    // Set the score text to the new score;
    score_text->setPlainText(QString::number(score));
    update_score_text();
}

void Player::color_changed() {
    // Set score text color to new color
    paddle->color_changed();
    score_text->setDefaultTextColor(Config::get<QColor>("text_color"));
}

void Player::set_computer() {
    // If the player is a computer, not anymore, and if it's
    // not, it now is
    is_computer = !is_computer;
}

void Player::calculate_goal(QPointF ball_pos, qreal ball_angle) {
    qreal board_height = Config::get<qreal>("board_height");
    qreal start_x = ball_pos.x(), start_y = ball_pos.y();
    qreal a = qTan(ball_angle), b;

    do {
        // Invert a because when the ball hits the side of
        // the board it bounces but keeps the same angle,
        // just opposite
        a = -a;
        // Calculate the trajectory of the ball
        // a is the coefficient of the linear function 
        // and b is the offset of the linear function
        b = start_y - (a * start_x);

        start_y = a < 0 ? -board_height / 2.f : board_height / 2.f;
        // The x coordinate of the ball when it's next going to hit the
        // top or bottom of the board
        start_x = (start_y - b) / a;

        // We continue doing this until the point the ball will hit
        // is behind the paddle
    } while (start_x < paddle->x());

    // The y coordinate where the ball will reach the x of the paddle
    goal = a * paddle->x() + b;
}

void Player::set_goal(qreal new_goal) {
    goal = new_goal;
}

bool Player::get_is_computer() const {
    return is_computer;
}

void Player::multiplayer_resize() {
    Config::set("paddle_width", 10.f * (Config::get<qreal>("board_width")) / 1920.f);
    Config::set("paddle_height", 100.f * (Config::get<qreal>("board_height")) / 1079.f);
    update_new_config();
}
