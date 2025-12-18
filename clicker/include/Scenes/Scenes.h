//
// Created by XL1TTE on 30.11.2025.
//

#ifndef CLICKER_SCENES_H
#define CLICKER_SCENES_H
#include <memory>
namespace xl
{
class IGameScene;

}
namespace sf
{
class RenderTarget;
}

enum SceneName
{
    MAIN_SCENE,
    SHOP_SCENE
};

class Scenes
{
  public:
    static std::unique_ptr<xl::IGameScene> CreateMainScene(const std::weak_ptr<sf::RenderTarget> &renderer);
    static std::unique_ptr<xl::IGameScene> CreateShopScene(const std::weak_ptr<sf::RenderTarget> &renderer);
    static void                            SwitchScene(const std::weak_ptr<sf::RenderTarget> &renderer, const SceneName &sceneName);
};

#define MAIN_SCENE_INSTANTIATE Scenes::GetMainScene()

#endif // CLICKER_SCENES_H
