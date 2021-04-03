#ifndef PADDLE_H
#define PADDLE_H

#include <QtWidgets>
#include <QTimer>
#include <QDataStream>
#include "config.h"

class Paddle : public QObject, public QGraphicsRectItem {
    Q_OBJECT

    public:
        Paddle();
        ~Paddle();
        void update_new_config();
        void color_changed();
};

#endif // PADDLE_H
