//
// Created by XL1TTE on 30.11.2025.
//

#include "G.h"
#include <algorithm>
#include <iostream>

GameSession G::m_GameSession = GameSession();

void G::NewSession()
{
    m_GameSession = GameSession();
}
GameSession &G::GetSession()
{
    return m_GameSession;
}