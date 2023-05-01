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
	ConfigFile(const std::string &fileName);

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
	std::string getSetting(const std::string &setting) const;

	/// <summary>
	/// Check if an error has occurred while reading the config file
	/// </summary>
	/// <returns>True if an error has occurred</returns>
	bool error() const;

private:
	/// <summary>
	/// Stores the settings and their values
	/// </summary>
	std::map<std::string, std::string> configs;

	/// <summary>
	/// Set if an error has occurred reading the config file
	/// </summary>
	bool errorOccurred;
};

#endif
