#include "../include/scene.h"

Scene::Scene(QObject* parent) : QGraphicsScene(parent), game_paused(false) {
    // Setting the background to black
    this->setBackgroundBrush(Qt::black);

    // Instanciating the game objects
    ball = new Ball;
    ball->reset(static_cast<PlayerPosition>(QRandomGenerator::global()->bounded(0, 2) - 1));
    p1 = new Player(PlayerPosition::Left);
    p2 = new Player(PlayerPosition::Right);

    // Creating the middle line
    middle_line = new QGraphicsLineItem;
    setup_middle_line();
    
    pause_text = new QGraphicsTextItem;
    setup_pause_text();

    // Adding the game objects to the scene
    this->addItem(p1->paddle());
    this->addItem(p2->paddle());
    this->addItem(p1->score_text());
    this->addItem(p2->score_text());
    this->addItem(middle_line);
    this->addItem(ball);
    this->addItem(pause_text);

    // Timer which is going to update every game object each frame
    QTimer* update_timer = new QTimer(this);
    connect(update_timer, SIGNAL(timeout()), this, SLOT(update()));
    update_timer->start((1.f / Config::get<qreal>("fps")) * 1000.f);

    // Connect to the signal the ball emits when a player scores
    connect(ball, SIGNAL(player_scored(quint8)), this, SLOT(player_scored(quint8)));

    // QGraphicsPixmapItem* qdpi = new QGraphicsPixmapItem(QPixmap("assets/images/uno.png"));
    // this->addItem(qdpi);
}

Scene::~Scene() {
    delete ball;
    delete p1;
    delete p2;
    delete middle_line;
}

void Scene::update() {
    if (game_paused) return;

    ball->move();
    ball->collision(p1->paddle(), p2->paddle());
    p1->update();
    p2->update();
}

void Scene::player_scored(quint8 player) {
    if (player == 1) {
        p1->scored(); 
        ball->reset(PlayerPosition::Left);
    } else {
        p2->scored();
        ball->reset(PlayerPosition::Right);
    }
}

void Scene::resize_event() {
    p1->update_paddle();
    p2->update_paddle();
    p1->update_score_text();
    p2->update_score_text();
    update_middle_line();
    ball->reset(PlayerPosition::Default);
}

void Scene::keyPressEvent(QKeyEvent* event) {
    if (!game_paused) {
        switch (event->key()) {
            case Qt::Key_Z:
                p1->set_up_pressed(true);
                break;
            case Qt::Key_S:
                p1->set_down_pressed(true);
                break;
            case Qt::Key_O:
                p2->set_up_pressed(true);
                break;
            case Qt::Key_L:
                p2->set_down_pressed(true);
                break;
            case Qt::Key_Space:
                if (!ball->is_moving())
                    ball->launch();
                break;
            case Qt::Key_Escape:
                pause_text->show();
                game_paused = true;
                break;
        }
    } else {
        switch (event->key()) {
            case Qt::Key_Escape:
                pause_text->hide();
                game_paused = false;
                break;
        }
    }
}

void Scene::keyReleaseEvent(QKeyEvent * event) {
    switch (event->key()) {
        case Qt::Key_Z:
            p1->set_up_pressed(false);
            break;
        case Qt::Key_S:
            p1->set_down_pressed(false);
            break;
        case Qt::Key_O:
            p2->set_up_pressed(false);
            break;
        case Qt::Key_L:
            p2->set_down_pressed(false);
    }
}

void Scene::setup_middle_line() {
    // Create a pen for the line, so it's a gray dashed line
    // that extends through the whole board
    QPen pen;

    pen.setWidth(5);
    pen.setDashPattern({ 5, 3 });
    pen.setBrush((QBrush)Qt::lightGray);

    quint16 b_h = Config::get<quint16>("board_height");
    middle_line->setLine(0, -b_h / 2, 0, b_h / 2);
    middle_line->setPen(pen);
}

void Scene::update_middle_line() {
    quint16 b_h = Config::get<quint16>("board_height");
    middle_line->setLine(-10, -b_h / 2, -10, b_h / 2);
}

void Scene::setup_pause_text() {
    int id = QFontDatabase::addApplicationFont("assets/fonts/bit5x3.ttf");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont font(family);

    quint16 text_size = Config::get<quint16>("score_text_size");

    pause_text->setFont(font);
    pause_text->setPlainText("PAUSE");
    pause_text->setScale(text_size);

    QRectF rect = pause_text->boundingRect();
    pause_text->setPos((-rect.width() / 2) * text_size, (-rect.height() / 2) * text_size);
    pause_text->hide();
}
