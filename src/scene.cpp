#include "../include/scene.h"

Scene::Scene(QObject* parent) :
        QGraphicsScene(parent),
        game_paused(false),
        background_image_set(false),
        multiplayer_game(nullptr) {
    // Setting the background to black
    this->setBackgroundBrush(Qt::black);

    // Initialize the background music
    QString nb = QRandomGenerator::global()->bounded(0, 2) ? "3" : "5";
    background_music.setSource(QUrl::fromLocalFile("assets/audio/pong" + nb + ".wav"));
    background_music.setLoopCount(QSoundEffect::Infinite);
    background_music.setVolume(Config::get<qreal>("music_volume", "audio") / 100.0);
    background_music.play();

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

    // Place a text on the top right hand corner indicating player 1
    p1_text = new QGraphicsTextItem;
    setup_text(p1_text, "P1");
    update_player_text(p1_text, 1);

    // Place a text on the top right hand corner indicating player 2
    p2_text = new QGraphicsTextItem;
    setup_text(p2_text, "P2");
    update_player_text(p2_text, 2);

    // Adding the game objects to the scene
    this->addItem(p1->get_paddle());
    this->addItem(p2->get_paddle());
    this->addItem(p1->get_score_text());
    this->addItem(p2->get_score_text());
    this->addItem(middle_line);
    this->addItem(ball);
    this->addItem(pause_text);
    this->addItem(win_text);
    this->addItem(p1_text);
    this->addItem(p2_text);

    // Timer which is going to update every game object each frame
    update_timer = new QTimer(this);
    this->connect(update_timer, SIGNAL(timeout()), this, SLOT(update()));
    update_timer->start((1.f / Config::get<qreal>("fps")) * 1000.f);

    // Connect to the signal the ball emits when a player scores
    this->connect(ball, SIGNAL(player_scored(int)), this, SLOT(player_scored(int)));

    // When the ball bounces off a paddle, we notify player 2
    // Only used when player 2 is a computer, the purpose of the SIGNAL/SLOT
    // is the compute the goal of the computer paddle
    // If the ball bounced off the player 2's paddle, just set its goal to 0;0
    this->connect(ball, &Ball::ball_bounce_paddle, p2, [this](QPointF p, qreal a, int player) {
        if (!p2->get_is_computer()) return;
        if (player == 2) p2->set_goal(0.f);
        else p2->calculate_goal(p, a);
    });
}

Scene::~Scene() {
    delete update_timer;
    delete ball;
    delete p1;
    delete p2;
    delete pause_text;
    delete middle_line;
    delete p1_text;
    delete p2_text;
    delete win_text;
}

void Scene::update() {
    if (game_paused || multiplayer_game != nullptr) return;

    ball->move();
    ball->collision(p1->get_paddle(), p2->get_paddle());
    p1->update(ball->y());
    p2->update(ball->y());

    quint16 b_w = Config::get<quint16>("board_width");
    quint16 b_h = Config::get<quint16>("board_height");
    QGraphicsScene::update(-b_w / 2, -b_h / 2, b_w, b_h);
}

void Scene::player_scored(int player) {
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
    if (multiplayer_game != nullptr) {
        p1->multiplayer_resize();
        p2->multiplayer_resize();
        ball->multiplayer_resize();
    }
        
    p1->update_paddle();
    p2->update_paddle();
    p1->update_score_text();
    p2->update_score_text();
    update_player_text(p1_text, 1);
    update_player_text(p2_text, 2);
    update_middle_line();
    update_background_image();
    ball->reset(PlayerPosition::Default);
}

void Scene::keyPressEvent(QKeyEvent* event) {
    if (event->isAutoRepeat()) return;

    int pressed_key = event->key();

    if (pressed_key == Config::get<int>("fullscreen", "controls")) {
        emit fullscreen();
        return;
    }

    if (multiplayer_game != nullptr) {
        multiplayer_game->key_event(pressed_key, "down");
        return;
    }

    if (!game_paused) {
        if (pressed_key == Config::get<int>("player_1_up", "controls"))
            p1->set_up_pressed(true);
        else if (pressed_key == Config::get<int>("player_1_down", "controls"))
            p1->set_down_pressed(true);
        else if (pressed_key == Config::get<int>("player_2_up", "controls"))
            p2->set_up_pressed(true);
        else if (pressed_key == Config::get<int>("player_2_down", "controls"))
            p2->set_down_pressed(true);
        else if (pressed_key == Config::get<int>("launch_ball", "controls")) {
            if (!ball->get_is_moving()) {
                win_text->hide();
                ball->reset(PlayerPosition::Default);
                ball->launch();
            }
        } else if (pressed_key == Config::get<int>("pause", "controls")) {
            pause_text->show();
            game_paused = true;
        }
    } else if (pressed_key == Config::get<int>("pause", "controls")) {
        pause_text->hide();
        game_paused = false;
    }
}

void Scene::keyReleaseEvent(QKeyEvent * event) {
    if (event->isAutoRepeat()) return;

    int pressed_key = event->key();
    
    if (multiplayer_game != nullptr) {
        multiplayer_game->key_event(pressed_key, "up");
        return;
    }

    if (pressed_key == Config::get<int>("player_1_up", "controls"))
        p1->set_up_pressed(false);
    else if (pressed_key == Config::get<int>("player_1_down", "controls"))
        p1->set_down_pressed(false);
    else if (pressed_key == Config::get<int>("player_2_up", "controls"))
        p2->set_up_pressed(false);
    else if (pressed_key == Config::get<int>("player_2_down", "controls"))
        p2->set_down_pressed(false);
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
    // Update the middle line in case of a window resize
    quint16 b_h = Config::get<quint16>("board_height");
    middle_line->setLine(-10, -b_h, -10, b_h);
}

void Scene::setup_text(QGraphicsTextItem* text, QString content) {
    // Create a text with the specified parameter
    int id = QFontDatabase::addApplicationFont("assets/fonts/bit5x5.ttf");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont font(family);

    quint16 text_size = Config::get<quint16>("text_size");

    text->setFont(font);
    text->setPlainText(content);
    text->setScale(text_size);
    text->setDefaultTextColor(Config::get<QColor>("text_color"));

    QRectF rect = text->boundingRect();
    text->setPos((-rect.width() / 2) * text_size, (-rect.height() / 2) * text_size);
}

void Scene::update_text(QGraphicsTextItem* text) {
    // Update the text in case of a configuration change
    quint16 text_size = Config::get<quint16>("text_size");
    text->setScale(text_size);
    QRectF rect = text->boundingRect();
    text->setPos((-rect.width() / 2) * text_size, (-rect.height() / 2) * text_size);
}

void Scene::drawBackground(QPainter* painter, const QRectF& rect) {
    quint16 b_w = Config::get<quint16>("board_width");
    quint16 b_h = Config::get<quint16>("board_height");

    if (!background_image_set) {
        // If there is no background image, draw a back background
        painter->setBrush((QBrush)Qt::black);
        painter->drawRect(-b_w / 2 - 5, -b_h / 2 - 5, b_w + 10, b_h + 10);
    } else {
        // If there is a background image, fit it to the screen
        QRectF source(0.0, 0.0, background_image.width(), background_image.height());
        QRectF target(-b_w / 2, -b_h / 2, b_w, b_h);
        painter->drawPixmap(target, background_image, source);
    }
}

void Scene::set_background_image() {
    // Get an image to put in the background
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

    // Update all the game objects because the configuration changed
    ball->update_new_config();
    p1->update_new_config();
    p2->update_new_config();
    update_timer->start((1.f / Config::get<qreal>("fps")) * 1000.f);
    update_text(pause_text);
    update_text(win_text);
    update_player_text(p1_text, 1);
    update_player_text(p2_text, 2);
    QGraphicsScene::update(-b_w / 2, -b_h / 2, b_w, b_h);
}

void Scene::player_won(int player) {
    // Display the player who won on the screen and reset the scores
    QString text = "Player " + QString::number(player) + " won!";
    win_text->setPlainText(text);
    win_text->show();
    p1->set_score(0);
    p2->set_score(0);

    // If the game is multiplayer, hide the text after 3 seconds
    // because the ball launch that normally hides it is serverside
    if (multiplayer_game != nullptr)
        QTimer::singleShot(3000, [this] { win_text->hide(); });
}

void Scene::focusOutEvent(QFocusEvent* event) {
    // When the scene loses focus, stop the paddles from moving further
    p1->set_up_pressed(false);
    p1->set_down_pressed(false);
    p2->set_up_pressed(false);
    p2->set_down_pressed(false);
}

void Scene::music_volume_changed(qreal volume) {
    background_music.setVolume(volume);
}

Ball* Scene::get_ball() const {
    return ball;
}

Player* Scene::get_player_2() const {
    return p2;
}

void Scene::color_changed() {
    QColor text_color = Config::get<QColor>("text_color");
    pause_text->setDefaultTextColor(text_color);
    win_text->setDefaultTextColor(text_color);
    p1_text->setDefaultTextColor(text_color);
    p2_text->setDefaultTextColor(text_color);

    ball->color_changed();
    p1->color_changed();
    p2->color_changed();
}

void Scene::start_multiplayer_game(QTcpSocket* server) {
    if (game_paused) {
        pause_text->hide();
        game_paused = false;
    }

    multiplayer_game = new MultiplayerGame(server);

    // If the player 2 is currently a computer, change the CP text to P2
    if (p2->get_is_computer())
        p2_text->setPlainText("P2");

    // Reconfigure the game to a blank game
    Config::reset_to_default();
    update_new_config();
    color_changed();
    resize_event();
    p1->set_score(0);
    p2->set_score(0);

    this->connect(multiplayer_game, SIGNAL(multiplayer_ball_move(qreal, qreal)), this, SLOT(multiplayer_ball_move(qreal, qreal)));
    this->connect(multiplayer_game, SIGNAL(multiplayer_player_move(int, qreal, qreal)), this, SLOT(multiplayer_player_move(int, qreal, qreal)));
    this->connect(multiplayer_game, SIGNAL(multiplayer_score(int)), this, SLOT(multiplayer_score(int)));
    this->connect(multiplayer_game, SIGNAL(multiplayer_player_won(int)), this, SLOT(multiplayer_player_won(int)));
    this->connect(multiplayer_game, SIGNAL(multiplayer_game_end()), this, SLOT(multiplayer_game_end()));

    // Two seconds after game start, color the paddle of the player yellow
    QTimer::singleShot(2000, [this] {
        if (multiplayer_game == nullptr) return;
        if (multiplayer_game->get_side() == 1) {
            p1->get_paddle()->set_color(QColor("#FFFF00"));
            p1_text->setDefaultTextColor(QColor("#FFFF00"));
        } else if (multiplayer_game->get_side() == 2) {
            p2->get_paddle()->set_color(QColor("#FFFF00"));
            p2_text->setDefaultTextColor(QColor("#FFFF00"));
        }
    });

    // Enable the ability to disconnect from the window menus
    emit enable_disconnect();
}

void Scene::multiplayer_ball_move(qreal x, qreal y) {
    x *= Config::get<qreal>("board_width") / 1920.f;
    y *= Config::get<qreal>("board_height") / 1080.f;
    ball->setPos(x, y); 
}

void Scene::multiplayer_player_move(int player, qreal x, qreal y) {
    x *= Config::get<qreal>("board_width") / 1920.f;
    y *= Config::get<qreal>("board_height") / 1080.f;

    if (player == 1)
        p1->get_paddle()->setPos(x, y);
    else if (player == 2)
        p2->get_paddle()->setPos(x, y);
}

void Scene::multiplayer_score(int player) {
    if (player == 1)
        p1->scored();
    else if (player == 2)
        p2->scored();
}

void Scene::multiplayer_player_won(int player) {
    player_won(player);
}

void Scene::multiplayer_game_end() {
    // Disable the ability to disconnect from the game
    emit disable_disconnect();

    delete multiplayer_game;
    multiplayer_game = nullptr;

    // Reconfigure the game to not multiplayer
    Config::reset_to_default();
    update_new_config();
    color_changed();

    p1->set_score(0);
    p2->set_score(0);
    // ball->reset();

    // If the player 2 was a computer before the multiplayer game starting, set
    // the CP tag back
    if (p2->get_is_computer())
        p2_text->setPlainText("CP");
}

bool Scene::is_multiplayer() {
    return multiplayer_game != nullptr;
}

MultiplayerGame* Scene::get_multiplayer_game() const {
    return multiplayer_game;
}

void Scene::update_player_text(QGraphicsTextItem* text, int player) {
    qreal scale = Config::get<qreal>("text_size") / 3.f;
    text->setScale(scale);

    const qreal SPACING = 2.f;
    qreal x;
    if (player == 1)
        x = -Config::get<qreal>("board_width") / 2.f + SPACING;
    else
        x = Config::get<qreal>("board_width") / 2.f //- SPACING
                - text->boundingRect().width() * scale;
        
    text->setPos(x, -Config::get<qreal>("board_height") / 2.f + SPACING);
}

void Scene::set_p2_computer() {
    if (multiplayer_game != nullptr)
        return;

    p2->set_computer();
    p2_text->setPlainText(p2->get_is_computer() ? "CP" : "P2");
}
