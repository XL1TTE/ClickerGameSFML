//
// Created by XL1TTE on 07.12.2025.
//

#ifndef XLENGINE_MOUSEEVENTSSYSTEM_H
#define XLENGINE_MOUSEEVENTSSYSTEM_H

#include "SFML/Window/Event.hpp"

#include <memory>

namespace sf
{
class WindowBase;
}

namespace xl
{

class IPointerEnterHandler;
class BoxCollider2D;
class xlEngine;
class IGameScene;

class MouseEventsSystem final
{
    friend class xlEngine;

  protected:
    static std::weak_ptr<IPointerEnterHandler> m_underCursor;

    static void ProcessPointerEvents(const sf::WindowBase &window, const IGameScene &scene);
    static void ProcessClickEvent(const sf::Event::MouseButtonPressed &, const sf::WindowBase &window, const IGameScene &scene);
};
} // namespace xl
#endif // CLICKER_MOUSEEVENTSSYSTEM_H
