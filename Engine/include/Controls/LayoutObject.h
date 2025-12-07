//
// Created by XL1TTE on 07.12.2025.
//

#ifndef XLENGINE_LAYOUTOBJECT_H
#define XLENGINE_LAYOUTOBJECT_H
#include "Behaviour/GameObject.h"
#include "SFML/Graphics/Transformable.hpp"

namespace xl
{

template <typename T>
class LayoutObject : public GameObject
{
  public:
    explicit LayoutObject(std::unique_ptr<T> &&mesh);
    ~LayoutObject() override = default;

  protected:
    std::unique_ptr<T> m_Mesh;

    void PivotToCenter() const;

  public:
    void AlignCenter() const;
    void VerticalBottom() const;
    void VerticalTop() const;
    void HorizontalLeft() const;
    void HorizontalRight() const;
    void HorizontalCenter() const;
    void VerticalCenter() const;
};

} // namespace xl

#endif // XLENGINE_LAYOUTOBJECT_H
