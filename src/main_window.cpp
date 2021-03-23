#include "../include/main_window.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    this->setWindowState(Qt::WindowMaximized);
    this->setMinimumSize(800, 600);

    Scene* scene = new Scene(this);
    view = new View(scene, this);

    file_menu = menuBar()->addMenu(tr("File"));
    config_menu = menuBar()->addMenu(tr("Config"));
    help_menu = menuBar()->addMenu(tr("Help"));

    action_add_background_image = new QAction(tr("Select a background image"), this);
    action_remove_background_image = new QAction(tr("Remove the background image"), this);
    file_menu->addAction(action_add_background_image);
    file_menu->addAction(action_remove_background_image);

    connect(action_add_background_image, SIGNAL(triggered()), view->get_scene(), SLOT(set_background_image()));
    connect(action_remove_background_image, SIGNAL(triggered()), view->get_scene(), SLOT(remove_background_image()));

    Config::set("board_width", view->width());
    Config::set("board_height", view->height());

    this->setCentralWidget(view);
}

MainWindow::~MainWindow() {}
