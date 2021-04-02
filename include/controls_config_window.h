#ifndef CONTROLS_CONFIG_WINDOW_H
#define CONTROLS_CONFIG_WINDOW_H

#include <QtWidgets>
#include <QDebug>
#include "config.h"

class ControlsConfigWindow : public QWidget {
    Q_OBJECT

    public:
        ControlsConfigWindow(QWidget* parent = 0);
        ~ControlsConfigWindow();

    private:
        struct KeyEntry {
            QLabel label;
            QLabel key;
            QPushButton change_button;
        };
        QVector<KeyEntry> key_config;
        QVBoxLayout* v1;
        QVBoxLayout* v2;
        QVBoxLayout* v3;
};

#endif
