//
// Created by XL1TTE on 07.12.2025.
//

#ifndef CLICKER_IPOINTEREXITHANDLER_H
#define CLICKER_IPOINTEREXITHANDLER_H
#include "Interfaces/IHaveCollider.h"

struct PointerExitEvent
{
};

namespace xl
{
class IPointerExitHandler : public IHaveCollider
{
  public:
    ~IPointerExitHandler() override                    = default;
    virtual void OnPointerExit(PointerExitEvent event) = 0;
};
} // namespace xl

#endif // CLICKER_IPOINTEREXITHANDLER_H
