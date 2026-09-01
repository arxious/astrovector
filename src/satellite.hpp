#pragma once

#include <string>
#include <SFML/Graphics/CircleShape.hpp>

struct SatelliteConfig {
	std::string name;
	double latitude;
	double longitude;
	double altitude;
	double speed;
};

class Satellite {
		
	public:
		 sf::CircleShape visual;
		 std::string name;
		 double latitude;
		 double longitude;
		 double altitude;
		 double speed;
		 Satellite(const SatelliteConfig& cfg) {
			name = cfg.name;
			visual = sf::CircleShape(3.0f, 100);
			visual.setFillColor(sf::Color::Red);
			latitude = cfg.latitude;
			longitude = cfg.longitude;
			altitude = cfg.altitude;
			speed = cfg.speed;
		}
};
