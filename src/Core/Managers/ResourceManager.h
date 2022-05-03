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

#include "../../Helper/Holders/Singleton.h"

#include "../Entities/World.h"

#include "../../Helper/Vector.h"


namespace Core::Managers
{
    class ResourceManager : public IManager<ResourceManager>,public Helper::Holders::Singleton<ResourceManager>
    {
    private:
        std::map<std::string, std::shared_ptr<sf::Texture>> _textures;
        int windowWidth = 0;
        int windowHeight = 0;

    public:
        void initialize();

        int getWindowWidth() const;
        int getWindowHeight() const;

        void setWindowWidth(int width);
        void setWindowHeight(int height);

        sf::Texture* loadTexture(const std::string& filename);
    };
}


#endif //PSEUDO3DGAME_RESOURCEMANAGER_H
