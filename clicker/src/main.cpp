#include "Behaviour/GameObject.h"
#include "G.h"
#include "GUI/Scenes/MainScene.h"
#include "Game.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SignalBus/SignalBus.h"
#include "SignalBus/Signals/Signals.h"

int main()
{
    Game::New();
    Game::SetFrameRate(144);

    const auto window = Game::GetWindow().lock();

    const auto mainScene = std::make_shared<MainScene>(window);

    Game::SetScene(std::weak_ptr(mainScene));

    const auto onKeyPressed = [&window, &mainScene](const sf::Event::KeyPressed &keyPressed)
    {
        if (keyPressed.scancode == sf::Keyboard::Scancode::Space)
        {
            G::AddGold(1);
            Game::GetBus().publish(GoldChangedSignal(G::GetGold()));
        }
    };
    const auto onExit = [&window](const sf::Event::Closed &exit)
    {
        Game::Exit();
    };

    while (Game::IsExist())
    {
        Game::Update();

        Game::UpdateScreen();

        window->handleEvents(onKeyPressed, onExit);
    }
}
