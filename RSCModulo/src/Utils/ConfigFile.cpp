#include <fstream>

#include "ConfigFile.h"

ConfigFile::ConfigFile()
{
    std::fstream configFile;
    configFile.open("client.config", std::ios::in);
    std::string line;
    while (!configFile.eof())
    {
        std::getline(configFile, line);
        int split = line.find_first_of("=");
        std::string key = line.substr(0, split);
        std::string value = line.substr(split + 1);
        configs[key] = value;
    }
    configFile.close();
}

int ConfigFile::settingsCount() const
{
    return configs.size();
}

std::string ConfigFile::getSetting(std::string setting) const
{
    return configs.at(setting);
}
