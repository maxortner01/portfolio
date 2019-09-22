#pragma once

#include "EngineName.h"
#include "card.h"
#include "poker.h"

class GameEngine : public Engine
{
    struct Textures {
        sf::Texture cards, bg, felt;

        Textures() {
            cards.loadFromFile("./assets/images/cards.jpg");
            bg.loadFromFile("./assets/images/bg.jpg");
            felt.loadFromFile("./assets/images/fabric.jpg");
            
            felt.setRepeated(true);
        }
    };

    //std::vector<Card> Cards;
    std::vector<sf::Uint8> screenBuffer;

    Poker poker;

    float val = 0;

    Textures textures;
    sf::Sprite cards;

    int nStep = 0;

public:
    GameEngine(int w, int h, bool f = false, std::string title = "GameEngine") : Engine(w, h, f, title), poker(w, h, &animations) {}

    void draw();
    void drawTable();

    void update() override;
    void init()   override;

};