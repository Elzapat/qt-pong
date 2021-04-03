#include "../include/config_window.h"

ConfigWindow::ConfigWindow(QWidget* parent) : QWidget(parent) {
    this->setWindowIcon(QIcon("assets/images/settings.png"));
    this->setWindowTitle(tr("Config"));

    main_layout = new QGridLayout;

    int row = 0;
    foreach (const QString& key, Config::get_all_keys()) {
        QString label_text = key;
        label_text = label_text.replace('_', ' ').replace(0, 1, label_text[0].toUpper());
        
        if (key.contains("color")) {
            QLabel* name = new QLabel(label_text);
            QLabel* value = new QLabel(Config::get<QString>(key));
            QPushButton* color_select = new QPushButton(tr("Change"));

            main_layout->addWidget(name, row, 0);
            main_layout->addWidget(value, row, 1);
            main_layout->addWidget(color_select, row++, 2);

            this->connect(color_select, &QPushButton::clicked, this, [this, key, value]() {
                this->change_color(key, value);
            });

            color_configs.push_back(ColorConfig { name, value, color_select });
        } else {
            QLabel* label = new QLabel(label_text);
            QLineEdit* input = new QLineEdit(Config::get<QString>(key));
            main_layout->addWidget(label, row, 0);
            main_layout->addWidget(input, row++, 1, 1, 2);

            input->setValidator(new QIntValidator(1, 9999, this));

            inputs.push_back(ConfigInput { key, label, input });
            this->connect(input, SIGNAL(textChanged(QString)), this, SLOT(config_input(QString)));
        }
    }

    reset_button = new QPushButton(tr("Reset to default"));
    save_button = new QPushButton(tr("Save configuration"));
    load_button = new QPushButton(tr("Load configuration"));
    remove_button = new QPushButton(tr("Remove configuration"));

    main_layout->addWidget(reset_button, row++, 0, 1, 3);
    main_layout->addWidget(save_button, row, 0);
    main_layout->addWidget(load_button, row, 1);
    main_layout->addWidget(remove_button, row, 2);

    this->connect(reset_button, SIGNAL(clicked()), this, SLOT(reset_default_config()));
    this->connect(save_button, SIGNAL(clicked()), this, SLOT(save_config()));
    this->connect(load_button, SIGNAL(clicked()), this, SLOT(load_config()));
    this->connect(remove_button, SIGNAL(clicked()), this, SLOT(remove_config()));

    this->setLayout(main_layout);
}

ConfigWindow::~ConfigWindow() {
    delete main_layout;
    delete reset_button;
    delete save_button;
    delete load_button;
    delete remove_button;
    for (auto& [_, l, i] : inputs) {
        delete l;
        delete i;
    }
    for (auto& [n, v, s] : color_configs) {
        delete n;
        delete v;
        delete s;
    }
}

void ConfigWindow::reset_default_config() {
    Config::reset_to_default();

    for (auto [input_name, _, input] : inputs)
        input->setText(Config::get<QString>(input_name));
    for (auto [config_name, value, _] : color_configs) {
        QString name = config_name->text();
        QString key = name.replace(' ', '_').replace(0, 1, name[0].toLower());
        value->setText(Config::get<QString>(key));
    }

    emit color_changed();
}

void ConfigWindow::config_input(QString value) {
    for (auto [input_name, _, input] : inputs) {
        if (input->text() == value) {
            Config::set(input_name, value);
        }
    }
    QIntValidator validator(1, 9999);
    int pos = 0;
    if (validator.validate(value, pos) == QValidator::Acceptable)
        emit config_changed();
}

void ConfigWindow::save_config() {
    bool ok;
    QString config_name = QInputDialog::getText(this, tr("Choose a config name"),
                                        tr("Configuration name:"), QLineEdit::Normal,
                                        "", &ok);

    if (!ok) return;

    if (Config::get_groups().indexOf(config_name) != -1) {
        QMessageBox::information(this, tr("Config name not available"),
                    tr("This configuration name is already taken!"));
    } 
    Config::save_config(config_name);
}

void ConfigWindow::load_config() {
    bool ok;
    QStringList groups = Config::get_groups();
    QString config_name = QInputDialog::getItem(this, tr("Choose a configuration"),
                                        tr("Choose a configuration to load"), groups,
                                        0, false, &ok);
    if (!ok) return;

    for (auto [input_name, _, input] : inputs)
        input->setText(Config::get<QString>(input_name, config_name));
}

void ConfigWindow::remove_config() {
    bool ok;
    QStringList groups = Config::get_groups();
    int index = groups.indexOf("default");
    groups.removeAt(index);

    if (groups.isEmpty()) {
        QMessageBox::information(this, tr("No saved configuration"),
                    tr("You have no saved configuration!"));
        return;
    }

    QString config_name = QInputDialog::getItem(this, tr("Choose a configuration"),
                                        tr("Choose a configuration to remove"),
                                        groups, 0, false, &ok);
    if (!ok) return;
    Config::remove_config(config_name);
}

void ConfigWindow::change_color(QString config_name, QLabel* value_label) {
    QColor chosen_color = QColorDialog::getColor(value_label->text());

    value_label->setText(chosen_color.name());
    Config::set(config_name, chosen_color);

    emit color_changed();
}
