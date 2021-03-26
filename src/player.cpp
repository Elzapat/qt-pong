#include "../include/player.h"

Player::Player(PlayerPosition pos, bool computer) : is_computer(computer),
    up_pressed(false), down_pressed(false), m_position(pos), score(0) {

    m_paddle = new Paddle();
    update_paddle();

    m_score_text = new QGraphicsTextItem(QString::number(score));
    setup_score_text();
}

Player::~Player() {
    delete m_paddle;
    delete m_score_text;
}

void Player::update_paddle() {
    quint16 p_h = Config::get<quint16>("paddle_height");
    quint16 p_s = Config::get<quint16>("paddle_spacing");
    quint16 b_w = Config::get<quint16>("board_width");

    if (m_position == PlayerPosition::Left)
        m_paddle->setPos(-b_w / 2 + p_s, m_paddle->y());
    else if (m_position == PlayerPosition::Right)
        m_paddle->setPos(b_w / 2 - p_s, m_paddle->y());
}

Paddle* Player::paddle() const {
    return m_paddle;
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
        m_paddle->setY(m_paddle->y() - paddle_speed * dt);
    else if (down_pressed)
        m_paddle->setY(m_paddle->y() + paddle_speed * dt);

    // If the paddle has gone out of the board's limits, bring it back
    quint16 p_h = Config::get<quint16>("paddle_height");
    quint16 b_h = Config::get<quint16>("board_height");
    if (m_paddle->y() < -b_h / 2)
        m_paddle->setY(-b_h / 2);
    else if (m_paddle->y() + p_h > b_h / 2)
        m_paddle->setY(b_h / 2 - p_h);
}

void Player::setup_score_text() {
    int id = QFontDatabase::addApplicationFont("assets/fonts/bit5x3.ttf");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont font(family);

    m_score_text->setDefaultTextColor(Qt::lightGray);
    m_score_text->setFont(font);

    update_score_text();
}

void Player::update_score_text() {
    quint16 text_size = Config::get<quint16>("score_text_size");
    quint16 board_width = Config::get<quint16>("board_width");
    quint16 board_height = Config::get<quint16>("board_height");
    qreal text_width = m_score_text->boundingRect().width();
    qreal text_height = m_score_text->boundingRect().width();

    m_score_text->setScale(text_size);

    if (m_position == PlayerPosition::Left)
        m_score_text->setPos(-board_width / 4 - (text_width / 2) * text_size, 
                -board_height / 4);
    else if (m_position == PlayerPosition::Right)
        m_score_text->setPos(board_width / 4 - (text_width / 2) * text_size,
                -board_height / 4);
}

QGraphicsTextItem* Player::score_text() const {
    return m_score_text;
}

void Player::scored() {
    score++;
    m_score_text->setPlainText(QString::number(score));
    update_score_text();
}

void Player::update_new_config() {
    update_paddle();
    update_score_text();
    m_paddle->update_new_config();
}
