#include "../include/main_window.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    this->setWindowTitle(tr("qt-pong"));
    this->setWindowIcon(QIcon("assets/images/pong.png"));
    this->setWindowState(Qt::WindowMaximized);
    this->setMinimumSize(800, 600);

    Scene* scene = new Scene(this);
    view = new View(scene, this);

    config_window = new ConfigWindow;

    file_menu = menuBar()->addMenu(tr("File"));
    config_menu = menuBar()->addMenu(tr("Config"));
    help_menu = menuBar()->addMenu(tr("Help"));

    add_background_image = new QAction(tr("Select a background image"), this);
    remove_background_image = new QAction(tr("Remove the background image"), this);
    file_menu->addAction(add_background_image);
    file_menu->addAction(remove_background_image);

    show_config_window = new QAction(tr("Change configuration"), this);
    config_menu->addAction(show_config_window);

    QAction* test = new QAction("test", this);
    help_menu->addAction(test);

    this->connect(add_background_image, SIGNAL(triggered()), view->get_scene(), SLOT(set_background_image()));
    this->connect(remove_background_image, SIGNAL(triggered()), view->get_scene(), SLOT(remove_background_image()));
    this->connect(show_config_window, SIGNAL(triggered()), config_window, SLOT(show()));
    this->connect(config_window, SIGNAL(config_changed()), view->get_scene(), SLOT(update_new_config()));

    Config::set("board_width", view->width());
    Config::set("board_height", view->height());

    this->setCentralWidget(view);
}

MainWindow::~MainWindow() {
    delete view;
    delete config_window;
}
