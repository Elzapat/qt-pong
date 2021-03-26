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
        void drawBackground(QPainter* painter, const QRectF& rect) override;

    public slots:
        void update();
        void player_scored(quint8 player);
        void set_background_image();
        void remove_background_image();
        void update_new_config();

    private:
        QTimer* update_timer;
        Ball* ball;
        Player* p1;
        Player* p2;
        bool game_paused;
        QGraphicsTextItem* pause_text;
        QGraphicsLineItem* middle_line;
        QPixmap background_image;
        bool background_image_set;
        void setup_middle_line();
        void setup_pause_text();
        void update_middle_line();
        void update_background_image();
};

#endif

