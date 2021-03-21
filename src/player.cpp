#include "../include/player.h"

Player::Player(PlayerPosition pos, bool computer) : is_computer(computer),
    up_pressed(false), down_pressed(false), m_position(pos) {

    m_paddle = new Paddle(0, 0);
    update_position();
}

Player::~Player() {
    delete m_paddle;
}

void Player::update_position() {
    quint16 p_h = Config::get<quint16>("paddle_height");
    quint16 p_s = Config::get<quint16>("paddle_spacing");
    quint16 b_w = Config::get<quint16>("board_width");

    if (m_position == PlayerPosition::Left)
        m_paddle->set_pos(-b_w / 2 + p_s, -p_h / 2);
    else if (m_position == PlayerPosition::Right)
        m_paddle->set_pos(b_w / 2 - p_s, -p_h / 2);
}

Paddle* Player::paddle() {
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

    if (up_pressed) {
        m_paddle->setY(m_paddle->y() - paddle_speed);
    } else if (down_pressed) {
        m_paddle->setY(m_paddle->y() + paddle_speed);
    }
}
