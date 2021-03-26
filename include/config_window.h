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
        void config_input(QString value);
        void save_config();
        void load_config();
        void remove_config();

    signals:
        void config_changed();

    public:
        struct ConfigInput {
            QString input_name;
            QLineEdit* input;
        };
        QVBoxLayout* main_layout;
        QPushButton* reset_button;
        QPushButton* save_button;
        QPushButton* load_button;
        QPushButton* remove_button;
        QVector<ConfigInput> inputs;
};

#endif
