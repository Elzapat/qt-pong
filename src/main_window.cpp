#include "../include/main_window.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    this->setWindowState(Qt::WindowMaximized);
    this->setMinimumSize(800, 600);

    file_menu = menuBar()->addMenu(tr("File"));
    config_menu = menuBar()->addMenu(tr("Config"));
    help_menu = menuBar()->addMenu(tr("Help"));

    Scene* scene = new Scene(this);
    view = new View(scene, this);

    Config::set("board_width", view->width());
    Config::set("board_height", view->height());

    this->setCentralWidget(view);
}

MainWindow::~MainWindow() {}
