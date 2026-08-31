#include <SFML/Graphics.hpp>
#include "satellite.hpp"

int main()
{
    sf::RenderWindow window(
        sf::VideoMode({ 1280u, 640u }),
        "astrovector",
		sf::Style::Titlebar | sf::Style::Close
    );

    sf::Image icon;
	if (!icon.loadFromFile("../assets/sat_icon.png"))
	{
		return 1;
	}
    window.setIcon(icon);

    sf::Texture worldMap;
	if (!worldMap.loadFromFile("../assets/blue_marble.png"))
	{
		return 1;
	}

    sf::Clock frameClock;
    

	sf::Sprite worldSprite(worldMap);

    SatelliteConfig testConfig;
    testConfig.name = "testSatellite";
    testConfig.latitude = 1280 / 2;
    testConfig.longitude = 640 / 2;
    testConfig.x_velocity = 100;
    testConfig.y_velocity = 100;

    Satellite testSatellite(testConfig);
    

    //worldSprite.setPosition(sf::Vector2f(0, 0));

    while (window.isOpen())
    {
        while (const auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        sf::Time elapsed = frameClock.restart();
        float deltaTime = elapsed.asSeconds();

        testSatellite.latitude += testSatellite.x_velocity * deltaTime;
        testSatellite.longitude -= testSatellite.y_velocity * deltaTime;

        // couple conditions before setting pos mate
        if (testSatellite.longitude < 0)  {
            testSatellite.longitude = 640;
        }

        if (testSatellite.latitude < 0) {
            testSatellite.latitude = 1280;
        }

        testSatellite.visual.setPosition(sf::Vector2f(std::fmod(testSatellite.latitude, 1280), std::fmod(testSatellite.longitude, 640)));

        window.clear();
        window.draw(worldSprite);
        window.draw(testSatellite.visual);
        window.display();
    }
}

// So far what this program does is open a window of fixed dimensions and load a world map.