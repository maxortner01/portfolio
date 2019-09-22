#pragma once

#define WIDTH  950
#define HEIGHT 392
#define X_AMT  13
#define Y_AMT  4

#include "EngineName.h"

struct Card
{
    enum FACE {
        CLUBS,
        SPADES,
        HEARTS,
        DIAMONDS,
        FACE_AMOUNT
    } typedef FACE;

    int value, face;

    bool folded    = false;
    bool face_down = false;

    static std::vector<sf::Vector2i> picked_cards;

    float rotation = 0;
    sf::Vector2f position;
    static sf::Texture back;

    static float width, height;

    Card(int v, int f, sf::Vector2f location = { 0, 0 }) {
        value = v; face = f;
        position = location;
    }

    void loadSprite(sf::Sprite *spr, sf::Sprite card_map) {
        if (!face_down) {
            *spr = card_map;
            spr->setTextureRect({ 
                (WIDTH  / X_AMT) * value, 
                (HEIGHT / Y_AMT) * face, 
                (WIDTH  / X_AMT),
                (HEIGHT / Y_AMT)
            });
        }
        else {
            spr->setTexture(back);
            spr->setScale(sf::Vector2f(
                (float)(WIDTH  / X_AMT)  / (float)spr->getGlobalBounds().width,
                (float)(HEIGHT / Y_AMT) / (float)spr->getGlobalBounds().height
            ));
        }
    }

    static Card getRandom(sf::Vector2f location = { 0, 0 }, bool fromDeck = true) {
        sf::Vector2i loc = { rand() % X_AMT, rand() % Y_AMT };

        if (fromDeck) {
            while (1) {
                loc = { rand() % X_AMT, rand() % Y_AMT };

                bool found = false;
                for (int i = 0; i < picked_cards.size(); i++) {
                    if (loc.x == picked_cards.at(i).x && loc.y == picked_cards.at(i).y) {
                        found = true;
                        break;
                    }
                }

                if (!found) {
                    picked_cards.push_back(loc);
                    break;
                }
            }
        }
            
        Card card(loc.x, loc.y, location);

        return card;
    }

    static void clear() { picked_cards.clear(); }

    static sf::Vector2f getCardSize() { return { (WIDTH / X_AMT) * (width / 1920.f), (HEIGHT / Y_AMT) * (height / 1080.f) }; }

    bool operator==(Card card) {
        if (card.value == value && card.face == face)
            return true;

        return false;
    }
};