//
// Created by XL1TTE on 30.11.2025.
//

#ifndef CLICKER_G_H
#define CLICKER_G_H
#include "Data/GameSession.h"

#include <cstdint>

class G
{
  private:
    static GameSession m_GameSession;

  public:
    static void         NewSession();
    static GameSession &GetSession();
};

#endif // CLICKER_G_H
