#include "../include/paddle.h"

Paddle::Paddle(qreal x, qreal y) : QGraphicsRectItem(
        x, y,
        Config::get<quint16>("paddle_width"),
        Config::get<quint16>("paddle_height")
) {
    const QBrush PADDLE_COLOR = (QBrush)Qt::white;
    this->setBrush(PADDLE_COLOR);
}

Paddle::~Paddle() {}

void Paddle::set_pos(qreal x, qreal y) {
    this->setPos(x, y);
}
