

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

    while (xlEngine::IsExist())
    {
        xlEngine::Update();

        xlEngine::UpdateScreen();
    }
}
