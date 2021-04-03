#ifndef AUDIO_CONFIG_WINDOW_H
#define AUDIO_CONFIG_WINDOW_H

#include <QtWidgets>
#include <QDebug>
#include "config.h"

class AudioConfigWindow : public QWidget {
    Q_OBJECT

    public:
        explicit AudioConfigWindow(QWidget* parent = 0);
        ~AudioConfigWindow();

    signals:
        void music_volume_changed(qreal volume);
        void sfx_volume_changed(qreal volume);

    private:
        QGridLayout* main_layout;
        QSlider* music_volume;
        QSlider* sfx_volume;
        QLabel* music_label;
        QLabel* sfx_label;
};

#endif // AUDIO_CONFIG_WINDOW_H
