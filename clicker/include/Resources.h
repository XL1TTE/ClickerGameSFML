//
// Created by XL1TTE on 11.12.2025.
//

#ifndef CLICKER_RESOURCES_H
#define CLICKER_RESOURCES_H

#include "GUI/Sprites/Sprites.h"
#include "SFML/Graphics/Sprite.hpp"

#include <memory>
#include <string>

constexpr std::string_view MONSTER_TEXTURE_PATH = RESOURCES_PATH "sprites/cyclop.png";

inline std::shared_ptr<sf::Sprite> SPR_MONSTER()
{
    static auto sprite = SpriteManager::CreateSprite(
        {0, 0},
        {100, 100},
        std::string(MONSTER_TEXTURE_PATH));
    return sprite;
}
#endif // CLICKER_RESOURCES_H
