# Documenting my first project

### Inspiration and Motivations
Since I wanted to actually build something in C++, I thought, why not a satellite tracker? that's pretty cool, and it connects to my interest in space and astronomy.
Back when I used to go plane watching near Heathrow airport, I used to use an app called FlightRadar24. The purpose was to display the location of planes through their user interface, which I thought it would be worthwhile to take inspiration and build something similar.

### Why C++?
Now you might be asking, why C++? This is because I've wanted to work in a low level language and build a desktop application. I don't know if the project will be good enough to host on the web, but if it gets to that stage, then I dont mind adding an integration for that.

## Choosing an IDE
I decided to go with Visual Studio as I already have it downloaded and it seems suitable for developing desktop applications in C++, I intend for the project to display the location of satellites, My aim is to be able to click on each one, see their name, latitude, longitude, altitude, and have it map to an approximation of their position.

<img width="529" height="460" alt="image" src="https://github.com/user-attachments/assets/26f135db-ea3e-4d52-bc50-77b96d9a49dd"/>

This is an image of FlightRadar24's tracker system. This is what originally inspired me (for reference)


## Starting point
I found it reasonable to start off with a rectangular world map, while not a full scrolling system (yet), I will display this instead to build a prototype.

## Libraries and Dependencies
C++ by default does not have a way to load and render a window. To get around this, I found a useful library called **SFML**, which uses a loop to update an open window each frame. So I decided to render a window of dimensions 1280x640, the same size as the world map.

Next, I noticed SFML can also be used to display the world map to the screen using `sf::Texture`, which I used to load the image. However to display it to the window, I created a map sprite using `sf::Sprite`, and I could then simply draw the sprite using `window.draw(worldSprite)`, which displayed it to the screen, by default, at 0,0, which perfectly aligned the map with the window. The issue was the window was resizable, which I disabled by writing `sf::Style::Titlebar | sf::Style::Close` as as the third parameter for `sf::RenderWindow`, I had to read a lot of the documentation to figure this out.

<img width="1277" height="660" alt="image" src="https://github.com/user-attachments/assets/b02158a8-3674-457c-9dc8-e53dc7b20774"/>

Now I had a world map loaded, great. Next I needed to represent the satellites that would be displayed on the map. To do this, I found out that SFML had objects for graphics, so i used their `sf::CircleShape`, to create a white circle that had radius `3` pixels, and displayed them on the world map.

At this current time, I came up with this struct as a representation of the satellite visual (the white circle)

```cpp
struct SatelliteVisual {
	std::string name;
	sf::CircleShape *visual; // This will store the memory address of the circle object
	double latitude;
	double longitude;
	double altitude;
	double velocity;
};
```

There are some issues with this structure, namely,  `*visual` means that I am using a pointer to a SFML CircleShape object. This assumes that I will create one in my `main.cpp` program. If I extend my representation to potentially hundreds of satellites this is unreliable as I will have to manage the construction of many CircleShape objects manually.

```cpp
struct SatelliteConfig {
	std::string name;
	double latitude;
	double longitude;
	double altitude;
	double x_velocity;
	double y_velocity;
};
```
In my updated version, I changed the approach, in order to display and render satellites they need will need their "configuration" populated.

```cpp
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
```
This class represents a satellite. My initial plan was that the constructor function will take in the `SatelliteConfig` and set the object's internal variables to the ones in the configuration.
At runtime, the satellite's white circle is drawn at (latitude, longitude), each measured in pixels. My constructor function also automatically creates the circle object, this prevents me from having to create it manually.

Test Satellite Configuration (in `main.cpp`)

```cpp
SatelliteConfig testConfig;
testConfig.name = "testSatellite";
testConfig.latitude = 1280 / 2;
testConfig.longitude = 640 / 2;
testConfig.x_velocity = 100;
testConfig.y_velocity = 100;

Satellite testSatellite(testConfig);
```

```cpp
// In window loop
testSatellite.visual.setPosition(sf::Vector2f(1280, 640));
window.draw(testSatellite.visual);
```
Next, I needed it to move across the screen. Initially, I tried to use a while loop to smoothly move the white circle to the edge of the screen. `(x = 1280)` However I realised that it was inside the event loop, causing it to move instantly. Taking it out of the event loop fixed the issue.

Now, since the circle was going outside the bounds of the screen while it was moving, It was necessary to include a way for it to wrap around the map. I found this easy as just setting positional updates to be `latitude MOD 1280` and `longitude MOD 640`. However, there were still some issues when `MOD` was used with a negative value, to account for this, I made the program first check if the latitude/longitude was less than `0`, and if it was, it would be positioned to the opposite side of the window "re-emerging".

https://github.com/user-attachments/assets/f0c959ca-dbde-4471-bc4f-7684aa4d667a

# Researching how to get the Satellite Data
Researching online has taught me that my current implementation isn't feasible, it turns out, my understanding of latitude and longitude were wrong, it is not a replacement for any x/y coordinates but an entirely different coordinate system using degrees and is specifically for the earth.

Unlike FlightRadar24 where planes broadcast their exact location through GPS in real time, Satellites do not have such a thing. Instead, I found out that they have TLE "Two Line Element" Data that includes the name of the satellite, and any orbital data such as it's inclination (tilt), mean motion (orbits per day) etc. They use all of this information in an algorithm called SGP4, which takes in a specific time $t$ and returns a 3D Position Vector in km representing the satellite's position in 3D space and Velocity Vector representing the speed and direction of the satellite. The format for this is $(x,y,z)$. 

Experimenting with this:





