//
// Created by XL1TTE on 11.12.2025.
//

#ifndef CLICKER_SPRITES_H
#define CLICKER_SPRITES_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <string>
#include <unordered_map>

class SpriteManager
{
  private:
    static std::unordered_map<std::string, std::shared_ptr<sf::Texture>> s_textureCache;

    static std::unordered_map<std::string, std::shared_ptr<sf::Sprite>> s_spriteCache;

  public:
    static std::shared_ptr<sf::Texture> GetTexture(const std::string &path);

    static std::shared_ptr<sf::Sprite> CreateSprite(
        const sf::Vector2i &texturePos,
        const sf::Vector2i &textureSize,
        const std::string  &texturePath);

    static void ClearCache();
};

#endif // CLICKER_SPRITES_H
