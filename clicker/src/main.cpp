

#include "Resources.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include "Scenes/Scenes.h"

#include <XL_ENGINE_H>

using namespace xl;

int main()
{
    xlEngine::New();
    xlEngine::SetFrameRate(144);

    const auto window = xlEngine::GetWindow().lock();

    xlEngine::SetScene(Scenes::CreateMainScene(window));

    while (xlEngine::IsExist())
    {
        xlEngine::Update();

        xlEngine::UpdateScreen();
    }
}
