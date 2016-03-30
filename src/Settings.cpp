#include "Settings.h"

#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Widgets.hpp>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <vector>
#include <iostream>

Settings::Settings(const std::string& filename):
m_fileName(filename)
{
    if(!m_parser.loadFromFile(filename)){
        std::cout << "Failed to load config.txt \n";
    }
}

Settings::~Settings()
{

}

void Settings::showSettings(const int width, const int height)
{
	m_renderWindow.create(sf::VideoMode(width,height),"Settings");

 	createGui();

	while (m_renderWindow.isOpen())
	{
		//Update GUI
		m_desktop.Update( 0.f );

		//Clear previous frame
		m_renderWindow.clear(sf::Color::Black);

		//Show it to the user
		m_sfgui.Display(m_renderWindow);
		m_renderWindow.display();

		while (m_renderWindow.pollEvent(m_event))
        	{
			// "close requested" event: we close the m_renderWindow
			if (m_event.type == sf::Event::Closed)
			m_renderWindow.close();

			//Gui Event Handler
			m_desktop.HandleEvent( m_event );

			// catch the resize events
			if (m_event.type == sf::Event::Resized)
	        	{
			        // update the view to the new size of the window
			        sf::FloatRect visibleArea(0, 0, (float)m_event.size.width, (float)m_event.size.height);
			        m_renderWindow.setView(sf::View(visibleArea));
			        m_view = m_renderWindow.getView();
			}
		}
	}
}

void Settings::saveChanges()
{
    for(int i = 0; i < m_settingsEntry.size(); i++){
        std::string value = m_settingsEntry[i]->GetText();
        m_parser.set(m_settingsNames[i],value);
    }
    m_parser.saveToFile();
}

void Settings::createGui()
{
	//Get vector of settings names
	m_settingsNames = m_parser.getAllSettings();

	//Label vector generated from settings file
	std::vector<sfg::Label::Ptr> labels;
	labels.resize(m_settingsNames.size());
	auto fillerLabel = sfg::Label::Create(" ");

	//resize entry vector
	m_settingsEntry.resize(m_settingsNames.size());

	//Change Font Size
	m_desktop.SetProperty( "Button#Button", "FontSize", 24.f );

	// Reset GL states so the widnow will render without SFML rendering
	m_renderWindow.resetGLStates();

	//Create button for comitting changes
	auto save = sfg::Button::Create("Save Changes");

	//create and set labels and entries
	for(int i = 0; i < labels.size(); i++){
		labels[i] = sfg::Label::Create(m_settingsNames[i]);
		std::string name;
		m_parser.get(m_settingsNames[i], name);
		m_settingsEntry[i] = sfg::Entry::Create(name);
	}

	//Create Settings Window
	m_window = sfg::Window::Create();
	m_window->SetTitle( "Settings" );

	auto settingsTable = sfg::Table::Create();
		
	//Table Position Iterators
	int x = 0, y = 0;
	for(int i = 0; i < m_settingsNames.size(); i++){

		//Attach Widgets to locations in a table for SGUI
		settingsTable->Attach(labels[i], sf::Rect<sf::Uint32>(x,y,1,1),sfg::Table::FILL, sfg::Table::FILL, sf::Vector2f( 10.f, 10.f ) );
		settingsTable->Attach(m_settingsEntry[i], sf::Rect<sf::Uint32>(x+1,y,1,1),sfg::Table::FILL, sfg::Table::FILL, sf::Vector2f( 20.f, 10.f ) );

		y++;
		if(y > 6){
			settingsTable->Attach(fillerLabel, sf::Rect<sf::Uint32>(x+2,y,1,1),sfg::Table::FILL, sfg::Table::FILL, sf::Vector2f( 20.f, 10.f ) );
			x+= 3;
			y = 0;
			std::cout << y << "\n";
		}
	}
	
	//Attach Save Button and Bind Save Function
	settingsTable->Attach(save, sf::Rect<sf::Uint32>(9,9,1,1),sfg::Table::FILL , sfg::Table::FILL, sf::Vector2f( 10.f, 10.f ) );
	save->GetSignal( sfg::Widget::OnLeftClick ).Connect(std::bind( &Settings::saveChanges, this ) );

	m_window->Add(settingsTable);
	m_desktop.Add(m_window);
}


