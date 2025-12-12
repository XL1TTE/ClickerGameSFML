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

constexpr std::string_view UPGRADE_TEXTURE_POINTS_PER_CLICK = RESOURCES_PATH "sprites/up_gold_per_click.png";

constexpr std::string_view MAIN_SCENE_TEXTURE = RESOURCES_PATH "sprites/main_scene.png";
constexpr std::string_view SHOP_SCENE_TEXTURE = RESOURCES_PATH "sprites/shop_scene.png";

constexpr std::string_view SHOP_BUY_TEXTURE = RESOURCES_PATH "sprites/shop_buy.png";

inline std::shared_ptr<sf::Sprite> SPR_MONSTER()
{
    static auto sprite = SpriteManager::CreateSprite(
        {0, 0},
        {100, 100},
        std::string(MONSTER_TEXTURE_PATH));
    return sprite;
}

inline std::shared_ptr<sf::Sprite> UP_POINTS_PER_CLICK()
{
    static auto sprite = SpriteManager::CreateSprite(
        {0, 0},
        {64, 64},
        std::string(UPGRADE_TEXTURE_POINTS_PER_CLICK));
    return sprite;
}
inline std::shared_ptr<sf::Sprite> SPR_MAIN_SCENE_BUTTON()
{
    static auto sprite = SpriteManager::CreateSprite(
        {0, 0},
        {64, 64},
        std::string(MAIN_SCENE_TEXTURE));
    return sprite;
}
inline std::shared_ptr<sf::Sprite> SPR_TO_SHOP_BUTTON()
{
    static auto sprite = SpriteManager::CreateSprite(
        {0, 0},
        {64, 64},
        std::string(SHOP_SCENE_TEXTURE));
    return sprite;
}
inline std::shared_ptr<sf::Sprite> SPR_BUY_BUTTON()
{
    static auto sprite = SpriteManager::CreateSprite(
        {0, 0},
        {64, 64},
        std::string(SHOP_BUY_TEXTURE));
    return sprite;
}

#endif // CLICKER_RESOURCES_H
