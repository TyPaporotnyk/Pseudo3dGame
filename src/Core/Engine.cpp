//
// Created by Даниил on 30.04.2022.
//

#include "Engine.h"

#include "Drawer.h"

#include "../Precompiler.h"

void Engine::initWindow()
{
    std::string title = "None";
    sf::VideoMode window_bounds(1280,720);
    unsigned frame_limit = 60;
    bool vertical_sync_enabled = false;

    std::ifstream ifs(DATA_DIR + std::string("/config/windowConfig.ini"));

    if(ifs.is_open())
    {
        std::getline(ifs, title);
        ifs >> window_bounds.width >> window_bounds.height;
        ifs >> frame_limit;
        ifs >> vertical_sync_enabled;
    }

    ifs.close();

    window = new sf::RenderWindow(window_bounds, title);
    window->setFramerateLimit(frame_limit);
    window->setVerticalSyncEnabled(vertical_sync_enabled);
    window->setMouseCursorVisible(false);

    RESOURCE_MANAGER.setWindowWidth(window_bounds.width);
    RESOURCE_MANAGER.setWindowHeight(window_bounds.height);
}

void Engine::initWorld()
{
    int world_scale = 16;

    std::ifstream ifs(DATA_DIR + std::string("/config/worldConfig.ini"));

    if(ifs.is_open())
    {
        ifs >> world_scale;
    }

    ifs.close();

    world = new World(std::string(DATA_DIR + std::string("/texture/sky/sky.png")), "", world_scale);
    worldLoader.loadMap(*world, DATA_DIR + std::string("/map/map.png"));
}

void Engine::initCamera()
{
    float speed = 2;
    int raysNum = 100;
    int sight = 60;

    std::ifstream ifs(DATA_DIR + std::string("/config/playerConfig.ini"));

    if(ifs.is_open())
    {
        ifs >> speed;
        ifs >> raysNum;
        ifs >> sight;
    }

    ifs.close();

    camera = new Camera(*world,{10,10}, speed, raysNum, sight,0);
}

Engine::Engine()
{
    initWindow();
    initWorld();
    initCamera();

    isPaused = false;

    font.loadFromFile(DATA_DIR + std::string("/font/font.ttf"));

    text.setFont(font);
    text.setPosition(world->getCellScale(),20*world->getCellScale() + world->getCellScale());
    text.setCharacterSize(24);
}

Engine::~Engine()
{
    delete window;
}

void Engine::updateDTime()
{
    deltaTime = clock.restart().asSeconds();
}

void Engine::run()
{
    while(window->isOpen())
    {
        updateDTime();
        update();
        render();
    }
}

void Engine::updateEvent()
{
    while (window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
        {
            window->close();
        }
        if (event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            isPaused = !isPaused;
            window->setMouseCursorVisible(isPaused);

            unsigned int windowCenterX = window->getSize().x / 2;
            unsigned int windowCenterY = window->getSize().x / 2;

            sf::Mouse::setPosition(sf::Vector2i(windowCenterX, windowCenterY), *window);
        }
    }
}

void Engine::update()
{
    updateEvent();

    camera->control(*window, deltaTime, isPaused);
}

void Engine::render()
{
    window->clear();

    Core::Drawer::drawWorld(*window, *camera, *world);
    Core::Drawer::drawSight(*window, *camera, *world);
    Core::Drawer::drawMap(*window, *world);

    renderText();

    window->display();
}

void Engine::renderText()
{
    std::stringstream ost;

    ost << std::setw(2) << (int)(1/deltaTime) << " FPS" << std::endl;
    ost << std::setprecision(3) << "x: " << camera->getPosition().x << ", ";
    ost << std::setprecision(3) << "y: " << camera->getPosition().y << std::endl;
    ost << std::setw(3) << "angle: " << camera->getAngle() << std::endl;

    text.setString(ost.str().c_str());

    window->draw(text);
}
