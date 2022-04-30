#include "ResourceManager.h"
#include <map>
#include <memory>
#include <iostream>

namespace ResourceManager
{
    namespace
    {
        std::map<std::string, std::shared_ptr<sf::Texture>> _textures;
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