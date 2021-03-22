#ifndef SCENE_H
#define SCENE_H

#include <QtWidgets>
#include <QRandomGenerator>
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
        void player_scored(quint8 player);

    private:
        Ball* ball;
        Player* p1;
        Player* p2;
        bool game_paused;
        QGraphicsTextItem* pause_text;
        QGraphicsLineItem* middle_line;
        void setup_middle_line();
        void setup_pause_text();
        void update_middle_line();
};

#endif

