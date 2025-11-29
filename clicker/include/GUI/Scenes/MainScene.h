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
    MainScene();

  protected:
    uint32_t                  m_gold = 0;
    std::shared_ptr<sf::Text> m_goldText;

  protected:
    void Render(const std::weak_ptr<sf::RenderWindow> &) override;

  public:
    void AddGold(const uint32_t amount);
};

#endif // CLICKER_MAINSCENE_H
