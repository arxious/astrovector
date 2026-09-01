#include <iostream>
#include <array>
#include <SFML/Graphics.hpp>
#include "satellite.hpp"

#include <libsgp4/SGP4.h>
#include <libsgp4/Tle.h>

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

    libsgp4::Tle tle("ISS (ZARYA)",
        "1 25544U 98067A   26244.49851261  .00003910  00000-0  79223-4 0  9994",
        "2 25544  51.6312 282.3953 0005055  96.4740 263.6825 15.48958602583586"
    );

    libsgp4::SGP4 sgp4(tle);

    libsgp4::DateTime startTime = libsgp4::DateTime::Now(true);
    libsgp4::Eci initialEci = sgp4.FindPosition(startTime);
    libsgp4::CoordGeodetic initialGeo = initialEci.ToGeodetic();
    libsgp4::Vector initialVel = initialEci.Velocity();

    SatelliteConfig testConfig;
    testConfig.name = "ISS (ZARYA)";
    testConfig.latitude = libsgp4::Util::RadiansToDegrees(initialGeo.latitude);
    testConfig.longitude = libsgp4::Util::RadiansToDegrees(initialGeo.longitude);
    testConfig.altitude = initialGeo.altitude;
    testConfig.speed = initialVel.Magnitude();

    Satellite testSatellite(testConfig);

    while (window.isOpen())
    {
        while (const auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        libsgp4::DateTime time = libsgp4::DateTime::Now(true);
        libsgp4::Eci eci = sgp4.FindPosition(time);
        libsgp4::CoordGeodetic geo = eci.ToGeodetic();
        libsgp4::Vector vel = eci.Velocity();

        
        testSatellite.latitude = libsgp4::Util::RadiansToDegrees(geo.latitude);
        testSatellite.longitude = libsgp4::Util::RadiansToDegrees(geo.longitude);
        testSatellite.altitude = geo.altitude;
        testSatellite.speed = vel.Magnitude();

		std::printf("Time: %s, Lat: %.6f, Lon: %.6f, Alt: %.3f km, Speed: %.3f km/s\n",
			time.ToString().c_str(),
			testSatellite.latitude,
			testSatellite.longitude,
			testSatellite.altitude,
			testSatellite.speed
		);

        float screenX = ((testSatellite.longitude + 180.0) / 360) * 1280.0;
        float screenY = ((90.0 - testSatellite.latitude) / 180) * 640.0;

        testSatellite.visual.setPosition(sf::Vector2f(screenX, screenY));

        window.clear();
        window.draw(worldSprite);
        window.draw(testSatellite.visual);
        window.display();
    }

    return 0;
}
