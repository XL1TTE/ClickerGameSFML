//
// Created by XL1TTE on 29.11.2025.
//

#ifndef CLICKER_MAINSCENE_H
#define CLICKER_MAINSCENE_H
#include "Scenes/IGameScene.h"

namespace sf
{
class Text;
} // namespace sf

class MainScene final : public xl::IGameScene
{

  public:
    explicit MainScene(const std::weak_ptr<sf::RenderTarget> &);

    [[nodiscard]] std::unique_ptr<xl::IGameScene> clone() const override;
};

#endif // CLICKER_MAINSCENE_H
