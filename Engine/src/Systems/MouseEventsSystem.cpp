//
// Created by XL1TTE on 07.12.2025.
//

#include "EventSystems/MouseEventsSystem.h"
#include "EventSystems/Events/IPointerEnterHandler.h"
#include "EventSystems/Events/IPointerExitHandler.h"
#include "SFML/Window/Mouse.hpp"
#include "Scenes/IGameScene.h"

std::weak_ptr<xl::IPointerEnterHandler> xl::MouseEventsSystem::m_underCursor;

void xl::MouseEventsSystem::ProcessEvents(const sf::WindowBase &window, const IGameScene &scene)
{
    const auto mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));

    const auto objects = scene.GetAllObjectsByType<IPointerEnterHandler>();

    std::shared_ptr<IPointerEnterHandler> t_underCursor = nullptr;

    for (const auto &object_weak : objects)
    {
        if (const auto object_locked = object_weak.lock())
        {
            if (object_locked->Contains(mousePos))
            {
                t_underCursor = object_locked;
                break;
            }
        }
    }

    std::shared_ptr<IPointerEnterHandler> t_lastUnderCursor = m_underCursor.lock();

    if (t_lastUnderCursor && t_lastUnderCursor != t_underCursor)
    {
        std::shared_ptr<IPointerExitHandler> t_lastUnderCursor_casted = std::dynamic_pointer_cast<IPointerExitHandler>(t_lastUnderCursor);
        if (t_lastUnderCursor_casted != nullptr)
        {
            t_lastUnderCursor_casted->OnPointerExit(PointerExitEvent());
        }
    }

    if (t_underCursor && t_underCursor != t_lastUnderCursor)
    {
        t_underCursor->OnPointerEnter(PointerEnterEvent());
    }

    m_underCursor = t_underCursor;
}