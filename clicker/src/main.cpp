

#include "G.h"
#include "Game.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include "Scenes/Scenes.h"
#include "Signals/Signals.h"

#include <xlEngine>

int main()
{
    Game::New();
    Game::SetFrameRate(144);

    const auto window = Game::GetWindow().lock();

    Scenes::LoadScenes(window);

    Game::SetScene(Scenes::CreateMainScene(window));

    const auto onKeyPressed = [&](const sf::Event::KeyPressed &keyPressed)
    {
        if (keyPressed.scancode == sf::Keyboard::Scancode::Space)
        {
            G::AddGold(1);
            Game::GetBus().emit(GoldChangedSignal(G::GetGold()));
        }
    };
    const auto onExit = [](const sf::Event::Closed &exit)
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
