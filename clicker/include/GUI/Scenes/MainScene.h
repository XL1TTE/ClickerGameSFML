//
// Created by XL1TTE on 29.11.2025.
//

#ifndef CLICKER_MAINSCENE_H
#define CLICKER_MAINSCENE_H
#include "IGameScene.h"

class MainScene final : public IGameScene
{
    explicit MainScene(sf::RenderWindow &) noexcept;

    void Render() override
    {
    }
};

#endif // CLICKER_MAINSCENE_H
