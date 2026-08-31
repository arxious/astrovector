# Documenting my first project

-- So I wanted to document the process however I was too deep into learning and building this that I forgot, so here's my official writeup!

### Inspiration and Motivations
Since I wanted to actually build something in C++, I thought, why not a satellite tracker? that's pretty cool, and it connects to my interest in space and astronomy.
Back when I used to go plane watching near Heathrow airport, I used to use an app called FlightRadar24. The purpose was to display the location of planes through their user interface, which I thought it would be worthwhile to take inspiration and build something similar.

### Why C++?
Now you might be asking, why C++? This is because I've wanted to work in a low level language and build a desktop application. I don't know if the project will be good enough to host on the web, but if it gets to that stage, then I dont mind adding an integration for that.

## Day 1: Choosing an IDE & Setting the project scope
I decided to go with Visual Studio as I already have it downloaded and it seems suitable for developing desktop applications in C++, I intend for the project to display the location of satellites, My aim is to be able to click on each one, see their name, latitude, longitude, altitude, and have it map to an approximation of their position.

<img width="529" height="460" alt="image" src="https://github.com/user-attachments/assets/26f135db-ea3e-4d52-bc50-77b96d9a49dd"/>

This is an image of FlightRadar24's tracker system. This is what originally inspired me (for reference)


# Starting point
I found it reasonable to start off with a rectangular world map, while not a full scrolling system (yet), I will display this instead to build a prototype.

<img width="1280" height="640" alt="blue_marble" src="https://github.com/user-attachments/assets/4b8617ab-7f6d-404f-b573-bbc74b9a558c"/>


## Technical Stack
Tech Stack Used:
C++20
SFML 3.1
CMake 3.23

In order to build a desktop application, I first need a way to render and open a window. To do this, I decided to use a library called SFML, which uses a loop to keep the window open and update it.
I also thought if other people were going to download and run my software, there should be an easier process to build and run it. That's when I found CMake, which is a useful tool to help with the build process.

