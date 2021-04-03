#ifndef SCENE_H
#define SCENE_H

#include <QtWidgets>
#include <QRandomGenerator>
#include <QSoundEffect>
#include "config.h"
#include "ball.h"
#include "player.h"

class Scene : public QGraphicsScene {
    Q_OBJECT

    public:
        explicit Scene(QObject* parent = 0);
        ~Scene();
        Ball* get_ball();
        void resize_event();
        void keyPressEvent(QKeyEvent* event) override;
        void keyReleaseEvent(QKeyEvent* event) override;
        void drawBackground(QPainter* painter, const QRectF& rect) override;
        void focusOutEvent(QFocusEvent* event) override;

    public slots:
        void update();
        void player_scored(quint8 player);
        void set_background_image();
        void remove_background_image();
        void update_new_config();
        void color_changed();
        void music_volume_changed(qreal volume);

    private:
        QTimer* update_timer;
        Ball* ball;
        Player* p1;
        Player* p2;
        bool game_paused;
        QGraphicsTextItem* pause_text;
        QGraphicsTextItem* win_text;
        QGraphicsLineItem* middle_line;
        QPixmap background_image;
        bool background_image_set;
        QSoundEffect background_music;
        void setup_middle_line();
        void setup_text(QGraphicsTextItem* text, QString content);
        void update_middle_line();
        void update_background_image();
        void player_won(quint8 player);
};

#endif // SCENE_H
