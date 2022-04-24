#include <SFML/Graphics.hpp>

#include "2DFigures/Object2D.h"

#include "Settings.h"
#include "World.h"
#include "Camera.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Pseudo 3D Game",
                            sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);
    window.setMouseCursorVisible(false);

    World world;
    world.addObject(Object2D({{300,100},{300,300},{500,100}}));
    Camera camera(world, {30,200}, 0);

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

        camera.draw(window);
        world.draw(window);


        window.display();
    }

    return 0;
}
