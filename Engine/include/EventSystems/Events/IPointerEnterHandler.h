//
// Created by XL1TTE on 07.12.2025.
//

#ifndef XLENGINE_IPOINTERENTERHANDLER_H
#define XLENGINE_IPOINTERENTERHANDLER_H
#include "Interfaces/IHaveCollider.h"

struct PointerEnterEvent
{
};

namespace xl
{
class IPointerEnterHandler : public IHaveCollider
{
  public:
    IPointerEnterHandler()                               = default;
    ~IPointerEnterHandler() override                     = default;
    virtual void OnPointerEnter(PointerEnterEvent event) = 0;
};

} // namespace xl

#endif // XLENGINE_IPOINTERENTERHANDLER_H
