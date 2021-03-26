#include "../include/config.h"

QSettings Config::config("config.ini", QSettings::IniFormat);

void Config::set(QString conf_name, QVariant value) {
    // Set a new config value
    config.setValue("config/" + conf_name, value);
}

void Config::reset_to_default() {
    QMap<QString, QVariant> default_values;

    config.beginGroup("default");
    foreach (const QString& key, config.childKeys()) {
        default_values[key] = config.value(key);
    }
    config.endGroup();

    for (auto it = default_values.begin(); it != default_values.end(); ++it) {
        config.setValue("config/" + it.key(), it.value());
    }
}

QStringList Config::get_all_keys() {
    config.beginGroup("default");
    QStringList keys = config.childKeys();
    config.endGroup();

    return keys;
}

QStringList Config::get_groups() {
    QStringList groups = config.childGroups();
    int index = groups.indexOf("config");
    groups.removeAt(index);
    return groups;
}

void Config::save_config(QString config_name) {
    QStringList keys = get_all_keys(); 
    foreach (const QString& key, keys) {
        config.setValue(config_name + '/' + key, config.value("config/" + key));
    }
}

void Config::remove_config(QString config_name) {
    config.beginGroup(config_name);
    config.remove("");
    config.endGroup();
}
