#include "ResourceManager.h"

#include <map>
#include <memory>

sf::Texture *Core::Managers::ResourceManager::ResourceManager::loadTexture(const std::string &filename)
{
    auto it = _textures.find(filename);
    if (it != _textures.end())
        return it->second.get();

    std::shared_ptr<sf::Texture> texture(new sf::Texture);
    if (!texture->loadFromFile(filename))
        return nullptr;

    texture->setRepeated(true);
    _textures.emplace(filename, texture);

    return texture.get();
}

sf::Font* Core::Managers::ResourceManager::loadFont(const std::string &filename)
{
    auto it = _fonts.find(filename);
    if (it != _fonts.end())
        return it->second.get();

    std::shared_ptr<sf::Font> font(new sf::Font);
    if (!font->loadFromFile(filename))
        return nullptr;

    _fonts.emplace(filename, font);

    return font.get();
}

sf::SoundBuffer* Core::Managers::ResourceManager::loadSound(const std::string &filename)
{
    auto it = _sounds.find(filename);
    if (it != _sounds.end())
        return it->second.get();

    std::shared_ptr<sf::SoundBuffer> soundBuffer(new sf::SoundBuffer);
    if (!soundBuffer->loadFromFile(filename))
        return nullptr;

    _sounds.emplace(filename, soundBuffer);

    return soundBuffer.get();
}

void Core::Managers::ResourceManager::initialize()
{

}




