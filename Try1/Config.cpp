#include <iostream>
#include <fstream>
#include "Config.h"


Config::Config()
{
	// Initializes the values then sets them
	m_width = 0;
	m_height = 0;
	loadConfig();
}

// This reads the file on the disk and sets the variables to the numbers found
// TODO: Use an xml or .ini file with a better structured document

void Config::loadConfig()
{
	std::ifstream m_configFile;
	m_configFile.open("GameResolution.txt");
	if( !m_configFile.is_open() )
	{
		std::cout << "Failed to open GameResolution.txt";
	}

	m_configFile >> m_width >> m_height;
}