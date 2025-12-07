

#include "../../Engine/include/xlEngine.h"
#include "G.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include "Scenes/Scenes.h"
#include "Signals/Signals.h"

#include <XL_ENGINE_H>

using namespace xl;

int main()
{
    xlEngine::New();
    xlEngine::SetFrameRate(144);

    const auto window = xlEngine::GetWindow().lock();

    Scenes::LoadScenes(window);

    xlEngine::SetScene(Scenes::CreateMainScene(window));

    const auto onKeyPressed = [&](const sf::Event::KeyPressed &keyPressed)
    {
        if (keyPressed.scancode == sf::Keyboard::Scancode::Space)
        {
            G::AddGold(1);
            xlEngine::GetBus().emit(GoldChangedSignal(G::GetGold()));
        }
    };
    const auto onExit = [](const sf::Event::Closed &exit)
    {
        xlEngine::Exit();
    };

    while (xlEngine::IsExist())
    {
        xlEngine::Update();

        xlEngine::UpdateScreen();

        window->handleEvents(onKeyPressed, onExit);
    }
}
