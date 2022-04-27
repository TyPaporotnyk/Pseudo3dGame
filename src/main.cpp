#include <SFML/Graphics.hpp>

#include <sstream>
#include <iomanip>

#include "Settings.h"
#include "World.h"
#include "Camera.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Pseudo 3D Game",
                            sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);
    window.setMouseCursorVisible(false);

    sf::Clock clock;

    sf::Font font;
    font.loadFromFile(DATA_DIR + std::string("/fonts/font.ttf"));
    sf::Text text;
//    text.setOutlineThickness(1);
//    text.setOutlineColor(sf::Color(0,0,0));
    text.setFont(font);
    text.setPosition(20,20);
    text.setCharacterSize(24);

    World world;
    Vector playerPos = world.loadMapFromImage(DATA_DIR + std::string("/map1.png"));

    Camera camera(world, playerPos, 0.05);

    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
            {
                window.close();
            }
        }

        window.clear(sf::Color(162,101,62));

        camera.control(window, 1);

        auto textBuilder = std::ostringstream();

        camera.drawWorld(window);
        if(MAP_VIEW)
        {
            camera.draw(window);
            world.draw(window);
        }
        else
        {
            auto textSceneBuilder = std::ostringstream();
            textSceneBuilder << std::setw(2) << 1'000'000 / clock.restart().asMicroseconds() << " FPS" << std::endl;
            textSceneBuilder << std::setprecision(3) << "x: " << camera.getPosition().x << ", ";
            textSceneBuilder << std::setprecision(3) << "y: " << camera.getPosition().y << std::endl;

            text.setString(textSceneBuilder.str());

            window.draw(text);
        }
        window.display();
    }

    return 0;
}
