#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QtWidgets>
#include <QMainWindow>
#include <QDebug>
#include "config.h"
#include "view.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

    public:
        explicit MainWindow(QWidget* parent = 0);
        ~MainWindow();
        
    public slots:

    private:
        QHBoxLayout* main_layout;
        QMenu* file_menu;
        QMenu* config_menu;
        QMenu* help_menu;
        View* view;
};

#endif
