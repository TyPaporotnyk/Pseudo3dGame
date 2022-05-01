//
// Created by Даниил on 29.04.2022.
//

#ifndef PSEUDO3DGAME_RESOURCEMANAGER_H
#define PSEUDO3DGAME_RESOURCEMANAGER_H

#include <SFML/Graphics.hpp>
#include <fstream>
#include <sstream>
#include <iostream>

#include "../Resources/Vector.h"
#include "../Entities/World.h"

#include "../Entities/2DFigures/Object2D.h"
#include "../Entities/2DFigures/Cube.h"
#include "../Entities/2DFigures/Circle.h"

namespace ResourceManager
{
    namespace Window
    {
        int getWindowWidth();
        int getWindowHeight();

        void setWindowWidth(int width);
        void setWindowHeight(int height);
    }
    void loadMapFromImage(const std::string& path, World* world);

    sf::Texture* loadTexture(const std::string& filename);

    Vector getPlayerPosition();
}


#endif //PSEUDO3DGAME_RESOURCEMANAGER_H
