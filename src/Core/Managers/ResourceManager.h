//
// Created by Даниил on 29.04.2022.
//

#ifndef PSEUDO3DGAME_RESOURCEMANAGER_H
#define PSEUDO3DGAME_RESOURCEMANAGER_H

#include <SFML/Graphics.hpp>
#include <fstream>
#include <sstream>
#include <iostream>

#include "IManager.h"

#include "../Helper/Holders/Singleton.h"

#include "../Helper/Vector.h"


namespace Core::Managers
{
    class ResourceManager : public IManager<ResourceManager>,public Helper::Holders::Singleton<ResourceManager>
    {
    private:
        std::map<std::string, std::shared_ptr<sf::Texture>> _textures;
        std::map<std::string, std::shared_ptr<sf::Font>> _fonts;

    public:
        void initialize() override;

        sf::Texture* loadTexture(const std::string& filename);
        sf::Font* loadFont(const std::string& filename);
    };
}


#endif //PSEUDO3DGAME_RESOURCEMANAGER_H
