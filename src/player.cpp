#include "../include/player.h"

Player::Player(PlayerPosition pos, bool computer) : is_computer(computer),
    up_pressed(false), down_pressed(false), position(pos), score(0) {

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
    up_pressed = is_pressed;
} 

void Player::set_down_pressed(bool is_pressed) {
    down_pressed = is_pressed;
}

void Player::update() {
    qreal paddle_speed = Config::get<qreal>("paddle_speed");
    qreal dt = 1.f / Config::get<qreal>("fps");

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

    score_text->setDefaultTextColor(Qt::lightGray);
    score_text->setFont(font);

    update_score_text();
}

void Player::update_score_text() {
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
    score_text->setPlainText(QString::number(score));
    update_score_text();
}

void Player::color_changed() {
    paddle->color_changed();
    score_text->setDefaultTextColor(Config::get<QColor>("text_color"));
}
