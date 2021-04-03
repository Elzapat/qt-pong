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
        void keyPressEvent(QKeyEvent* event) override;

    private:
        struct KeyConfig {
            QString config_name;
            QString key_name;
            QLabel* label;
            QLabel* key_label;
            QPushButton* change_button;
            bool listening_for_key;
        };
        QVector<KeyConfig*> key_config;
        QGridLayout* main_layout;
        void change_button_clicked(KeyConfig* conf);
};

#endif // CONTROLS_CONFIG_WINDOW_H
