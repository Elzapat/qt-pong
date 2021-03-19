#include "../include/main_window.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    main_widget = new QWidget;
    QHBoxLayout* main_qbl = new QHBoxLayout;
    main_widget->setLayout(main_qbl);
    this->setCentralWidget(main_widget);

    main_qbl->addWidget(main_widget);

    file_menu = menuBar()->addMenu(tr("File"));
}

MainWindow::~MainWindow() {}

QGroupBox* MainWindow::build_group_box_control() {
    QGroupBox* qgb = new QGroupBox(tr("Control"));
    return qgb;
}

https://stackoverflow.com/questions/47471629/fail-to-use-q-object-macro-in-cmake-project
