#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Widgets.hpp>

#include <SFML/Graphics.hpp>

#include <string>
#include <vector>

class SplashScreen
{
public:
	SplashScreen(const std::string& filename);
	~SplashScreen();

	void showSplash(const int time_seconds);

private:

	//Splash Screen Image File
	std::string m_filename;

};

