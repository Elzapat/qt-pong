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
    multiplayer_window = new MultiplayerWindow;

    config_menu = menuBar()->addMenu(tr("Config"));
    help_menu = menuBar()->addMenu(tr("Help"));
    game_menu = menuBar()->addMenu(tr("Game"));

    // Instanciating and adding actions to the Config menu
    add_background_image = new QAction(tr("Select a background image"), this);
    remove_background_image = new QAction(tr("Remove the background image"), this);
    show_config_window = new QAction(tr("Configuration"), this);
    show_controls_config_window = new QAction(tr("Controls"), this) ;
    show_audio_config_window = new QAction(tr("Audio"), this);
    config_menu->addAction(add_background_image);
    config_menu->addAction(remove_background_image);
    config_menu->addAction(show_config_window);
    config_menu->addAction(show_controls_config_window);
    config_menu->addAction(show_audio_config_window);

    // Instanciating and adding actions to the Help menu
    QAction* test = new QAction("test", this);
    help_menu->addAction(test);

    // Instanciating and adding actions to the Game menu
    set_p2_computer = new QAction(tr("Set P2 as Computer"));
    show_multiplayer_window = new QAction(tr("Multiplayer"), this);
    game_menu->addAction(set_p2_computer);
    game_menu->addAction(show_multiplayer_window);
    
    // Config menu actions
    this->connect(add_background_image, SIGNAL(triggered()), view->get_scene(), SLOT(set_background_image()));
    this->connect(remove_background_image, SIGNAL(triggered()), view->get_scene(), SLOT(remove_background_image()));
    this->connect(show_config_window, SIGNAL(triggered()), config_window, SLOT(show()));
    this->connect(show_controls_config_window, SIGNAL(triggered()), controls_config_window, SLOT(show()));
    this->connect(show_audio_config_window, SIGNAL(triggered()), audio_config_window, SLOT(show()));

    // Config menu signals
    this->connect(config_window, SIGNAL(config_changed()), view->get_scene(), SLOT(update_new_config()));
    this->connect(config_window, SIGNAL(color_changed()), view->get_scene(), SLOT(color_changed()));
    this->connect(audio_config_window, SIGNAL(music_volume_changed(qreal)), view->get_scene(), SLOT(music_volume_changed(qreal)));
    this->connect(audio_config_window, SIGNAL(sfx_volume_changed(qreal)), view->get_scene()->get_ball(), SLOT(sfx_volume_changed(qreal)));

    // Game menu actions
    this->connect(set_p2_computer, SIGNAL(triggered()), view->get_scene()->get_player_2(), SLOT(set_computer()));
    this->connect(show_multiplayer_window, SIGNAL(triggered()), multiplayer_window, SLOT(show_window()));

    // Update the config with the current board height and width
    Config::set("board_width", view->width());
    Config::set("board_height", view->height());

    this->setCentralWidget(view);
}

MainWindow::~MainWindow() {
    delete config_menu;
    delete help_menu;
    delete game_menu;
    delete view;
    delete config_window;
    delete controls_config_window;
    delete audio_config_window;
    delete multiplayer_window;
    delete add_background_image;
    delete remove_background_image;
    delete show_config_window;
    delete show_controls_config_window;
    delete set_p2_computer;
}
