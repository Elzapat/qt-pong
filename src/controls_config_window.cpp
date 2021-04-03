#include "../include/controls_config_window.h"

ControlsConfigWindow::ControlsConfigWindow(QWidget* parent) : QWidget(parent) {
    this->setWindowIcon(QIcon("assets/images/settings.png"));
    this->setWindowTitle(tr("Controls Config"));

    main_layout = new QGridLayout;

    QStringList controls = Config::get_all_keys("controls");
    int row = 0;
    foreach (const QString& control, controls) {
        // The control variable holds the config key, such as player1_up
        QString label_text = control;
        QLabel* label = new QLabel(label_text.replace('_', ' ').replace(0, 1, control[0].toUpper()) + ':'); 

        // Getting the value that corresponds to the config key
        Qt::Key key = Config::get<Qt::Key>(control, "controls");
        // Transforming the enum value to a string, and remove the starting "Key_"
        QString key_name = QMetaEnum::fromType<Qt::Key>().valueToKey(key);
        key_name = key_name.replace("Key_", "");
        QLabel* key_label = new QLabel(key_name);
        key_label->setAlignment(Qt::AlignCenter);

        QPushButton* change_button = new QPushButton(tr("Change"));

        KeyConfig* conf = new KeyConfig {
            control,
            key_name,
            label,
            key_label,
            change_button,
            false
        };

        this->connect(change_button, &QPushButton::clicked, this, [this, conf]() {
            this->change_button_clicked(conf);
        });

        key_config.push_back(conf);

        main_layout->addWidget(label, row, 0);
        main_layout->addWidget(key_label, row, 1);
        main_layout->addWidget(change_button, row, 2);
        row++;
    }

    this->setLayout(main_layout);
}

ControlsConfigWindow::~ControlsConfigWindow() {
    for (auto& key_entry : key_config) {
        delete key_entry->label;
        delete key_entry->key_label;
        delete key_entry->change_button;
        delete key_entry;
    }
    delete main_layout;
}

void ControlsConfigWindow::change_button_clicked(KeyConfig* conf) {
    // Setting all the key configs to default, and not listening
    // so the user can't set two keys at the same time
    for (auto& key_conf : key_config) {
        key_conf->key_label->setText(key_conf->key_name);
        key_conf->listening_for_key = false;
    }

    conf->key_label->setText(tr("Press a key"));
    conf->listening_for_key = true;
    // Unfocus the button so the spacebar can be used to set a key
    conf->change_button->clearFocus();
}

void ControlsConfigWindow::keyPressEvent(QKeyEvent* event) {

    for (auto& conf : key_config) {
        if (conf->listening_for_key) {
            conf->listening_for_key = false;

            QString key_name = QMetaEnum::fromType<Qt::Key>().valueToKey(event->key());
            key_name = key_name.replace("Key_", "");

            // If the key is already set for another config,
            // cancel the key listening;
            for (auto& other_conf : key_config) {
                if (other_conf->key_name == key_name) {
                    conf->key_label->setText(conf->key_name);
                    return;
                }
            }

            // Set the new key in the config
            Config::set(conf->config_name, event->key(), "controls");

            // Register the new key name
            conf->key_name = key_name;
            conf->key_label->setText(key_name);
        }
    }
}
