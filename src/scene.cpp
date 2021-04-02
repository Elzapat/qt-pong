#include "../include/scene.h"

Scene::Scene(QObject* parent) : QGraphicsScene(parent), game_paused(false), background_image_set(false) {
    // Setting the background to black
    this->setBackgroundBrush(Qt::black);

    // Loading and playing background music
    music_player.setMedia(QUrl::fromLocalFile(
        QFileInfo("assets/audio/pong3.wav").absoluteFilePath()
    ));
    music_player.play();

    // Instanciating the game objects
    ball = new Ball;
    ball->reset(static_cast<PlayerPosition>(QRandomGenerator::global()->bounded(0, 2) - 1));
    p1 = new Player(PlayerPosition::Left);
    p2 = new Player(PlayerPosition::Right);

    // Creating the middle line
    middle_line = new QGraphicsLineItem;
    setup_middle_line();
    
    pause_text = new QGraphicsTextItem;
    setup_text(pause_text, "PAUSE");
    pause_text->hide();

    win_text = new QGraphicsTextItem;
    setup_text(win_text, "Player 1 won!");
    win_text->hide();

    // Adding the game objects to the scene
    this->addItem(p1->get_paddle());
    this->addItem(p2->get_paddle());
    this->addItem(p1->get_score_text());
    this->addItem(p2->get_score_text());
    this->addItem(middle_line);
    this->addItem(ball);
    this->addItem(pause_text);
    this->addItem(win_text);

    // Timer which is going to update every game object each frame
    update_timer = new QTimer(this);
    this->connect(update_timer, SIGNAL(timeout()), this, SLOT(update()));
    update_timer->start((1.f / Config::get<qreal>("fps")) * 1000.f);

    // Connect to the signal the ball emits when a player scores
    this->connect(ball, SIGNAL(player_scored(quint8)), this, SLOT(player_scored(quint8)));
}

Scene::~Scene() {
    delete update_timer;
    delete ball;
    delete p1;
    delete p2;
    delete pause_text;
    delete middle_line;
    delete pause_text;
    delete win_text;
}

void Scene::update() {
    if (game_paused) return;

    ball->move();
    ball->collision(p1->get_paddle(), p2->get_paddle());
    p1->update();
    p2->update();

    quint16 b_w = Config::get<quint16>("board_width");
    quint16 b_h = Config::get<quint16>("board_height");
    QGraphicsScene::update(-b_w / 2, -b_h / 2, b_w, b_h);
}

void Scene::player_scored(quint8 player) {
    quint16 score_to_win = Config::get<quint16>("score_to_win");
    if (player == 1) {
        p1->scored(); 
        ball->reset(PlayerPosition::Left);
        if (p1->get_score() >= score_to_win)
            player_won(player);
    } else {
        p2->scored();
        ball->reset(PlayerPosition::Right);
        if (p2->get_score() >= score_to_win)
            player_won(player);
    }
}

void Scene::resize_event() {
    p1->update_paddle();
    p2->update_paddle();
    p1->update_score_text();
    p2->update_score_text();
    update_middle_line();
    update_background_image();
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
                if (!ball->is_moving()) {
                    win_text->hide();
                    ball->reset(PlayerPosition::Default);
                    ball->launch();
                }
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

void Scene::setup_text(QGraphicsTextItem* text, QString content) {
    int id = QFontDatabase::addApplicationFont("assets/fonts/bit5x5.ttf");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont font(family);

    quint16 text_size = Config::get<quint16>("text_size");

    text->setFont(font);
    text->setPlainText(content);
    text->setScale(text_size);

    QRectF rect = text->boundingRect();
    text->setPos((-rect.width() / 2) * text_size, (-rect.height() / 2) * text_size);
}

void Scene::drawBackground(QPainter* painter, const QRectF& rect) {
    quint16 b_w = Config::get<quint16>("board_width");
    quint16 b_h = Config::get<quint16>("board_height");

    if (!background_image_set) {
        painter->setBrush((QBrush)Qt::black);
        painter->drawRect(-b_w / 2 - 5, -b_h / 2 - 5, b_w + 10, b_h + 10);
    } else {
        QRectF source(0.0, 0.0, background_image.width(), background_image.height());
        QRectF target(-b_w / 2, -b_h / 2, b_w, b_h);
        painter->drawPixmap(target, background_image, source);
    }
}

void Scene::set_background_image() {
    QString filename = QFileDialog::getOpenFileName(nullptr, tr("Open Image"),
            "", tr("Image Files (*.png *.jpg *.bmp)"));
    if (filename.isEmpty()) return;

    background_image.load(filename);
    background_image_set = true;
    update_background_image();
}

void Scene::remove_background_image() {
    background_image_set = false;

    quint16 b_w = Config::get<quint16>("board_width");
    quint16 b_h = Config::get<quint16>("board_height");
    QGraphicsScene::update(-b_w / 2, -b_h / 2, b_w, b_h);
}

void Scene::update_background_image() {
    if (!background_image_set) return;

    quint16 b_w = Config::get<quint16>("board_width");
    quint16 b_h = Config::get<quint16>("board_height");
    background_image = background_image.scaled(b_w, b_h, Qt::KeepAspectRatio);
}

void Scene::update_new_config() {
    quint16 b_w = Config::get<quint16>("board_width");
    quint16 b_h = Config::get<quint16>("board_height");

    ball->update_new_config();
    p1->update_new_config();
    p2->update_new_config();
    update_timer->start((1.f / Config::get<qreal>("fps")) * 1000.f);
    pause_text->setScale(Config::get<qreal>("text_size"));
    win_text->setScale(Config::get<qreal>("text_size"));
    QGraphicsScene::update(-b_w / 2, -b_h / 2, b_w, b_h);
}

void Scene::player_won(quint8 player) {
    QString text = "Player " + QString::number(player) + " won!";
    win_text->setPlainText(tr(text.toStdString().c_str()));
    win_text->show();
    p1->set_score(0);
    p2->set_score(0);
}
