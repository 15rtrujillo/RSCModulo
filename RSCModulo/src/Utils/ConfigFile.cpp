#include <fstream>

#include "ConfigFile.h"

ConfigFile::ConfigFile(const std::string &fileName)
{
    std::fstream configFile;
    configFile.open(fileName, std::ios::in);
    std::string line;
    while (std::getline(configFile, line))
    {
        size_t split = line.find_first_of("=");
        if (split == std::string::npos)
        {
            continue;
        }
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

std::string ConfigFile::getSetting(const std::string& setting) const
{
    auto iterator = configs.find(setting);
    if (iterator == configs.end())
    {
        return "";
    }

    return iterator->second;
}
