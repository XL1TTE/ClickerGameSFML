//
// Created by XL1TTE on 07.12.2025.
//

#ifndef XLENGINE_LAYOUTOBJECT_H
#define XLENGINE_LAYOUTOBJECT_H
#include "Behaviour/GameObject.h"
#include "Layout.h"

namespace xl
{

template <typename T>
class LayoutObject : public GameObject
{
  public:
    explicit LayoutObject(std::unique_ptr<T> &&mesh);
    ~LayoutObject() override = default;

  protected:
    std::unique_ptr<T>  m_Mesh;
    std::vector<Layout> m_Styles;

    virtual void ApplyAllStyles() const;

    void PivotToCenter() const;
    void AlignCenter() const;
    void VerticalBottom() const;
    void VerticalTop() const;
    void HorizontalLeft() const;
    void HorizontalRight() const;
    void HorizontalCenter() const;
    void VerticalCenter() const;

  public:
    void DefineLayout(std::vector<Layout> &&styles);
    void Draw(const std::weak_ptr<sf::RenderTarget> &) override;
};

} // namespace xl

#endif // XLENGINE_LAYOUTOBJECT_H
