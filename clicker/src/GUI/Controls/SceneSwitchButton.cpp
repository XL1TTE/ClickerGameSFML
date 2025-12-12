//
// Created by XL1TTE on 11.12.2025.
//

#include "GUI/Controls/SceneSwitchButton.h"

#include "SFML/Graphics/RenderTarget.hpp"
#include "Scenes/IGameScene.h"

#include "SFML/Graphics/Sprite.hpp"
#include "Signals/Signals.h"

SceneSwitchButton::SceneSwitchButton(const sf::Sprite &mesh, const SceneName &sceneName)
    : LayoutObject(mesh), m_Scene(sceneName)
{
}
sf::Vector2<float> SceneSwitchButton::GetSize() const
{
    return m_Mesh->getGlobalBounds().size;
}
bool SceneSwitchButton::Contains(sf::Vector2<float> point)
{
    return m_Mesh->getGlobalBounds().contains(point);
}
void SceneSwitchButton::OnPointerClick(const sf::Event::MouseButtonPressed &event)
{
    std::cout << "Click" << std::endl;
    xl::xlEngine::GetBus().emit(SceneSwitchRequest(m_Scene));
}
void SceneSwitchButton::OnPointerEnter(PointerEnterEvent event)
{
}
void SceneSwitchButton::Draw(const std::weak_ptr<sf::RenderTarget> &weak_ptr)
{
    ApplyAllStyles();
    weak_ptr.lock()->draw(*m_Mesh);
}