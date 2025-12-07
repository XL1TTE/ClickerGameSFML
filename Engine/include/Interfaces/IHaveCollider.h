//
// Created by XL1TTE on 07.12.2025.
//

#ifndef CLICKER_IHAVECOLLIDER_H
#define CLICKER_IHAVECOLLIDER_H
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
    virtual ~IHaveCollider()                                      = default;
    virtual sf::Vector2<float> GetSize()                          = 0;
    virtual bool               Contains(sf::Vector2<float> point) = 0;
};
} // namespace xl

#endif // CLICKER_IHAVECOLLIDER_H
