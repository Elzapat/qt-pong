#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include <QtWidgets>

class MainWindow : public QMainWindow {
    Q_OBJECT

    public:
        explicit MainWindow(QWidget* parent = 0);
        ~MainWindow();
        QGroupBox* build_group_box_control();

    public slots:

    private:
        QWidget* main_widget;
        QMenu* file_menu;
};

#endif
