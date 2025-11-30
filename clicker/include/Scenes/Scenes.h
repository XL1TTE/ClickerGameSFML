//
// Created by XL1TTE on 30.11.2025.
//

#ifndef CLICKER_SCENES_H
#define CLICKER_SCENES_H
#include "GUI/Scenes/IGameScene.h"
#include <memory>

class IGameScene;
namespace sf
{
class RenderTarget;
}
class Scenes
{
  public:
    static void LoadScenes(const std::weak_ptr<sf::RenderTarget> &);

  public:
    static std::unique_ptr<IGameScene> GetMainScene();
    static std::unique_ptr<IGameScene> CreateMainScene(const std::weak_ptr<sf::RenderTarget> &renderer);
};

#define MAIN_SCENE_INSTANTIATE Scenes::GetMainScene()

#endif // CLICKER_SCENES_H
