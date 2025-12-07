//
// Created by XL1TTE on 07.12.2025.
//

#ifndef XLENGINE_IPOINTERCLICKHANDLER_H
#define XLENGINE_IPOINTERCLICKHANDLER_H
#include "Interfaces/IHaveCollider.h"
#include "SFML/Window/Event.hpp"

struct PointerClickEvent
{
};

namespace xl
{
class IPointerClickHandler : public IHaveCollider
{
  public:
    IPointerClickHandler()                                                  = default;
    ~IPointerClickHandler() override                                        = default;
    virtual void OnPointerClick(const sf::Event::MouseButtonPressed &event) = 0;
};

} // namespace xl

#endif // XLENGINE_IPOINTERCLICKHANDLER_H
