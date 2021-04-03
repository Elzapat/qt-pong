#include "../include/paddle.h"

Paddle::Paddle() : QGraphicsRectItem(
        0, 0,
        Config::get<quint16>("paddle_width"),
        Config::get<quint16>("paddle_height")
) {
    this->setBrush(Config::get<QColor>("paddle_color"));
}

Paddle::~Paddle() {}

void Paddle::update_new_config() {
    quint16 paddle_width = Config::get<quint16>("paddle_width");
    quint16 paddle_height = Config::get<quint16>("paddle_height");
    quint16 paddle_spacing = Config::get<quint16>("paddle_spacing");
    quint16 board_width = Config::get<quint16>("board_width");
    quint16 board_height = Config::get<quint16>("board_height");

    this->setRect(0, 0, paddle_width, paddle_height);
    if (this->x() < 0)
        this->setX(-board_width / 2 + paddle_spacing);
    else
        this->setX(board_width / 2 - paddle_spacing);
}

void Paddle::color_changed() {
    this->setBrush(Config::get<QColor>("paddle_color"));
}
