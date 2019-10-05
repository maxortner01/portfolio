#include "GameEngine.h"

float Card::width = 0;
float Card::height = 0;

sf::Texture Card::back = sf::Texture();
std::vector<sf::Vector2i> Card::picked_cards = std::vector<sf::Vector2i>();

std::vector<std::string> Poker::hand_names = {
    "High Card",
    "Pair",
    "Two Pair",
    "Set",
    "Straight",
    "Flush",
    "Full House",
    "Quad",
    "Straight Flush",
    "Royal Flush"
};

void GameEngine::init() {
    Card::back.loadFromFile("assets/images/cardback.png");
    cards.setTexture(textures.cards);

    Card::back.setSmooth(true);
    Card::width = (float)width; Card::height = (float)height;

    poker.playerPosition = poker.getPlayerSize();
    poker.addPlayer(Player());
    poker.addPlayer(Player());
    poker.addPlayer(Player());
    poker.addPlayer(Player());
    poker.addPlayer(Player());
    poker.addPlayer(Player());
    poker.step();
        
}

void GameEngine::drawTable() {
    sf::RectangleShape middle;
    middle.setPosition(sf::Vector2f(width / 4.f, height / 4.f));
    middle.setSize(sf::Vector2f(width / 2.f, height / 2.f));
    middle.setTexture(&textures.felt);
    
    // set outline color to brown
    middle.setOutlineColor(sf::Color(160, 82, 45));
    middle.setOutlineThickness(10.f);

    window.draw(middle);

    sf::CircleShape ends;
    ends.setPointCount(200);
    ends.setRadius(height / 4.f);
    ends.setTexture(&textures.felt);
    ends.setOrigin(sf::Vector2f(ends.getRadius(), ends.getRadius()));

    // set outline color to brown
    ends.setOutlineColor(sf::Color(160, 82, 45));
    ends.setOutlineThickness(10.f);

    ends.setPosition(sf::Vector2f(width / 4.f, height / 2.f));
    window.draw(ends);

    ends.setPosition(sf::Vector2f(width - (width / 4.f), height / 2.f));
    window.draw(ends);

    middle.setOutlineThickness(0.f);
    window.draw(middle);


    //draw players
    for (int i = 0; i < 9; i++) {
        int index = (i + 4 - poker.playerPosition) % 9;

        sf::CircleShape circle;
        circle.setRadius(10.f);
        sf::Vector2f player = Poker::getPlayerPosition({width, height}, index);
        circle.setPosition(player);

        if (i >= poker.getPlayerSize())
            circle.setFillColor(sf::Color::Black);
        else {
            int p = poker.getPlayerRank(i);
            drawString(Poker::hand_names.at(p), { player.x, player.y - height / 5.f });

            /**/ if (poker.getPlayer(i).active) {
                circle.setOutlineColor(sf::Color::Red);
                circle.setOutlineThickness(5.f);
            }
            else if (poker.getPlayer(i).folded) {
                circle.setFillColor(sf::Color(255, 255, 255, 100));
            }

        }

        window.draw(circle);
    }
}

void GameEngine::draw() {
    //Render background
    sf::Sprite background;
    background.setTexture(textures.bg);
    background.setColor(sf::Color(255, 255, 255, 200));

    sf::FloatRect size = background.getGlobalBounds();
    sf::Vector2f scale = {
        width / size.width,
        height / size.height
    };

    background.setScale(scale);
    window.draw(background);

    //timer at top
    sf::RectangleShape rTime;
    rTime.setPosition(sf::Vector2f(width / 4, 10));

    rTime.setSize(sf::Vector2f((width / 2), height / 40.f));
    rTime.setFillColor(sf::Color(255, 255, 255, 100));
    window.draw(rTime);

    //Set length according to time elapsed
    rTime.setSize(sf::Vector2f((width / 2) * (poker.timer.getElapsedTime().asSeconds() / poker.limit), height / 40.f));

    rTime.setFillColor(sf::Color(205, 133, 63, 255));
    window.draw(rTime);

    //Draw board table
    drawTable();

    // draw fps
    drawString(std::to_string( (int)fps ), { 0, 0 });
    
    for (int i = 0; i < poker.getCards().size(); i++) {
        Card cPokerCard = poker.getCards().at(-i + poker.getCards().size() - 1);

        sf::Sprite sCard;
        cPokerCard.loadSprite(&sCard, cards);

        sCard.setScale({ (width / 1920.f) * sCard.getScale().x, (height / 1080.f) * sCard.getScale().y});
        sCard.setOrigin(sf::Vector2f(
                (float)sCard.getLocalBounds().width  / 2.f,
                (float)sCard.getLocalBounds().height / 2.f
            ));

        if (cPokerCard.folded)
            sCard.setColor(sf::Color(255, 255, 255, 127));
        
        sCard.setRotation(cPokerCard.rotation);

        drawSprite(sCard, cPokerCard.position);
    }

    // draw options
    drawString(Poker::hand_names.at(poker.getPlayerRank(poker.playerPosition)), {0, (float)height - 40});

}

void GameEngine::update() {

    if (poker.timer.getElapsedTime().asSeconds() > poker.limit) {
        poker.fold();
        poker.step();
    }

    // handle events
    sf::Event event;
    while ( window.pollEvent( event ) ) {

        switch ( event.type ) {
            case sf::Event::Closed:
                window.close();
                break;

            case sf::Event::KeyPressed:
                if ( sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) )
                    window.close();
                    
                if ( sf::Keyboard::isKeyPressed(sf::Keyboard::Space) ) {
                    poker.step();
                }

                if ( sf::Keyboard::isKeyPressed(sf::Keyboard::F) ) {
                    poker.move(Poker::MOVE::FOLD, 0, poker.playerPosition);              
                }

                break;

            default:
                break;
        }
    }

    // handle drawing
    window.clear();


    draw();
}
