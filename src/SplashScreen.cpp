#include "SplashScreen.h"

#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Widgets.hpp>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <vector>
#include <iostream>


SplashScreen::SplashScreen(const std::string& filename):
m_filename(filename)
{
}


SplashScreen::~SplashScreen()
{

}

//Display splash screen for time_seconds seconds
void SplashScreen::showSplash(int time_seconds){

    //Splash Screen Image loading
    sf::Texture splashTexture;
    if(!splashTexture.loadFromFile(m_filename)){
        std::cout << "Could not locate splash image \n";
    }
    else{
        //Sprite for splash screen
        sf::Sprite splashSprite;
        splashSprite.setTexture(splashTexture);

        const int splashWidth = splashSprite.getLocalBounds().width;
        const int splashHeight = splashSprite.getLocalBounds().height;

        //Timing varible
        sf::Clock clock;
        sf::RenderWindow window(sf::VideoMode(splashWidth, splashHeight), "",sf::Style::None);
        window.setVerticalSyncEnabled(true);

        //Alpha for fun transition to full sprite color
        int alpha = 0;
        while (clock.getElapsedTime().asSeconds() < time_seconds)
        {
            window.clear(sf::Color::Black);
            window.draw(splashSprite);
            splashSprite.setColor(sf::Color(255,255,255,alpha));
            std::cout << alpha << "\n";
            alpha = alpha < 250 ? alpha + 4 : 255;
            window.display();
        }
        window.close();
    }
}


