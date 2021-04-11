#include "../include/audio_config_window.h"

AudioConfigWindow::AudioConfigWindow(QWidget* parent) : QWidget(parent) {
    this->setWindowIcon(QIcon("assets/images/settings.png"));
    this->setWindowTitle(tr("Audio Config"));

    main_layout = new QGridLayout;
    main_layout->setSizeConstraint(QLayout::SetFixedSize);

    music_volume = new QSlider(Qt::Horizontal);
    sfx_volume = new QSlider(Qt::Horizontal);
    music_label = new QLabel(tr("Music Volume"));
    sfx_label = new QLabel(tr("Sound Effects Volume"));

    music_volume->setMinimum(0);
    music_volume->setMaximum(100);
    music_volume->setValue((int)(Config::get<int>("music_volume", "audio")));

    sfx_volume->setMinimum(0);
    sfx_volume->setMaximum(100);
    sfx_volume->setValue((int)(Config::get<int>("sfx_volume", "audio")));

    this->connect(music_volume, &QSlider::valueChanged, this, [this](int value) {
        Config::set("music_volume", value, "audio");
        emit this->music_volume_changed((qreal)value / 100.f);
    });
    this->connect(sfx_volume, &QSlider::valueChanged, this, [this](int value) {
        Config::set("sfx_volume", value, "audio");
        emit this->sfx_volume_changed((qreal)value / 100.f);
    });

    main_layout->addWidget(music_label, 0, 0);
    main_layout->addWidget(music_volume, 0, 1);
    main_layout->addWidget(sfx_label, 1, 0);
    main_layout->addWidget(sfx_volume, 1, 1);

    this->setLayout(main_layout);
}

AudioConfigWindow::~AudioConfigWindow() {
    delete music_volume;
    delete sfx_volume;
    delete main_layout;
    delete music_label;
    delete sfx_label;
}
