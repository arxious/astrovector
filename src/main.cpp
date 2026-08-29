#include <SFML/Graphics.hpp>

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

	sf::Sprite worldSprite(worldMap);
    
	worldSprite.setPosition(sf::Vector2f(0.f, 0.f));

    while (window.isOpen())
    {
        while (const auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }


        
        window.clear();
        window.draw(worldSprite);
        window.display();
    }
}