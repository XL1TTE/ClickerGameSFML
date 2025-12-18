

#include "Resources.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include "Scenes/Scenes.h"
#include "Signals/Signals.h"

#include <XL_ENGINE_H>

using namespace xl;

int main()
{
    xlEngine::Get();
    xlEngine::SetFrameRate(144);

    const auto window = xlEngine::GetWindow().lock();

    xlEngine::SetScene(Scenes::CreateMainScene(window));

    xlEngine::GetBus().subscribe<SceneSwitchRequest>(
        [window](const SceneSwitchRequest &signal)
        {
            Scenes::SwitchScene(window, signal.m_scene);
        });

    while (xlEngine::IsExited() == false)
    {
        xlEngine::Update();

        xlEngine::UpdateScreen();
    }
}
