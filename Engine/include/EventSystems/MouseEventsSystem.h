//
// Created by XL1TTE on 07.12.2025.
//

#ifndef CLICKER_MOUSEEVENTSSYSTEM_H
#define CLICKER_MOUSEEVENTSSYSTEM_H
#include <memory>
namespace xl
{
class IPointerEnterHandler;
}
namespace sf
{
class WindowBase;
}
namespace xl
{
class BoxCollider2D;
class xlEngine;
class IGameScene;

class MouseEventsSystem final
{
    friend class xlEngine;

  protected:
    static std::weak_ptr<IPointerEnterHandler> m_underCursor;

    static void ProcessEvents(const sf::WindowBase &window, const IGameScene &scene);
};
} // namespace xl
#endif // CLICKER_MOUSEEVENTSSYSTEM_H
