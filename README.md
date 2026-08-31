# Documenting my first project

-- So I wanted to document the process however I was too deep into learning and building this that I forgot, so here's my official writeup!

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

<img width="1277" height="667" alt="image" src="https://github.com/user-attachments/assets/1ab20856-9c35-44c7-b15e-6dea906fe382" />





