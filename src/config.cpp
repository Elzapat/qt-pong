#include "../include/config.h"

QSettings Config::config("config.ini", QSettings::IniFormat);

void Config::set(QString conf_name, QVariant value) {
    // Set a new config value
    config.setValue("config/" + conf_name, value);
}

void Config::reset_config() {}
