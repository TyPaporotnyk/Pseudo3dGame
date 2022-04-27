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

    World world;
    Vector playerPos = world.loadMapFromImage(DATA_DIR + std::string("/map1.png"));

    Camera camera(world, playerPos, 0.05);

    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        window.clear(sf::Color::Black);

        camera.control(window);

        auto textBuilder = std::ostringstream();

        textBuilder << std::setw(2) << 1'000'000 / clock.restart().asMicroseconds() << " FPS";
//        textBuilder << std::setw(3) << player.getOrigin() << " origin, ";

        window.setTitle(textBuilder.str());

        camera.draw(window);
        world.draw(window);

        window.display();
    }

    return 0;
}
