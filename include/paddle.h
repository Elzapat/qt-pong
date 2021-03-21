#ifndef PADDLE_H
#define PADDLE_H

#include <QtWidgets>
#include <QTimer>
#include <QDataStream>
#include "config.h"

class Paddle : public QObject, public QGraphicsRectItem {
    Q_OBJECT

    public:
        Paddle(qreal x, qreal y);
        ~Paddle();
        void set_pos(qreal x, qreal y);

    private:
};

#endif
