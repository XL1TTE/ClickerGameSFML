//
// Created by XL1TTE on 11.12.2025.
//

#ifndef CLICKER_SCENESWITHBUTTON_H
#define CLICKER_SCENESWITHBUTTON_H
#include "Controls/LayoutObject.h"
#include "EventSystems/Events/IPointerClickHandler.h"
#include "EventSystems/Events/IPointerEnterHandler.h"
#include "Scenes/Scenes.h"

namespace sf
{
class Sprite;
}
class SceneSwitchButton final : public xl::LayoutObject<sf::Sprite>,
                                public xl::IPointerEnterHandler,
                                public xl::IPointerClickHandler
{
  public:
    explicit SceneSwitchButton(const sf::Sprite &mesh, const SceneName &sceneName);
    [[nodiscard]] sf::Vector2<float> GetSize() const override;
    bool                             Contains(sf::Vector2<float> point) override;
    void                             OnPointerClick(const sf::Event::MouseButtonPressed &event) override;
    void                             OnPointerEnter(PointerEnterEvent event) override;

    void Draw(const std::weak_ptr<sf::RenderTarget> &) override;

  private:
    SceneName m_Scene;
};

#endif // CLICKER_SCENESWITHBUTTON_H
