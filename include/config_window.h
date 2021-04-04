#ifndef CONFIG_WINDOW_H
#define CONFIG_WINDOW_H

#include <QtWidgets>
#include "config.h"

class ConfigWindow : public QWidget {
    Q_OBJECT

    public:
        explicit ConfigWindow(QWidget* parent = 0);
        ~ConfigWindow();

    public slots:
        void reset_default_config();
        void config_input(int value);
        void save_config();
        void load_config();
        void remove_config();
        void change_color(QString config_name, QLabel* value_label);

    signals:
        void config_changed();
        void color_changed();

    private:
        struct ConfigInput {
            QString input_name;
            QLabel* label;
            QSpinBox* input;
        };
        struct ColorConfig {
            QLabel* config_name;
            QLabel* config_value;
            QPushButton* color_select;
        };
        QGridLayout* main_layout;
        QPushButton* reset_button;
        QPushButton* save_button;
        QPushButton* load_button;
        QPushButton* remove_button;
        QVector<ConfigInput> inputs;
        QVector<ColorConfig> color_configs;
};

#endif
