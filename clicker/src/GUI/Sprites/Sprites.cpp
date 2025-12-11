//
// Created by XL1TTE on 11.12.2025.
//

#include "GUI/Sprites/Sprites.h"
#include <iostream>

std::unordered_map<std::string, std::shared_ptr<sf::Texture>> SpriteManager::s_textureCache;
std::unordered_map<std::string, std::shared_ptr<sf::Sprite>>  SpriteManager::s_spriteCache;

std::shared_ptr<sf::Texture> SpriteManager::GetTexture(const std::string &path)
{
    if (const auto it = s_textureCache.find(path); it != s_textureCache.end())
    {
        return it->second;
    }

    auto texture = std::make_shared<sf::Texture>();
    if (!texture->loadFromFile(path))
    {
        std::cerr << "Failed to load texture: " << path << std::endl;
        return nullptr;
    }

    s_textureCache[path] = texture;
    return texture;
}

std::shared_ptr<sf::Sprite> SpriteManager::CreateSprite(
    const sf::Vector2i &texturePos,
    const sf::Vector2i &textureSize,
    const std::string  &texturePath)
{
    const std::string key = texturePath +
                            "_" + std::to_string(texturePos.x) +
                            "_" + std::to_string(texturePos.y) +
                            "_" + std::to_string(textureSize.x) +
                            "_" + std::to_string(textureSize.y);

    if (const auto it = s_spriteCache.find(key); it != s_spriteCache.end())
    {
        return it->second;
    }

    const auto texture = GetTexture(texturePath);
    if (!texture)
    {
        return nullptr;
    }

    auto sprite = std::make_shared<sf::Sprite>(*texture);
    sprite->setTextureRect(sf::IntRect(texturePos, textureSize));

    const auto bounds = sprite->getGlobalBounds();
    sprite->setOrigin({bounds.size.x / 2, bounds.size.y / 2});

    s_spriteCache[key] = sprite;
    return sprite;
}

void SpriteManager::ClearCache()
{
    s_textureCache.clear();
    s_spriteCache.clear();
}