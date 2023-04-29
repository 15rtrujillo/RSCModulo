#include <map>
#include <string>

#ifndef CONFIGFILE_H
#define CONFIGFILE_H

/// <summary>
/// Reads and stores configuration settings for the client
/// </summary>
class ConfigFile
{
public:
	ConfigFile();

	/// <summary>
	/// Get the count of settings that have been read from the config file
	/// </summary>
	/// <returns>The count of settings that have been read in from the config</returns>
	int settingsCount() const;

	/// <summary>
	/// Get the specified setting
	/// </summary>
	/// <param name="setting">The setting to retrieve</param>
	/// <returns>The specified setting's value</returns>
	std::string getSetting(std::string setting) const;

private:
	std::map<std::string, std::string> configs;
};

#endif
