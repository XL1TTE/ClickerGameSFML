//
// Created by XL1TTE on 07.12.2025.
//

#include "Controls/RectangleButton.h"

#include "Controls/TextMesh.h"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/Graphics/Shape.hpp"
#include "SFML/Graphics/Text.hpp"
#include "SFML/System/Vector2.hpp"

using namespace xl;

RectangleButton::RectangleButton(const sf::RectangleShape &mesh)
    : LayoutObject(mesh)
{
    m_Mesh->setFillColor(sf::Color::Blue);
}
RectangleButton::~RectangleButton() = default;

void RectangleButton::SetLabel(const std::string &&label, const sf::Font &font)
{
    m_label = std::make_unique<xl::TextMesh>(font);
    m_label->SetText(label);

    m_label->SetParent(shared_from_this());

    m_label->DefineLayout({
        Layout::HorizontalCenter,
        Layout::VerticalCenter,
    });
}
void RectangleButton::ChangeText(const std::string &text) const
{
    if (m_label != nullptr)
    {
        m_label->SetText(text);
    }
}
void RectangleButton::SetColor(const sf::Color &color) const
{
    m_Mesh->setFillColor(color);
}

sf::Vector2<float> RectangleButton::GetPosition() const
{
    return m_Mesh->getPosition();
}
sf::Vector2<float> RectangleButton::GetSize() const
{
    return m_Mesh->getLocalBounds().size;
}

void RectangleButton::Draw(const std::weak_ptr<sf::RenderTarget> &weak_ptr)
{
    ApplyAllStyles();
    if (const auto renderer = weak_ptr.lock())
    {
        renderer->draw(*m_Mesh);
        if (m_label != nullptr)
        {
            m_label->Draw(weak_ptr);
        }
    }
}