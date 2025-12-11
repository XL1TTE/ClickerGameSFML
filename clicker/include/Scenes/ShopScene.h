//
// Created by XL1TTE on 11.12.2025.
//

#ifndef CLICKER_SHOPSCENE_H
#define CLICKER_SHOPSCENE_H
#include "Scenes/IGameScene.h"

class ShopScene final : public xl::IGameScene
{
  public:
    explicit ShopScene(const std::weak_ptr<sf::RenderTarget> &renderer);
    [[nodiscard]] std::unique_ptr<IGameScene> clone() const override;
};

#endif // CLICKER_SHOPSCENE_H
