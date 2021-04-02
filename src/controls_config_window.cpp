#include "../include/controls_config_window.h"

ControlsConfigWindow::ControlsConfigWindow(QWidget* parent) : QWidget(parent) {
    QVBoxLayout* main_layout = new QVBoxLayout;
    QTableWidget* table = new QTableWidget(10, 3);

    main_layout->addWidget(table);

    // QStringList labels = 
    qDebug() << QMetaEnum::fromType<Qt::Key>().valueToKey(Qt::Key_Z);
    QStringList controls = Config::get_all_keys("controls");
    foreach (const QString& control, controls) {

    }

    this->setLayout(main_layout);
    this->show();
}

ControlsConfigWindow::~ControlsConfigWindow() {}
