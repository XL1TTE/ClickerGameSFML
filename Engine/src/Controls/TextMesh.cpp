//
// Created by XL1TTE on 29.11.2025.
//

#include "Controls/TextMesh.h"

#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/Graphics/Text.hpp"

#include <iostream>

using namespace xl;

TextMesh::TextMesh(const sf::Font &font)
    : LayoutObject(std::make_unique<sf::Text>(font))
{
}
void TextMesh::Draw(const std::weak_ptr<sf::RenderTarget> &drawer)
{
    GameObject::Draw(drawer);

    drawer.lock()->draw(*m_Mesh);
}
TextMesh &TextMesh::SetText(const std::string &text)
{
    m_Mesh->setString(text);
    return *this;
}
TextMesh &TextMesh::SetColor(const sf::Color color)
{
    m_Mesh->setFillColor(color);
    return *this;
}
TextMesh &TextMesh::SetFontSize(const unsigned int size)
{
    m_Mesh->setCharacterSize(size);
    return *this;
}
TextMesh &TextMesh::AlignCenter()
{
    if (m_parent.expired())
    {
        return *this;
    }

    const auto textBounds = m_Mesh->getLocalBounds();
    m_Mesh->setOrigin({textBounds.position.x + textBounds.size.x / 2.0f,
                       textBounds.position.y + textBounds.size.y / 2.0f});

    const auto [parentX, parentY] = m_parent.lock()->GetPosition();
    // const auto [parentW, parentH] = m_parent.lock()->GetSize();
    m_Mesh->setPosition({parentX, parentY});
    return *this;
}
sf::Vector2<float> TextMesh::GetSize() const
{
    return m_Mesh->getGlobalBounds().size;
}

sf::Vector2<float> TextMesh::GetPosition() const
{
    return m_Mesh->getPosition();
}
sf::Transform TextMesh::GetTransform() const
{
    return m_Mesh->getTransform();
}

void TextMesh::Destroy()
{
    GameObject::Destroy();
}