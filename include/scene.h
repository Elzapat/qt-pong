#ifndef SCENE_H
#define SCENE_H

#include <QtWidgets>
#include "config.h"
#include "ball.h"
#include "player.h"

class Scene : public QGraphicsScene {
    Q_OBJECT

    public:
        explicit Scene(QObject* parent = 0);
        ~Scene();
        void resize_event();
        void keyPressEvent(QKeyEvent* event) override;
        void keyReleaseEvent(QKeyEvent* event) override;

    public slots:
        void update();

    private:
        Ball* ball;
        Player* p1;
        Player* p2;
        QGraphicsLineItem* middle_line;
        void setup_middle_line();
        void update_middle_line();
};

#endif

