#include "ResourceManager.h"
#include <map>
#include <memory>
#include <iostream>

namespace ResourceManager
{
    namespace
    {
        std::map<std::string, std::shared_ptr<sf::Texture>> _textures;
        Vector playerPosition;
        int windowWidth = 0;
        int windowHeight = 0;
    }


    namespace Window
    {
        int getWindowWidth()
        {
            return windowWidth;
        }
        int getWindowHeight()
        {
            return windowHeight;
        }

        void setWindowWidth(int width)
        {
            if(windowWidth == 0)
            {
                windowWidth = width;
            }
        }

        void setWindowHeight(int height)
        {
            if(windowHeight == 0)
            {
                windowHeight = height;
            }
        }
    }



    Vector getPlayerPosition()
    {
        return playerPosition;
    }

    void loadMapFromImage(const std::string& path, World* world)
    {
        sf::Image mapImage;
        sf::Color pixel;

        mapImage.loadFromFile(path);

        int cell_height = mapImage.getSize().y;
        int cell_width = mapImage.getSize().x;

        for(size_t i = 0; i < cell_width; i++)
        {
            for(size_t j = 0; j < cell_height; j++)
            {
                if((i == 1 && j == 1) || (i == 1 && j == cell_width-1) ||
                   (i == cell_height-1 && j == 1) || (i == cell_height-1 && j == cell_width-1))
                {
                    Circle circle(std::to_string(i + 1) + ":" + std::to_string(j + 1) + "-Circle",
                                  *ResourceManager::loadTexture(std::string(DATA_DIR + std::string("/texture/woodWall1"
                                                                                                   ".jpg"))),
                                  {static_cast<float>(i),static_cast<float>(j)});
                    world->addObject(circle);
                }

                pixel = mapImage.getPixel(i,j);

                if(pixel == sf::Color(0,0,0))
                {
                    Cube cube(std::to_string(i + 1) + ":" + std::to_string(j + 1) + "-Cube",
                              *ResourceManager::loadTexture(std::string(DATA_DIR + std::string("/texture/wall2.png"))),
                              {static_cast<float>(i), static_cast<float>(j)});
                    world->addObject(cube);
                }
                else if(pixel == sf::Color(0,0,255))
                {
                    playerPosition = {static_cast<float>(i),static_cast<float>(j)};
                }
            }
        }

    }

    sf::Texture* loadTexture(const std::string& filename)
    {
        // If texture is already loaded - return pointer to it
        auto it = _textures.find(filename);
        if (it != _textures.end())
            return it->second.get();

        // Otherwise - try to load it. If failure - return zero
        std::shared_ptr<sf::Texture> texture(new sf::Texture);
        if (!texture->loadFromFile(filename))
            return nullptr;

        // If success - remember and return texture pointer
        texture->setRepeated(true);
        _textures.emplace(filename, texture);

        return texture.get();
    }
}