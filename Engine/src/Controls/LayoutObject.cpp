//
// Created by XL1TTE on 07.12.2025.
//

#include "Controls/LayoutObject.h"

#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Text.hpp"

#include <memory>

namespace xl
{
template <typename T>
LayoutObject<T>::LayoutObject(const T &mesh)
    : m_Mesh(std::make_unique<T>(mesh)), m_margin(0)
{
}

template <typename T>
void LayoutObject<T>::ApplyAllStyles() const
{
    // Applying layouts  -->
    for (const auto &style : m_Layouts)
    {
        switch (style)
        {
        case Layout::HorizontalCenter:
            HorizontalCenter();
            break;
        case Layout::HorizontalLeft:
            HorizontalLeft();
            break;
        case Layout::HorizontalRight:
            HorizontalRight();
            break;
        case Layout::VerticalTop:
            VerticalTop();
            break;
        case Layout::VerticalBottom:
            VerticalBottom();
            break;
        case Layout::VerticalCenter:
            VerticalCenter();
            break;
        }
    }
    // <-- Applying layouts
}
template <typename T>
sf::Vector2f LayoutObject<T>::AddMargin(const sf::Vector2f &size) const
{
    auto [x, y]       = size;
    auto [t, b, l, r] = m_margin;
    return {x - r - l, y - t - b};
}
template <typename T>
void LayoutObject<T>::PivotToCenter() const
{
    const auto textBounds = m_Mesh->getLocalBounds();
    m_Mesh->setOrigin({textBounds.position.x + textBounds.size.x / 2.0f,
                       textBounds.position.y + textBounds.size.y / 2.0f});
}
template <typename T>
void LayoutObject<T>::AlignCenter() const
{
    PivotToCenter();
    if (const auto parent = m_parent.lock())
    {
        auto [x, y] = AddMargin(GetPosition());
        m_Mesh->setPosition({x, y});
    }
}
template <typename T>
void LayoutObject<T>::VerticalBottom() const
{
    PivotToCenter();
    if (const auto parent = m_parent.lock())
    {
        auto [x, y]             = GetPosition();
        auto [w, h]             = GetSize();
        auto [parentX, parentY] = parent->GetPosition();
        auto [parentW, parentH] = AddMargin(parent->GetSize());

        m_Mesh->setPosition(
            {x, parentY + (parentH / 2) - (h / 2)});
    }
}
template <typename T>
void LayoutObject<T>::VerticalTop() const
{
    PivotToCenter();
    if (const auto parent = m_parent.lock())
    {
        auto [x, y]             = GetPosition();
        auto [w, h]             = GetSize();
        auto [parentX, parentY] = parent->GetPosition();
        auto [parentW, parentH] = AddMargin(parent->GetSize());

        m_Mesh->setPosition(
            {x, parentY - (parentH / 2) + h / 2});
    }
}
template <typename T>
void LayoutObject<T>::HorizontalLeft() const
{
    PivotToCenter();
    if (const auto parent = m_parent.lock())
    {
        auto [x, y]             = GetPosition();
        auto [parentX, parentY] = parent->GetPosition();
        auto [parentW, parentH] = AddMargin(parent->GetSize());
        auto [w, h]             = GetSize();

        m_Mesh->setPosition(
            {parentX - (parentW / 2) + w / 2, y});
    }
}
template <typename T>
void LayoutObject<T>::HorizontalRight() const
{
    PivotToCenter();
    if (const auto parent = m_parent.lock())
    {
        auto [x, y]             = GetPosition();
        auto [parentX, parentY] = parent->GetPosition();
        auto [parentW, parentH] = AddMargin(parent->GetSize());
        auto [w, h]             = GetSize();

        m_Mesh->setPosition(
            {parentX + (parentW / 2) - w / 2, y});
    }
}
template <typename T>
void LayoutObject<T>::HorizontalCenter() const
{
    PivotToCenter();
    if (const auto parent = m_parent.lock())
    {
        auto [x, y]             = GetPosition();
        auto [parentX, parentY] = AddMargin(parent->GetPosition());
        m_Mesh->setPosition(
            {parentX, y});
    }
}
template <typename T>
void LayoutObject<T>::VerticalCenter() const
{
    PivotToCenter();
    if (const auto parent = m_parent.lock())
    {
        auto [x, y]             = GetPosition();
        auto [parentX, parentY] = AddMargin(parent->GetPosition());

        m_Mesh->setPosition(
            {x, parentY});
    }
}
template <typename T>
sf::Vector2<float> LayoutObject<T>::GetPosition() const
{
    return m_Mesh->getPosition();
}
template <typename T>
void LayoutObject<T>::Margin(const xl::Margin &margin)
{
    m_margin = margin;
}
template <typename T>
void LayoutObject<T>::DefineLayout(std::vector<Layout> &&styles)
{
    m_Layouts = std::move(styles);
}
template <typename T>
void LayoutObject<T>::Draw(const std::weak_ptr<sf::RenderTarget> &weak_ptr)
{
    weak_ptr.lock()->draw(*m_Mesh);
}
template <typename T>
sf::Vector2<float> LayoutObject<T>::GetSize() const
{
    return m_Mesh->getGlobalBounds().size;
}

template class LayoutObject<sf::RectangleShape>;
template class LayoutObject<sf::Sprite>;
template class LayoutObject<sf::Text>;

} // namespace xl