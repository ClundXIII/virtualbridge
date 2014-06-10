#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include "../headers.h"

class Game
{
    public:

    Game();
    Game(int pPNS, int pPOW, int pErgNS, int pErgOW);
    ~Game();

    void setGame(int *pPNS, int *pPOW, int *pErgNS, int *pErgOW);
    void getGame(int *pPNS, int *pPOW, int *pErgNS, int *pErgOW);

    protected:
    private:

    int PNS;
    int POW;
    int ErgNS;
    int ErgOW;
};

#endif /* GAME_h_INCLUDED */
