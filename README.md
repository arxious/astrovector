# Documenting my first project

### Inspiration and Motivations
Since I wanted to actually build something in C++, I thought, why not a satellite tracker? that's pretty cool, and it connects to my interest in space and astronomy.
Back when I used to go plane watching near Heathrow airport, I used to use an app called FlightRadar24. The purpose was to display the location of planes through their user interface, which I thought it would be worthwhile to take inspiration and build something similar.

### Why C++?
This is because I've wanted to work in a low level language and build a desktop application. I don't know if the project will be good enough to host on the web, but if it gets to that stage, then I dont mind adding an integration for that.

## Choosing an IDE
I decided to go with Visual Studio as I already have it downloaded and it seems suitable for developing desktop applications in C++, I intend for the project to display the location of satellites, My aim is to be able to click on each one, see their name, latitude, longitude, altitude, and have it map to an approximation of their position.

<img width="529" height="460" alt="image" src="https://github.com/user-attachments/assets/26f135db-ea3e-4d52-bc50-77b96d9a49dd"/>

This is an image of FlightRadar24's tracker system. This is what originally inspired me (for reference)


## Starting point
I found it reasonable to start off with a rectangular world map, while not a full scrolling system (yet), I will display this instead to build a prototype.

## Libraries and Dependencies
C++ by default does not have a way to load and render a window. To get around this, I found a useful library called **SFML**, which uses a loop to update an open window each frame. So I decided to render a window of dimensions 1280x640, the same size as the world map. In order to include SFML, in my build, I am using **CMake**, which tells the compiler how my executable will be built and what libraries to include

```cmake
FetchContent_Declare( # This was added to fetch SFML from GitHub
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.1.0
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
)

FetchContent_MakeAvailable(SFML)
```

This code will fetch the library from github and make it available in my program. Also if people download and build the executable libraries are installed automatically through this.


Next, I noticed SFML can also be used to display the world map to the screen using `sf::Texture`, which I used to load the image. However to display it to the window, I created a map sprite using `sf::Sprite`, and I could then simply draw the sprite using `window.draw(worldSprite)`, which displayed it to the screen, by default, at 0,0, which perfectly aligned the map with the window. The issue was the window was resizable, which I disabled by writing `sf::Style::Titlebar | sf::Style::Close` as as the third parameter for `sf::RenderWindow`, I had to read a lot of the documentation to figure this out.

<img width="1277" height="660" alt="image" src="https://github.com/user-attachments/assets/b02158a8-3674-457c-9dc8-e53dc7b20774"/>

Now I had a world map loaded, great. Next I needed to represent the satellites that would be displayed on the map. To do this, I found out that SFML had objects for graphics, so i used their `sf::CircleShape`, to create a white circle that had radius `3` pixels, and displayed them on the world map.

I came up with this struct as a representation of the satellite visual (the white circle), this would be in my `satellite.hpp` file, which I plan on using to handle the visuals.

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
	double speed;
};
```
In my updated version, I changed the approach, in order to display and render satellites they need will need their "configuration" populated. I also change velocity to speed as it's the magnitude.

```cpp
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
			latitude = cfg.latitude;
			longitude = cfg.longitude;
			altitude = cfg.altitude;
			speed = cfg.speed;
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


Satellite testSatellite(testConfig);
```

```cpp
// In window loop
testSatellite.visual.setPosition(sf::Vector2f(1280, 640));
window.draw(testSatellite.visual);
```
Next, I needed it to move across the screen. Initially, I tried to use a while loop to smoothly move the white circle to the edge of the screen. However I realised that it was inside the window loop, causing it to move instantly. Taking it out of the window loop fixed the issue.

Now, since the circle was going outside the bounds of the screen while it was moving, It was necessary to include a way for it to wrap around the map. I found this easy as just setting positional updates to be `X MOD 1280` and `Y MOD 640`. However, there were still some issues when `MOD` was used with a negative value, to account for this, I made the program first check if the latitude/longitude was less than `0`, and if it was, it would be positioned to the opposite side of the window "re-emerging".

https://github.com/user-attachments/assets/f0c959ca-dbde-4471-bc4f-7684aa4d667a

Experimenting with this taught me the basics of how to represent the satellite and how I would get it to move across the map, now I needed to research how to get the satellite data to display it's position in real time.

# Researching how to get the Satellite Data

Unlike FlightRadar24 where planes broadcast their exact location through GPS in real time, satellites don't. This made it pretty hard to find a suitable way to find data representing their exact positions. Through researching modern satellite trackers, I found https://celestrak.org/ which has orbital data on over 12,600 satellites. However, this data does not directly specify it's location over the earth. Instead it has "orbital data" which includes `inclination`, `orbit period`, etc. The website says this data can be used to get a suitable approximation of their position through the `SGP4` Algorithm, which supposedly takes these factors, runs them through an extensive mathematical algorithm and returns `Position` and `Velocity` Vectors for the satellite in question.

### Small Note
The website had a section on converting these vectors into latitude and longitude, **that's when I found my understanding of latitude and longitude was wrong**, I was quite silly for thinking it was supposed to represent cartesian x and y coordinates, instead it's an entirely different coordinate system measured in degrees.

<img width="500" height="391" alt="Lat_Long" src="https://github.com/user-attachments/assets/d042fa2c-3623-4371-be3b-67103d455335"/>

I must say though, it is quite similar, Latitude loosely represents the y axis and Longitude the x.

Latitude spans $-90 < Lat < 90$ and Longitude spans $-180 < Long < 180$, together they can describe any geographic position. 


## Refactoring my program + Parsing the data
From what I found on CelesTrak, the SGP4 Algorithm takes in a satellite's TLE data and returns position and velocity vectors. I wasn't going to re-implement the entire thing myself by scratch which would take too long, so I found a very useful repository that is able to parse the TLE data, and run the SGP4 Algorithm for me which I'll link here: https://github.com/dnwrnr/sgp4.

Inside my `CMakeLists.txt`, I added support for the sgp4 library from github

```cmake
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # This is so their tests don't run during the build process
set(BUILD_TESTS OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
    sgp4
    GIT_REPOSITORY https://github.com/dnwrnr/sgp4.git
    GIT_TAG master
    GIT_SHALLOW TRUE
)
```

Inside `main.cpp`, I include:

```cpp
#include <libsgp4/SGP4.h>
#include <libsgp4/Tle.h>
```

These libraries will assist me in parsing the satellite data and returning the approximate position of the satellite.

# Testing display and accuracy

```cpp
libsgp4::Tle tle("ISS (ZARYA)",
    "1 25544U 98067A   26244.49851261  .00003910  00000-0  79223-4 0  9994",
    "2 25544  51.6312 282.3953 0005055  96.4740 263.6825 15.48958602583586"
);
```
I will be testing the ISS and seeing if I can get it displayed on the world map
I obtained the updated TLE data that I downloaded from CelesTrak, this function takes in the name, and the first and second line of the data, and returns a tle object

```cpp
libsgp4::SGP4 sgp4(tle);
```
I then passed the data into the library's SGP4 function, which i found returns an sgp4 object

```cpp
libsgp4::DateTime startTime = libsgp4::DateTime::Now(true);
libsgp4::Eci initialEci = sgp4.FindPosition(startTime);
libsgp4::CoordGeodetic initialGeo = initialEci.ToGeodetic();
libsgp4::Vector initialVel = initialEci.Velocity();
```

From this code, I get the current time in UTC, and pass it to `eci` to get a position at that time, basically the satellite's position is measured relative to a fixed axis that does not rotate with the earth. In order to fix this, we have to convert it to ECEF (Earth Centred, Earth Fixed), which the `.ToGeodetic()` function handles, and it also returns the satellite's latitude and longitude that I can now use. I also got it's initial velocity which i will get the magnitude of later.

```cpp
SatelliteConfig testConfig;
testConfig.name = "ISS (ZARYA)";
testConfig.latitude = libsgp4::Util::RadiansToDegrees(initialGeo.latitude);
testConfig.longitude = libsgp4::Util::RadiansToDegrees(initialGeo.longitude);
testConfig.altitude = initialGeo.altitude;
testConfig.speed = initialVel.Magnitude();

Satellite testSatellite(testConfig);
```

I made a test config for the first satellite i'll be testing which is the ISS, since the library returned the longitude and latitude in radians, I had to convert them to degrees, which the library had a function for. The altitude was simply measured in km so I used that value, and I took the magnitude of the velocity which was a vector, so I get a constant speed.

```cpp
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
 ```

Inside the window loop, I repeated the process of getting the latitude and longitude of the satellite at the current time, I have to repeatedly convert this to degrees since it is returned in radians, and I updated each attribute in the test satellite, I added a debug statement so I can view the stats of the satellite as it is running.

The hard part was realising how to convert the latitude and longitude into fixed screen coordinates so it could be displayed on my world map, I knew that the range of the longitude was $-180 < x < 180$ measured in degrees, so I added 180 to all sides to get $0 < x + 180 < 360$, using this, now any value of x will be between 0 and 360, so i divided by 360 to get a percentage between 0 and 1. multiplying that by my width (1280) gets me how far across the map the satellite is.

For the latitude, the process was similar but the latitude's range was $-90 < y < 90$. Adding 90 to both sides we get $0 < y + 90 < 180$, the problem with this is, if I have e.g. latitude = -90, we would expect the satellite to be at the bottom of the map, however, -90 + 90 = 0, in the program, this would mean that the satellite is rendered at the top. to fix this, we would instead take 90 - y, as 90 - - 90 = 180 (which is at the bottom), and at 90, 90 - 90 = 0 which is at the top. This was the way I was able to fix that issue.

<img width="686" height="447" alt="image" src="https://github.com/user-attachments/assets/4c74ef3e-0de9-4372-9178-d94a7e5375bd"/>

I finally managed to get it working and compared it using this website https://isstracker.pl/en?satId=25544, It was fair to say that it was pretty accurate and I was happy with what I accomplished

# 01/09/2025
Unfortunately exams are coming up and I didn't get much time to complete the project. I'm happy I managed to display the ISS and I learned a lot about C++, how to make desktop applications, how to work with libraries, CMake and how to build an executable, all of this was very useful experience to me and I hope to finish this project in the future.






