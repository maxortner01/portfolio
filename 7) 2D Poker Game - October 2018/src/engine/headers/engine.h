#pragma once

#include "animate.h"

#include <algorithm>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>

class Engine 
{
protected:
    // width and height of window
    unsigned int width, height, uFrame;

    // fps of screen
    float fps;

    // sfml context settings
    sf::ContextSettings settings;

    // sfml window instance
    sf::RenderWindow window;

    // standard font
    sf::Font fSys;

    // animations
    std::vector<Animate> animations;

    // virtual functions
    virtual void update() = 0;

    virtual void updateGL()  {}
    virtual void init()      {}
    virtual void onDestroy() {}
    virtual void renderUI()  {}
    
    // drawing function
    void drawString(std::string str, sf::Vector2f location = { 0, 0 } , unsigned int size = 20);

    void drawSprite(sf::Sprite  spr, sf::Vector2f location = { 0, 0 });
    void drawSprite(sf::Sprite  spr, sf::IntRect section, sf::Vector2f location = { 0, 0 });

    void drawRect(sf::IntRect rect, sf::Color color = sf::Color::White);
    void drawCircle(sf::Vector2f location, float radius, sf::Color color = sf::Color::White);

public:
    // create window instance and initialize object
    Engine(int nWidth, int nHeight, bool bFullscreen = false, std::string title = "Engine", bool aa = true);

    // main loop
    void run();

    // return size of screen
    inline sf::Vector2u getSize() { return sf::Vector2u( width, height ); }
    inline void pushAnimation(Animate animation) { animations.push_back(animation); }
};