#include "ResourceManager.h"

#include <map>
#include <memory>

int Core::Managers::ResourceManager::ResourceManager::getWindowWidth() const
{
    return windowWidth;
}

int Core::Managers::ResourceManager::ResourceManager::getWindowHeight() const
{
    return windowHeight;
}

void Core::Managers::ResourceManager::ResourceManager::setWindowWidth(int width)
{
    windowWidth = width;
}

void Core::Managers::ResourceManager::ResourceManager::setWindowHeight(int height)
{
    windowHeight = height;
}

sf::Texture *Core::Managers::ResourceManager::ResourceManager::loadTexture(const std::string &filename)
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

void Core::Managers::ResourceManager::initialize()
{

}
