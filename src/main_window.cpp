#include "../include/main_window.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    this->setWindowTitle(tr("qt-pong"));
    this->setWindowIcon(QIcon("assets/images/pong.png"));
    this->setWindowState(Qt::WindowMaximized);
    this->setMinimumSize(800, 600);

    Scene* scene = new Scene(this);
    view = new View(scene, this);

    config_window = new ConfigWindow;
    controls_config_window = new ControlsConfigWindow;
    audio_config_window = new AudioConfigWindow;

    file_menu = menuBar()->addMenu(tr("File"));
    config_menu = menuBar()->addMenu(tr("Config"));
    help_menu = menuBar()->addMenu(tr("Help"));

    add_background_image = new QAction(tr("Select a background image"), this);
    remove_background_image = new QAction(tr("Remove the background image"), this);
    file_menu->addAction(add_background_image);
    file_menu->addAction(remove_background_image);

    show_config_window = new QAction(tr("Configuration"), this);
    show_controls_config_window = new QAction(tr("Controls"), this) ;
    show_audio_config_window = new QAction(tr("Audio"), this);
    config_menu->addAction(show_config_window);
    config_menu->addAction(show_controls_config_window);
    config_menu->addAction(show_audio_config_window);

    QAction* test = new QAction("test", this);
    help_menu->addAction(test);

    this->connect(add_background_image, SIGNAL(triggered()), view->get_scene(), SLOT(set_background_image()));
    this->connect(remove_background_image, SIGNAL(triggered()), view->get_scene(), SLOT(remove_background_image()));

    this->connect(show_config_window, SIGNAL(triggered()), config_window, SLOT(show()));
    this->connect(show_controls_config_window, SIGNAL(triggered()), controls_config_window, SLOT(show()));
    this->connect(show_audio_config_window, SIGNAL(triggered()), audio_config_window, SLOT(show()));

    this->connect(config_window, SIGNAL(config_changed()), view->get_scene(), SLOT(update_new_config()));
    this->connect(config_window, SIGNAL(color_changed()), view->get_scene(), SLOT(color_changed()));

    this->connect(audio_config_window, SIGNAL(music_volume_changed(qreal)), view->get_scene(), SLOT(music_volume_changed(qreal)));
    this->connect(audio_config_window, SIGNAL(sfx_volume_changed(qreal)), view->get_scene()->get_ball(), SLOT(sfx_volume_changed(qreal)));

    Config::set("board_width", view->width());
    Config::set("board_height", view->height());

    this->setCentralWidget(view);
}

MainWindow::~MainWindow() {
    delete file_menu;
    delete config_menu;
    delete help_menu;
    delete view;
    delete config_window;
    delete controls_config_window;
    delete audio_config_window;
    delete add_background_image;
    delete remove_background_image;
    delete show_config_window;
    delete show_controls_config_window;
}
