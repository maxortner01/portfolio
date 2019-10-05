#include "engine.h"

Engine::Engine(int nWidth, int nHeight, bool bFullscreen, std::string title, bool aa) {
    width = nWidth; height = nHeight;

    if (aa)
        settings.antialiasingLevel = 12;

    // create window
    window.create( sf::VideoMode( width, height ), title, 7, settings );

    // load font
    fSys.loadFromFile("assets/fonts/arial.ttf");
}

void Engine::run() {

    init();

    sf::Clock clock;
    while ( window.isOpen() ) {

        // animation handling
        for (int i = 0; i < animations.size(); i++) {
            if (animations.at(i).update() == 1) {
                animations.erase(animations.begin() + i);
            }
        }

        //printf((std::to_string(animations.size()) + "\n").c_str());

        updateGL();

        update();

        window.display();

        fps = 1.f / clock.getElapsedTime().asSeconds();
        clock.restart();

        uFrame++;
    }

    onDestroy();

}

void Engine::drawString(std::string str, sf::Vector2f location, unsigned int size) {
    sf::Text tFps;
    tFps.setPosition(location);
    tFps.setString(str);
    tFps.setFont(fSys);
    tFps.setCharacterSize(size);
    window.draw(tFps);
}

void Engine::drawSprite(sf::Sprite spr, sf::Vector2f location) {
    spr.setPosition(location);
    window.draw(spr);
}

void Engine::drawSprite(sf::Sprite spr, sf::IntRect section, sf::Vector2f location) {
    spr.setTextureRect(section);
    spr.setPosition(location);
    window.draw(spr);
}