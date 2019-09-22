#pragma once

#include "card.h"

struct Player
{
    std::vector<Card> cards;

    bool folded = false;
    bool active = false;

    Player() { cards.reserve(2); }
};

class Poker
{
    unsigned int width, height;
    unsigned int uCurrentStep = 0;
    unsigned int uCurrentTurn = 0;


    std::vector<Animate> *animations;

    std::vector<Player> Players;

    std::vector<Card> Cards;
    std::vector<Card> off_cards;


public:
    static std::vector<std::string> hand_names;

    enum MOVE {
        FOLD, 
        CALL,
        RAISE,
        CHECK
    } typedef MOVE;

    enum HAND_RANK {
        HIGH_CARD,
        PAIR,
        TWO_PAIR,
        SET,
        STRAIGHT,
        FLUSH,
        FULL_HOUSE,
        QUAD,
        STRAIGHT_FLUSH,
        ROYAL_FLUSH,
        AMOUNT
    } typedef RANK;

    struct Hand {
        RANK rank;
        int  high;
    };

    unsigned int playerPosition;

    float limit = 10.f;
    sf::Clock timer;

    Poker(int w, int h, std::vector<Animate> *a) { 
        width = w; 
        height = h; 
        animations = a;

        Cards.reserve(8);

        //printf("a\n");
        //for (int i = 0; i < 4; i++) {
        //    step();
        //}
        //printf("a\n");

    }

    inline void addPlayer(Player player) { Players.push_back(player); }
    inline Card getCard(int index) { return Cards.at(index); }
    inline int  getPlayerSize()    { return Players.size();  }
    inline Player getPlayer(int index) { return Players.at(index); }

    RANK getPlayerRank(int playerLocation) {
        std::vector<Card> cards = Players.at(playerLocation).cards;

        std::vector<int>  suits;
        std::vector<int>  values;
        
        suits.resize(Card::FACE::FACE_AMOUNT);
        values.resize(13);

        //Count amount of suits
        suits.at(cards.at(0).face)++;
        suits.at(cards.at(1).face)++;

        //Count amount of values
        values.at(cards.at(0).value)++;
        values.at(cards.at(1).value)++;
        
        for (int i = 0; i < Cards.size(); i++) {
            suits.at(Cards.at(i).face)++;
            values.at(Cards.at(i).value)++;
        }

        std::sort(values.begin(), values.end());
        std::reverse(values.begin(), values.end());

        std::sort(suits.begin(), suits.end());
        std::reverse(suits.begin(), suits.end());
        
        bool flush = suits.at(0) >= 5;
        bool straight = false;

        //for (int i = 0; i < values.size(); i++)
        //    printf((std::to_string(values.at(i)) + ", ").c_str());
        //printf("\n");

        //Royal Flush

        //Straight flush
        /**/ if (straight && flush)
            return RANK::STRAIGHT_FLUSH;

        //Quad
        else if (values.at(0) >= 4)
            return RANK::QUAD;

        //Full House
        else if (values.at(0) == 3 && values.at(1) == 2)
            return RANK::FULL_HOUSE;

        //Flush
        else if (flush)
            return RANK::FLUSH;

        //Straight
        else if (straight)
            return RANK::STRAIGHT;

        //Set
        else if (values.at(0) == 3)
            return RANK::SET;

        //Two Pair
        else if (values.at(0) == 2 && values.at(1) == 2)
            return RANK::TWO_PAIR;

        //Pair
        else if (values.at(0) == 2)
            return RANK::PAIR;

        return RANK::HIGH_CARD;
    }

    inline std::vector<Card> getCards() {
        std::vector<Card> all_cards = Cards;

        //Get all the players cards and compile them
        for (int i = 0; i < Players.size(); i++) {
            Card card1 = Players.at(i).cards.at(0);
            Card card2 = Players.at(i).cards.at(1);

            if (i != playerPosition) {
                card1.face_down = false;
                card2.face_down = false;
            }

            all_cards.push_back(card1);
            all_cards.push_back(card2);
        }

        //Get all offcards and compile them (inserting them in backwards for rendering)
        for (int i = 0; i < off_cards.size(); i++) 
            all_cards.push_back(off_cards.at(-i + off_cards.size() - 1));

        return all_cards; 
    }

    void fold(bool toss = false) {
        Players.at(0).folded = true;

        // if the player wants to toss the cards, do the animation
        if (toss) {
            for (int i = 0; i < 2; i++) {
                // angle for rotation... SFML is in degrees
                float turn_angle = ( rand() % 270 );
                // angle in which the card is thrown
                float angle      = ( rand() % 90  ) + 45 + 180;
                // strength of the throw
                float strength   = ( rand() % 300 ) + 150;

                // calculate change in x and y using previously defined variables
                float change_x = strength * cosf(angle * (3.14159f / 180.f));
                float change_y = strength * sinf(angle * (3.14159f / 180.f));

                // push seperate animations to the stack
                animations->push_back( Animate(&Players.at(0).cards.at(i).position.x, Players.at(0).cards.at(i).position.x + change_x, 2.f) );
                animations->push_back( Animate(&Players.at(0).cards.at(i).position.y, Players.at(0).cards.at(i).position.y + change_y, 2.f) );
                animations->push_back( Animate(&Players.at(0).cards.at(i).rotation  , turn_angle                       , 2.f) );
                Players.at(0).cards.at(i).folded = true;
                Players.at(0).cards.at(i).face_down = true;
            }
        }
        else {
            for (int i = 0; i < 2; i++) {
                Players.at(0).cards.at(i).face_down = true;
                animations->push_back( Animate(&Players.at(0).cards.at(i).position.y, Players.at(0).cards.at(i).position.y + height / 20.f, 2.f) );
            }
        }
    }

    void move(MOVE move, int amount, int pl) {
        if ( Players.at(pl).folded || !Players.at(pl).active )
            return;

        switch (move) {
            case FOLD:
                fold();
                break;

            default:
                return;
        }
    
        uCurrentTurn--;
        step();
    }

    void step() {
        std::vector<int> in;
        for (int i = 0; i < Players.size(); i++) {
            if (!Players.at(i).folded)
                in.push_back(i);
            
            Players.at(i).active = false;
        }

        printf((std::to_string(in.size()) + "\n").c_str());
        printf((std::to_string(uCurrentTurn) + "\n").c_str());
        printf((std::to_string(uCurrentTurn % in.size()) + "\n").c_str());
        printf("\n");

        if (uCurrentTurn % in.size() == 0) {
            uCurrentTurn = 0;
            turn();
        }
        
        for (int i = 0; i < in.size(); i++) {
            if (i == uCurrentTurn)
                Players.at(in.at(i)).active = true;
        }
        
        timer.restart();
        uCurrentTurn++;
    }

    void turn() {
        float duration = .25f;
        unsigned int nStepSize = 4;
        animations->clear();

        // First Step:
        // Deal out hands
        /**/ if (uCurrentStep % nStepSize == 0) {
            // clear cards on table and clear ongoing animations

            //Empty vectors of table cards
            Cards.clear();
            off_cards.clear();

            //Empty player hands and deal cards
            for (int i = 0; i < Players.size(); i++) {
                sf::Vector2f player_position = getPlayerPosition({width, height}, (i + 4 - playerPosition) % 9);
                //printf((std::to_string((i + 4 - playerPosition)) + "\n").c_str());

                Players.at(i).cards.clear();
                Players.at(i).folded = false;

                Players.at(i).cards.push_back(Card::getRandom({ 
                    player_position.x + ((float)(Card::getCardSize().x) * .5f), 
                    player_position.y - height / 10.f
                }));
            

                Players.at(i).cards.push_back(Card::getRandom({ 
                        player_position.x + ((float)(Card::getCardSize().x) * -.5f), 
                        player_position.y - height / 10.f
                    }));

                sf::Vector2f end_point;

                end_point = Players.at(i).cards.at(0).position;
                Players.at(i).cards.at(0).position.x = width / 2.f;
                Players.at(i).cards.at(0).position.y = height / 4.f;
                animations->push_back( Animate(&Players.at(i).cards.at(0).position.x, end_point.x, (duration / 3.f), (duration / 3.f) * i) );
                animations->push_back( Animate(&Players.at(i).cards.at(0).position.y, end_point.y, (duration / 3.f), (duration / 3.f) * i) );

                end_point = Players.at(i).cards.at(1).position;
                Players.at(i).cards.at(1).position.x = width / 2.f;
                Players.at(i).cards.at(1).position.y = height / 4.f;
                animations->push_back( Animate(&Players.at(i).cards.at(1).position.x, end_point.x, (duration / 3.f), (duration / 3.f) * (i + Players.size())) );
                animations->push_back( Animate(&Players.at(i).cards.at(1).position.y, end_point.y, (duration / 3.f), (duration / 3.f) * (i + Players.size())) );
            }

        }
        
        // Second Step:
        // Deal flop to board
        else if (uCurrentStep % nStepSize == 1) {

            //Create the off card
            int index = off_cards.size();
            off_cards.push_back(Card::getRandom({
                width / 2.f,
                height / 3.f
            }));

            off_cards.at(index).face_down = true;
            animations->push_back( Animate(&off_cards.at(index).position.x, off_cards.at(index).position.x - (float)width / 25.f, duration) );


            //Create and animate flop cards
            for (int i = 0; i < 3; i++) {
                Cards.push_back(Card::getRandom({ 
                    width / 2.f + ((float)(Card::getCardSize().x) * ((float)i - .5f - 2.f)), 
                    height / 2.f - ((float)(Card::getCardSize().y) / 2.f)
                }));

                sf::Vector2f end_point = Cards.at(i).position;
                Cards.at(i).position.x = width / 2.f;
                animations->push_back( Animate(&Cards.at(i).position.x, end_point.x, duration, duration / 4.f) );
            }
        }

        // Third Step:
        // Deal Turn
        else if (uCurrentStep % nStepSize == 2) {

            //Create the off card
            int index = off_cards.size();
            off_cards.push_back(Card::getRandom({
                width / 2.f,
                height / 3.f
            }));

            off_cards.at(index).face_down = true;
            animations->push_back( Animate(&off_cards.at(index).position.x, off_cards.at(index).position.x - (float)width / 25.f + (WIDTH / X_AMT / 2), duration) );

            //Create and animate Turn card
            Cards.push_back(Card::getRandom({ 
                    width / 2.f + ((float)(Card::getCardSize().x) * (5.f - .5f - 4.f)), 
                    height / 2.f - ((float)(Card::getCardSize().y) / 2.f)
                }));
            
            sf::Vector2f end_point = Cards.at(3).position;
            Cards.at(3).position.x = width / 2.f;
            Cards.at(3).position.y = height / 4.f;
            animations->push_back( Animate(&Cards.at(3).position.x, end_point.x, duration, duration / 4.f) );
            animations->push_back( Animate(&Cards.at(3).position.y, end_point.y, duration, duration / 4.f) );
        }

        // Third Step:
        // Deal River
        else if (uCurrentStep % nStepSize == 3) {

            //Create the off card
            int index = off_cards.size();
            off_cards.push_back(Card::getRandom({
                width / 2.f,
                height / 3.f
            }));

            off_cards.at(index).face_down = true;
            animations->push_back( Animate(&off_cards.at(index).position.x, off_cards.at(index).position.x - (float)width / 25.f + (WIDTH / X_AMT), duration) );

            //Create and animate river card
            Cards.push_back(Card::getRandom({ 
                    width / 2.f + ((float)(Card::getCardSize().x) * (6.f - .5f - 4.f)), 
                    height / 2.f - ((float)(Card::getCardSize().y) / 2.f)
                }));
                
            sf::Vector2f end_point = Cards.at(4).position;
            Cards.at(4).position.x = width / 2.f;
            Cards.at(4).position.y = height / 4.f;
            animations->push_back( Animate(&Cards.at(4).position.x, end_point.x, duration, duration / 4.f) );
            animations->push_back( Animate(&Cards.at(4).position.y, end_point.y, duration, duration / 4.f) );
            
            Card::clear();
        }

        uCurrentStep++;
    }

    static sf::Vector2f getPlayerPosition(sf::Vector2u uScreenDim, int index) {

        /**/ if (index < 4)  { //Right Circle

            sf::Vector2f origin = {
                uScreenDim.x - (uScreenDim.x / 4.f), 
                uScreenDim.y / 2.f
            };

            // 180 degrees over four players
            float degChange = 180.f / 3;

            // current degree is change in degrees * index + 90 degrees
            float degree = degChange * index - 90;

            // point is located at { r * cos(deg), r * sin(deg) }
            return {
                (uScreenDim.y / 3.5f) * cosf(degree * 3.14159f / 180.f) + origin.x,
                (uScreenDim.y / 3.5f) * sinf(degree * 3.14159f / 180.f) + origin.y
            };
        }
        else if (index == 4) { // Center (always current player)
            return {
                 uScreenDim.x / 2.f,
                (uScreenDim.y / 2.f) + (uScreenDim.y / 3.5f)
            };
        }
        else if (index > 4 && index < 9) { //Left Circle
            sf::Vector2f origin = {
                uScreenDim.x / 4.f, 
                uScreenDim.y / 2.f
            };

            // 180 degrees over four players
            float degChange = 180.f / 3;

            // current degree is -change in degrees * index + 90 degrees
            float degree = degChange * (index - 5) + 90;

            // point is located at { r * cos(deg), r * sin(deg) }
            return {
                (uScreenDim.y / 3.5f) * cosf(degree * 3.14159f / 180.f) + origin.x,
                (uScreenDim.y / 3.5f) * sinf(degree * 3.14159f / 180.f) + origin.y
            };
        }

    }
};