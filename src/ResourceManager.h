//
// Created by Даниил on 29.04.2022.
//

#ifndef PSEUDO3DGAME_RESOURCEMANAGER_H
#define PSEUDO3DGAME_RESOURCEMANAGER_H


#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

namespace ResourceManager
{
    sf::Texture* loadTexture(const std::string& filename);
};


#endif //PSEUDO3DGAME_RESOURCEMANAGER_H
