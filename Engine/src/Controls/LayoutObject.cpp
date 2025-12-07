//
// Created by XL1TTE on 07.12.2025.
//

#include "../../include/Controls/LayoutObject.h"

#include "SFML/Graphics/Shape.hpp"
#include "SFML/Graphics/Text.hpp"

#include <memory>

namespace xl
{
template <typename T>
LayoutObject<T>::LayoutObject(std::unique_ptr<T> &&mesh)
    : m_Mesh(std::move(mesh))
{
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
        auto [x, y] = parent->GetPosition();
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
        auto [parentW, parentH] = parent->GetSize();

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
        auto [parentW, parentH] = parent->GetSize();

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
        auto [w, h]             = parent->GetSize();

        m_Mesh->setPosition(
            {parentX + w / 2, y});
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
        auto [w, h]             = parent->GetSize();

        m_Mesh->setPosition(
            {parentX - w / 2, y});
    }
}
template <typename T>
void LayoutObject<T>::HorizontalCenter() const
{
    PivotToCenter();
    if (const auto parent = m_parent.lock())
    {
        auto [x, y]             = GetPosition();
        auto [parentX, parentY] = parent->GetPosition();
        auto [w, h]             = parent->GetSize();

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
        auto [parentX, parentY] = parent->GetPosition();
        auto [w, h]             = parent->GetSize();

        m_Mesh->setPosition(
            {x, parentY});
    }
}

template class LayoutObject<sf::Shape>;
template class LayoutObject<sf::Text>;

} // namespace xl