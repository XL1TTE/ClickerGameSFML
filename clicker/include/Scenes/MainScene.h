//
// Created by XL1TTE on 29.11.2025.
//

#ifndef CLICKER_MAINSCENE_H
#define CLICKER_MAINSCENE_H
#include "Data/GameSession.h"
#include "Scenes/IGameScene.h"

namespace sf
{
class Text;
} // namespace sf

class MainScene final : public xl::IGameScene
{

  public:
    explicit MainScene(const std::weak_ptr<sf::RenderTarget> &);

    void                                      OnAwake() override;
    void                                      OnUpdate(float dt) override;
    [[nodiscard]] std::unique_ptr<IGameScene> clone() const override;

    float                               m_timer;
    std::shared_ptr<GameSession::IStat> m_gold_per_second;
};

#endif // CLICKER_MAINSCENE_H
