#include <fstream>

#include "ConfigFile.h"

ConfigFile::ConfigFile(const std::string &fileName)
{
    std::fstream configFile;
    configFile.open(fileName, std::ios::in);

    if (configFile.fail())
    {
        errorOccurred = true;
        return;
    }

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

    if (settingsCount() < 1)
    {
        errorOccurred = true;
        return;
    }

    errorOccurred = false;
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

bool ConfigFile::error() const
{
    return errorOccurred;
}
