#include "../include/scene.h"

Scene::Scene(QObject* parent) : QGraphicsScene(parent) {
    // Setting the background to black
    this->setBackgroundBrush(Qt::black);

    // Instanciating the game objects
    ball = new Ball;
    p1 = new Player(PlayerPosition::Left);
    p2 = new Player(PlayerPosition::Right);

    // Creating the middle line
    middle_line = new QGraphicsLineItem;
    setup_middle_line();

    // Adding the game objects to the scene
    this->addItem(ball);
    this->addItem(p1->paddle());
    this->addItem(p2->paddle());
    this->addItem(middle_line);

    // Timer which is going to update every game object each frame
    QTimer* update_timer = new QTimer(this);
    connect(update_timer, SIGNAL(timeout()), this, SLOT(update()));
    update_timer->start((1.f / Config::get<qreal>("fps")) * 1000.f);

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
    ball->move();
    ball->collision(p1->paddle(), p2->paddle());
    p1->update();
    p2->update();
}

void Scene::resize_event() {
    p1->update_position();
    p2->update_position();
}

void Scene::keyPressEvent(QKeyEvent* event) {
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
    pen.setDashOffset(5);
    pen.setBrush((QBrush)Qt::gray);

    quint16 b_h = Config::get<quint16>("board_height");
    middle_line->setLine(0, -b_h / 2, 0, b_h / 2);
    middle_line->setPen(pen);
}

void Scene::update_middle_line() {

}
