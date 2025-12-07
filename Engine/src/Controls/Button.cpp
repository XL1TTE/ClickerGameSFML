//
// Created by XL1TTE on 07.12.2025.
//

#include "Controls/Button.h"

#include "Controls/TextMesh.h"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/Graphics/Text.hpp"
#include "SFML/System/Vector2.hpp"

using namespace xl;

Button::Button(std::unique_ptr<sf::Shape> &&mesh)
    : LayoutObject(std::move(mesh))
{
    m_Mesh->setFillColor(sf::Color::Blue);
}
Button::~Button() = default;

void Button::SetLabel(std::unique_ptr<TextMesh> &label)
{
    m_label = std::move(label);
}
void Button::SetLabel(const std::shared_ptr<Button> &shared_this, const std::string &&label, const sf::Font &font)
{
    m_label = std::make_unique<xl::TextMesh>(font);
    m_label->SetText(label);

    m_label->SetParent(shared_this);

    m_label->HorizontalCenter();
    m_label->VerticalCenter();
}
void Button::ChangeText(const std::string &text) const
{
    if (m_label != nullptr)
    {
        m_label->SetText(text);
    }
}
void Button::SetColor(const sf::Color &color) const
{
    m_Mesh->setFillColor(color);
}

sf::Vector2<float> Button::GetPosition() const
{
    return m_Mesh->getPosition();
}
sf::Vector2<float> Button::GetSize() const
{
    return m_Mesh->getLocalBounds().size;
}

void Button::Draw(const std::weak_ptr<sf::RenderTarget> &weak_ptr)
{
    if (const auto renderer = weak_ptr.lock())
    {
        renderer->draw(*m_Mesh);
        if (m_label != nullptr)
        {
            m_label->Draw(weak_ptr);
        }
    }
}