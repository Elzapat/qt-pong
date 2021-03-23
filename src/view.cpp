#include "../include/view.h"

View::View(Scene* s, QWidget* parent) : scene(s), QGraphicsView(s, parent) {
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

View::~View() {}

void View::resizeEvent(QResizeEvent* event) {
    QWidget::resizeEvent(event);

    this->setSceneRect(-this->width() / 2, -this->height() / 2, this->width(), this->height());

    Config::set("board_width", this->width());
    Config::set("board_height", this->height());

    scene->resize_event();

    this->setScene(scene);
    this->fitInView(this->sceneRect());
}

Scene* View::get_scene() {
    return scene;
}
