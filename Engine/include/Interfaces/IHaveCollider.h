//
// Created by XL1TTE on 07.12.2025.
//

#ifndef XLENGINE_IHAVECOLLIDER_H
#define XLENGINE_IHAVECOLLIDER_H
#include "Components/BoxCollider2D.h"

namespace sf
{
template <typename T>
class Vector2;

}
namespace xl
{

class IHaveCollider
{
  public:
    IHaveCollider()                                                             = default;
    virtual ~IHaveCollider()                                                    = default;
    [[nodiscard]] virtual sf::Vector2<float> GetSize() const                    = 0;
    virtual bool                             Contains(sf::Vector2<float> point) = 0;
};
} // namespace xl

#endif // XLENGINE_IHAVECOLLIDER_H
