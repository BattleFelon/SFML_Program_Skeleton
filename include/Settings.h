#include "SettingsParser.h"

#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Widgets.hpp>

#include <SFML/Graphics.hpp>

#include <string>
#include <vector>

class Settings
{
public:
	Settings(const std::string& filename);
	~Settings();

	void showSettings(const int settingsWidth, const int settingsHeight);

private:

    //Setup Gui Enviroment
	void createGui();

	//Save Changed to setting file
	void saveChanges();

	//Config File Name
	std::string m_fileName;

    //Settings Names
    std::vector<std::string> m_settingsNames;

    //Settings Parser
    SettingsParser m_parser;

	//Gui Object
	sfg::SFGUI m_sfgui;

    //SFGui varibles
	sfg::Desktop m_desktop;
	sfg::Window::Ptr m_window;
	std::vector<sfg::Entry::Ptr> m_settingsEntry;

	//SFML Window Varibles
    sf::RenderWindow m_renderWindow;
	sf::View m_view;
	sf::Event m_event;

	//Settings Sprite and Image vaibles
	sf::Texture m_texture;
	sf::Sprite m_sprite;

};
