#ifndef SCENE_H
#define SCENE_H

#include <QtWidgets>
#include <QRandomGenerator>
#include <QSoundEffect>
#include <QTcpSocket>
#include "config.h"
#include "ball.h"
#include "player.h"
#include "multiplayer_game.h"

class Scene : public QGraphicsScene {
    Q_OBJECT

    public:
        explicit Scene(QObject* parent = 0);
        ~Scene();
        Ball* get_ball() const;
        Player* get_player_2() const;
        MultiplayerGame* get_multiplayer_game() const;
        void resize_event();
        bool is_multiplayer();
        void keyPressEvent(QKeyEvent* event) override;
        void keyReleaseEvent(QKeyEvent* event) override;
        void drawBackground(QPainter* painter, const QRectF& rect) override;
        void focusOutEvent(QFocusEvent* event) override;

    public slots:
        void update();
        void player_scored(int player);
        void set_background_image();
        void remove_background_image();
        void update_new_config();
        void color_changed();
        void music_volume_changed(qreal volume);
        void set_p2_computer();
        void start_multiplayer_game(QTcpSocket* server);
        void multiplayer_ball_move(qreal x, qreal y);
        void multiplayer_player_move(int player, qreal x, qreal y);
        void multiplayer_score(int player);
        void multiplayer_player_won(int player);
        void multiplayer_game_end();

    signals:
        void fullscreen();
        void enable_disconnect();
        void disable_disconnect();

    private:
        QTimer* update_timer;
        Ball* ball;
        Player* p1;
        Player* p2;
        MultiplayerGame* multiplayer_game;
        bool game_paused;
        QGraphicsTextItem* pause_text;
        QGraphicsTextItem* win_text;
        QGraphicsTextItem* p1_text;
        QGraphicsTextItem* p2_text;
        QGraphicsLineItem* middle_line;
        QPixmap background_image;
        bool background_image_set;
        QSoundEffect background_music;
        void setup_middle_line();
        void setup_text(QGraphicsTextItem* text, QString content);
        void update_text(QGraphicsTextItem* text);
        void update_player_text(QGraphicsTextItem* text, int player);
        void update_middle_line();
        void update_background_image();
        void player_won(int player);
};

#endif // SCENE_H
