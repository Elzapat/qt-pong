#ifndef CONFIG_H
#define CONFIG_H

#include <QDataStream>
#include <QSettings>
#include <QDebug>
#include <QVariant>

class Config {
    public:
        template <typename T>
        static T get(QString conf_name);
        static void set(QString conf_name, QVariant value);
        static void reset_config();

    private:
        static QSettings config;
};

template <typename T>
T Config::get(QString conf_name) {
    // Return the asked config with the asked type
    return static_cast<T>(config.value("config/" + conf_name).toInt());
}

#endif
