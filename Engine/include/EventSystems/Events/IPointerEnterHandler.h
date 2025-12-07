//
// Created by XL1TTE on 07.12.2025.
//

#ifndef CLICKER_IPOINTERENTERHANDLER_H
#define CLICKER_IPOINTERENTERHANDLER_H
#include "Interfaces/IHaveCollider.h"

struct PointerEnterEvent
{
};

namespace xl
{
class IPointerEnterHandler : public IHaveCollider
{
  public:
    ~IPointerEnterHandler() override                     = default;
    virtual void OnPointerEnter(PointerEnterEvent event) = 0;
};

} // namespace xl

#endif // CLICKER_IPOINTERENTERHANDLER_H
