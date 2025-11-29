#include "GUI/Scenes/MainScene.h"
#include "Game.h"
#include "SFML/Graphics/RenderWindow.hpp"

int main()
{
    Game::Start();
    Game::SetFrameRate(144);

    const auto mainScene = std::make_shared<MainScene>();

    Game::SetScene(std::weak_ptr(mainScene));

    const auto window = Game::GetWindow().lock();

    const auto onKeyPressed = [&window, &mainScene](const sf::Event::KeyPressed &keyPressed)
    {
        if (keyPressed.scancode == sf::Keyboard::Scancode::Space)
        {
            mainScene->AddGold(1);
        }
    };
    const auto onExit = [&window](const sf::Event::Closed &exit)
    {
        Game::Exit();
    };

    while (Game::Update())
    {
        window->handleEvents(onKeyPressed, onExit);
    }
}
