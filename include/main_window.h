#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QtWidgets>
#include <QMainWindow>
#include <QDebug>
#include "config.h"
#include "view.h"
#include "config_window.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

    public:
        explicit MainWindow(QWidget* parent = 0);
        ~MainWindow();

    private:
        QHBoxLayout* main_layout;
        QMenu* file_menu;
        QMenu* config_menu;
        QMenu* help_menu;
        View* view;
        ConfigWindow* config_window;

        QAction* add_background_image;
        QAction* remove_background_image;
        QAction* show_config_window;
};

#endif
