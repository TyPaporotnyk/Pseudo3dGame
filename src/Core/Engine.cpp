//
// Created by Даниил on 30.04.2022.
//

#include "Engine.h"

#include "Painter.h"

#include "Helper/ConfigParser.h"

#include "../Precompiler.h"

void Engine::initWindow()
{
    std::string title = "None";
    sf::VideoMode window_bounds(1280,720);
    unsigned frame_limit = 60;
    bool vertical_sync_enabled = false;

    ConfigParser* windowParser = new ConfigParser;
    windowParser->parse(DATA_DIR + std::string("/config/windowConfig.ini"));


    title                 = windowParser->lookupString("name");
    window_bounds.width   = windowParser->lookupInt("windowWidth");
    window_bounds.height  = windowParser->lookupInt("windowHeight");
    frame_limit           = windowParser->lookupInt("maxFps");
    vertical_sync_enabled = windowParser->lookupBool("verticalSync");


    window = new sf::RenderWindow(window_bounds, title);
    window->setFramerateLimit(frame_limit);
    window->setVerticalSyncEnabled(vertical_sync_enabled);
    window->setMouseCursorVisible(false);

    delete windowParser;
}

void Engine::initWorld()
{
    int world_scale = 16;

    ConfigParser* worldParser = new ConfigParser;
    worldParser->parse(DATA_DIR + std::string("/config/worldConfig.ini"));

    world_scale = worldParser->lookupInt("cellScale");

    world = new World(std::string(DATA_DIR + std::string("/texture/sky/sky.png")), "", world_scale,
                      window->getSize().x, window->getSize().y);
    Loaders::WorldLoader::loadMap(*world, DATA_DIR + std::string("/map/map.png"));

    delete worldParser;
}

void Engine::initCamera()
{
    float speed = 2;
    int raysNum = 100;
    int sight = 60;

    ConfigParser* cameraParser = new ConfigParser;
    cameraParser->parse(DATA_DIR + std::string("/config/playerConfig.ini"));

    speed   = cameraParser->lookupFloat("speed");
    raysNum = cameraParser->lookupInt("raysNum");
    sight   = cameraParser->lookupInt("sight");

    camera = new Camera(*world,{10,10}, speed, raysNum, sight,0);

    delete cameraParser;
}

Engine::Engine()
{
    initWindow();
    initWorld();
    initCamera();

    isPaused = false;

    text.setFont(*RESOURCE_MANAGER.loadFont(std::string(DATA_DIR + std::string("/font/font.ttf"))));
    text.setPosition(world->getCellScale(),(20*world->getCellScale())+world->getCellScale());
    text.setCharacterSize(24);
}

Engine::~Engine()
{
    delete window;
    delete world;
    delete camera;
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

    Core::Painter::drawWorld(*window, *camera, *world);
    Core::Painter::drawSight(*window, *camera, *world);
    Core::Painter::drawMap(*window, *world);

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
