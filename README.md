# Documenting my first project

-- So I wanted to document the process however I was too deep into learning and building this that I forgot, so here's my official writeup!

### Inspiration and Motivations
Since I wanted to actually build something in C++, I thought, why not a satellite tracker? that's pretty cool, and it connects to my interest in space and astronomy.
Back when I used to go plane watching near Heathrow airport I used to use an app called FlightRadar24, which displayed the location of planes through their user interface, I thought it would be worthwhile to take inspiration and build something similar

### Why C++?
Now you might be asking, why C++?: This is because I've wanted to work in a low level language and build a desktop application.
If I want to host the project on the web (which I probably wont be) then I may use other languages like JavaScript and HTML. I figured this would also teach me the basics of software development and how to actually use programming to achieve this.

## Day 1: Choosing an IDE & Setting the project scope
I decided to go with Visual Studio as I already have it downloaded and it seems suitable for developing desktop applications, I intend for the project to be a way to view the current location of satellites on a world map.

<img width="529" height="460" alt="image" src="https://github.com/user-attachments/assets/26f135db-ea3e-4d52-bc50-77b96d9a49dd"/>

This is an image of FlightRadar24's map scroll system. While my ultimate goal is to achieve something like this, it's something I'll work on integrating if I have time at the end of the project, I don't want it to get too technically complex yet.

I first think starting off with a Fixed 2D World Map is a realistic starting point for this demonstration I will use an equirectangular world map
<img width="1280" height="640" alt="blue_marble" src="https://github.com/user-attachments/assets/4b8617ab-7f6d-404f-b573-bbc74b9a558c"/>

## Technical Stack
Tech Stack Used:
C++20
SFML 3.1
CMake 3.23

In order to build a desktop application, I first need a way to render and open a window. To do this, I decided to use a library called SFML, which uses a loop to keep the window open and update it.
I also thought if other people were going to download and run my software, there should be an easier process to build and run it. That's when I found CMake, which is a useful tool to help with the build process.

