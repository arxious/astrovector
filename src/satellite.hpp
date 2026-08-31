#pragma once

#include <string>
#include <SFML/Graphics/CircleShape.hpp>

struct SatelliteVisual {
	std::string name;
	sf::CircleShape *visual; // This will store the memory address of the circle object
	double latitude;
	double longitude;
	double altitude;
	double velocity;
};

struct SatelliteConfig {
	std::string name;
	double latitude;
	double longitude;
	double altitude;
	double x_velocity;
	double y_velocity;
};

class Satellite {
		

	public:
		 sf::CircleShape visual;
		 std::string name;
		 double latitude;
		 double longitude;
		 double altitude;
		 double x_velocity;
		 double y_velocity;
		 Satellite(const SatelliteConfig& cfg) {
			name = cfg.name;
			visual = sf::CircleShape(3.0f, 100);
			latitude = cfg.latitude;
			longitude = cfg.longitude;
			altitude = cfg.altitude;
			x_velocity = cfg.x_velocity;
			y_velocity = cfg.y_velocity;
		}
};
