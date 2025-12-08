//
// Created by XL1TTE on 07.12.2025.
//

#ifndef XLENGINE_LAYOUTOBJECT_H
#define XLENGINE_LAYOUTOBJECT_H
#include "Behaviour/GameObject.h"
#include "Layout.h"
#include "SFML/System/Vector2.hpp"

namespace xl
{

struct Margin
{
    float top, bottom, left, right;

    Margin(const float all) // NOLINT(*-explicit-constructor)
        : top(all), bottom(all), left(all), right(all)
    {
    }

    Margin(const float vertical, const float horizontal)
        : top(vertical), right(horizontal), bottom(vertical), left(horizontal)
    {
    }

    Margin(const float t, const float b, const float l, const float r)
        : top(t), bottom(b), left(l), right(r)
    {
    }
};

template <typename T>
class LayoutObject : public GameObject
{
  public:
    explicit LayoutObject(const T &mesh);
    ~LayoutObject() override = default;

  protected:
    std::unique_ptr<T>  m_Mesh;
    std::vector<Layout> m_Layouts;
    Margin              m_margin;

    virtual void ApplyAllStyles() const;

    [[nodiscard]] sf::Vector2f AddMargin(const sf::Vector2f &size) const;

    void PivotToCenter() const;
    void AlignCenter() const;
    void VerticalBottom() const;
    void VerticalTop() const;
    void HorizontalLeft() const;
    void HorizontalRight() const;
    void HorizontalCenter() const;
    void VerticalCenter() const;

  public:
    void Margin(const Margin &margin);
    void DefineLayout(std::vector<Layout> &&styles);
    void Draw(const std::weak_ptr<sf::RenderTarget> &) override;
};

} // namespace xl

#endif // XLENGINE_LAYOUTOBJECT_H
