//
// Created by Даниил on 30.04.2022.
//

#ifndef PSEUDO3DGAME_ENGINE_H
#define PSEUDO3DGAME_ENGINE_H

#include "../Entities/World.h"
#include "../Entities/Camera.h"

class Engine
{
private:
    sf::RenderWindow* window;
    sf::Event event;

    World *world;
    Camera *camera;

    bool isPaused;

    sf::Text text;
    sf::Font font;

    sf::Clock clock;
    float deltaTime;

    void initWindow();
    void initWorld();
    void initCamera();

    void updateDTime();
    void updateEvent();

    void update();

    void render();
    void renderText();

public:

    Engine();
    virtual ~Engine();

    void run();
};


#endif //PSEUDO3DGAME_ENGINE_H
