#ifndef CONFIG_H
#define CONFIG_H

#include <QDataStream>
#include <QSettings>
#include <QDebug>
#include <QVariant>

class Config {
    public:
        template <typename T>
        static T get(QString conf_name, QString group = "config");
        static void set(QString conf_name, QVariant value);
        static QStringList get_all_keys();
        static QStringList get_groups();
        static void reset_to_default();
        static void save_config(QString config_name);
        static void remove_config(QString config_name);

    private:
        static QSettings config;
};

template <typename T>
T Config::get(QString conf_name, QString group) {
    // Return the asked config with the asked type
    return static_cast<T>(config.value(group + '/' + conf_name).toInt());
}

#endif
