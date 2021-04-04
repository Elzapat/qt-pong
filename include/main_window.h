#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QtWidgets>
#include <QMainWindow>
#include <QDebug>
#include "config.h"
#include "view.h"
#include "config_window.h"
#include "controls_config_window.h"
#include "audio_config_window.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

    public:
        explicit MainWindow(QWidget* parent = 0);
        ~MainWindow();

    private:
        QMenu* config_menu;
        QMenu* help_menu;
        QMenu* game_menu;
        View* view;
        ConfigWindow* config_window;
        ControlsConfigWindow* controls_config_window;
        AudioConfigWindow* audio_config_window;

        QAction* add_background_image;
        QAction* remove_background_image;
        QAction* show_config_window;
        QAction* show_controls_config_window;
        QAction* show_audio_config_window;
        QAction* set_p2_computer;
};

#endif
