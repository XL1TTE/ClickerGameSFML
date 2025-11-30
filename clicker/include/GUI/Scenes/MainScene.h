//
// Created by XL1TTE on 29.11.2025.
//

#ifndef CLICKER_MAINSCENE_H
#define CLICKER_MAINSCENE_H
#include "IGameScene.h"

namespace sf
{
class Text;
} // namespace sf

class MainScene final : public IGameScene
{

  public:
    explicit MainScene(const std::weak_ptr<sf::RenderTarget> &);

    std::unique_ptr<IGameScene> clone() const override;
};

#endif // CLICKER_MAINSCENE_H
