#include "../headers.h"
#include "game.h"

Game::Game(int pPNS, int pPOW, int pErgNS, int pErgOW)
{
    PNS   = pPNS;
    POW   = pPOW;
    ErgNS = pErgNS;
    ErgOW = pErgOW;
}

Game::Game()
{
    PNS   = 0;
    POW   = 0;
    ErgNS = 0;
    ErgOW = 0;
}

Game::~Game()
{
    std::cout << "Spiel gelöscht!" << std::endl;
}

void Game::setGame(int *pPNS, int *pPOW, int *pErgNS, int *pErgOW)
{
    if (pPNS)   PNS   = *pPNS;
    if (pPOW)   POW   = *pPOW;
    if (pErgNS) ErgNS = *pErgNS;
    if (pErgOW) ErgOW = *pErgOW;
}

void Game::getGame(int *pPNS, int *pPOW, int *pErgNS, int *pErgOW)
{
    if (pPNS)   *pPNS   = PNS;
    if (pPOW)   *pPOW   = POW;
    if (pErgNS) *pErgNS = ErgNS;
    if (pErgOW) *pErgOW = ErgOW;
}
