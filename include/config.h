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
        static void set(QString conf_name, QVariant value, QString group = "config");
        static QStringList get_all_keys(QString group = "default");
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
    return config.value(group + '/' + conf_name).value<T>();
}

#endif
