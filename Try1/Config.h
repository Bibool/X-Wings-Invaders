#ifndef CONFIG_H
#define CONFIG_H

class Config
{
private:
	// Values that store the resolution of the screen that is read from file
	int m_width;
	int m_height;
	
public:
	Config();

	// Reads from file and sets the variables to hold the values
	void loadConfig();

	// Returns the values set
	int getWidth()  const { return m_width;  };
	int getHeight() const { return m_height; };	
};
#endif