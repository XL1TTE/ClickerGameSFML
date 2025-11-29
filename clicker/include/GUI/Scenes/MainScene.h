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

  protected:
    uint32_t                     m_gold = 999999999;
    std::shared_ptr<std::string> m_goldText;

  public:
    void AddGold(const uint32_t amount);
};

#endif // CLICKER_MAINSCENE_H
