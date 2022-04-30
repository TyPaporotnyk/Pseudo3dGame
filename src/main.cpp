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

    sf::Clock clock;

    // Text init
    sf::Font font;
    font.loadFromFile(DATA_DIR + std::string("/font/font.ttf"));

    sf::Text text;
    text.setFont(font);
    text.setPosition(20,20);
    text.setCharacterSize(24);

    // World and camera init
    World world(std::string(DATA_DIR + std::string("/texture/sky/sky.png")));

    std::string path = DATA_DIR + std::string("/map/map.png");
    Vector playerPos = world.loadMapFromImage(path);

    Camera camera(world, playerPos, 0.05);

    bool mapView = false;
    bool isPaused = false;

    // Cursor init
    window.setMouseCursorVisible(isPaused);

    while(window.isOpen())
    {
        // Control
        sf::Event event = {};
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
            {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::M) && !isPaused)
            {
                mapView = !mapView;
            }
            if (event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                isPaused = !isPaused;
                window.setMouseCursorVisible(isPaused);
                sf::Mouse::setPosition(sf::Vector2i(window.getSize().x / 2, window.getSize().y / 2), window);
            }
        }

        window.clear();

        // Calculation
        if (!isPaused)
        {
            camera.control(window, 1, isPaused);
        }
        // Draw world
        camera.drawWorld(window);


        if (mapView)
        {
            // Draw map and camera
            camera.draw(window);
            world.draw(window);
        } else
        {
            // Draw text
            auto textSceneBuilder = std::ostringstream();
            textSceneBuilder << std::setw(2) << 1'000'000 / clock.restart().asMicroseconds() << " FPS" << std::endl;
            textSceneBuilder << std::setprecision(3) << "x: " << camera.getPosition().x << ", ";
            textSceneBuilder << std::setprecision(3) << "y: " << camera.getPosition().y << std::endl;
            textSceneBuilder << std::setw(3) << "angle: " << camera.getAngle() << std::endl;

            text.setString(textSceneBuilder.str());

            window.draw(text);
        }

        window.display();

    }
    return 0;
}
