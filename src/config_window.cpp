#include "../include/config_window.h"

ConfigWindow::ConfigWindow(QWidget* parent) : QWidget(parent) {
    this->setWindowTitle(tr("Config"));

    main_layout = new QVBoxLayout;

    QHBoxLayout* labels_and_inputs = new QHBoxLayout;
    QVBoxLayout* labels_layout = new QVBoxLayout;
    QVBoxLayout* inputs_layout = new QVBoxLayout;

    foreach (const QString& key, Config::get_all_keys()) {
        QString label_text = key;
        label_text = label_text.replace('_', ' ').replace(0, 1, label_text[0].toUpper());
        QLabel* label = new QLabel(label_text);
        QLineEdit* input = new QLineEdit(QString::number(Config::get<qreal>(key)));

        labels_layout->addWidget(label);
        inputs_layout->addWidget(input);

        input->setValidator(new QIntValidator(1, 9999, this));

        inputs.push_back(ConfigInput { key, input });
        this->connect(input, SIGNAL(textChanged(QString)), this, SLOT(config_input(QString)));
    }

    reset_button = new QPushButton(tr("Reset to default"));
    save_button = new QPushButton(tr("Save configuration"));
    load_button = new QPushButton(tr("Load configuration"));
    remove_button = new QPushButton(tr("Remove configuration"));

    labels_and_inputs->addLayout(labels_layout);
    labels_and_inputs->addLayout(inputs_layout);
    main_layout->addLayout(labels_and_inputs);

    main_layout->addWidget(reset_button);
    main_layout->addWidget(save_button);
    main_layout->addWidget(load_button);
    main_layout->addWidget(remove_button);

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
    for (auto config_input : inputs) {
        delete config_input.input;
    }
}

void ConfigWindow::reset_default_config() {
    Config::reset_to_default();
    quint8 i = 0;
    for (auto [input_name, input] : inputs)
        input->setText(QString::number(Config::get<qreal>(input_name)));
}

void ConfigWindow::config_input(QString value) {
    for (auto [input_name, input] : inputs) {
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

    for (auto [input_name, input] : inputs)
        input->setText(QString::number(Config::get<qreal>(input_name, config_name)));
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
