#include "Game.h"

#include <SFML/Graphics.hpp>

int main()
{
    Game::Init();
    Game::SetFrameRate(144);
    Game::Update();
}
